#pragma once
#include "class.h"
#include "libraryfile_and_define.h"
#include "calculate_suffix.h"
#include "translate_into_suffix.h"


//�Ƚ�����word�Ƿ���ͬ�������ͬ����1�����򷵻�0
int cmp_word(word a, word b);

//�ж�a,b�������Ƿ��н���Ƚϵı�Ҫ������У�����1
int swap_flag(bi_tree a, bi_tree b);

//�����������ͬ����1�����򷵻�0
int compare_tree(class bi_tree *a, bi_tree *b);

//��׺���ʽת��Ϊ������
bi_tree translate_into_bi_tree(std::queue<word> suffix);

//������ת���ɲ�����
char translate_into_oper(int num);

int generate_exp(int N, int max_number = 100, int max_oper_sum = 20);