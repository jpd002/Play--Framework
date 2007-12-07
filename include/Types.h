/*

	Framework - Types.h
	File Version 1.0.000
	Basic Types Definitions

*/

#ifndef _TYPES_H_
#define _TYPES_H_

typedef char int8;
typedef unsigned char uint8;

typedef short int16;
typedef unsigned short uint16;

typedef long int32;

//Fixes compilation problem under xcode
#ifndef _UINT32
typedef unsigned long uint32;
#endif

typedef long long int64;
typedef unsigned long long uint64;

#endif
