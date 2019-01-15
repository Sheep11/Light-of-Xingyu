#pragma once
#include"class.h"
#include"libraryfile_and_define.h"

class generate_tool
{
public:

	//��׺���ʽת��Ϊ������
	bi_tree translate_into_bi_tree(class queue<word> suffix);

	//�Ƚ�����word�Ƿ���ͬ�������ͬ����1�����򷵻�0
	int cmp_word(word a, word b);

	//�ж�a,b�������Ƿ��н���Ƚϵı�Ҫ������У�����1
	int swap_flag(bi_tree a, bi_tree b);

	//�����������ͬ����1�����򷵻�0
	int compare_tree(bi_tree *a, bi_tree *b);

	//������ת���ɲ�����
	char translate_into_oper(int num);

	//��Ӳ�����
	void add_oper_into_exp(string& exp, int max_oper_sum);

	//�����в������ı��ʽ�淶��
	void normalize_exp(string& oper_exp);

	//����в������ı��ʽ�������
	void add_number_into_exp(string& oper_exp, int max_number);

	//���ƽ���ķ�Χ���߸�ʽ
	int restrict_result(string exp, word result);

	//����Ƿ����ظ�������У�����1��û�з���0
	int is_repeat(word result_array[], word result, bi_tree tree_array[], bi_tree tree, int n);

	//�����ǰ��¼
	void clear_trail(string& exp, queue<word>& suffix, word& result, bi_tree& tree);

	//�ı���ʾ�˷��ķ�ʽ
	void change_show_way(string& exp);

	vector<formula> generate_exp(int N = 1000, int max_number = 10, int max_oper_sum = 10, int show_way = 0);
};