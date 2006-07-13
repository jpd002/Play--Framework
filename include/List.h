#ifndef _SKIPLIST_H_
#define _SKIPLIST_H_

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include "Types.h"

#define SKIPLIST_THRESHOLD		(0.5f)
#define SKIPLIST_MAXLEVEL		(4)

namespace Framework
{
	template <typename T> class CList
	{
	protected:
		class NODE
		{
		public:
			NODE()
			{
				memset(m_pNext, 0, sizeof(NODE*) * SKIPLIST_MAXLEVEL);
				m_pData = NULL;
				m_nKey = 0;
				m_bTail = false;
			}

			bool IsEqual(uint32 nKey)
			{
				if(m_bTail) return false;
				return (m_nKey == nKey);
			}

			bool IsGreater(uint32 nKey)
			{
				if(m_bTail) return true;
				return (m_nKey >= nKey);
			}

			bool IsTail()
			{
				return m_bTail;
			}

			NODE*	m_pNext[SKIPLIST_MAXLEVEL];
			T*		m_pData;
			uint32	m_nKey;
			bool	m_bTail;
		};

	public:
		class ITERATOR
		{
		public:
			ITERATOR()
			{
				m_pNode = NULL;
			}

			ITERATOR(NODE* pNode)
			{
				m_pNode = pNode;
			}

			ITERATOR& operator ++(int nValue)
			{
				if(m_pNode->m_bTail) return (*this);
				m_pNode = m_pNode->m_pNext[0];
				return (*this);
			}

			ITERATOR& operator =(NODE* pNode)
			{
				m_pNode = pNode;
				return (*this);
			}

			ITERATOR& operator =(ITERATOR& rIter)
			{
				if(&rIter == this) return;
				m_pNode = rIter.m_pNode;
			}

			operator NODE*()
			{
				return m_pNode;
			}

			T* operator *()
			{
				if(m_pNode->m_bTail) return NULL;
				return m_pNode->m_pData;
			}

			bool HasNext()
			{
				return (!m_pNode->m_bTail);
			}

			uint32 GetKey()
			{
				if(m_pNode->m_bTail) return -1;
				return m_pNode->m_nKey;
			}

		private:
			NODE* m_pNode;
		};

		class INDEXOR
		{
		public:
			INDEXOR(CList* pList)
			{
				m_pList = pList;
				Reset();
			}

			void Reset()
			{
				if(m_pList == NULL) return;
				m_nPosition = 0;
				m_Cache = m_pList->Begin();
			}

			uint32 KeyAt(unsigned int nIndex)
			{
				if(m_pList == NULL) return NULL;
				if(nIndex >= m_pList->Count()) return NULL;
				MoveTo(nIndex);
				return m_Cache.GetKey();
			}

			T* GetAt(unsigned int nIndex)
			{
				if(m_pList == NULL) return NULL;
				if(nIndex >= m_pList->Count()) return NULL;
				MoveTo(nIndex);
				return (*m_Cache);
			}

		private:
			void MoveTo(unsigned int nIndex)
			{
				unsigned int i;
				if(m_nPosition > nIndex)
				{
					Reset();
				}
				if(nIndex == m_nPosition) return;
				for(i = m_nPosition; i < nIndex; i++)
				{
					m_Cache++;
				}
				m_nPosition = nIndex;
			}

			CList*				m_pList;
			ITERATOR			m_Cache;
			unsigned int		m_nPosition;
		};

		CList()
		{
			static bool bIsRandomInit = false;
			unsigned int i;

			if(!bIsRandomInit)
			{
				srand((unsigned int)time(NULL));
				bIsRandomInit = true;
			}

			m_Tail.m_bTail = true;
			for(i = 0; i < SKIPLIST_MAXLEVEL; i++)
			{
				m_Head.m_pNext[i] = &m_Tail;
			}

			m_nCount = 0;
		}

		virtual ~CList()
		{
			while(Count() != 0)
			{
				Pull();
			}
		}

		void Insert(T* pData, uint32 nKey = 0)
		{
			int i;
			unsigned int nLevel;
			NODE* pNode;
			NODE* pUpdate[SKIPLIST_MAXLEVEL];

			pNode = &m_Head;
			for(i = (SKIPLIST_MAXLEVEL - 1); i >= 0; i--)
			{
				while(1)
				{
					if(!pNode->m_pNext[i]->IsEqual(nKey))
					{
						if(pNode->m_pNext[i]->IsGreater(nKey)) break;
					}
					pNode = pNode->m_pNext[i];
				}
				pUpdate[i] = pNode;
			}

			nLevel = GenerateRandomLevel();

			pNode = new NODE;
			pNode->m_pData = pData;
			pNode->m_nKey = nKey;

			for(i = 0; (unsigned int)i < nLevel; i++)
			{
				pNode->m_pNext[i] = pUpdate[i]->m_pNext[i];
				pUpdate[i]->m_pNext[i] = pNode;
			}

			m_nCount++;
		}


		T* RemoveAt(NODE* pNode)
		{
			T* pData;
			unsigned int i;
			NODE* pCurrent;

			pData = pNode->m_pData;

			for(i = 0; i < SKIPLIST_MAXLEVEL; i++)
			{
				pCurrent = &m_Head;
				while(!pCurrent->m_pNext[i]->IsTail())
				{
					if(pCurrent->m_pNext[i] == pNode)
					{
						pCurrent->m_pNext[i] = pCurrent->m_pNext[i]->m_pNext[i];
						break;
					}
					pCurrent = pCurrent->m_pNext[i];
				}
			}

			delete pNode;
			m_nCount--;

			return pData;
		}

		T* Remove(uint32 nKey)
		{
			int i;
			NODE* pNode;
			NODE* pUpdate[SKIPLIST_MAXLEVEL];
			T* pData;

			pData = NULL;
			pNode = &m_Head;
			for(i = (SKIPLIST_MAXLEVEL - 1); i >= 0; i--)
			{
				while(1)
				{
					if(pNode->m_pNext[i]->IsGreater(nKey)) break;
					pNode = pNode->m_pNext[i];
				}
				pUpdate[i] = pNode;
			}

			pNode = pNode->m_pNext[0];
			if(pNode->m_nKey == nKey)
			{
				for(i = 0; (unsigned int)i < SKIPLIST_MAXLEVEL; i++)
				{
					if(pUpdate[i]->m_pNext[i] != pNode) break;
					pUpdate[i]->m_pNext[i] = pNode->m_pNext[i];
				}
				pData = pNode->m_pData;
				delete pNode;

				m_nCount--;
			}

			return pData;
		}

		T* Pull()
		{
			if(m_nCount == 0) return NULL;
			return Remove(m_Head.m_pNext[0]->m_nKey);
		}

		bool DoesKeyExist(uint32 nKey)
		{
			return (FindNode(nKey) != NULL);
		}

		T* Find(uint32 nKey)
		{
			NODE* pNode;
			pNode = FindNode(nKey);

			if(pNode == NULL) return NULL;

			return pNode->m_pData;
		}

		NODE* Begin()
		{
			return m_Head.m_pNext[0];
		}

		unsigned int Count()
		{
			return m_nCount;
		}

		uint32 MakeKey()
		{
			uint32 i;
			for(i = 0; i < UINT_MAX; i++)
			{
				if(FindNode(i) == NULL) return i;
			}
			return 0;
		}

	private:
		NODE* FindNode(uint32 nKey)
		{
			int i;
			NODE* pNode;

			pNode = &m_Head;
			for(i = (SKIPLIST_MAXLEVEL - 1); i >= 0; i--)
			{
				while(1)
				{
					if(pNode->m_pNext[i]->IsGreater(nKey)) break;
					pNode = pNode->m_pNext[i];
				}
			}

			pNode = pNode->m_pNext[0];

			if(pNode->m_bTail) return NULL;
			if(pNode->m_nKey == nKey) return pNode;
			return NULL;
		}

		static int GenerateRandomLevel()
		{
			int nLevel;
			double nRand;

			nLevel = 1;
			while(1)
			{
				nRand = (double)rand() / (double)RAND_MAX;
				if(nRand >= SKIPLIST_THRESHOLD) break;
				if(nLevel == SKIPLIST_MAXLEVEL) break;
				nLevel++;
			}

			return nLevel;
		}

		NODE			m_Head;
		NODE			m_Tail;
		unsigned int	m_nCount;
	};
}

#endif
