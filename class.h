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

	string str_word();
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

//题目和答案
class formula
{
public:
	int id;
	string problem;
	string answer;

	formula();
	formula(string P, string A);
	formula(const formula& F);

	void init();
	void init(string P, string A);

	formula& operator =(const formula& source_formula);//重载赋值运算符

	int check(string u_answer);
};


class generator
{
private:
	vector<formula> formula_vector;//存储题目和答案的容器
	int sum;//存储的数量
	int index;//没有使用过的第一个题目和答案的编号（编号数值等于下标+1）
public:
	generator();

	//输出式子到文件path中，默认为problem_file.txt
	void output_into_file(string exp, string path = "problem_file.txt");

	//获取一个式子及答案,返回值为formula对象
	//默认显示乘方为“^”，如果需要切换为“**”，传入整型参数1
	formula get_formula(int show_way = 0);

	//检查答案是否正确。id为题号，u_answer为答案
	int check_answer(int id, string u_answer);
};

