#include"calculate_suffix.h"
using namespace std;

//����a,b���������
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

//����a op b�ļ���������������˳���0����ָ����Ϊ�Ǹ����������ص�result.type = -1
word calculate(word a, word op, word b)
{
	int an = a.num, //a�ķ���
		ad = a.de;//a�ķ�ĸ
	int bn = b.num, //b�ķ���
		bd = b.de;//b�ķ�ĸ

	word result;	//���
	int rn = 0, //����ķ���
		rd = 0;//����ķ�ĸ

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
		if (bd != 1 || bn < 0)//ָ���ķ�ĸ��Ϊ1���߷���С��0
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

	//����
	int g = gcd(rn, rd);//����ķ��ӣ���ĸ���������
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

//���غ�׺���ʽsuffix�ļ�������������ʽ����ȷ�����ص�result.type = -1
word calculate_suffix(queue<word> suffix)
{
	word result;
	class stack<word> num_stack;//����ջ

	//��׺���зǿ�ʱ
	while (!suffix.empty())
	{
		word t_word;//��ʱ�洢�Ӷ����е�����Ԫ��
		t_word = suffix.front();
		suffix.pop();

		if (t_word.type == 0)//���Ϊ����
		{
			num_stack.push(t_word);//������ջ
		}
		else//���Ϊ������
		{
			//������ջ�е����������֣��������������������ջ

			word b = num_stack.top();
			num_stack.pop();
			word a = num_stack.top();
			num_stack.pop();

			word c = calculate(a, t_word, b);
			if (c.type == -1)//������������ִ���
			{
				result.init(-1, 0, 0);
				return result;
			}
			else
				num_stack.push(c);
		}
	}

	//�����������ջ��ֻ��һ�����֣�˵�����ʽ��ȷ���������
	if (num_stack.size() == 1)
		return num_stack.top();
	else
	{
		result.init(-1, 0, 0);
		return result;
	}

}