#ifndef _LEXICAL_CAST_EX_H_
#define _LEXICAL_CAST_EX_H_

#include <string>
#include <sstream>
#include <assert.h>
#include "alloca_def.h"
#include <algorithm>
#include <iomanip>

template <typename Format>
Format lexical_cast_hex(unsigned int nNumber, unsigned int nWidth = 1)
{	
    enum MAXNIBBLE
    {
        MAXNIBBLE = 8,
    };

    assert(nWidth <= MAXNIBBLE);
    if(nWidth == 0) nWidth = 1;

    unsigned int nNumSize = 0;
    for(unsigned int i = 0; i < MAXNIBBLE; nNumSize++, i++)
    {
        if((nNumber >> (i * 4)) == 0) break;
    }

    nWidth = std::min<unsigned int>(nWidth, MAXNIBBLE);
    nWidth = std::max<unsigned int>(nNumSize, nWidth);

    typename Format::value_type* sBuffer;
    sBuffer = reinterpret_cast<typename Format::value_type*>(alloca(sizeof(typename Format::value_type) * (nWidth + 1)));

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
    std::basic_istringstream<typename Format::value_type> Stream(sValue);
    Stream >> std::hex >> nNumber;

    if(Stream.fail())
    {
        throw std::exception();
    }

    return nNumber;
}

template <typename Format>
Format lexical_cast_uint(unsigned int number, unsigned int width = 1)
{
    std::basic_ostringstream<typename Format::value_type> stream;
    stream << std::setw(width) << std::setfill(static_cast<typename Format::value_type>('0')) << number;
    return stream.str();
}

template <typename Format>
Format lexical_cast_int(int number, unsigned int width = 1, typename Format::value_type fillChar = '0')
{
    std::basic_ostringstream<typename Format::value_type> stream;
    stream << std::setw(width) << std::setfill(fillChar) << number;
    return stream.str();
}

#endif
