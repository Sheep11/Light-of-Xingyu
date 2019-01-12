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

