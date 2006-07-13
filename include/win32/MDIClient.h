#ifndef _MDICLIENT_H_
#define _MDICLIENT_H_

#include "Window.h"

namespace Framework
{

	class CMDIClient : public CWindow
	{
	public:
					CMDIClient(HWND, HMENU);
					~CMDIClient();
		void		Cascade();
		void		TileHorizontal();
		void		TileVertical();
	};

}

#endif