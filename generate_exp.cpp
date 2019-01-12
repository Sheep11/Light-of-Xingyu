#include"generate_exp.h"

using namespace std;

//int check_repeat(bi_tree tree_array[], bi_tree tree, int n)
//{
//	tool Tool;
//	for (int i = 0; i < n; i++)
//	{
//		if (Tool.compare_tree(&tree, &tree_array[i]) == 1)
//		{
//			return 1;
//		}
//	}
//
//	return 0;
//}

//����N�����ʽ,����ɹ�����N��max_numberΪ���ʽ�����ֵ����ֵ��max_oper_sumΪ���ʽ����ຬ�е������������
int generate_exp(int N, int max_number, int max_oper_sum)
{	
	srand(time(NULL));

	string exp[MAX_SIZE];//���ʽ���ַ�����ʽ
	bi_tree tree[MAX_SIZE];//���ʽ�Ķ�������ʽ
	queue<word> suffix[MAX_SIZE];//��׺���ʽ
	word result[MAX_SIZE];//���ʽ�ļ�����


	tool Tool;
	int n = 0;//��ǰ��ʽ�ӱ��
	while (n < N)
	{
		while (1)
		{
			//��Ӳ�����
			Tool.add_oper_into_exp(exp[n], max_oper_sum);

			//�淶��
			Tool.normalize_exp(exp[n]);

			//�������
			Tool.add_number_into_exp(exp[n], max_number);

			//switch (n)
			//{
			//	case 0:exp[n] = "1+2+3"; break;
			//	case 1:exp[n] = "3+2+1"; break;
			//	//case 2:exp[n] = "3+2+1"; break;
			//	default:
			//		break;
			//}

			//ת��Ϊ��׺���ʽ
			suffix[n] = translate_into_suffix(exp[n]);

			
			result[n] = calculate_suffix(suffix[n]);//�����׺���ʽ��ֵ
			if (result[n].type == -1)//������ʽ�����������ɱ��ʽ
			{
				//���exp[n],suffix[n],result[n],tree[n]
				exp[n].clear();
				result[n].init();
				tree[n].init();
				while (!suffix[n].empty())
					suffix[n].pop();

				continue;
			}
			else
			{
				tree[n] = Tool.translate_into_bi_tree(suffix[n]);

				int repeat_flag = 0;
				for (int i = 0; i < n; i++)
				{
					if (Tool.compare_tree(&tree[n], &tree[i]) == 1)
					{
						//���exp[n],suffix[n],result[n],tree[n]
						exp[n].clear();
						result[n].init();
						tree[n].init();
						while (!suffix[n].empty())
							suffix[n].pop();
						repeat_flag = 1;
						break;
					}
				}
				if (repeat_flag == 1)
					continue;
				else
					break;
			}
		}


		cout << exp[n] << endl;
		n++;
	}
	return n;
}