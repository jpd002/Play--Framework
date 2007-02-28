#ifndef _LEXICAL_CAST_EX_H_
#define _LEXICAL_CAST_EX_H_

#include <string>
#include <assert.h>
#include <algorithm>

template <typename Format>
Format lexical_cast_hex(unsigned int nNumber, unsigned int nWidth = 0)
{
    assert(nWidth <= 8);
    nWidth = std::min<unsigned int>(nWidth, 8);

    Format::value_type* sBuffer;
    sBuffer = reinterpret_cast<Format::value_type*>(_alloca(sizeof(Format::value_type) * (nWidth + 1)));

    for(unsigned int i = 0; i < nWidth; i++)
    {
        unsigned int nNibble;
        nNibble = (nNumber >> ((nWidth - i - 1) * 4)) & 0xF;
        sBuffer[i] = (nNibble > 9) ? (nNibble - 0xA + 'A') : (nNibble + '0');
    }
    sBuffer[nWidth] = 0;

    return Format(sBuffer);
}

#endif
