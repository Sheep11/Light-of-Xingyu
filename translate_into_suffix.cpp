#include"translate_into_suffix.h"

using namespace std;


//���x�����֣�����-1�����򷵻ز�������Ӧ������
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

//�������ֶ�Ӧ�Ĳ�����
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

//������ȼ������x�ǲ������򷵻������ȼ������򷵻�-1,���ŵ����ȼ�Ϊ0
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

//�Ƚϲ�����x��y�����ȼ������x>y����1��x=y����0��x<y����-1
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

//��expת��Ϊ��׺���ʽ,���ڶ����ﷵ��
queue<word> translate_into_suffix(const string exp)
{
	queue<class word>suffix;//�洢��׺���ʽ�Ķ���
	stack<int>oper_stack;//��ʱ�洢��������ջ

	for (int i = 0; i < exp.size(); i++)
	{
		int type = check_type(exp[i]);//��ǰ�ַ�������

		if (type < 0)//���Ϊ����
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
			suffix.push(num_t);//�����׺ʽ����

			continue;
		}
		else//���Ϊ����
		{
			//���Ϊ����
			if (type == L_BRACKET)//����������ţ�ֱ���������ջ
			{
				oper_stack.push(L_BRACKET);
				continue;
			}
			else if (type == R_BRACKET)//����������ţ����Ͻ�������ջ��ջ����������׺ʽ���У�ֱ�����������ţ����������Ҳ��ջ���������׺ʽ���У�
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

			//���Ϊ�����
			if (oper_stack.empty())//���������ջΪ����ֱ����ջ
			{
				oper_stack.push(type);
			}
			else//���������ջ��Ϊ�գ�����ǰ������������ջ�������������ȼ�ʱ�����ϳ�ջ����󽫵�ǰ��������ջ
			{
				//������ջ�ǿ��ҵ�ǰ�����������ȼ������ڲ�����ջ���Ĳ�����
				while ((!oper_stack.empty()) && cmp_priority(exp[i], change_oper(oper_stack.top())) <= 0)
				{
					word tem_oper(1, oper_stack.top());
					suffix.push(tem_oper);
					oper_stack.pop();
				}

				oper_stack.push(type);//��ǰ���������׺ʽ����
			}

		}
	}

	//��������ջ��ʣ��Ĳ�����ȫ����������׺ʽ����
	while (!oper_stack.empty())
	{
		word tem_oper(1, oper_stack.top());
		suffix.push(tem_oper);
		oper_stack.pop();
	}

	return suffix;
}

