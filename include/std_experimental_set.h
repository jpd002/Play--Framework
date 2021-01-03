#pragma once

#ifdef _MSC_VER

#include <experimental/set>

#else

namespace std
{
	namespace experimental
	{
		template<class T, class Compare, class Alloc, class Pred>
		void erase_if(std::set<T, Compare, Alloc>& c, Pred pred)
		{
			for(auto i = c.begin(), last = c.end(); i != last; )
			{
				if(pred(*i))
				{
					i = c.erase(i);
				}
				else
				{
					++i;
				}
			}
		}
	}
}

#endif
