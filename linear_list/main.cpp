#include<stdio.h>
#include<malloc.h>   //动态存储分配函数头文件,ANSI标准建议使用stdlib.h头文件,但许多C编译要求用malloc.h
#include<math.h>

#define ERROR 1      //定义正确和错误的返回值
#define OK    0

struct node        //定义结构体，表示多项式中的每一项
{
	float coef;      //多项式中每项的系数
	int   exp;       //多项式中每项的次数
};

typedef struct node node;     //定义结点
typedef struct slist *linklist; 

struct slist         //单链表结点结构
{
	node data;     //结构体node的数据
	struct slist *next;     //指向下一个数据
};

linklist append(linklist tail, node item)     //在链表后面增加一个结点
{
	tail->next = (linklist)malloc(sizeof(slist));    // 为新的结点分配内存
	if (!tail)       //判断条件相当于(tail==0)
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

int add(linklist y1, linklist y2, linklist y3)       //相加计算，y3用以存储y1和y2计算的结果
{
	linklist point1, point2, point3;
	node item;
	point1 = y1;
	point2 = y2;
	point3 = y3;
	while (point1->next != NULL&&point2->next != NULL)
	{
		if (point1->next->data.exp == point2->next->data.exp)     //如果两多项式有次数相同的项，则相加
		{
			item.coef = point1->next->data.coef + point2->next->data.coef;
			item.exp = point1->next->data.exp;
			point3 = append(point3, item);
			point1 = point1->next;
			point2 = point2->next;
			continue;
		}
		else if (point1->next->data.exp > point2->next->data.exp)         //如果两多项式中的某项次数不同，则直接分别输出两项
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
	while (point1->next != NULL)    //复制y1的余项
	{
		item.exp = point1->next->data.exp;
		item.coef = point1->next->data.coef;
		point3 = append(point3, item);
		point1 = point1->next;
	}
	while (point2->next != NULL)    //复制y2的余项
	{
		item.exp = point2->next->data.exp;
		item.coef = point2->next->data.coef;
		point3 = append(point3, item);
		point2 = point2->next;
	}
	return OK;
}
 
int multiply(linklist y1, linklist y2, linklist count)       //相乘计算，y3用以存储y1和y2计算的结果
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

int output(linklist head)   //将结果输出
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
		printf("链表为空!\n");
	printf("\n\n");
	return OK;
}

double value(linklist head, double x)    //求多项式的值
{
	double sum = 0;
	linklist p;
	for (p = head->next; p != NULL; p = p->next)
	{
		sum += p->data.coef*pow(x, p->data.exp);
	}
	printf("多项式的值为：%.4lf\n", sum);
	return sum;
}

int main()      //主函数
{
	double x;
	linklist y1, y2, y3, y4;
	linklist tail1, tail2, tail3, tail4;
	node a;
	tail1 = y1 = (linklist)malloc(sizeof(struct slist));   //将四个链表初始化，若分配内存失败则返回“malloc error”的信息
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

	printf("输入y1(输入 0 0 表示结束）:\n");    //输入多项式y1,y2的提示语
	for (scanf_s("%f%d", &a.coef, &a.exp); fabs(a.coef)>0.000001;)     //将检验值设置为0.000001以避免过小的数字导致的bug，以下同理
	{
		tail1 = append(tail1, a);
		scanf_s("%f%d", &a.coef, &a.exp);
	}
	printf("输入y2(输入 0 0 表示结束）:\n");
	for (scanf_s("%f%d", &a.coef, &a.exp); fabs(a.coef)>0.000001;)
	{
		tail2 = append(tail2, a);
		scanf_s("%f%d", &a.coef, &a.exp);
	}

	printf("y1=");       //输出多项式的值
	output(y1);
	printf("y2=");
	output(y2);

	add(y1, y2, y3);      //计算并输出结果
	printf("y1+y2=");
	output(y3);

	multiply(y1, y2, y4);
	printf("y1*y2=");
	output(y4);

	printf("输入X的值：");      //求值
	scanf_s("%lf", &x);
	value(y3, x);
	value(y4, x);
	return OK;
}