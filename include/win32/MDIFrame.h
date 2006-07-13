#ifndef _MDIFRAME_H_
#define _MDIFRAME_H_

#include "Window.h"
#include "MDIClient.h"

namespace Framework
{

	class CMDIFrame : public CWindow
	{
	public:
						CMDIFrame();
		virtual			~CMDIFrame();
	protected:
		virtual long	OnWndProc(unsigned int, WPARAM, LPARAM);
		void			CreateClient(HMENU);
		CMDIClient*		m_pMDIClient;
	};

}

#endif