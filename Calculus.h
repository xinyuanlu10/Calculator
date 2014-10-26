#ifndef _CALCULUS_H_
#define _CALCULUS_H_
#define err 0.000000001//允许误差

#include "postfix.h"//使用同组同学写的类用来计算输入函数在给定位点的值
#include <cmath>
using namespace std;

class calculus 
{
private:
	expression fx;
	//私有函数
	double adaptive_simpson_method(double, double, double, int);
	double adaptive_simpson_method_recursive(double, double, double, double, double, double, double, int);

public:
	//构造函数
	calculus(){};
	calculus(const char*);
	//析构函数
	~calculus();
	//公有函数
	void input_exp(const char*);
    double getcalculus(double a,double b);
};

calculus::calculus(const char* input)//构造函数，用于赋初值
{
	fx.input_exp(input);//通过调用公有函数input_exp给成员变量fx赋初值
}

calculus::~calculus()//析构函数
{
	;
}

void calculus::input_exp(const char* input)//用于给成员变量fx赋值
{
	fx.input_exp(input);//通过调用expression类的公有函数input_exp实现变量赋值给成员变量fx赋初值
}

double calculus::getcalculus(double a, double b)
//输入积分的上下限，返回积分运算的结果
//a-积分下限  b-积分上限
{
	return adaptive_simpson_method(a, b, err, 10);
}

double calculus::adaptive_simpson_method(double a, double b, double epsilon, int maxRecursionDepth)
//计算给定的函数在给定的区间上使用辛普森算法得到的值，并且调用adaptive_simpson_method_recursive函数
//计算二分后的两个区间分别用辛普森算法得到的值的和，并判断是否需要进一步递归以实现自适应。
{
	double c = (a + b) / 2;//c-积分中值
	double h = b - a;//h-积分区间的长度
	double fa = fx.result(a);//fa-积分函数在a点的函数值
	double fb = fx.result(b);//fb-积分函数在b点的函数值
	double fc = fx.result(c);//fc-积分函数在c点的函数值
	double res = (h / 6)*(fa + fb + 4 * fc);//辛普森公式得出的区间[a,b]的积分值
	return adaptive_simpson_method_recursive(a,b,epsilon,res,fa,fb,fc,maxRecursionDepth);
}

double calculus::adaptive_simpson_method_recursive(double a, double b, double epsilon, double res, 
													double fa, double fb, double fc, int depth)
//通过递归的方式实现自适应
{
	double c = (a + b) / 2;
	double h = b - a;
	double d = (a + c) / 2;//d-区间[a,c]的积分中值
	double e = (c + b) / 2;//e-区间[c,b]的积分中值
	double fd = fx.result(d);//fd-积分函数在d点的函数值
	double fe = fx.result(e);//fe-积分函数在e点的函数值
	double res_left = (h / 12)*(fa + fc + 4 * fd);//辛普森公式得出的区间[a,c]的积分值
	double res_right = (h / 12)*(fc + fb + 4 * fe);//辛普森公式得出的区间[c,b]的积分值
	double _res = res_left + res_right;
	if (depth <= 0 || fabs(_res - res) <= 15 * epsilon)//判断是否需要继续递归
		return _res + (_res - res) / 15;
	return adaptive_simpson_method_recursive(a, c, epsilon / 2, res_left, fa, fc, fd, depth - 1) + 
		adaptive_simpson_method_recursive(c, b, epsilon / 2, res_right, fc, fb, fe, depth - 1);
}

#endif
