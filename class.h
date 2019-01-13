#pragma once
#include "libraryfile_and_define.h"

using namespace std;

class word
{
public:
	int type;//type = 0���ʾ���֣�����1��ʾ������������-1��ʾ����Ľ����δ��ʼ�������ֳ���0�����ʽ����

	int num;//numerator����
	int de;//denominator��ĸ
	int oper;//������

	word();
	word(int type_t, int n, int d = 1);//���ͣ����ӣ���ĸ

	void init();
	void init(int type_t, int n, int d = 1);//���ͣ����ӣ���ĸ

	word& operator =(const word& source_word);//���ظ�ֵ�����

	string str_word();
};

//������
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

	bi_tree& operator =(const bi_tree& source_tree);//���ظ�ֵ�����
};

//��Ŀ�ʹ�
class formula
{
private:
	string Problem;
	string Answer;
public:

	formula();
	formula(string P, string A);
	formula(const formula& F);

	void init();
	void init(string P, string A);

	string problem();
	string answer();

	int check(string u_answer);
};


class generator
{
private:
	int show_way;
	stack<formula> Formula;
public:
	generator();
	void output_into_file(string exp, string path = "problem_file.txt");

	formula get_formula();//��ȡһ��ʽ�Ӽ���,����ֵΪformula����
	formula get_formula(int show_way);//��ȡһ��ʽ�Ӽ���,����ֵΪformula����
};

