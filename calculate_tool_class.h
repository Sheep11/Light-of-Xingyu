#include "libraryfile_and_define.h"
#include "class.h"

class calculate_tool
{
public:
	//返回a,b的最大公因数
	int gcd(int a, int b);

	//返回a op b的计算结果。如果出现了除以0或者指数不为非负整数，返回的result.type = -1
	word calculate(word a, word op, word b);

	//返回后缀表达式suffix的计算结果，如果表达式不正确，返回的result.type = -1
	word calculate_suffix(std::queue<word> suffix);
};

