#include "ini_parser.h"

namespace qh
{


	INIParser::INIParser()
	{

	}

	INIParser::~INIParser()
	{

	}

	bool INIParser::Parse(const std::string& ini_file_path)
	{
	    /*
		std::ifstream in_file(ini_file_path);  // ´ÓÓ²ÅÌµ½ÄÚ´æ

		if (!in_file)   // if (!file.is_open())
		{
			return false;
		}
		in_file.seekg(0, ios::end);

		*/
		return true;

	}

	bool INIParser::Parse(const char* ini_data, size_t ini_data_len, const std::string& line_seperator, const std::string& key_value_seperator)
	{
		const char *p = ini_data;

		std::string key;    // save the key
		std::string value;  // save the value
		while (p < ini_data + ini_data_len)
		{
			p += strspn(p, " \t\r");  // skip leading blanks
			size_t index = strspn(p, line_seperator.c_str());
			p += index;
			p += strspn(p, " \t\r");  // skip blanks

			// key_value_seperator position
			const char *key_value_seperator_pos = strstr(p, key_value_seperator.c_str());
			if (key_value_seperator_pos != NULL)
			{
				key = std::string(p, key_value_seperator_pos - p);
				trimSpace(key);
			}
			else  // When key_value_seperator_pos == NULL, it means we have parsed all the key-value pair
			{
				break;
			}
			p = key_value_seperator_pos;

			p += strspn(p, " \t\r");            // skip blanks
			p += key_value_seperator.length();  // skip key_value_seperator

			// line_seperator position
			const char *line_seperator_pos = strstr(p, line_seperator.c_str());
			if (line_seperator_pos != NULL)
			{
				value = std::string(p, line_seperator_pos - p);
				trimSpace(value);
			}
			p = line_seperator_pos;

			InitSection section;
			// std::string section_name = defaultSection;
			sections_[defaultSection].keyIntem[key] = value;

			// typedef std::unordered_map < std::string, InitSection>
		}
		return true;
	}


	const std::string& INIParser::Get(const std::string& key, bool* found)
	{
		return sections_[defaultSection].keyIntem[key];
	}

}  //end of namespace qh
