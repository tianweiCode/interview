#include "ini_parser.h"

namespace qh
{


	INIParser::INIParser()
	{

	}

	INIParser::~INIParser()
	{

	}

	bool INIParser::Parse(const std::string& ini_file_path)  // PerfCounters.ini  system.ini
	{
		// 从硬盘读ini文件到内存中
		std::ifstream in_file(ini_file_path);  

		if (!in_file)   // if (!file.is_open())
		{
			return false;
		}

		in_file.seekg(0, std::ios::end);    // 文件指针定位到文件末尾 
		long file_length = in_file.tellg();
		if (file_length < 0)
		{
			return false;
		}
		char *ini_input = new char[file_length + 1];
		if (ini_input == NULL)
		{
			return false;
		}
		in_file.seekg(0, std::ios::beg);    // 文件指针定位到文件开始 
		in_file.read(ini_input, file_length);
		ini_input[file_length = in_file.gcount()] = 0;

		// parse ini file
		std::string section_name;
		std::string comment;
		char *pcurrent = ini_input;
		while (pcurrent < ini_input + file_length)
		{
			pcurrent += strspn(pcurrent, " \t\r");  // skip leading blanks
			if (*pcurrent == comment_tag)           // comment ;
			{
				++pcurrent;
				pcurrent += strspn(pcurrent, " \t\r");
				const char *newline_pos = strstr(pcurrent, "\n");
				comment = std::string(pcurrent, newline_pos - pcurrent);

				pcurrent += newline_pos - pcurrent;
				pcurrent += strspn(pcurrent, "\n");
			}
			else if (*pcurrent == left_bracket_tag)  // [
			{
				++pcurrent;
				pcurrent += strspn(pcurrent, " \t\r");
				const char *right_bracket_tag_pos = strstr(pcurrent, "]");
				section_name = std::string(pcurrent, right_bracket_tag_pos - pcurrent);

				pcurrent += right_bracket_tag_pos - pcurrent + 1;
				pcurrent += strspn(pcurrent, "\n");

				// Only have section name, do not have key-value
				if (pcurrent == ini_input + file_length)
				{
					sections_[section_name].comment = comment;
				}
				
				// Get all the key-value pairs string, then parse
				std::string ini_key_values;
				while (pcurrent < ini_input + file_length)
				{
					while (pcurrent < ini_input + file_length && *pcurrent != comment_tag && *pcurrent != left_bracket_tag)
					{
						ini_key_values += *pcurrent;
						++pcurrent;
					}
					
					Parse(ini_key_values.c_str(), ini_key_values.length(), "\n", "=", section_name);
					sections_[section_name].comment = comment;
					
					section_name.clear();
					comment.clear();
					break;
				}
			}
		}

		// 释放内存
		delete[] ini_input;

		return true;
	}

	bool INIParser::Parse(const char* ini_data, size_t ini_data_len, const std::string& line_seperator, const std::string& key_value_seperator, const std::string& section_name)
	{
		const char *p = ini_data;

		std::string key;    // save the key
		std::string value;  // save the value
		while (p < ini_data + ini_data_len)
		{
			p += strspn(p, " \t\r");                 // skip leading blanks
			p += strspn(p, line_seperator.c_str());  // skip line_seperator
			p += strspn(p, " \t\r");                 // skip blanks

			// Find key_value_seperator position, then get the KEY
			const char *key_value_seperator_pos = strstr( p, key_value_seperator.c_str() );
			if ( key_value_seperator_pos != NULL )
			{
				key = std::string(p, key_value_seperator_pos - p);
				trimSpace(key);
			}
			else  // When key_value_seperator_pos == NULL, it means we have parsed all the key-value pair
			{
				break;
			}
			p = key_value_seperator_pos;

			p += strspn(p, " \t\r");                 // skip blanks
			p += key_value_seperator.length();       // skip key_value_seperator

			// Find line_seperator position, then get the VALUE
			const char *line_seperator_pos = strstr( p, line_seperator.c_str() );
			if ( line_seperator_pos != NULL )
			{
				value = std::string(p, line_seperator_pos - p);
				trimSpace(value);
			}
			p = line_seperator_pos;

			// When is section_name, save the current key-val
			sections_[section_name].keyIntem[key] = value;  
		}
		return true;
	}

	const std::string& INIParser::Get(const std::string& key, bool* found)
	{
		return sections_[defaultSection].keyIntem[key];
	}

	const std::string& Get(const std::string& section_name, const std::string& key, bool* found)
	{
		// return sections_[section_name].keyIntem[key];\
		
		return "k";
	}

}  //end of namespace qh
