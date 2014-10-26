//g++编译方法
//g++ -std=c++11 postfix.cpp solvex.cpp main.cpp -o solve_equation
//若是想去掉讨厌的c++11，遵循下列步骤
//postfix.h文件中把enum class替换为enum就好啦

//三角函数的计算采用的是弧度制
//solvex::solve_secant_method()的参数非常重要，是解方程的初始值

//程序功能
//输入一个方程
//解之
//例子：
//输入(x+1)^2=4，返回1，调整solve_secant_method()的初始值可获得另外一个解


#include "solvex.h"
#include <iostream>
#include <string>

int solve_eq(string equation, double left, double right)
{
		try{
			solvex equ(equation.c_str());
			return equ.solve_secant_method(left, right);
			//equ.print_postfix();
		}
		catch (string exc)
		{
			cout << exc << endl;
		}
		catch (...)
		{
			cout << "遇到未知的错误！" << endl;
		}
	return 0;
}
