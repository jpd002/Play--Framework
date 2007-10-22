#ifndef _UTF8_H_
#define _UTF8_H_

#include <string>

namespace Framework
{
    namespace Utf8
    {
        template <typename IteratorType>
        std::wstring ConvertFrom(const IteratorType itBegin, const IteratorType itEnd)
        {
            std::wstring sTemp;

            for(IteratorType itChar(itBegin); itChar != itEnd; itChar++)
            {
                char nChar(*itChar);
                if((nChar & 0x80) == 0)
                {
                    sTemp += nChar;
                }
                else
                {
                    if((nChar & 0xF0) == 0xE0)
                    {
                        char nByte1(*(++itChar));
                        char nByte2(*(++itChar));
                        
                        if((nByte1 & 0xC0) != 0x80) throw std::exception();
                        if((nByte2 & 0xC0) != 0x80) throw std::exception();

                        wchar_t nWChar;
                        nWChar = ((nChar & 0x0F) << 12) | ((nByte1 & 0x3F) << 6) | (nByte2 & 0x3F);

                        sTemp += nWChar;
                    }
                    else
                    {
                        throw std::exception();
                    }
                }
            }

            return sTemp;
        }

        std::wstring ConvertFrom(const std::string&);
    };
}

#endif
