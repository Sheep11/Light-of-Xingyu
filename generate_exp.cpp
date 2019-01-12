#include"generate_exp.h"
#include"calculate_tool_class.h"
#include"translate_tool_class.h"
#include"generate_tool_class.h"

using namespace std;

//生成N个表达式,如果成功返回N，max_number为表达式中数字的最大值，max_oper_sum为表达式中最多含有的运算符的数量
int generate_exp(int N, int max_number, int max_oper_sum, int show_way)
{	
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
		//添加操作符
		G_tool.add_oper_into_exp(exp[n], max_oper_sum);

		//规范化
		G_tool.normalize_exp(exp[n]);

		//添加数字
		G_tool.add_number_into_exp(exp[n], max_number);

		//转化为后缀表达式
		suffix[n] = T_tool.translate_into_suffix(exp[n]);
	
		result[n] = C_tool.calculate_suffix(suffix[n]);//计算后缀表达式的值
		if (result[n].type == -1)//如果表达式有误，重新生成表达式
		{
			G_tool.clear_trail(exp[n], suffix[n], result[n], tree[n]);//清除记录
			continue;
		}
		else//表达式无误，检测是否与之前生成的表达式重复
		{
			tree[n] = G_tool.translate_into_bi_tree(suffix[n]);//由后缀表达式生成二叉树

			int repeat_flag = G_tool.is_repeat(tree, tree[n], n);
			if (repeat_flag == 1)//重复
			{
				G_tool.clear_trail(exp[n], suffix[n], result[n], tree[n]);//清除记录
				continue;
			}
		}

		if (show_way == 1)
			G_tool.change_show_way(exp[n]);

		cout << exp[n] << endl;
		n++;
	}
	return n;
}
