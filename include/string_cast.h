#ifndef _STRING_CAST_H_
#define _STRING_CAST_H_

template <typename Target, typename Source> Target string_cast(const Source&);
template <typename Target, typename Source> Target string_cast(const Source*);

#endif
