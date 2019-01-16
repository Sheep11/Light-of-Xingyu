#include "class.h"
#include"generate_tool_class.h"
#include"calculate_tool_class.h"
#include"translate_tool_class.h"

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

formula::formula()
{
	id = -1;
}
formula::formula(string P, string A)
{
	problem = P;
	answer = A;
}
formula::formula(const formula& F)
{
	this->id = F.id;
	this->problem = F.problem;
	this->answer = F.answer;
}

void formula::init()
{
	id = -1;
}
void formula::init(string P, string A)
{
	problem = P;
	answer = A;
}

formula& formula::operator =(const formula& source_formula)
{
	if (this != &source_formula)
	{
		this->id = source_formula.id;
		this->problem = source_formula.problem;
		this->answer = source_formula.answer;
	}
	return *this;
}

int formula::check(string u_answer)
{
	if (u_answer == answer)
		return 1;

	for (int i = 0; i < u_answer.size(); i++)
	{
		if (u_answer[i] == '/')
		{
			if (u_answer[i + 1] == '-')
			{
				u_answer.erase(i + 1, 1);
				u_answer.insert(0, "-");
				if (u_answer == answer)
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
	sum = 0;
	index = 1;
}

void generator::output_into_file(string exp, string path)
{
	ofstream out(path, ios::app);
	out << exp << endl;
}

formula generator::get_formula(int show_way)
{
	if (index > sum)//��Ŀ�þ�����������
	{
		generate_tool G_tool;
		vector<formula> tem_vector = G_tool.generate_exp(1000, 10, 10);//����1000����Ŀ
		formula_vector.insert(formula_vector.end(), tem_vector.begin(), tem_vector.end());//���ɵ���Ŀ����������
		sum += 1000;
	}
	
	//����Ŀ�ʹ𰸽��б��
	formula_vector[index-1].id = index;

	//�����ʾģʽΪ1
	if (show_way == 1)
	{
		generate_tool G_tool;
		G_tool.change_show_way(formula_vector[index-1].problem);//�ı���Ŀ����ʾģʽ
	}

	formula return_value;
	return_value = formula_vector[index-1];//����ֵ

	index++;

	//������ļ�
	output_into_file(return_value.problem);

	return return_value;
}

int generator::check_answer(int id, string u_answer)
{
	if (u_answer == formula_vector[id - 1].answer)
		return 1;

	for (int i = 0; i < u_answer.size(); i++)
	{
		if (u_answer[i] == ' ' || u_answer[i] == '\n')
			u_answer.erase(i, 1);

		if (u_answer[i] == '/')
		{
			if (u_answer[i + 1] == '-')
			{
				u_answer.erase(i + 1, 1);
				u_answer.insert(0, "-");
				if (u_answer == formula_vector[id - 1].answer)
					return 1;
				else
					return 0;
			}
		}
	}

	return 0;
}

