#ifndef QIHOO_INI_PARSER_H_
#define QIHOO_INI_PARSER_H_

#include <string>
#include <vector>
#include <map>
#include <fcntl.h>
#include <fstream>
#include <string.h>


namespace qh
{
	static const char defaultSection[] = "defaultSection";

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
			std::map<std::string, std::string> keyIntem;  // unordered_map
			std::string comment;
		};

		typedef std::map < std::string, InitSection> Section;

    public:
        INIParser();
        ~INIParser();

        //! \brief ����һ�������ϵ�INI�ļ�
        //! \param[in] - const std::string & ini_file_path
        //! \return - bool
        bool Parse(const std::string& ini_file_path);

        //! \brief ����һ������INI��ʽ���ڴ����ݡ�
        //!   ���磺ini_data="a:1||b:2||c:3"
        //!         ����<code>Parse(ini_data, ini_data_len, "||", ":")</code>���ɽ�����������ݡ�
        //!         �������֮��
        //!         Get("a")=="1" && Get("b")=="2" && Get("c")=="3"
        //! \param[in] - const char * ini_data
        //! \param[in] - size_t ini_data
        //! \param[in] - const std::string & line_seperator
        //! \param[in] - const std::string & key_value_seperator
        //! \return - bool
		bool Parse(const char* ini_data, size_t ini_data_len, const std::string& line_seperator = "\n", const std::string& key_value_seperator = "=");

        //! \brief ��Ĭ��section�в���ĳ��key���������ҵ���value������Ҳ���������һ���մ�
        //! \param[in] - const std::string & key
        //! \param[in] - bool * found - ���������true�����ҵ����key
        //! \return - const std::string& - ���صľ���key��Ӧ��value
        const std::string& Get(const std::string& key, bool* found);

        const std::string& Get(const std::string& section, const std::string& key, bool* found);

    private:

		Section sections_;



		//! \brief ȥ���ַ�����β�Ŀո�
		//! \param[in] - std::string & str
		//! \return - void
		inline void trimSpace(std::string &str)
		{
			str.erase(str.find_last_not_of(" ") + 1);
		    str.erase(0, str.find_first_not_of(" "));
		}



		//! \brief ����key_value_seperator��λ��key_value_seperator_pos����ini_data�н���key �� value
		//! \param[in] - const std::string & ini_data
		//! \param[in] - const std::string & line_seperator
		//! \param[in] - std::string & key   �������  �ؼ���key
		//! \param[in] - std::string & value �������  key��Ӧ��value
		//! \return - void

    };
}

#endif
