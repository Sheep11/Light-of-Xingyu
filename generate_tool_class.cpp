#include"libraryfile_and_define.h"
#include"generate_tool_class.h"
#include"calculate_tool_class.h"
#include"translate_tool_class.h"

//���ɹ�����
//��׺���ʽת��Ϊ������
bi_tree generate_tool::translate_into_bi_tree(class queue<word> suffix)
{
	stack<bi_tree> t_stack;//��ʱջ

	//��׺���зǿ�ʱ
	while (!suffix.empty())
	{
		word t_word;//��ʱ�洢�Ӷ����е�����Ԫ��
		t_word = suffix.front();
		suffix.pop();
		//bi_tree *a = new bi_tree();

		if (t_word.type == 0)//���Ϊ����
		{
			bi_tree t_tree(t_word);
			t_stack.push(t_tree);
		}
		else//���Ϊ������
		{
			bi_tree* b = new bi_tree();
			*b = t_stack.top();
			t_stack.pop();

			bi_tree* a = new bi_tree();
			*a = t_stack.top();
			t_stack.pop();

			bi_tree* c = new bi_tree();
			c->init(t_word, a, b);
			t_stack.push(*c);

		}

	}

	bi_tree return_value = t_stack.top();
	return return_value;
}

//�Ƚ�����word�Ƿ���ͬ�������ͬ����1�����򷵻�0
int generate_tool::cmp_word(word a, word b)
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
int generate_tool::swap_flag(bi_tree a, bi_tree b)
{
	//���a,b�洢�ľ�Ϊ+����*
	if ((a.value.oper == PLUS && b.value.oper == PLUS) || (a.value.oper == MULTI && b.value.oper == MULTI))
		return 1;
	else
		return 0;
}

//�����������ͬ����1�����򷵻�0
int generate_tool::compare_tree(bi_tree *a, bi_tree *b)
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
};

//������ת���ɲ�����
char generate_tool::translate_into_oper(int num)
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

//��Ӳ�����
void generate_tool::add_oper_into_exp(string& exp, int max_oper_sum)
{
	int oper_sum = rand() % max_oper_sum + 1;//��Ҫ��ӵĲ���������
	for (int i = 1; i <= oper_sum; i++)
	{
		exp += translate_into_oper(rand() % 7 + 1);
	}
}

//�����в������ı��ʽ�淶��
void generate_tool::normalize_exp(string& oper_exp)
{
	while(oper_exp[0] == '(')
		oper_exp.erase(0, 1);

	//��������ƥ�䣬����в��Ϸ���)��ɾ�����ж����(�����ַ���ĩβ���)��֮ƥ��
	stack<char>bracket_stack;
	for (int i = 0; i < oper_exp.size(); i++)
	{
		if (oper_exp[i] == '(')
		{
			bracket_stack.push('(');
		}
		else
		{
			if (oper_exp[i] == ')')
			{
				if (bracket_stack.empty())//�����ʱ)û����֮ƥ���(,ɾ��)
				{
					oper_exp.erase(i, 1);
					i--;
				}
				else
				{
					bracket_stack.pop();//����Ӧ��(��ջ
				}

			}
		}
	}

	//ջ����(,���)���ַ���ĩβ��֮ƥ��
	while (!bracket_stack.empty())
	{
		oper_exp += ')';
		bracket_stack.pop();
	}

	//��)��(����(��)֮��û�в������������м����һ��������
	for (int i = 0; i < oper_exp.size(); i++)
	{
		if (oper_exp[i] == '(')
		{
			if (i > 0 && oper_exp[i - 1] == ')')//���(��ǰһ��Ϊ)
			{
				//���м����һ��������
				string tem;
				tem += translate_into_oper(rand() % 5 + 1);
				oper_exp.insert(i, tem);
			}
		}
		else
		{
			if (oper_exp[i] == ')')
			{
				if (oper_exp[i - 1] == '(')// )ǰһ��Ϊ(
				{
					//���м����һ��������
					string tem;
					tem += translate_into_oper(rand() % 5 + 1);
					oper_exp.insert(i, tem);
				}
			}
		}
	}

	//��֤���ʽ��������һ��������
	if (oper_exp.size() == 0)
	{
		oper_exp += translate_into_oper(rand() % 5 + 1);
	}
}

//����в������ı��ʽ������֣����ֵ����ֵΪmax_number
void generate_tool::add_number_into_exp(string& oper_exp, int max_number)
{
	//���ַ������������
	if (oper_exp[0] != '(')
		oper_exp.insert(0, to_string(rand() % (max_number + 1)));
	else
		oper_exp.insert(1, to_string(rand() % (max_number + 1)));

	for (int i = 1; i < oper_exp.size(); i++)
	{
		if ((oper_exp[i] >= '0' && oper_exp[i] <= '9') || oper_exp[i] == ')')
			continue;
		else
		{
			if ((i + 1 < oper_exp.size()) && oper_exp[i + 1] == '(')
				continue;

			if (oper_exp[i] != '^')
				oper_exp.insert(i + 1, to_string(rand() % (max_number + 1)));
			else
				oper_exp.insert(i + 1, to_string(rand() % 2 + 1));
		}
	}
}

//���ƽ���ķ�Χ���߸�ʽ
int generate_tool::restrict_result(string exp, word result)
{
	if (result.type == -1)
		return 0;

	if (exp == result.str_word())
		return 0;
	
	if (result.num > 1000 || result.de > 100 || result.num * (-1) > 1000 || result.de * (-1) > 100)
		return 0;

	return 1;
}

//����Ƿ����ظ�������У�����1��û�з���0
int generate_tool::is_repeat(word result_array[], word result, bi_tree tree_array[], bi_tree tree, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (!(result_array[i].num == result.num && result_array[i].de == result.de))
			continue;

		if (compare_tree(&tree, &tree_array[i]) == 1)
		{
			return 1;
		}
	}
	return 0;
}

//�����ǰ��¼
void generate_tool::clear_trail(string& exp, queue<word>& suffix, word& result, bi_tree& tree)
{
	//���exp[n],suffix[n],result[n],tree[n]
	exp.clear();
	result.init();
	tree.init();
	while (!suffix.empty())
		suffix.pop();
}

//�ı���ʾ�˷��ķ�ʽ
void generate_tool::change_show_way(string& exp)
{
	for (int i = 0; i < exp.size(); i++)
	{
		if (exp[i] == '^')
		{
			exp.erase(i, 1);
			exp.insert(i, "**");
		}
	}
}

//����N�����ʽ�ʹ𰸣�����ջ�з���
//max_numberΪ���ʽ�����ֵ����ֵ��
//max_oper_sumΪ���ʽ����ຬ�е������������
//show_wayΪ��ʾ�˷���ģʽ��Ϊ0��ʾ^��Ϊ1��ʾ**
vector<formula> generate_tool::generate_exp(int N, int max_number, int max_oper_sum, int show_way)
{
	vector<formula>	F_vector;//��Ҫ���ص�����
	if (N > MAX_SIZE)
		return F_vector;

	srand(time(NULL));

	string exp[MAX_SIZE];//���ʽ���ַ�����ʽ
	bi_tree tree[MAX_SIZE];//���ʽ�Ķ�������ʽ
	queue<word> suffix[MAX_SIZE];//��׺���ʽ
	word result[MAX_SIZE];//���ʽ�ļ�����


	translate_tool T_tool;
	calculate_tool C_tool;
	generate_tool G_tool;

	int n = 0;//��ǰ��ʽ�ӱ��
	while (n < N)
	{
		G_tool.add_oper_into_exp(exp[n], max_oper_sum);//��Ӳ�����
	
		G_tool.normalize_exp(exp[n]);//�淶��
		
		G_tool.add_number_into_exp(exp[n], max_number);//�������

		suffix[n] = T_tool.translate_into_suffix(exp[n]);//ת��Ϊ��׺���ʽ

		result[n] = C_tool.calculate_suffix(exp[n]);//�����׺���ʽ��ֵ

		if (G_tool.restrict_result(exp[n], result[n]) == 0)//���������������Ҫ���������ɱ��ʽ
		{
			G_tool.clear_trail(exp[n], suffix[n], result[n], tree[n]);//�����¼
			continue;
		}
		else//�������Ҫ�󣬼���Ƿ���֮ǰ���ɵı��ʽ�ظ�
		{
			tree[n] = G_tool.translate_into_bi_tree(suffix[n]);//�ɺ�׺���ʽ���ɶ�����

			int repeat_flag = G_tool.is_repeat(result, result[n], tree, tree[n], n);
			if (repeat_flag == 1)//�ظ�
			{
				G_tool.clear_trail(exp[n], suffix[n], result[n], tree[n]);//�����¼
				continue;
			}
		}

		//���show_way = 1���ѱ��ʽ�е�^����**
		if (show_way == 1)
			G_tool.change_show_way(exp[n]);

		//���ʽ�ʹ𰸴���������
		formula F;
		F.init(exp[n], result[n].str_word());
		F_vector.push_back(F);

		n++;
	}

	return F_vector;
}
