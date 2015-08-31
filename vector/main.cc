#include <stdlib.h>
#include "qh_vector.h"
#include <assert.h>

void test1()
{
	// 测试：默认构造函数  size()函数
	qh::vector<int> a;
	assert(a.size() == 0);
	a.push_back(1);
	a.push_back(2);
	assert(a.size() == 2);

	// 测试：显示构造函数
	qh::vector<int> b(10, 0);
	assert(b.size() == 10);
	b.push_back(1);
	b.push_back(2);
	assert(b.size() == 12);

	// 测试：operator[]
	qh::vector<int> c;
	// int num_1 = c[1];
	// int num_2 = c[0];
	c.push_back(1);
	c.push_back(2);
	int num_3 = c[0];
	int num_4 = c[1];
	assert(num_3 == 1);
	assert(num_4 == 2);


	// 测试：operator=
	qh::vector<int> d;
	d.push_back(1);
	d.push_back(2);
    qh::vector<int> e;
    e = d;
	assert(d.size() == 2);
	assert(e.size() == 2);
	e.clear();
	assert(d.size() == 2);
	assert(e.size() == 0);

}

void test2()
{
	// 测试：push_back() pop_back()
	qh::vector<int> a;
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	assert(a.size() == 3);
	a.pop_back();
	assert(a.size() == 2);
	a.pop_back();
	a.pop_back();
	assert(a.size() == 0);


	// 测试：resize()
	qh::vector<int> b;
	b.push_back(1);
	b.push_back(2);
	b.push_back(3);
	assert(b.size() == 3);
	b.resize(5, 0);
	assert(b.size() == 5);
	int num_1 = b[0];
	assert(num_1 == 0);
	int num_2 = b[1];
	assert(num_2 == 0);
	int num_3 = b[2];
	assert(num_3 == 0);
	int num_4 = b[3];
	assert(num_4 == 0);

	// 测试：reserve()
	b.reserve(15);
}

void test3()
{
	// 测试：clear()
	qh::vector<int> a;
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	assert(a.size() == 3);
	a.clear();
	assert(a.size() == 0);

	// 测试：empty()
	assert(a.empty() == true);
}


int main(int argc, char* argv[])
{
    //TODO 在这里添加单元测试，越多越好，代码路径覆盖率越全越好
    //TODO 单元测试写法请参考INIParser那个项目，不要写一堆printf，要用assert进行断言判断。

	test1();
	test2();
	test3();

#ifdef WIN32
    system("pause");
#endif

	return 0;
}
