#include "Csv.h"
#include <cassert>

using namespace Framework;
using namespace Framework::Csv;

enum class PARSER_STATE
{
	STANDARD_READCHAR,
	STANDARD_PROCESSCHAR,
	DELIMITER_ADVANCE,
	DELIMITER_END_ADVANCE,
	DONE
};

static std::string CsvEscape(const std::string& input)
{
	std::string result;
	for(auto inputChar : input)
	{
		switch(inputChar)
		{
		case '\"':
			result += "\"\"";
			break;
		default:
			result += inputChar;
			break;
		}
	}
	return result;
}

Contents Csv::Parse(CStream& stream, char separator)
{
	char textDelimiter = '\"';
	bool useTextDelimiter = true;
	Contents contents;
	bool done = false;
	auto parserState = PARSER_STATE::STANDARD_READCHAR;
	uint8 currentChar = 0;
	Line currentLine;
	std::string currentValue;
	auto flushCurrentValue =
			[&currentValue, &currentLine] ()
			{
				currentLine.push_back(currentValue);
				currentValue.clear();
			};
	auto flushCurrentLine =
			[&currentLine, &contents] ()
			{
				contents.push_back(currentLine);
				currentLine.clear();
			};
	while(!done)
	{
		switch(parserState)
		{
		case PARSER_STATE::STANDARD_READCHAR:
			currentChar = stream.Read8();
			if(stream.IsEOF())
			{
				parserState = PARSER_STATE::DONE;
				continue;
			}
			parserState = PARSER_STATE::STANDARD_PROCESSCHAR;
			break;
		case PARSER_STATE::STANDARD_PROCESSCHAR:
			if(useTextDelimiter && (currentChar == textDelimiter))
			{
				assert(currentValue.empty());
				parserState = PARSER_STATE::DELIMITER_ADVANCE;
				continue;
			}
			//Standard cases
			if(currentChar == separator)
			{
				flushCurrentValue();
			}
			else if(currentChar == '\r')
			{
				//Ignore CR
			}
			else if(currentChar == '\n')
			{
				flushCurrentValue();
				flushCurrentLine();
			}
			else
			{
				currentValue += currentChar;
			}
			parserState = PARSER_STATE::STANDARD_READCHAR;
			break;
		case PARSER_STATE::DELIMITER_ADVANCE:
			currentChar = stream.Read8();
			if(stream.IsEOF())
			{
				//Unexpected end of file
				throw std::exception();
			}
			if(currentChar == textDelimiter)
			{
				parserState = PARSER_STATE::DELIMITER_END_ADVANCE;
			}
			else
			{
				currentValue += currentChar;
			}
			break;
		case PARSER_STATE::DELIMITER_END_ADVANCE:
			//Should always come from text delimiter
			assert(currentChar == textDelimiter);
			currentChar = stream.Read8();
			if(stream.IsEOF())
			{
				parserState = PARSER_STATE::DONE;
				continue;
			}
			if(currentChar == textDelimiter)
			{
				//Actually meant to escape the delimiter
				currentValue += textDelimiter;
				parserState = PARSER_STATE::DELIMITER_ADVANCE;
			}
			else
			{
				parserState = PARSER_STATE::STANDARD_PROCESSCHAR;
			}
			break;
		case PARSER_STATE::DONE:
			flushCurrentValue();
			flushCurrentLine();
			done = true;
			break;
		default:
			throw std::exception();
			break;
		}
	}
	return contents;
}

void Csv::Write(const Contents& contents, CStream& outputStream, char separator)
{
	for(const auto& line : contents)
	{
		std::string lineString;
		for(uint32 i = 0; i < line.size(); i++)
		{
			auto field = line[i];
			//Also, new lines
			if(field.find(separator) != std::string::npos)
			{
				field = "\"" + CsvEscape(field) + "\"";
			}
			lineString += field;
			if(i != line.size())
			{
				lineString += separator;
			}
		}
		lineString += "\n";
		outputStream.Write(lineString.c_str(), lineString.size());
	}
}
