#include"generate_exp.h"
#include"calculate_tool_class.h"
#include"translate_tool_class.h"
#include"generate_tool_class.h"

using namespace std;

//����N�����ʽ,����ɹ�����N��max_numberΪ���ʽ�����ֵ����ֵ��max_oper_sumΪ���ʽ����ຬ�е������������
int generate_exp(int N, int max_number, int max_oper_sum, int show_way)
{	
	srand(time(NULL));

	string exp[MAX_SIZE];//���ʽ���ַ�����ʽ
	bi_tree tree[MAX_SIZE];//���ʽ�Ķ�������ʽ
	queue<word> suffix[MAX_SIZE];//��׺���ʽ
	word result[MAX_SIZE];//���ʽ�ļ�����

	translate_tool T_tool;
	calculate_tool C_tool;
	generate_tool G_tool;

	int n = 0;//��ǰ��ʽ�ӱ��
	while (n < N)
	{
		//��Ӳ�����
		G_tool.add_oper_into_exp(exp[n], max_oper_sum);

		//�淶��
		G_tool.normalize_exp(exp[n]);

		//�������
		G_tool.add_number_into_exp(exp[n], max_number);

		//ת��Ϊ��׺���ʽ
		suffix[n] = T_tool.translate_into_suffix(exp[n]);
	
		result[n] = C_tool.calculate_suffix(suffix[n]);//�����׺���ʽ��ֵ
		if (result[n].type == -1)//������ʽ�����������ɱ��ʽ
		{
			G_tool.clear_trail(exp[n], suffix[n], result[n], tree[n]);//�����¼
			continue;
		}
		else//���ʽ���󣬼���Ƿ���֮ǰ���ɵı��ʽ�ظ�
		{
			tree[n] = G_tool.translate_into_bi_tree(suffix[n]);//�ɺ�׺���ʽ���ɶ�����

			int repeat_flag = G_tool.is_repeat(tree, tree[n], n);
			if (repeat_flag == 1)//�ظ�
			{
				G_tool.clear_trail(exp[n], suffix[n], result[n], tree[n]);//�����¼
				continue;
			}
		}

		if (show_way == 1)
			G_tool.change_show_way(exp[n]);

		cout << exp[n] << endl;
		n++;
	}
	return n;
}
