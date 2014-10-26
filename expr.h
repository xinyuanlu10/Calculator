#include "postfix.h"
class expr{
private:
	expression e;
public:
	expr(){};
	expr(const char*);
	~expr(){};

	void input_expr(const char*);
	double result();
};
