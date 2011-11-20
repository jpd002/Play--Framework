#ifndef _BASE64_H_
#define _BASE64_H_

#include "boost/archive/iterators/base64_from_binary.hpp"
#include "boost/archive/iterators/binary_from_base64.hpp"
#include "boost/archive/iterators/transform_width.hpp"

namespace Framework
{
    typedef boost::archive::iterators::base64_from_binary<    // convert binary values to base64 characters
                boost::archive::iterators::transform_width<   // retrieve 6 bit integers from a sequence of 8 bit bytes
                    const char*,
                    6,
                    8
                >
            > base64_t;

    typedef boost::archive::iterators::transform_width<
                boost::archive::iterators::binary_from_base64<const char*>, 8, 6
            > binary_t;

    static std::string ToBase64(const void* pBuffer, size_t nSize)
    {
        base64_t itBegin(reinterpret_cast<const char*>(pBuffer));
        base64_t itEnd(reinterpret_cast<const char*>(pBuffer) + nSize);
        return std::string(itBegin, itEnd);
    }

    static void FromBase64(void* pDst, size_t nSize, const char* pSrc)
    {
        binary_t itChar(pSrc);
        binary_t itEnd(pSrc + strlen(pSrc));
        char* pDstChar(reinterpret_cast<char*>(pDst));
        for(; itChar != itEnd && nSize != 0; itChar++, nSize--)
        {
            (*pDstChar++) = *itChar;
        }
    }
}

#endif
