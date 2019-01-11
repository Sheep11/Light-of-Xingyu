#include "class.h"

word::word()
	{
		type = oper = -1;
		num = 0;
		de = 1;
	}
word::word(int type_t, int n, int d)//类型，分子，分母
	{
		type = type_t;
		num = oper = 0;

		if (type_t == 0)
			num = n, de = d;
		else
			oper = n;
	}

void word:: init()
	{
		type = oper = -1;
		num = 0;
		de = 1;
	}
void word::init(int type_t, int n, int d)
{
	type = type_t;
	num = oper = 0;

	if (type_t == 0)
		num = n, de = d;
	else
		oper = n;
}


word& word::operator =(const word& str)//重载赋值运算符
	{
		if (this != &str)
		{
			this->type = str.type;
			this->oper = str.oper;
			this->num = str.num;
			this->de = str.de;
		}
		return *this;
	}


//二叉树
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