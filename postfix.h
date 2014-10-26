//注意！
//这里使用了c++11的枚举类
//啊当然你可以去掉那个class，不过我担心有问题
#ifndef _POST_
#define _POST_

#include <queue>
#include <stack>
#include <string>
using namespace std;


enum class exp_type{
	number,	//数的类型
	op,		//运算符
	var		//变量(x之类的)
};

enum class exp_op{
	plus,		// +
	minus,		// -
	mul,		// *
	div,		// /
	exp,		// ^
	exp_cos,	// cos
	exp_sin,	// sin
	exp_tan,	// tan
	left_par,	// (
	right_par,	// )
	neg_sign	// - 负号
};

enum exp_var{
	x	//变量x
};

class queue_postfix
{
private:
	queue<double> queue_num;	//用于存储浮点数
	queue<exp_op> queue_op;		//用于存储运算符
	queue<exp_var> queue_var;	//用于存储变量
	queue<exp_type> queue_type;	//用于存储类型的顺序，统筹全部的
	int num_bin_op = 0;			//二元运算符的数量
	int num_unary = 0;			//一元运算符的数量

public:
	void push(double);	//push一个值，此处为浮点数
	void push(exp_op);	//push一个值，此处为运算符
	void push(exp_var);	//push一个值，此处为变量
	bool empty();		//判断queue是否为空
	exp_type front();	//返回front位置的值的类型
	double pop_num();	//pop一个浮点数，并返回其值
	exp_op pop_op();	//pop一个运算符，并返回其值
	exp_var pop_var();	//pop一个变量，并返回其值
	bool check();		//检查
	void print();		//测试函数，打印queue	!!!!注意，这回造成queue为空(全部弹出)
};

class expression
{

private:
	string infix;									//中序表达式，就是f(x)
	queue_postfix postfix;							//后序表达式，使用queue存储
	void init();//输入表达式							//初始化值
	void push_operator(int&, stack<exp_op>&, bool);	//
	void top_pop(exp_op, stack<exp_op>&);
	int operator_precedence(exp_op);

//公共函数
public:
    expression(){}					//构造函数，这个是空的，初始化使用input_exp(const char*)
	expression(const char*);		//构造函数，初始化
	~expression();					//析构函数，没有内容
	void input_exp(const char*);	//输入表达式，用于初始化
	double result(double);			//输入一个浮点数，返回表达式的值(也就是f(x))
	void print_postfix();			//测试，用于输出后序表达式
};

#endif
