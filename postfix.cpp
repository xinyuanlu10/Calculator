#include "postfix.h"
#include <stack>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <string>

//-------------------------------------------------------------------------
//	expression的部分

//构造函数
//调用input_exp()函数
expression::expression(const char* input)
{
	input_exp(input);
}

//析构函数
expression::~expression()
{
	;//空
}

//初始化函数
void expression::input_exp(const char* input)
{
	infix.assign(input);	//初始化infix string的
	init();					//初始化postfix queue的
}

//queue初始化的函数
//也就是中缀转后缀，基本上最重要的函数
void expression::init()
{
	stack<exp_op> stack_op;	//存储
	bool flag_op = true;	//这个flag的作用是判断最近输入的是不是运算符,以用于减号还是负号的判断
	
	//一次遍历
	for (int i = 0; infix[i] != 0; i++)
	{
		//遇到空格则跳过
		if (infix[i] != ' ')
		{
			//switch语句相较于if速度更快
			switch (infix[i])
			{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				//如果是字符的话则直接push
				double dou_num;
				dou_num = atof(infix.substr(i).c_str());			//原c语言中的函数，字符向浮点转换
				postfix.push(dou_num);
				while ((infix[i] >= '0' && infix[i] <= '9') || infix[i] == '.')
					i++;
				i--;
				flag_op = false;									//输入不是运算符，flag_op = false
				break;
			case 'x':
			case 'X':
				//如果是变量的话则直接push
				postfix.push(exp_var::x);
				flag_op = false;									//输入不是运算符，flag_op = false
				break;
			case '(':
				//遇到左括号，直接push左括号
				stack_op.push(exp_op::left_par);
				flag_op = true;										//输入算作字符串，flag_op = true，处理(-1)这种情况
				break;
			case ')':
				//遇到右括号，pop直到遇到左括号
				if (stack_op.empty())
					throw string("表达式缺少匹配的左括号!\n");		//异常
				while (stack_op.top() != exp_op::left_par)			//遇到左括号之前一直pop
				{
					postfix.push(stack_op.top());
					stack_op.pop();
					if (stack_op.empty())
						throw string("表达式缺少匹配的左括号!\n");	//如果pop之后没有左括号而stack为空，抛出异常
				}
				stack_op.pop();		//最后pop出左括号
				flag_op = false;	//此时flag_op为false，为什么我不想写注释了啊
				break;
			case '+':
			case '-':
			case '*':
			case '/':
			case '^':
			case 'c':
			case 'C':
			case 's':
			case 'S':
			case 't':
			case 'T':
				//如果遇到运算符，执行push_operator函数(因为运算符的确定比较复杂)
				push_operator(i, stack_op, flag_op);
				i--;
				flag_op = true;		//flag_op为true
				break;
			default:
				throw string("输入表达式出现无法解析的符号\n" + string("  >> ")//不是上面的符号的话则抛出异常
					+ infix.substr(0, i + 1) + "\n")
					+ string(5 + i, ' ') + string("^");
			}
		}
	}
	while (!stack_op.empty())
		//如果遍历了infix之后stack不是空的，则全部弹出
	{
		postfix.push(stack_op.top());
		stack_op.pop();
	}
	if (postfix.check() == false)
		//check()检查表达式是否合法
		//方法是双目运算符数量加一等于运算数数量
		//非法则抛出异常
		throw string("表达式非法! 双目运算符的个数不等于操作数+1\n")
		+ string("  >> ") + infix;
	return;
}

//这是遇到运算符的时候的push and pop函数
void expression::push_operator(int& i, stack<exp_op>& stack_op, bool flag)
{
	//这些都简单明了，不解释
	if (infix.substr(i, 3) == "cos" || infix.substr(i, i + 2) == "COS")
	{
		top_pop(exp_op::exp_cos, stack_op);
		i = i + 3;
	}
	else if (infix.substr(i, 3) == "sin" || infix.substr(i, 3) == "SIN")
	{
		top_pop(exp_op::exp_sin, stack_op);
		i = i + 3;
	}
	else if (infix.substr(i, 3) == "tan" || infix.substr(i, 3) == "TAN")
	{
		top_pop(exp_op::exp_tan, stack_op);
		i = i + 3;
	}
	else if (infix[i] == '+')
	{
		top_pop(exp_op::plus, stack_op);
		i++;
	}
	else if (infix[i] == '-')
	{
		if (flag == false)
			//判断运算符的flag
			//true代表了首次遇到运算符，按减号处理
			//false代表二次遇到运算符，按照负号处理
		{
			top_pop(exp_op::minus, stack_op);
			i++;
		}
		else
		{
			top_pop(exp_op::neg_sign, stack_op);
			i++;
		}
	}
	else if (infix[i] == '*')
	{
		top_pop(exp_op::mul, stack_op);
		i++;
	}
	else if (infix[i] == '/')
	{
		top_pop(exp_op::div, stack_op);
		i++;
	}
	else if (infix[i] == '^')
	{
		top_pop(exp_op::exp, stack_op);
		i++;
	}
	else
		//无法解析，抛出异常
		//这里具有确定位置的功能
		throw string("输入表达式出现无法解析的符号\n" + string("  >> ")
		+ infix.substr(0, i + 3) + "\n")
		+ string(5 + i, ' ') + string("^^^");
	return;
}

//运算符pop函数
//就是一直从stack中pop直到遇到了优先级比之低的，然后push自己
void expression::top_pop(exp_op op, stack<exp_op>& stack_op)
{
	if (stack_op.empty())
	{
		stack_op.push(op);
		return;
	}
	while (!stack_op.empty() && operator_precedence(op) >= operator_precedence(stack_op.top()))
	{
		postfix.push(stack_op.top());
		stack_op.pop();
	}
	stack_op.push(op);
	return;
}

//运算符优先级判断函数
int expression::operator_precedence(exp_op op)
{
	int precedence = 0;		//这个默认似乎没有什么用
	switch (op)
	{
	case exp_op::left_par:	//左括号优先级最低，设为1000
		precedence = 1000;
		break;
	case exp_op::exp_cos:	//一级优先级，有cos,sin,tan和负号，它们都是一元运算符
	case exp_op::exp_sin:
	case exp_op::exp_tan:
	case exp_op::neg_sign:
		precedence = 1;
		break;
	case exp_op::exp:		// ^ 为二级运算符
		precedence = 2;
		break;
	case exp_op::mul:		// * / 为三级运算符
	case exp_op::div:
		precedence = 3;
		break;
	case exp_op::plus:		// + - 为四级运算符
	case exp_op::minus:
		precedence = 4;
		break;
	default:
		break;
	}
	return precedence;
}

//运算f(x)结果的函数，输入是x的值
//基本的思想也比较简单，就是从queue中取出内容
//遇到数字和变量就push进stack
//遇到一元运算符就从stack中pop一个计算后再push进去
//遇到二元运算符就从stack中pop两个计算后再push进去
double expression::result(double x)
{
	stack<double> stack_num;
	double result;
	double temp_a;
	double temp_b;
	while (!postfix.empty())
	{
		switch (postfix.front())
		{
		case exp_type::number:
			stack_num.push(postfix.pop_num());
			break;
		case exp_type::op:
			switch (postfix.pop_op())
			{
			case exp_op::plus:
				temp_a = stack_num.top();
				stack_num.pop();
				temp_b = stack_num.top();
				stack_num.pop();
				stack_num.push(temp_a + temp_b);
				break;
			case exp_op::minus:
				temp_a = stack_num.top();
				stack_num.pop();
				temp_b = stack_num.top();
				stack_num.pop();
				stack_num.push(temp_b - temp_a);
				break;
			case exp_op::mul:
				temp_a = stack_num.top();
				stack_num.pop();
				temp_b = stack_num.top();
				stack_num.pop();
				stack_num.push(temp_a * temp_b);
				break;
			case exp_op::div:
				temp_a = stack_num.top();
				if (temp_a == 0.0)
					throw string("发生了除法除数为零的错误!\n");
				stack_num.pop();
				temp_b = stack_num.top();
				stack_num.pop();
				stack_num.push(temp_b / temp_a);
				break;
			case exp_op::exp:
				temp_a = stack_num.top();
				stack_num.pop();
				temp_b = stack_num.top();
				stack_num.pop();
				stack_num.push(pow(temp_b, temp_a));
				break;
			case exp_op::exp_cos:
				temp_a = stack_num.top();
				stack_num.pop();
				stack_num.push(cos(temp_a));
				break;
			case exp_op::exp_sin:
				temp_a = stack_num.top();
				stack_num.pop();
				stack_num.push(sin(temp_a));
				break;
			case exp_op::exp_tan:
				temp_a = stack_num.top();
				stack_num.pop();
				stack_num.push(tan(temp_a));
				break;
			case exp_op::neg_sign:
				temp_a = stack_num.top();
				stack_num.pop();
				stack_num.push(-temp_a);
				break;
            case exp_op::left_par: break;
            case exp_op::right_par: break;
			}
			break;
		case exp_type::var:
			switch (postfix.pop_var())
			{
			case exp_var::x:
				stack_num.push(x);
				break;
			}
			break;
		}
	}
	//最后结果就是stack_num中的数字
	//应该只有一个数字了，可以再添加一个异常判断
	result = stack_num.top();
	stack_num.pop();
	if (!stack_num.empty())
		throw string("这究竟是什么邪门错误...反人类啊\n")
		+ string("位于result函数的最后\n");
	//此时queue已经空了，必须再次初始化
	init();
	//返回结果
	return result;
}

//打印测试函数
void expression::print_postfix()
{
	postfix.print();
	return;
}


//---------------------------------------------------------------------
//	queue_postfix部分

//double版push函数
//没什么解释的
void queue_postfix::push(double num)
{
	queue_num.push(num);
	queue_type.push(exp_type::number);
	return;
}

//运算符版push函数
//也没什么解释的
void queue_postfix::push(exp_op op)
{
	queue_op.push(op);
	queue_type.push(exp_type::op);
	switch (op)
	{
	case exp_op::plus:
	case exp_op::minus:
	case exp_op::mul:
	case exp_op::div:
	case exp_op::exp:
		num_bin_op++;		//如果是双目的话则num_bin_op++
		break;
	case exp_op::exp_cos:
	case exp_op::exp_sin:
	case exp_op::exp_tan:
	case exp_op::neg_sign:
		num_unary++;		//如果是单目的话则num_unary++
		break;
	default:
		break;
	}
	return;
}

//变量版...
void queue_postfix::push(exp_var var)
{
	queue_var.push(var);
	queue_type.push(exp_type::var);
	return;
}

//判断是否为空函数
bool queue_postfix::empty()
{
	return queue_type.empty();
}

//返回queue的第一个究竟是什么类型的
exp_type queue_postfix::front()
{
	return queue_type.front();
}

//弹出double
double queue_postfix::pop_num()
{
	double temp = queue_num.front();
	queue_num.pop();
	queue_type.pop();
	return temp;
}

//弹出运算符
exp_op queue_postfix::pop_op()
{
	exp_op temp = queue_op.front();
	queue_op.pop();
	queue_type.pop();
	switch (temp)
	{
	case exp_op::plus:
	case exp_op::minus:
	case exp_op::mul:
	case exp_op::div:
	case exp_op::exp:
		num_bin_op--;
		break;
	case exp_op::exp_cos:
	case exp_op::exp_sin:
	case exp_op::exp_tan:
	case exp_op::neg_sign:
		num_unary--;
		break;
	default:
		break;
	}
	return temp;
}

//弹出变量
exp_var queue_postfix::pop_var()
{
	exp_var temp = queue_var.front();
	queue_var.pop();
	queue_type.pop();
	return temp;
}

//检查表达式的合法性
//方法是双目运算符数量加一等于运算数数量
//这是二叉树的性质
bool queue_postfix::check()
{
	if (queue_num.size() + queue_var.size() == num_bin_op + 1)
		return true;
	return false;
}

//打印postfix函数
//仅用于测试
void queue_postfix::print()
{
	while (!empty())
	{
		switch (front())
		{
		case exp_type::number:
			cout << pop_num() << " ";
			break;
		case exp_type::op:
			switch (pop_op())
			{
			case exp_op::plus:
				cout << "+ ";
				break;
			case exp_op::minus:
			case exp_op::neg_sign:
				cout << "- ";
				break;
			case exp_op::mul:
				cout << "* ";
				break;
			case exp_op::div:
				cout << "/ ";
				break;
			case exp_op::exp:
				cout << "^ ";
				break;
			case exp_op::exp_cos:
				cout << "cos ";
				break;
			case exp_op::exp_sin:
				cout << "sin ";
				break;
			case exp_op::exp_tan:
				cout << "tan ";
				break;
            case exp_op::left_par:break;
            case exp_op::right_par:break;
			}
			break;
		case exp_type::var:
			switch (pop_var())
			{
			case x:
				cout << "x ";
				break;
			}
			break;
		}
	}
	return;
}
