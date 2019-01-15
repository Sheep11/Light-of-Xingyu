#include"libraryfile_and_define.h"
#include"generate_tool_class.h"
#include"calculate_tool_class.h"
#include"translate_tool_class.h"

//生成工具类
//后缀表达式转换为二叉树
bi_tree generate_tool::translate_into_bi_tree(class queue<word> suffix)
{
	stack<bi_tree> t_stack;//临时栈

	//后缀队列非空时
	while (!suffix.empty())
	{
		word t_word;//临时存储从队列中弹出的元素
		t_word = suffix.front();
		suffix.pop();
		//bi_tree *a = new bi_tree();

		if (t_word.type == 0)//如果为数字
		{
			bi_tree t_tree(t_word);
			t_stack.push(t_tree);
		}
		else//如果为操作符
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

//比较两个word是否相同，如果相同返回1，否则返回0
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

//判断a,b的子树是否有交叉比较的必要，如果有，返回1
int generate_tool::swap_flag(bi_tree a, bi_tree b)
{
	//如果a,b存储的均为+或者*
	if ((a.value.oper == PLUS && b.value.oper == PLUS) || (a.value.oper == MULTI && b.value.oper == MULTI))
		return 1;
	else
		return 0;
}

//如果两棵树相同返回1，否则返回0
int generate_tool::compare_tree(bi_tree *a, bi_tree *b)
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
};

//将数字转化成操作符
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

//添加操作符
void generate_tool::add_oper_into_exp(string& exp, int max_oper_sum)
{
	int oper_sum = rand() % max_oper_sum + 1;//将要添加的操作符数量
	for (int i = 1; i <= oper_sum; i++)
	{
		exp += translate_into_oper(rand() % 7 + 1);
	}
}

//将仅有操作符的表达式规范化
void generate_tool::normalize_exp(string& oper_exp)
{
	while(oper_exp[0] == '(')
		oper_exp.erase(0, 1);

	//进行括号匹配，如果有不合法的)则删除，有多出的(则在字符串末尾添加)与之匹配
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
				if (bracket_stack.empty())//如果此时)没有与之匹配的(,删除)
				{
					oper_exp.erase(i, 1);
					i--;
				}
				else
				{
					bracket_stack.pop();//将对应的(出栈
				}

			}
		}
	}

	//栈内有(,添加)到字符串末尾与之匹配
	while (!bracket_stack.empty())
	{
		oper_exp += ')';
		bracket_stack.pop();
	}

	//若)、(或者(、)之间没有操作符，则在中间添加一个操作符
	for (int i = 0; i < oper_exp.size(); i++)
	{
		if (oper_exp[i] == '(')
		{
			if (i > 0 && oper_exp[i - 1] == ')')//如果(的前一个为)
			{
				//在中间插入一个操作符
				string tem;
				tem += translate_into_oper(rand() % 5 + 1);
				oper_exp.insert(i, tem);
			}
		}
		else
		{
			if (oper_exp[i] == ')')
			{
				if (oper_exp[i - 1] == '(')// )前一个为(
				{
					//在中间插入一个操作符
					string tem;
					tem += translate_into_oper(rand() % 5 + 1);
					oper_exp.insert(i, tem);
				}
			}
		}
	}

	//保证表达式中至少有一个操作符
	if (oper_exp.size() == 0)
	{
		oper_exp += translate_into_oper(rand() % 5 + 1);
	}
}

//向仅有操作符的表达式添加数字，数字的最大值为max_number
void generate_tool::add_number_into_exp(string& oper_exp, int max_number)
{
	//向字符串中添加数字
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

//限制结果的范围或者格式
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

//检测是否有重复，如果有，返回1，没有返回0
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

//清除当前记录
void generate_tool::clear_trail(string& exp, queue<word>& suffix, word& result, bi_tree& tree)
{
	//清空exp[n],suffix[n],result[n],tree[n]
	exp.clear();
	result.init();
	tree.init();
	while (!suffix.empty())
		suffix.pop();
}

//改变显示乘方的方式
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

//生成N个表达式和答案，存在栈中返回
//max_number为表达式中数字的最大值，
//max_oper_sum为表达式中最多含有的运算符的数量
//show_way为显示乘方的模式，为0显示^，为1显示**
vector<formula> generate_tool::generate_exp(int N, int max_number, int max_oper_sum, int show_way)
{
	vector<formula>	F_vector;//将要返回的容器
	if (N > MAX_SIZE)
		return F_vector;

	srand(time(NULL));

	string exp[MAX_SIZE];//表达式的字符串形式
	bi_tree tree[MAX_SIZE];//表达式的二叉树形式
	queue<word> suffix[MAX_SIZE];//后缀表达式
	word result[MAX_SIZE];//表达式的计算结果


	translate_tool T_tool;
	calculate_tool C_tool;
	generate_tool G_tool;

	int n = 0;//当前的式子编号
	while (n < N)
	{
		G_tool.add_oper_into_exp(exp[n], max_oper_sum);//添加操作符
	
		G_tool.normalize_exp(exp[n]);//规范化
		
		G_tool.add_number_into_exp(exp[n], max_number);//添加数字

		suffix[n] = T_tool.translate_into_suffix(exp[n]);//转化为后缀表达式

		result[n] = C_tool.calculate_suffix(exp[n]);//计算后缀表达式的值

		if (G_tool.restrict_result(exp[n], result[n]) == 0)//如果计算结果不符合要求，重新生成表达式
		{
			G_tool.clear_trail(exp[n], suffix[n], result[n], tree[n]);//清除记录
			continue;
		}
		else//结果符合要求，检测是否与之前生成的表达式重复
		{
			tree[n] = G_tool.translate_into_bi_tree(suffix[n]);//由后缀表达式生成二叉树

			int repeat_flag = G_tool.is_repeat(result, result[n], tree, tree[n], n);
			if (repeat_flag == 1)//重复
			{
				G_tool.clear_trail(exp[n], suffix[n], result[n], tree[n]);//清除记录
				continue;
			}
		}

		//如果show_way = 1，把表达式中的^换成**
		if (show_way == 1)
			G_tool.change_show_way(exp[n]);

		//表达式和答案存入容器中
		formula F;
		F.init(exp[n], result[n].str_word());
		F_vector.push_back(F);

		n++;
	}

	return F_vector;
}
