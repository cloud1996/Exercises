#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<math.h>

typedef struct _slist _slist;     //������
typedef struct slist *linklist;

linklist *multiply(pnode *heada, pnode *headb)
{
	slist *A, *B, *pcRemark, *headc, *pcDel, *C;
	headc = (pnode *)malloc(sizeof(pnode));
	headc->link = NULL;
	int Exp;
	float Coef;
	A = heada->next;
	B = headb->next;
	while (A)
	{
		pcRemark = headc;
		while (B)
		{
			Exp = A->exp + B->exp;
			Coef = (A->coef)*(B->coef);
			C = (pnode *)malloc(sizeof(pnode));
			C->coef = Coef;
			C->exp = Exp;
			C->link = NULL;
			while (pcRemark->next && Exp<pcRemark->next->exp)//������һ������ָ���Ա�pcNew
				pcRemark = pcRemark->next;//�Ĵ��ʱ��pcRemark����
			if (pcRemark->next && Exp == pcRemark->next->exp)//��pcRemark����һ������ָ����
			{
				//  pcNew��ȵ����
				if (Coef + pcRemark->next->coef == 0.0)//�������ϵ�����Ϊ�㣬���ͷ������е��Ǹ����
				{
					pcDel = pcRemark->next;
					pcRemark->link = pcDel->next;
					free(pcDel);
				}
				else
					pcRemark->next->coef = pcRemark->next->coef + Coef;				
			}
			else
			{
				C->link = pcRemark->next;
				pcRemark->next = C;
			}
			B = B->next;
		}
		A = A->next;
		B = headb->link;
	}
	return(headc);	
}

int main() {
	return 0;
}