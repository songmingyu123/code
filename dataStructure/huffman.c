//yingying
#include<stdio.h>
#include<stdlib.h>

typedef struct HTNode
{
	int data;//权重
	struct HTNode *lchild;
	struct HTNode *rchild;
}HTNode;


HTNode *createHT(int [],int);//权重数组，数组元素个数
void findMin(int *, int *, HTNode **, int);//寻找最小的两个权值的下标
void inorderTraversal(HTNode *);//中序遍历二叉树
int WeightPathLength(HTNode *, int);//计算带权路径长度
void display(HTNode *);

int main()
{
	//int weights[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	//int weights[] = { 15, 3, 14, 2, 6, 9, 16, 17 };
	int weights[] = { 5, 6, 2, 9, 8 };
	int WPL = 0;
	HTNode *p = createHT(weights, sizeof(weights) / sizeof(int));
	printf("中序遍历哈夫曼树:");
	inorderTraversal(p);
	WPL = WeightPathLength(p, 0);
	printf("\n带权路径长度:%d\n",WPL);
	printf("哈夫曼树:");
	display(p);
	getch();
	return 0;
}


HTNode *createHT(int weight[], int n)
{
	HTNode **treeArray = (HTNode **)malloc(sizeof(HTNode*)*n);//创建指针数组
	HTNode *p = NULL;
	int min1, min2;//两个权值最小和次小的下表
	//for循环，把weight数组中的权值赋值给treeArray数组
	for (size_t i = 0; i < n; i++)
	{
		treeArray[i] = (HTNode*)malloc(sizeof(HTNode));
		treeArray[i]->data = weight[i];
		treeArray[i]->lchild = treeArray[i]->rchild = NULL;
	}
	for (size_t i = 0; i < n-1; i++)//如果有n个数字，每次合二为一，要执行n-1次，最后留下1个根节点
	{
		//找到了最小的两个权值的下标
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

//寻找最小的两个权值的下标
void findMin(int *min1, int *min2, HTNode **p, int n)
{
	int m1 = 0;
	int m2 = 0;
	m1 = -1;
	//for寻找权值数组中最前面的两个左右初始下标
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
	//if为空树
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