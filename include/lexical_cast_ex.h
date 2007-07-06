#ifndef _LEXICAL_CAST_EX_H_
#define _LEXICAL_CAST_EX_H_

#include <string>
#include <sstream>
#include <assert.h>
#include <algorithm>

template <typename Format>
Format lexical_cast_hex(unsigned int nNumber, unsigned int nWidth = 1)
{
    enum MAXNIBBLE
    {
        MAXNIBBLE = 8,
    };

    assert(nWidth <= MAXNIBBLE);

    unsigned int nNumSize = 0;
    for(unsigned int i = 0; i < MAXNIBBLE; nNumSize++, i++)
    {
        if((nNumber >> (i * 4)) == 0) break;
    }

    nWidth = std::min<unsigned int>(nWidth, MAXNIBBLE);
    nWidth = std::max<unsigned int>(nNumSize, nWidth);

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

template <typename Format>
unsigned int lexical_cast_hex(const Format& sValue)
{
    unsigned int nNumber;
    std::basic_istringstream<Format::value_type> Stream(sValue);
    Stream >> hex >> nNumber;

    if(Stream.fail())
    {
        throw exception();
    }

    return nNumber;
}

#endif
