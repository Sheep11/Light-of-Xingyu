#include "libraryfile_and_define.h"
#include "class.h"
#include"calculate_tool_class.h"
int main()
{
	//generator G;
	//for (int i = 1; i <= 50; i++)
	//{
	//	formula F = G.get_formula();//��ʾģʽ����ΪĬ�ϵ�0���˷���ʾΪ^
	//	//����get_formula������Ὣ��ȡ����ʽ��׷�����뵽�ļ�problem_file.txt��


	//	cout << "��Ŀ " << F.id << endl;
	//	cout << F.problem << endl;
	//	cout << "�𰸣�";
	//	cout << F.answer << endl << endl;

	//	//cout << "����𰸣�";
	//	//string answer;
	//	//cin >> answer;

	//	//if (G.check_answer(F.id, answer) == 1)//�����Ƿ���ȷ����ȷ����1
	//	//	cout << "�ش���ȷ" << endl << endl;
	//	//else
	//	//	cout << "�ش����" << endl << endl;
	//}

	//for (int i = 51; i <= 100; i++)
	//{
	//	formula F = G.get_formula(1);//��ʾģʽ����Ϊ1���˷���ʾΪ**

	//	cout << "��Ŀ " << F.id << endl;
	//	cout << F.problem << endl;
	//	cout << "�𰸣�";
	//	cout << F.answer << endl << endl;
	//}

	string str[100] = {
		"1 + 2 ",
		"1 / 0",
		"4/5 + 3/5",
		"1/3 + 1/4",
		"1 + 1/5"
	};
	
	calculate_tool C_tool;
	for (int i = 0; i < 5; i++)
	{
		word answer = C_tool.calculate_suffix(str[i]);
		cout << answer.str_word() << endl << endl;
	}

	system("pause");

}