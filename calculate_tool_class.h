#include "libraryfile_and_define.h"
#include "class.h"

class calculate_tool
{
public:
	//����a,b���������
	int gcd(int a, int b);

	//����a op b�ļ���������������˳���0����ָ����Ϊ�Ǹ����������ص�result.type = -1
	word calculate(word a, word op, word b);

	//���غ�׺���ʽsuffix�ļ�������������ʽ����ȷ�����ص�result.type = -1
	word calculate_suffix(std::queue<word> suffix);
};

