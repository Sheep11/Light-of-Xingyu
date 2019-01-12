#include"generate_exp.h"

using namespace std;


//生成N个表达式,如果成功返回N，
//max_number为表达式中数字的最大值，默认为10
//max_oper_sum为表达式中最多含有的运算符的数量，默认为5
//show_way为乘法的显示方式，为0时显示为^，为1时显示为**，默认为0
int generate_exp(int N, int max_number, int max_oper_sum, int show_way)
{	
	srand(time(NULL));

	string exp[MAX_SIZE];//表达式的字符串形式
	queue<word> suffix[MAX_SIZE];//后缀表达式
	word result[MAX_SIZE];//表达式的计算结果
	bi_tree tree[MAX_SIZE];//表达式的二叉树形式

	tool Tool;
	int n = 0;//当前的式子编号
	while (n < N)
	{	
		Tool.add_oper_into_exp(exp[n], max_oper_sum);//添加操作符
		
		Tool.normalize_exp(exp[n]);//规范化
		
		Tool.add_number_into_exp(exp[n], max_number);//添加数字

		switch (n)
		{
			case 0:exp[n] = "1+2+3"; break;
			case 1:exp[n] = "3+(2+1)"; break;
			//case 2:exp[n] = "3+2+1"; break;
			default:
				break;
		}

			
		suffix[n] = translate_into_suffix(exp[n]);//转化为后缀表达式

		result[n] = calculate_suffix(suffix[n]);//计算后缀表达式的值

		if (result[n].type == -1)//如果表达式有误，清除当前记录，重新生成表达式
		{
			Tool.clear_trail(exp[n], suffix[n], result[n], tree[n]);//清除当前记录
			continue;
		}
		else//表达式无误，检测是否与之前生成的表达式重复
		{
			//后缀式转化为二叉树
			tree[n] = Tool.translate_into_bi_tree(suffix[n]);

			//检测是否和之前的式子重复
			int repeat_flag = Tool.is_repeat(tree, tree[n], n);
			if (repeat_flag == 1)//重复，清除记录，重新生成
			{
				Tool.clear_trail(exp[n], suffix[n], result[n], tree[n]);//清除当前记录
				continue;
			}
		}

		//如果show_way = 1，把所有^替换为**
		if (show_way == 1)
			Tool.change_show_way(exp[n]);

		cout << exp[n] << endl;
		n++;
	}
	return n;
}