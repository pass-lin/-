typedef char TElemType;     // �������������Ԫ������Ϊ�ַ�
#define errornumber -10086
typedef struct  BiTNode {
    TElemType      data;     // ������
    struct BiTNode  *lchild,*rchild;  // ���Һ���ָ��
} BiTNode,*BiTree;   // ��������

typedef enum Status{	
	ERROR,
	SUCEESS
}Status;


Status InitBiTree(BiTree* T);
//�������������ն�����T
void DestroyBiTree(BiTree T);
//��ʼ������������T����
//����������ݻٶ�����T
BiTNode* CreateBiTree(BiTree T, char* definition);
//��ʼ������ definition�����������Ķ���
//�����������definition���������T


//���²��ֺ�������δָ����������
Status PreOrderTraverse(BiTree  T, void (*visit)(TElemType e));
//��ʼ������������T���ڣ�visitΪ�Խ��Ĳ�����Ӧ�ú���
//����������������T����ÿ��������visit����һ���ҽ�һ�Σ�һ��visitʧ�ܣ������ʧ��
Status InOrderTraverse(BiTree T, void (*visit)(TElemType e));	//�������(�˴��÷ǵݹ�ʵ��)
Status PostOrderTraverse(BiTree T ,void (*visit)(TElemType e));	//�������
Status LevelOrderTraverse(BiTree T, void(*visit)(TElemType e));	//�������
int Value(BiTree T);			//������Ķ�������ֵ
/*
��ʾ�����ڽ��ṹ�������ø�Tagֵ��־������������������������
�ɸ�����Ҫ�������Ӳ���.
*/
