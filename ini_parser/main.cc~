#include "ini_parser.h"

#include <string.h>
#include <assert.h>

void test1()
{
    const char* ini_text= "\na==1\nb==2\n"; 
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "\n", "==")) {
         assert(false);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    std::string b = parser.Get("b", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("c", NULL);
    assert(c == "");
}

void test2()
{
    const char* ini_text= "a=1||b=2||c=3||"; 
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "||", "=")) {
        assert(false);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    std::string b = parser.Get("b", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("c", NULL);
    assert(c == "3");
}

void test3()
{
	const char* ini_text= "||||a:1||b:2||||c:3||||||"; 
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "||", ":")) {
        assert(false);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    std::string b = parser.Get("b", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("c", NULL);
    assert(c == "3");
}

void test4()
{
	const char* ini_text = "  ||||     abc:123||abd:456 ||||abe:789||||||";  // ||||
	qh::INIParser parser;
	if (!parser.Parse(ini_text, strlen(ini_text), "||", ":")) {
		assert(false);
	}

	const std::string& a = parser.Get("abc", NULL);
	assert(a == "123");

	std::string b = parser.Get("abd", NULL);
	assert(b == "456");

	const std::string& c = parser.Get("abe", NULL);
	assert(c == "789");
}

void test5()
{
	const char* ini_text = "% a:12345%b:2%c:3%";
	qh::INIParser parser;
	if (!parser.Parse(ini_text, strlen(ini_text), "%", ":")) {
		assert(false);
	}

	const std::string& a = parser.Get("a", NULL);
	assert(a == "12345");

	std::string b = parser.Get("b", NULL);
	assert(b == "2");

	const std::string& c = parser.Get("c", NULL);
	assert(c == "3");

	// const std::string& d = parser.Get("d", NULL);
}

int main(int argc, char* argv[])
{
    //TODO 在这里添加单元测试，越多越好，代码路径覆盖率越全越好

    // test1();
    // test2();
    // test3();
	// test4();
	test5();

	getchar();
    return 0;
}


