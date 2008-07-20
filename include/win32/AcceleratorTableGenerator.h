#ifndef _ACCELERATORTABLEGENERATOR_H_
#define _ACCELERATORTABLEGENERATOR_H_

#include "Window.h"
#include <vector>

namespace Framework
{
    namespace Win32
    {
        class CAcceleratorTableGenerator
        {
        public:
                                    CAcceleratorTableGenerator();
            virtual                 ~CAcceleratorTableGenerator();

            void                    Insert(unsigned int, unsigned int, unsigned int);
            HACCEL                  Create();

        private:
            typedef std::vector<ACCEL> AcceleratorTableType;

            AcceleratorTableType    m_table;
        };
    }
}

#endif
