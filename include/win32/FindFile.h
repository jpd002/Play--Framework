#ifndef _FINDFILE_H_
#define _FINDFILE_H_

#include "win32/Window.h"

namespace Framework
{
    namespace Win32
    {
        class CFindFile
        {
        public:
                                CFindFile(const TCHAR*);
            virtual             ~CFindFile();

            bool                GetNext(WIN32_FIND_DATA*);

        private:
            WIN32_FIND_DATA     m_FindData;
            HANDLE              m_Handle;
            bool                m_nDone;
        };
    }
}

#endif
