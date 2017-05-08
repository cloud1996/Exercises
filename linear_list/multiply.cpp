#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<math.h>

typedef struct _slist _slist;     //定义结点
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
			while (pcRemark->next && Exp<pcRemark->next->exp)//当的下一个结点的指数仍比pcNew
				pcRemark = pcRemark->next;//的大的时候将pcRemark后移
			if (pcRemark->next && Exp == pcRemark->next->exp)//当pcRemark的下一个结点的指数和
			{
				//  pcNew相等的情况
				if (Coef + pcRemark->next->coef == 0.0)//如果它们系数相加为零，就释放链表中的那个结点
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