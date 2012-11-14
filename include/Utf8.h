#ifndef _UTF8_H_
#define _UTF8_H_

#include <stdexcept>
#include <string>

namespace Framework
{
	namespace Utf8
	{
		template <typename IteratorType>
		std::wstring ConvertFrom(const IteratorType& itBegin, const IteratorType& itEnd)
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
					if((nChar & 0xE0) == 0xC0)
					{
						bool valid = false;

						char byte1 = 0;
						++itChar;
						if(itChar != itEnd)
						{
							byte1 = (*itChar);
							valid = true;
						}

						if((byte1 & 0xC0) != 0x80) valid = false;

						if(valid)
						{
							wchar_t nWChar = ((nChar & 0x1F) << 6) | (byte1 & 0x3F);
							sTemp += nWChar;
						}
						else
						{
							sTemp += '?';
						}
					}
					else if((nChar & 0xF0) == 0xE0)
					{
						bool valid = false;

						char byte1 = 0;
						char byte2 = 0;
						++itChar;
						if(itChar != itEnd)
						{
							byte1 = (*itChar);
							++itChar;
							if(itChar != itEnd)
							{
								byte2 = (*itChar);
								valid = true;
							}
						}

						if((byte1 & 0xC0) != 0x80) valid = false;
						if((byte2 & 0xC0) != 0x80) valid = false;

						if(valid)
						{
							wchar_t nWChar = ((nChar & 0x0F) << 12) | ((byte1 & 0x3F) << 6) | (byte2 & 0x3F);
							sTemp += nWChar;
						}
						else
						{
							sTemp += '?';
						}
					}
					else
					{
						sTemp += '?';
					}
				}

				if(itChar == itEnd)
				{
					//Can get in here if we failed to fetch a character
					break;
				}
			}

			return sTemp;
		}

		template <typename IteratorType>
		std::string ConvertTo(const IteratorType& itBegin, const IteratorType& itEnd)
		{
			std::string result;

			for(IteratorType itChar(itBegin); itChar != itEnd; itChar++)
			{
				wchar_t ch = (*itChar);
				if(ch <= 0x7F)
				{
					result += static_cast<char>(ch);
				}
				else
				{
					if(ch <= 0x7FF)
					{
						wchar_t byte1 = 0xC0 | ((ch & 0x700) >> 6) | ((ch & 0xC0) >> 6);
						wchar_t byte2 = 0x80 | (ch & 0x3F);
						result += static_cast<char>(byte1);
						result += static_cast<char>(byte2);
					}
					else
					{
						if(ch <= 0xFFFF)
						{
							wchar_t byte1 = 0xE0 | ((ch & 0xF000) >> 12);
							wchar_t byte2 = 0x80 | ((ch & 0x0F00) >> 6) | ((ch & 0xC0) >> 6);
							wchar_t byte3 = 0x80 | (ch & 0x3F);
							result += static_cast<char>(byte1);
							result += static_cast<char>(byte2);
							result += static_cast<char>(byte3);
						}
						else
						{
							throw std::exception();
						}
					}
				}
			}

			return result;
		}

		std::wstring	ConvertFrom(const std::string&);
		std::string		ConvertTo(const std::wstring&);
	};
}

#endif
