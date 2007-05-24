#ifndef _TRAYICONSERVER_H_
#define _TRAYICONSERVER_H_

#include "TrayIcon.h"
#include <boost/ptr_container/ptr_map.hpp>
#include <functional>
#include <boost/signal.hpp>

namespace Framework
{
    namespace Win32
    {
	    class CTrayIconServer : public CWindow
	    {
	    public:
            typedef std::tr1::function<void (CTrayIcon*, LPARAM)> IconEventHandlerType;

							                                    CTrayIconServer();
							                                    ~CTrayIconServer();

		    CTrayIcon*			                                Insert();

		    void				                                RegisterHandler(IconEventHandlerType);

	    protected:
		    long				                                OnWndProc(unsigned int, WPARAM, LPARAM);

	    private:
            typedef boost::ptr_map<unsigned int, CTrayIcon> TrayIconMapType;

		    TrayIconMapType	                                    m_Icons;
            boost::signal<void (CTrayIcon*, LPARAM)>            m_IconEventSignal;
        };
    }
}

#endif
