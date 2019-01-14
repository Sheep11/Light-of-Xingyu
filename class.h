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
public:
	int id;
	string problem;
	string answer;

	formula();
	formula(string P, string A);
	formula(const formula& F);

	void init();
	void init(string P, string A);

	formula& operator =(const formula& source_formula);//���ظ�ֵ�����

	int check(string u_answer);
};


class generator
{
private:
	vector<formula> formula_vector;//�洢��Ŀ�ʹ𰸵�����
	int sum;//�洢������
	int index;//û��ʹ�ù��ĵ�һ����Ŀ�ʹ𰸵ı�ţ������ֵ�����±�+1��
public:
	generator();

	//���ʽ�ӵ��ļ�path�У�Ĭ��Ϊproblem_file.txt
	void output_into_file(string exp, string path = "problem_file.txt");

	//��ȡһ��ʽ�Ӽ���,����ֵΪformula����
	//Ĭ����ʾ�˷�Ϊ��^���������Ҫ�л�Ϊ��**�����������Ͳ���1
	formula get_formula(int show_way = 0);

	//�����Ƿ���ȷ��idΪ��ţ�u_answerΪ��
	int check_answer(int id, string u_answer);
};

