#include"generate_exp.h"

using namespace std;

//int check_repeat(bi_tree tree_array[], bi_tree tree, int n)
//{
//	tool Tool;
//	for (int i = 0; i < n; i++)
//	{
//		if (Tool.compare_tree(&tree, &tree_array[i]) == 1)
//		{
//			return 1;
//		}
//	}
//
//	return 0;
//}

//生成N个表达式,如果成功返回N，max_number为表达式中数字的最大值，max_oper_sum为表达式中最多含有的运算符的数量
int generate_exp(int N, int max_number, int max_oper_sum)
{	
	srand(time(NULL));

	string exp[MAX_SIZE];//表达式的字符串形式
	bi_tree tree[MAX_SIZE];//表达式的二叉树形式
	queue<word> suffix[MAX_SIZE];//后缀表达式
	word result[MAX_SIZE];//表达式的计算结果


	tool Tool;
	int n = 0;//当前的式子编号
	while (n < N)
	{
		while (1)
		{
			//添加操作符
			Tool.add_oper_into_exp(exp[n], max_oper_sum);

			//规范化
			Tool.normalize_exp(exp[n]);

			//添加数字
			Tool.add_number_into_exp(exp[n], max_number);

			//switch (n)
			//{
			//	case 0:exp[n] = "1+2+3"; break;
			//	case 1:exp[n] = "3+2+1"; break;
			//	//case 2:exp[n] = "3+2+1"; break;
			//	default:
			//		break;
			//}

			//转化为后缀表达式
			suffix[n] = translate_into_suffix(exp[n]);

			
			result[n] = calculate_suffix(suffix[n]);//计算后缀表达式的值
			if (result[n].type == -1)//如果表达式有误，重新生成表达式
			{
				//清空exp[n],suffix[n],result[n],tree[n]
				exp[n].clear();
				result[n].init();
				tree[n].init();
				while (!suffix[n].empty())
					suffix[n].pop();

				continue;
			}
			else
			{
				tree[n] = Tool.translate_into_bi_tree(suffix[n]);

				int repeat_flag = 0;
				for (int i = 0; i < n; i++)
				{
					if (Tool.compare_tree(&tree[n], &tree[i]) == 1)
					{
						//清空exp[n],suffix[n],result[n],tree[n]
						exp[n].clear();
						result[n].init();
						tree[n].init();
						while (!suffix[n].empty())
							suffix[n].pop();
						repeat_flag = 1;
						break;
					}
				}
				if (repeat_flag == 1)
					continue;
				else
					break;
			}
		}


		cout << exp[n] << endl;
		n++;
	}
	return n;
}