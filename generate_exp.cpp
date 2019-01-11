#include"generate_exp.h"

using namespace std;

//�Ƚ�����word�Ƿ���ͬ�������ͬ����1�����򷵻�0
int cmp_word(word a, word b)
{
	if (a.type != b.type)
		return 0;
	else
	{
		if (a.type == 0 && (a.num != b.num || a.de != b.de))
			return 0;

		if (a.type == 1 && (a.oper != b.oper))
			return 0;
	}
	return 1;
}

//�ж�a,b�������Ƿ��н���Ƚϵı�Ҫ������У�����1
int swap_flag(bi_tree a, bi_tree b)
{
	//���a,b�洢�ľ�Ϊ+����*
	if ((a.value.oper == PLUS && b.value.oper == PLUS) || (a.value.oper == MULTI && b.value.oper == MULTI))
		return 1;
	else
		return 0;

}

//�����������ͬ����1�����򷵻�0
int compare_tree(class bi_tree *a, class bi_tree *b)
{
	if (a == NULL && b == NULL)
		return 1;

	if ((a != NULL && b == NULL) || (a == NULL && b != NULL))
		return 0;

	if (a && b)
	{
		if (cmp_word(a->value, b->value))//�����ǰ�ڵ���ͬ
		{
			if (compare_tree(a->l_child, b->l_child))
				return compare_tree(a->r_child, b->r_child);
			else
			{
				if (swap_flag(*a, *b) && compare_tree(a->r_child, b->l_child))
					return compare_tree(a->l_child, b->r_child);
			}
		}
	}
	return 0;
}

//��׺���ʽת��Ϊ������
bi_tree translate_into_bi_tree(class queue<word> suffix)
{
	class stack<bi_tree> t_stack;//��ʱջ

	//��׺���зǿ�ʱ
	while (!suffix.empty())
	{
		word t_word;//��ʱ�洢�Ӷ����е�����Ԫ��
		t_word = suffix.front();
		suffix.pop();

		if (t_word.type == 0)//���Ϊ����
		{
			bi_tree t_tree(t_word);
			t_stack.push(t_tree);
		}
		else//���Ϊ������
		{

			bi_tree b = t_stack.top();
			t_stack.pop();
			bi_tree a = t_stack.top();
			t_stack.pop();

			bi_tree c(t_word, a, b);
			t_stack.push(c);
		}
	}

	return t_stack.top();
}

//������ת���ɲ�����
char translate_into_oper(int num)
{
	switch (num)
	{
	case PLUS:return '+'; break;
	case MINUS:return '-'; break;
	case MULTI:return '*'; break;
	case DIVID:return '/'; break;
	case POWER:return '^'; break;
	case L_BRACKET:return '('; break;
	case R_BRACKET:return ')'; break;
	default:
		break;
	}
}

int generate_exp(int N, int max_number, int max_oper_sum)
{
	string exp[MAX_SIZE];//���ʽ���ַ�����ʽ
	bi_tree tree[MAX_SIZE];//���ʽ�Ķ�������ʽ
	queue<word> suffix[MAX_SIZE];//��׺���ʽ
	word result[MAX_SIZE];//���ʽ�ļ�����

	int n = 0;//��ǰ��ʽ�ӱ��
	while (n < N)
	{
		srand(time(NULL));

		while (1)
		{
			//��Ӳ�����
			int oper_sum = rand() % max_oper_sum;
			while (oper_sum--)
			{
				exp[n] += translate_into_oper(rand() % 7 + 1);
			}

			//��������ƥ�䣬����в��Ϸ��ġ�)����ɾ�����ж���ġ�(�������ַ���ĩβ��ӡ�)����֮ƥ��
			stack<char>bracket_stack;
			for (int i = 0; i < exp[n].size(); i++)
			{

				if (exp[n][i] == '(')
				{
					bracket_stack.push('(');
					if (i > 0 && exp[n][i - 1] == ')')
					{
						exp[n] += translate_into_oper(rand() % 5 + 1);
					}
				}
				else
				{
					if (exp[n][i] == ')')
					{
						if (bracket_stack.empty())
						{
							exp[n].erase(i, 1);
							i--;
						}
						else
						{
							bracket_stack.pop();
						}

					}
				}
			}
			while (!bracket_stack.empty())
			{
				exp[n] += ')';
				bracket_stack.pop();
			}

			//���ַ������������
			for (int i = 0; i < exp[n].size(); i++)
			{
				if ((exp[n][i] >= '0' && exp[n][i] <= '9') || (exp[n][i] == '(' || exp[n][i] == ')'))
					continue;
				else
				{
					if (!(exp[n][i + 1] >= '0'&&exp[n][i + 1] <= '9'))
						exp[n].insert(i + 1, to_string(rand() % (max_number + 1)));

					if (i > 0 && exp[n][i - 1] != ')')
						exp[n].insert(i, to_string(rand() % (max_number + 1)));
				}
			}

			//ת��Ϊ��׺���ʽ
			translate_into_suffix(exp[n], suffix[n]);

			calculate_suffix(suffix[n], result[n]);//������ʽ��ֵ
			if (result[n].type == -1)//������ʽ�����������ɱ��ʽ
				continue;
			else
			{
				//��⵱ǰ���ʽ�Ƿ���֮ǰ���ɵı��ʽ�ظ�
				int repeat_flag = 0;
				tree[n] = translate_into_bi_tree(suffix[n]);
				for (int i = 0; i < n; i++)
				{
					if (compare_tree(&tree[i], &tree[n]))
					{
						repeat_flag = 1;
						break;
					}
				}

				if (repeat_flag == 1)//��֮ǰ���ɵı��ʽ�ظ�����������
					continue;
				else
					break;
			}

		}
		n++;
	}
	return n;
}