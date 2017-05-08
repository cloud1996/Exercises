#include<stdio.h>
#include<malloc.h>   //��̬�洢���亯��ͷ�ļ�,ANSI��׼����ʹ��stdlib.hͷ�ļ�,�����C����Ҫ����malloc.h
#include<math.h>

#define ERROR 1      //������ȷ�ʹ���ķ���ֵ
#define OK    0

struct node        //����ṹ�壬��ʾ����ʽ�е�ÿһ��
{
	float coef;      //����ʽ��ÿ���ϵ��
	int   exp;       //����ʽ��ÿ��Ĵ���
};

typedef struct node node;     //������
typedef struct slist *linklist; 

struct slist         //��������ṹ
{
	node data;     //�ṹ��node������
	struct slist *next;     //ָ����һ������
};

linklist append(linklist tail, node item)     //�������������һ�����
{
	tail->next = (linklist)malloc(sizeof(slist));    // Ϊ�µĽ������ڴ�
	if (!tail)       //�ж������൱��(tail==0)
	{
		printf("malloc error!\n");
		return NULL;
	}
	tail = tail->next;
	tail->data.coef = item.coef;
	tail->data.exp = item.exp;
	tail->next = NULL;
	return tail;
}

int add(linklist y1, linklist y2, linklist y3)       //��Ӽ��㣬y3���Դ洢y1��y2����Ľ��
{
	linklist point1, point2, point3;
	node item;
	point1 = y1;
	point2 = y2;
	point3 = y3;
	while (point1->next != NULL&&point2->next != NULL)
	{
		if (point1->next->data.exp == point2->next->data.exp)     //���������ʽ�д�����ͬ��������
		{
			item.coef = point1->next->data.coef + point2->next->data.coef;
			item.exp = point1->next->data.exp;
			point3 = append(point3, item);
			point1 = point1->next;
			point2 = point2->next;
			continue;
		}
		else if (point1->next->data.exp > point2->next->data.exp)         //���������ʽ�е�ĳ�������ͬ����ֱ�ӷֱ��������
		{
			item.exp = point2->next->data.exp;
			item.coef = point2->next->data.coef;
			point3 = append(point3, item);
			point2 = point2->next;
			continue;
		}
		else
		{
				item.exp = point1->next->data.exp;
				item.coef = point1->next->data.coef;
				point3 = append(point3, item);
				point1 = point1->next;
				continue;
		}
	}
	while (point1->next != NULL)    //����y1������
	{
		item.exp = point1->next->data.exp;
		item.coef = point1->next->data.coef;
		point3 = append(point3, item);
		point1 = point1->next;
	}
	while (point2->next != NULL)    //����y2������
	{
		item.exp = point2->next->data.exp;
		item.coef = point2->next->data.coef;
		point3 = append(point3, item);
		point2 = point2->next;
	}
	return OK;
}
 
int multiply(linklist y1, linklist y2, linklist count)       //��˼��㣬y3���Դ洢y1��y2����Ľ��
{
	linklist point1, point2, y3;
	node item;
	int num = 0;
	y3 = (linklist)malloc(sizeof(struct slist));
	point1 = (linklist)malloc(sizeof(struct slist));
	point2 = (linklist)malloc(sizeof(struct slist));
	if (!count)
		printf("malloc error!!!");
	count->next = NULL;
	point1 = y1->next;
	while(point1!= nullptr)
	{
		point2 = y2->next;
		while(point2!= nullptr)
		{
			item.exp = point1->data.exp + point2->data.exp;
			item.coef = point1->data.coef * point2->data.coef;
		    count = append(count, item);
			point2 = point2->next;
		}
		point1 = point1->next;
	}
	return OK;
}

int output(linklist head)   //��������
{
	int num = 0;
	linklist p;
	for (p = head->next; p != nullptr; p = p->next)
	{
		num++;
		if (p->data.coef > 0)
			printf("+");
		else
			printf("-");
		printf("%.2fx^%d", p->data.coef, p->data.exp);
	}
	if (!num)
		printf("����Ϊ��!\n");
	printf("\n\n");
	return OK;
}

double value(linklist head, double x)    //�����ʽ��ֵ
{
	double sum = 0;
	linklist p;
	for (p = head->next; p != NULL; p = p->next)
	{
		sum += p->data.coef*pow(x, p->data.exp);
	}
	printf("����ʽ��ֵΪ��%.4lf\n", sum);
	return sum;
}

int main()      //������
{
	double x;
	linklist y1, y2, y3, y4;
	linklist tail1, tail2, tail3, tail4;
	node a;
	tail1 = y1 = (linklist)malloc(sizeof(struct slist));   //���ĸ������ʼ�����������ڴ�ʧ���򷵻ء�malloc error������Ϣ
	if (!tail1)
	{
		printf("malloc error!!!");
		return ERROR;
	}
	tail1->next = NULL;
	tail2 = y2 =(linklist) malloc(sizeof(struct slist));
	if (!tail2)
	{
		printf("malloc error!!!");
		return ERROR;
	}
	tail2->next = NULL;
	tail3 = y3 =(linklist) malloc(sizeof(struct slist));
	if (!tail3)
	{
		printf("malloc error!!!");
		return ERROR;
	}
	tail3->next = NULL;
	tail4 = y4 = (linklist)malloc(sizeof(struct slist));
	if (!tail4)
	{
		printf("malloc error!!!");
		return ERROR;
	}
	tail4->next = NULL;

	printf("����y1(���� 0 0 ��ʾ������:\n");    //�������ʽy1,y2����ʾ��
	for (scanf_s("%f%d", &a.coef, &a.exp); fabs(a.coef)>0.000001;)     //������ֵ����Ϊ0.000001�Ա����С�����ֵ��µ�bug������ͬ��
	{
		tail1 = append(tail1, a);
		scanf_s("%f%d", &a.coef, &a.exp);
	}
	printf("����y2(���� 0 0 ��ʾ������:\n");
	for (scanf_s("%f%d", &a.coef, &a.exp); fabs(a.coef)>0.000001;)
	{
		tail2 = append(tail2, a);
		scanf_s("%f%d", &a.coef, &a.exp);
	}

	printf("y1=");       //�������ʽ��ֵ
	output(y1);
	printf("y2=");
	output(y2);

	add(y1, y2, y3);      //���㲢������
	printf("y1+y2=");
	output(y3);

	multiply(y1, y2, y4);
	printf("y1*y2=");
	output(y4);

	printf("����X��ֵ��");      //��ֵ
	scanf_s("%lf", &x);
	value(y3, x);
	value(y4, x);
	return OK;
}