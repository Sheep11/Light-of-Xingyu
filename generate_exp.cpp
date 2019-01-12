#include"generate_exp.h"

using namespace std;


//����N�����ʽ,����ɹ�����N��
//max_numberΪ���ʽ�����ֵ����ֵ��Ĭ��Ϊ10
//max_oper_sumΪ���ʽ����ຬ�е��������������Ĭ��Ϊ5
//show_wayΪ�˷�����ʾ��ʽ��Ϊ0ʱ��ʾΪ^��Ϊ1ʱ��ʾΪ**��Ĭ��Ϊ0
int generate_exp(int N, int max_number, int max_oper_sum, int show_way)
{	
	srand(time(NULL));

	string exp[MAX_SIZE];//���ʽ���ַ�����ʽ
	queue<word> suffix[MAX_SIZE];//��׺���ʽ
	word result[MAX_SIZE];//���ʽ�ļ�����
	bi_tree tree[MAX_SIZE];//���ʽ�Ķ�������ʽ

	tool Tool;
	int n = 0;//��ǰ��ʽ�ӱ��
	while (n < N)
	{	
		Tool.add_oper_into_exp(exp[n], max_oper_sum);//��Ӳ�����
		
		Tool.normalize_exp(exp[n]);//�淶��
		
		Tool.add_number_into_exp(exp[n], max_number);//�������

		switch (n)
		{
			case 0:exp[n] = "1+2+3"; break;
			case 1:exp[n] = "3+(2+1)"; break;
			//case 2:exp[n] = "3+2+1"; break;
			default:
				break;
		}

			
		suffix[n] = translate_into_suffix(exp[n]);//ת��Ϊ��׺���ʽ

		result[n] = calculate_suffix(suffix[n]);//�����׺���ʽ��ֵ

		if (result[n].type == -1)//������ʽ���������ǰ��¼���������ɱ��ʽ
		{
			Tool.clear_trail(exp[n], suffix[n], result[n], tree[n]);//�����ǰ��¼
			continue;
		}
		else//���ʽ���󣬼���Ƿ���֮ǰ���ɵı��ʽ�ظ�
		{
			//��׺ʽת��Ϊ������
			tree[n] = Tool.translate_into_bi_tree(suffix[n]);

			//����Ƿ��֮ǰ��ʽ���ظ�
			int repeat_flag = Tool.is_repeat(tree, tree[n], n);
			if (repeat_flag == 1)//�ظ��������¼����������
			{
				Tool.clear_trail(exp[n], suffix[n], result[n], tree[n]);//�����ǰ��¼
				continue;
			}
		}

		//���show_way = 1��������^�滻Ϊ**
		if (show_way == 1)
			Tool.change_show_way(exp[n]);

		cout << exp[n] << endl;
		n++;
	}
	return n;
}