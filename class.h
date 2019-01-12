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

