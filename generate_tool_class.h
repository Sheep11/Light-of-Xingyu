#pragma once
#include"class.h"
#include"libraryfile_and_define.h"

class generate_tool
{
public:

	//后缀表达式转换为二叉树
	bi_tree translate_into_bi_tree(class queue<word> suffix);

	//比较两个word是否相同，如果相同返回1，否则返回0
	int cmp_word(word a, word b);

	//判断a,b的子树是否有交叉比较的必要，如果有，返回1
	int swap_flag(bi_tree a, bi_tree b);

	//如果两棵树相同返回1，否则返回0
	int compare_tree(bi_tree *a, bi_tree *b);

	//将数字转化成操作符
	char translate_into_oper(int num);

	//添加操作符
	void add_oper_into_exp(string& exp, int max_oper_sum);

	//将仅有操作符的表达式规范化
	void normalize_exp(string& oper_exp);

	//向仅有操作符的表达式添加数字
	void add_number_into_exp(string& oper_exp, int max_number);

	//限制结果的范围或者格式
	int restrict_result(string exp, word result);

	//检测是否有重复，如果有，返回1，没有返回0
	int is_repeat(word result_array[], word result, bi_tree tree_array[], bi_tree tree, int n);

	//清除当前记录
	void clear_trail(string& exp, queue<word>& suffix, word& result, bi_tree& tree);

	//改变显示乘方的方式
	void change_show_way(string& exp);

	vector<formula> generate_exp(int N = 1000, int max_number = 10, int max_oper_sum = 10, int show_way = 0);
};