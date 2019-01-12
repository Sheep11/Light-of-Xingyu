#include"translate_into_suffix.h"

using namespace std;


//如果x是数字，返回-1，否则返回操作符对应的数字
int check_type(const char x)
{
	if (x == '+')
		return 1;
	if (x == '-')
		return 2;
	if (x == '*')
		return 3;
	if (x == '/')
		return 4;
	if (x == '^')
		return 5;

	if (x == '(')
		return 6;
	if (x == ')')
		return 7;

	return -1;
}

//返回数字对应的操作符
char change_oper(const int oper)
{
	switch (oper)
	{
	case 1:return '+'; break;
	case 2:return '-'; break;
	case 3:return '*'; break;
	case 4:return '/'; break;
	case 5:return '^'; break;
	case 6:return '('; break;
	case 7:return ')'; break;

	default:
		break;
	}


}

//检测优先级。如果x是操作符则返回其优先级，否则返回-1,括号的优先级为0
int check_priority(const char x)
{
	if (x == '+')
		return 1;
	if (x == '-')
		return 1;
	if (x == '*')
		return 2;
	if (x == '/')
		return 2;
	if (x == '^')
		return 3;
	if (x == '(')
		return 0;
	if (x == ')')
		return 0;

	return -1;
}

//比较操作符x和y的优先级。如果x>y返回1，x=y返回0，x<y返回-1
int cmp_priority(const char x, const char y)
{
	int x_p = check_priority(x),
		y_p = check_priority(y);

	if (x_p > y_p || (x_p == 3 && y_p == 3))
		return 1;

	if (x_p < y_p)
		return -1;

	if (x_p == y_p)
		return 0;
}

//将exp转化为后缀表达式,存在队列里返回
queue<word> translate_into_suffix(const string exp)
{
	queue<class word>suffix;//存储后缀表达式的队列
	stack<int>oper_stack;//暂时存储操作符的栈

	for (int i = 0; i < exp.size(); i++)
	{
		int type = check_type(exp[i]);//当前字符的类型

		if (type < 0)//如果为数字
		{
			int num = exp[i] - '0';

			for (i = i + 1; i < exp.size(); i++)
			{
				if (check_type(exp[i]) < 0)
					num = num * 10 + (exp[i] - '0');
				else
				{
					i--;
					break;
				}
			}

			word num_t(0, num);
			suffix.push(num_t);//加入后缀式队列

			continue;
		}
		else//如果为符号
		{
			//如果为括号
			if (type == L_BRACKET)//如果是左括号，直接入操作符栈
			{
				oper_stack.push(L_BRACKET);
				continue;
			}
			else if (type == R_BRACKET)//如果是右括号，不断将操作符栈的栈顶弹出到后缀式队列，直到遇到左括号（最后将左括号也出栈但不加入后缀式队列）
			{
				while (oper_stack.top() != L_BRACKET)
				{
					word tem_oper(1, oper_stack.top());
					suffix.push(tem_oper);
					oper_stack.pop();
				}
				oper_stack.pop();
				continue;
			}

			//如果为运算符
			if (oper_stack.empty())//如果操作符栈为空则直接入栈
			{
				oper_stack.push(type);
			}
			else//如果操作符栈不为空，当当前操作符不高于栈顶操作符的优先级时，不断出栈。最后将当前操作符入栈
			{
				//操作符栈非空且当前操作符的优先级不高于操作符栈顶的操作符
				while ((!oper_stack.empty()) && cmp_priority(exp[i], change_oper(oper_stack.top())) <= 0)
				{
					word tem_oper(1, oper_stack.top());
					suffix.push(tem_oper);
					oper_stack.pop();
				}

				oper_stack.push(type);//当前操作符入后缀式队列
			}

		}
	}

	//将操作符栈中剩余的操作符全部弹出到后缀式队列
	while (!oper_stack.empty())
	{
		word tem_oper(1, oper_stack.top());
		suffix.push(tem_oper);
		oper_stack.pop();
	}

	return suffix;
}

