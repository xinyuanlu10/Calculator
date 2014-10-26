#include "expr.h"
expr::expr(const char* input)
{
	input_expr(input);
}

void expr::input_expr(const char* input)
{

	string temp(input);
	int pos;
	pos = temp.find('x');
	if (pos != temp.npos)
	{
		throw string("表达式包含未知符号!\n");
	}
	e.input_exp(temp.c_str());
}

double expr::result()
{
	return e.result(0.0);
}
