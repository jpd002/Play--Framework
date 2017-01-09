#pragma once

#include <memory>
#include "Window.h"
#include "MDIClient.h"

namespace Framework
{
	namespace Win32
	{
		class CMDIFrame : public CWindow
		{
		protected:
			LRESULT    OnWndProc(unsigned int, WPARAM, LPARAM) override;
			void       CreateClient(HMENU);

			std::unique_ptr<CMDIClient> m_pMDIClient;
		};
	}
}
