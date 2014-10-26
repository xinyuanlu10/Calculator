#include "postfix.h"

class solvex
{

private:
	expression fx;			//这个是内建的表达式值

public:
    solvex(){}
	solvex(const char*);	//构造函数，输入为一个方程，未知数只能是x
	~solvex();				//析构函数，其实什么内容也没有

	void input_exp(const char*);				//同构造函数solvex(const char*)的功能，用于声明后的构造
	double solve_secant_method(double, double);	//采用割线法解方程，两个double为初始值，初始值一定要慎重选择啊，本函数的返回值就是解
	void print_postfix();						//输出后序表达式的函数，用于测试
};
