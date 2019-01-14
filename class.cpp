#include "class.h"
#include"generate_tool_class.h"
#include"calculate_tool_class.h"
#include"translate_tool_class.h"

using namespace std;


//word
//构造函数
word::word()
{
	type = -1;
	oper = num = de = 0;
}
word::word(int type_t, int n, int d)//类型，分子，分母
{
	type = type_t;
	if (type_t == 0)
		oper = 0, num = n, de = d;
	else
		oper = n, num = 0, de = 0;
}

//初始化函数
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

//等号重载
word& word::operator =(const word& source_word)//重载赋值运算符
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

string word::str_word()
{
	string t_result;
	t_result += to_string(num);
	if (de != 1)
	{
		t_result += '/';
		t_result += to_string(de);
	}

	return t_result;
}


//二叉树
//构造函数
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

//初始化函数
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

//等号重载
bi_tree& bi_tree::operator =(const bi_tree& source_tree)//重载赋值运算符
{
	if (this != &source_tree)
	{
		this->value = source_tree.value;
		this->l_child = source_tree.l_child;
		this->r_child = source_tree.r_child;
	}
	return *this;
}

formula::formula()
{
	;
}
formula::formula(string P, string A)
{
	Problem = P;
	Answer = A;
}
formula::formula(const formula& F)
{
	this->Problem = F.Problem;
	this->Answer = F.Answer;
}

void formula::init()
{
	;
}
void formula::init(string P, string A)
{
	Problem = P;
	Answer = A;
}

string formula::problem()
{
	return Problem;
}

string formula::answer()
{
	return Answer;
}

int formula::check(string u_answer)
{
	if (u_answer == Answer)
		return 1;

	for (int i = 0; i < u_answer.size(); i++)
	{
		if (u_answer[i] == '/')
		{
			if (u_answer[i + 1] == '-')
			{
				u_answer.erase(i + 1, 1);
				u_answer.insert(0, "-");
				if (u_answer == Answer)
					return 1;
				else
					return 0;
			}
		}
	}
	return 0;
}




generator::generator()
{
	show_way = 0;
}

void generator::output_into_file(string exp, string path)
{
	ofstream out(path, ios::app);
	out << exp << endl;
}

formula generator::get_formula(int Show_way)
{
	if (Show_way != 1)
		Show_way = 0;

	if (this->show_way != Show_way)
	{
		while (Formula.size() != 0)
			Formula.pop();

		this->show_way = Show_way;
	}

	if (Formula.size() != 0)
	{
		formula return_value = Formula.top();
		output_into_file(return_value.problem());

		Formula.pop();

		return return_value;
	}
	else
	{
		generate_tool G_tool;
		Formula = G_tool.generate_exp(1000, 10, 10, this->show_way);

		formula return_value = Formula.top();
		output_into_file(return_value.problem());

		Formula.pop();

		return return_value;
	}
}

