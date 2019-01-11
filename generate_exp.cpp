#include"generate_exp.h"

using namespace std;

//比较两个word是否相同，如果相同返回1，否则返回0
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

//判断a,b的子树是否有交叉比较的必要，如果有，返回1
int swap_flag(bi_tree a, bi_tree b)
{
	//如果a,b存储的均为+或者*
	if ((a.value.oper == PLUS && b.value.oper == PLUS) || (a.value.oper == MULTI && b.value.oper == MULTI))
		return 1;
	else
		return 0;

}

//如果两棵树相同返回1，否则返回0
int compare_tree(class bi_tree *a, class bi_tree *b)
{
	if (a == NULL && b == NULL)
		return 1;

	if ((a != NULL && b == NULL) || (a == NULL && b != NULL))
		return 0;

	if (a && b)
	{
		if (cmp_word(a->value, b->value))//如果当前节点相同
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

//后缀表达式转换为二叉树
bi_tree translate_into_bi_tree(class queue<word> suffix)
{
	class stack<bi_tree> t_stack;//临时栈

	//后缀队列非空时
	while (!suffix.empty())
	{
		word t_word;//临时存储从队列中弹出的元素
		t_word = suffix.front();
		suffix.pop();

		if (t_word.type == 0)//如果为数字
		{
			bi_tree t_tree(t_word);
			t_stack.push(t_tree);
		}
		else//如果为操作符
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

//将数字转化成操作符
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
	string exp[MAX_SIZE];//表达式的字符串形式
	bi_tree tree[MAX_SIZE];//表达式的二叉树形式
	queue<word> suffix[MAX_SIZE];//后缀表达式
	word result[MAX_SIZE];//表达式的计算结果

	int n = 0;//当前的式子编号
	while (n < N)
	{
		srand(time(NULL));

		while (1)
		{
			//添加操作符
			int oper_sum = rand() % max_oper_sum;
			while (oper_sum--)
			{
				exp[n] += translate_into_oper(rand() % 7 + 1);
			}

			//进行括号匹配，如果有不合法的“)”则删除，有多出的“(”则在字符串末尾添加“)”与之匹配
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

			//向字符串中添加数字
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

			//转化为后缀表达式
			translate_into_suffix(exp[n], suffix[n]);

			calculate_suffix(suffix[n], result[n]);//计算表达式的值
			if (result[n].type == -1)//如果表达式有误，重新生成表达式
				continue;
			else
			{
				//检测当前表达式是否与之前生成的表达式重复
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

				if (repeat_flag == 1)//与之前生成的表达式重复，重新生成
					continue;
				else
					break;
			}

		}
		n++;
	}
	return n;
}