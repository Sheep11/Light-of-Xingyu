#pragma once
#include "class.h"
#include "libraryfile_and_define.h"
#include "calculate_suffix.h"
#include "translate_into_suffix.h"


//比较两个word是否相同，如果相同返回1，否则返回0
int cmp_word(word a, word b);

//判断a,b的子树是否有交叉比较的必要，如果有，返回1
int swap_flag(bi_tree a, bi_tree b);

//如果两棵树相同返回1，否则返回0
int compare_tree(class bi_tree *a, bi_tree *b);

//后缀表达式转换为二叉树
bi_tree translate_into_bi_tree(std::queue<word> suffix);

//将数字转化成操作符
char translate_into_oper(int num);

int generate_exp(int N, int max_number = 100, int max_oper_sum = 20);