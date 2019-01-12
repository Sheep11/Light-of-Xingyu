#pragma once
#include"class.h"
#include"libraryfile_and_define.h"
#include"translate_tool_class.h"

using namespace std;

class translate_tool
{
public:
	//如果x是数字，返回-1，否则返回操作符对应的数字
	int check_type(const char x);

	//返回数字对应的操作符
	char change_oper(const int oper);

	//检测优先级。如果x是操作符则返回其优先级，否则返回-1,括号的优先级为0
	int check_priority(const char x);

	//比较操作符x和y的优先级。如果x>y返回1，x=y返回0，x<y返回-1
	int cmp_priority(const char x, const char y);

	//将exp转化为后缀表达式,存在队列里返回
	queue<word> translate_into_suffix(const string exp);
};


