//解方程中关于三角函数的计算采用的是弧度制

#include "solvex.h"

//构造函数
//输入参数是表达式的字符指针
solvex::solvex(const char* input)
{
	//调用input_exp函数
	input_exp(input);
}

//析构函数
//内容为空
solvex::~solvex()
{
	;//空
}

//初始化函数
//输入是表达式的字符指针
//例子：
//		"x^2=3"
void solvex::input_exp(const char* input)
{
	string temp(input);		//临时的string
	int pos_equ;			//用于存储 '=' 的位置，因为直接上函数的话就要重复好几遍，不如直接存储下来
	pos_equ = (int)temp.find('=');

	//这个if语句的作用就是把等式右边的东西放到左边，并且去掉等号
	//例子：
	//		"x^2=3+(x-1)^2"
	//	-->	"x^2-(3+(x-1)^2)"
	if (pos_equ != temp.npos)
	{
		if (temp.substr(pos_equ + 1).find('=') == temp.substr(pos_equ + 1).npos)
		{
			temp.replace(pos_equ, 1, "-(");
			temp += ")";
		}
		else
			//如果方程中出现了多个等于号，则抛出异常(string)
			throw
			string("方程中出现了多个等号\n")
			+ temp + "\n";
	}
	else
		//没有等号同样抛出异常
		throw string("方程中缺少等号\n")
		+ temp + "\n";

	//fx就是表达式f(x)，现在是初始化它
	fx.input_exp(temp.c_str());
}

//解方程的函数
//采用割线法
//参数列表的两个浮点数的作用是初始值
//参考：
//		http://en.wikipedia.org/wiki/Secant_method
double solvex::solve_secant_method(double x1, double x2)
{
	double x3 = 0;
	double divisor;
	//执行三十次迭代，当然，达到了要求的话就break了
	for (int i = 0; i < 30; i++)
	{
		divisor = fx.result(x2) - fx.result(x1);
		//如果除数为0(或者十分接近0)
		if (divisor < 0.0000001 && divisor > -0.0000001)
			break;
		x3 = x2 - (x2 - x1)*fx.result(x2) / (fx.result(x2) - fx.result(x1));
		x1 = x2;
		x2 = x3;
	}
	//这个是达不到要求的条件
	//这里的条件判断有一点乱。。。
	//	当方程的 |left-right| >0.01 时候认为无解
	if (fx.result(x3)>0.01 || fx.result(x3) < -0.01)
		throw string("不存在解或超出范围!\n")
		+ string("也有可能是初值取错了位置，导致结果不明\n");
	return x3;
}

//测试函数
//输出后序表达式
void solvex::print_postfix()
{
	fx.print_postfix();
}