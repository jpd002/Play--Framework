#ifndef _GUIDUTILS_H_
#define _GUIDUTILS_H_

#include <iostream>
#include "lexical_cast_ex.h"

static bool operator < (const GUID& guid1, const GUID& guid2)
{
    return memcmp(&guid1, &guid2, sizeof(GUID)) < 0;
}

static std::istream& operator >>(std::istream& Input, GUID& rGUID)
{
    char nTemp[9];

    //Data 1
    Input.read(nTemp, 8);
    nTemp[8] = 0;
    rGUID.Data1 = lexical_cast_hex<std::string>(nTemp);

    //Validation
    Input.read(nTemp, 1);
    if(nTemp[0] != '-')
    {
        throw std::exception();
    }

    unsigned short* pShortVals[2] =
    {
        &rGUID.Data2,
        &rGUID.Data3,
    };

    //Data2, 3
    for(unsigned int i = 0; i < 2; i++)
    {
        Input.read(nTemp, 4);
        nTemp[4] = 0;
        *pShortVals[i] = lexical_cast_hex<std::string>(nTemp);

        //Validation
        Input.read(nTemp, 1);
        if(nTemp[0] != '-')
        {
            throw std::exception();
        }
    }

    for(unsigned int i = 0; i < 2; i++)
    {
        Input.read(nTemp, 2);
        nTemp[2] = 0;
        rGUID.Data4[i] = lexical_cast_hex<std::string>(nTemp);
    }

    //Validation
    Input.read(nTemp, 1);
    if(nTemp[0] != '-')
    {
        throw std::exception();
    }

    for(unsigned int i = 2; i < 8; i++)
    {
        Input.read(nTemp, 2);
        nTemp[2] = 0;
        rGUID.Data4[i] = lexical_cast_hex<std::string>(nTemp);
    }

    return Input;
}

static std::ostream& operator <<(std::ostream& Output, const GUID& rGUID)
{
    //{CCCCCCCC-CCCC-CCCC-CCCC-CCCCCCCCCCCC}

    Output << std::hex << std::uppercase << std::setfill('0');
    Output << std::setw(8) << rGUID.Data1 << '-';
    Output << std::setw(4) << rGUID.Data2 << '-';
    Output << std::setw(4) << rGUID.Data3 << '-';

    for(unsigned int i = 0; i < 2; i++)
    {
        Output << std::setw(2) << static_cast<unsigned int>(rGUID.Data4[i]);
    }

    Output << '-';

    for(unsigned int i = 2; i < 8; i++)
    {
        Output << std::setw(2) << static_cast<unsigned int>(rGUID.Data4[i]);
    }

    return Output;
}

#endif
