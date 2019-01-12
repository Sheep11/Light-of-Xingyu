#include"calculate_suffix.h"
using namespace std;

//返回a,b的最大公因数
int gcd(int a, int b)
{
	if (a == 0 || b == 0)
		return 0;

	int c;
	if (a < b)
	{
		a = a + b;
		b = a - b;
		a = a - b;
	}
	c = a % b;
	while (a%b != 0)
	{
		a = b;
		b = c;
		c = a % b;
	}
	return b;
}

//返回a op b的计算结果。如果出现了除以0或者指数不为非负整数，返回的result.type = -1
word calculate(word a, word op, word b)
{
	int an = a.num, //a的分子
		ad = a.de;//a的分母
	int bn = b.num, //b的分子
		bd = b.de;//b的分母

	word result;	//结果
	int rn = 0, //结果的分子
		rd = 0;//结果的分母

	switch (op.oper)
	{
	case PLUS:
	{
		rn = an * bd + bn * ad;
		rd = ad * bd;
	}; break;

	case MINUS:
	{
		rn = an * bd - bn * ad;
		rd = ad * bd;
	}; break;

	case MULTI:
	{
		rn = an * bn;
		rd = ad * bd;
	}; break;

	case DIVID:
	{
		rn = an * bd;
		rd = ad * bn;

		if (rd == 0)
		{
			result.init(-1, 0, 0);
			return result;
		}
	}; break;

	case POWER:
	{
		if (bd != 1 || bn < 0)//指数的分母不为1或者分子小于0
		{
			result.init(-1, 0, 0);
			return result;
		}
		else
		{
			rn = rd = 1;
			for (int i = 1; i <= bn; i++)
			{
				rn *= an;
				rd *= ad;
			}
		}

	}; break;

	default:
		break;
	}

	//化简
	int g = gcd(rn, rd);//结果的分子，分母的最大公因数
	if (g != 0)
	{
		rn /= g;
		rd /= g;
	}
	if (rd < 0)
		rn *= -1, rd *= -1;

	result.init(0, rn, rd);

	return result;
}

//返回后缀表达式suffix的计算结果，如果表达式不正确，返回的result.type = -1
word calculate_suffix(queue<word> suffix)
{
	word result;
	class stack<word> num_stack;//数字栈

	//后缀队列非空时
	while (!suffix.empty())
	{
		word t_word;//临时存储从队列中弹出的元素
		t_word = suffix.front();
		suffix.pop();

		if (t_word.type == 0)//如果为数字
		{
			num_stack.push(t_word);//入数字栈
		}
		else//如果为操作符
		{
			//从数字栈中弹出两个数字，计算结果，将结果入数字栈

			word b = num_stack.top();
			num_stack.pop();
			word a = num_stack.top();
			num_stack.pop();

			word c = calculate(a, t_word, b);
			if (c.type == -1)//如果计算结果出现错误
			{
				result.init(-1, 0, 0);
				return result;
			}
			else
				num_stack.push(c);
		}
	}

	//如果最终数字栈里只有一个数字，说明表达式正确，否则错误
	if (num_stack.size() == 1)
		return num_stack.top();
	else
	{
		result.init(-1, 0, 0);
		return result;
	}

}