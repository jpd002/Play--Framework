#ifndef _PLACEHOLDER_DEF_H_
#define _PLACEHOLDER_DEF_H_

#ifdef _MSVC

#define PLACEHOLDER_1   placeholders::_1
#define PLACEHOLDER_2   placeholders::_2
#define PLACEHOLDER_3   placeholders::_3
#define PLACEHOLDER_4   placeholders::_4
#define PLACEHOLDER_5   placeholders::_5
#define PLACEHOLDER_6   placeholders::_6

#else

#define PLACEHOLDER_1   _1
#define PLACEHOLDER_2   _2
#define PLACEHOLDER_3   _3
#define PLACEHOLDER_4   _4
#define PLACEHOLDER_5   _5
#define PLACEHOLDER_6   _6

#endif

#endif
