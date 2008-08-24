#ifndef _DIRECTINPUTKEYBOARD_H_
#define _DIRECTINPUTKEYBOARD_H_

#include "Device.h"

namespace DirectInput
{
    class CKeyboard : public CDevice
    {
    public:
                                CKeyboard(LPDIRECTINPUTDEVICE8, HWND);
        virtual                 ~CKeyboard();

        virtual void            ProcessEvents(const InputEventHandler&);
    };
}

#endif
