#include "class.h"

using namespace std;


//word
//���캯��
word::word()
{
	type = -1;
	oper = num = de = 0;
}
word::word(int type_t, int n, int d)//���ͣ����ӣ���ĸ
{
	type = type_t;
	if (type_t == 0)
		oper = 0, num = n, de = d;
	else
		oper = n, num = 0, de = 0;
}

//��ʼ������
void word:: init()
{
	type = -1;
	oper = num = de = 0;
}
void word::init(int type_t, int n, int d)
{
	type = type_t;
	if (type_t == 0)
		oper = 0, num = n, de = d;
	else
		oper = n, num = 0, de = 0;
}

//�Ⱥ�����
word& word::operator =(const word& source_word)//���ظ�ֵ�����
{
	if (this != &source_word)
	{
		this->type = source_word.type;
		this->oper = source_word.oper;
		this->num = source_word.num;
		this->de = source_word.de;
	}
	return *this;
}


//������
//���캯��
bi_tree::bi_tree()
{
	value.init();
	l_child = r_child = NULL;
}
bi_tree::bi_tree(word v)
{
	value = v;
	l_child = r_child = NULL;
}
bi_tree::bi_tree(word v, bi_tree lc, bi_tree rc)
{
	value = v;
	l_child = &lc;
	r_child = &rc;
}

//��ʼ������
void bi_tree::init()
{
	value.init();
	l_child = r_child = NULL;
}
void bi_tree::init(word v)
{
	value = v;
	l_child = r_child = NULL;
}
void bi_tree::init(word v, bi_tree lc, bi_tree rc)
{
	value = v;
	bi_tree* t_lc = new bi_tree;
	bi_tree* t_rc = new bi_tree;
	*t_lc = lc;
	*t_rc = rc;
	
	this->l_child = t_lc;
	this->r_child = t_rc;
}
void bi_tree::init(word v, bi_tree* lc, bi_tree* rc)
{
	this->value = v;
	this->l_child = lc;
	this->r_child = rc;
}

//�Ⱥ�����
bi_tree& bi_tree::operator =(const bi_tree& source_tree)//���ظ�ֵ�����
{
	if (this != &source_tree)
	{
		this->value = source_tree.value;
		this->l_child = source_tree.l_child;
		this->r_child = source_tree.r_child;
	}
	return *this;
}

