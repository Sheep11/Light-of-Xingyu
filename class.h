#pragma once
#include "libraryfile_and_define.h"

using namespace std;

class word
{
public:
	int type;//type = 0则表示数字，等于1表示操作符，等于-1表示错误的结果（未初始化、出现除以0、表达式错误）

	int num;//numerator分子
	int de;//denominator分母
	int oper;//操作符

	word();
	word(int type_t, int n, int d = 1);//类型，分子，分母

	void init();
	void init(int type_t, int n, int d = 1);//类型，分子，分母

	word& operator =(const word& source_word);//重载赋值运算符
};

//二叉树
class bi_tree
{
public:
	word value;
	bi_tree *l_child;
	bi_tree *r_child;

	bi_tree();
	bi_tree(word v);
	bi_tree(word v, bi_tree lc, bi_tree rc);

	void init();
	void init(word v);
	void init(word v, bi_tree lc, bi_tree rc);
	void init(word v, bi_tree* lc, bi_tree* rc);

	bi_tree& operator =(const bi_tree& source_tree);//重载赋值运算符
};

class tool
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

	void add_oper_into_exp(string& exp, int max_oper_sum);

	//将仅有操作符的表达式规范化
	void normalize_exp(string& oper_exp);

	//向仅有操作符的表达式添加数字
	void add_number_into_exp(string& oper_exp, int max_number);

};
