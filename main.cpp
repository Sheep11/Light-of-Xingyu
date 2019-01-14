#include "libraryfile_and_define.h"
#include "class.h"

int main()
{
	generator G;
	for (int i = 1; i <= 50; i++)
	{
		formula F = G.get_formula();//显示模式参数为默认的0，乘方显示为^
		//调用get_formula函数后会将获取到的式子追加输入到文件problem_file.txt中


		cout << "题目 " << F.id << endl;
		cout << F.problem << endl;
		cout << "答案：";
		cout << F.answer << endl << endl;

		cout << "输入答案：";
		string answer;
		cin >> answer;

		if (G.check_answer(F.id, answer) == 1)//检查答案是否正确，正确返回1
			cout << "回答正确" << endl << endl;
		else
			cout << "回答错误" << endl << endl;
	}

	for (int i = 51; i <= 100; i++)
	{
		formula F = G.get_formula(1);//显示模式参数为1，乘方显示为**

		cout << "题目 " << F.id << endl;
		cout << F.problem << endl;
		cout << "答案：";
		cout << F.answer << endl << endl;
	}

	system("pause");

}