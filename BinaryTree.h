typedef char TElemType;     // 假设二叉树结点的元素类型为字符
#define errornumber -10086
typedef struct  BiTNode {
    TElemType      data;     // 数据域
    struct BiTNode  *lchild,*rchild;  // 左、右孩子指针
} BiTNode,*BiTree;   // 二叉链表

typedef enum Status{	
	ERROR,
	SUCEESS
}Status;


Status InitBiTree(BiTree* T);
//操作结果：构造空二叉树T
void DestroyBiTree(BiTree T);
//初始条件：二叉树T存在
//操作结果：摧毁二叉树T
BiTNode* CreateBiTree(BiTree T, char* definition);
//初始条件： definition给出二叉树的定义
//操作结果：按definition构造二叉树T


//以下部分函数定义未指定参数类型
Status PreOrderTraverse(BiTree  T, void (*visit)(TElemType e));
//初始条件：二叉树T存在，visit为对结点的操作的应用函数
//操作结果：先序遍历T，对每个结点调用visit函数一次且仅一次，一旦visit失败，则操作失败
Status InOrderTraverse(BiTree T, void (*visit)(TElemType e));	//中序遍历(此处用非递归实现)
Status PostOrderTraverse(BiTree T ,void (*visit)(TElemType e));	//后序遍历
Status LevelOrderTraverse(BiTree T, void(*visit)(TElemType e));	//层序遍历
int Value(BiTree T);			//构造出的二叉树求值
/*
提示：可在结点结构体中设置个Tag值标志数字与操作符来构造二叉树，
可根据需要自行增加操作.
*/
