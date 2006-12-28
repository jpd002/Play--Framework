#ifndef _LEXICAL_CAST_EX_H_
#define _LEXICAL_CAST_EX_H_

#include <string>
#include <iomanip>

template <typename Format>
Format lexical_cast_hex(unsigned int nNumber, unsigned int nWidth = 0)
{
	std::basic_ostringstream<Format::value_type> Stream;
	Stream << hex << uppercase
		<< setfill(static_cast<Format::value_type>('0')) << setw(nWidth)
		<< nNumber;
	return Stream.str();
}

#endif
