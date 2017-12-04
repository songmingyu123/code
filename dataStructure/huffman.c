//yingying
#include<stdio.h>
#include<stdlib.h>

typedef struct HTNode
{
	int data;//Ȩ��
	struct HTNode *lchild;
	struct HTNode *rchild;
}HTNode;


HTNode *createHT(int [],int);//Ȩ�����飬����Ԫ�ظ���
void findMin(int *, int *, HTNode **, int);//Ѱ����С������Ȩֵ���±�
void inorderTraversal(HTNode *);//�������������
int WeightPathLength(HTNode *, int);//�����Ȩ·������
void display(HTNode *);

int main()
{
	//int weights[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	//int weights[] = { 15, 3, 14, 2, 6, 9, 16, 17 };
	int weights[] = { 5, 6, 2, 9, 8 };
	int WPL = 0;
	HTNode *p = createHT(weights, sizeof(weights) / sizeof(int));
	printf("���������������:");
	inorderTraversal(p);
	WPL = WeightPathLength(p, 0);
	printf("\n��Ȩ·������:%d\n",WPL);
	printf("��������:");
	display(p);
	getch();
	return 0;
}


HTNode *createHT(int weight[], int n)
{
	HTNode **treeArray = (HTNode **)malloc(sizeof(HTNode*)*n);//����ָ������
	HTNode *p = NULL;
	int min1, min2;//����Ȩֵ��С�ʹ�С���±�
	//forѭ������weight�����е�Ȩֵ��ֵ��treeArray����
	for (size_t i = 0; i < n; i++)
	{
		treeArray[i] = (HTNode*)malloc(sizeof(HTNode));
		treeArray[i]->data = weight[i];
		treeArray[i]->lchild = treeArray[i]->rchild = NULL;
	}
	for (size_t i = 0; i < n-1; i++)//�����n�����֣�ÿ�κ϶�Ϊһ��Ҫִ��n-1�Σ��������1�����ڵ�
	{
		//�ҵ�����С������Ȩֵ���±�
		findMin(&min1, &min2, treeArray, n);
		p = (HTNode *)malloc(sizeof(HTNode));
		p->lchild = treeArray[min1];
		p->rchild = treeArray[min2];
		p->data = treeArray[min1]->data + treeArray[min2]->data;
		treeArray[min1] = p;
		treeArray[min2] = NULL;
	}
	free(treeArray);
	return p;
}

//Ѱ����С������Ȩֵ���±�
void findMin(int *min1, int *min2, HTNode **p, int n)
{
	int m1 = 0;
	int m2 = 0;
	m1 = -1;
	//forѰ��Ȩֵ��������ǰ����������ҳ�ʼ�±�
	for (size_t i = 0; i < n; i++)
	{
		if (p[i] != NULL && m1==-1)
		{
			m1 = i;
			continue;
		}
		if (p[i] != NULL)
		{
			m2 = i;
			break;
		}
	}

	for (size_t i = m2; i < n; i++)
	{
		if (p[i] != NULL)
		{
			if (p[i]->data < p[m1]->data)
			{
				m2 = m1;
				m1 = i;
			}
			else if (p[i]->data < p[m2]->data)
			{
				m2 = i;
			}
		}
	}
	*min1 = m1;
	*min2 = m2;
}

void inorderTraversal(HTNode *p)
{
	if (p != NULL)
	{
		inorderTraversal(p->lchild);
		printf("%d ", p->data);
		inorderTraversal(p->rchild);
	}
}

int WeightPathLength(HTNode *p, int len)
{
	//ifΪ����
	if (p == NULL)
	{
		return 0;
	}
	else
	{
		if (p->lchild == NULL && p->rchild == NULL)
		{
			return p->data*len;
		}
		else
		{
			return WeightPathLength(p->lchild, len + 1) + WeightPathLength(p->rchild, len + 1);
		}
	}
}

void display(HTNode *p)
{
	if (p != NULL)
	{
		printf("%d", p->data);
		if (p->lchild != NULL || p->rchild != NULL)
		{
			printf("(");
			display(p->lchild);
			if (p->rchild != NULL)
			{
				printf(",");
			}
			display(p->rchild);
			printf(")");
		}
	}
}