#ifndef QIHOO_INI_PARSER_H_
#define QIHOO_INI_PARSER_H_

#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <functional>
#include <iterator>



namespace qh
{
	static const char defaultSection[]   = "defaultSection";
	static const char left_bracket_tag   = '[';
	static const char right_bracket_tag	 = ']';
	static const char newline            = '/n';
	static const char comment_tag        = ';';
	
	class INIParser
	{
	public:
		/*struct keyIntem
		{
			std::string key;
			std::string value;
		};*/
		struct InitSection
		{
			// std::string section_name;
			std::map< std::string, std::string > keyIntem;  // unordered_map
			std::string comment;
		};

		typedef std::map < std::string, InitSection > Section;

    public:
        INIParser();
        ~INIParser();

        //! \brief 解析一个磁盘上的INI文件
        //! \param[in] - const std::string & ini_file_path
        //! \return - bool
        bool Parse(const std::string& ini_file_path);

        //! \brief 解析一段形如INI格式的内存数据。
        //!   例如：ini_data="a:1||b:2||c:3"
        //!         调用<code>Parse(ini_data, ini_data_len, "||", ":")</code>即可解析出这段数据。
        //!         解析完毕之后
        //!         Get("a")=="1" && Get("b")=="2" && Get("c")=="3"
        //! \param[in] - const char * ini_data
        //! \param[in] - size_t ini_data
        //! \param[in] - const std::string & line_seperator
        //! \param[in] - const std::string & key_value_seperator
		//! \param[in] - const std::string & section_name    secion name， 如果未指定名字，使用默认名字"defaultSection"
        //! \return - bool
		bool Parse(const char* ini_data, size_t ini_data_len, const std::string& line_seperator = "\n", const std::string& key_value_seperator = "=", const std::string& section_name = "defaultSection");


        //! \brief 从默认section中查找某个key，并返回找到的value。如果找不到，返回一个空串
        //! \param[in] - const std::string & key
        //! \param[in] - bool * found - 输出参数，true表明找到这个key
        //! \return - const std::string& - 返回的具体key对应的value
        const std::string& Get(const std::string& key, bool* found);

        const std::string& Get(const std::string& section, const std::string& key, bool* found);

    private:
		Section sections_;

		//! \brief 去除字符串首尾的空格
		//! \param[in] - std::string & str
		//! \return - void
		inline void trimSpace(std::string &str)
		{
			str.erase(str.find_last_not_of(" ") + 1);
		    str.erase(0, str.find_first_not_of(" "));
		}
    };
}

#endif

