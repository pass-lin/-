#include "../head/linkedList.h"
#include<stdlib.h>
/**
 *  @name        : Status InitList(LinkList *L);
 *	@description : initialize an empty linked list with only the head node without value
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status InitList(LinkedList *L) {
    if (L)
    {
        *L = (LinkedList)malloc(sizeof(LNode));/*�������Ĳ��ǿյ�ַ������һ��ͷ���*/
        (*L)->next = NULL;
        return SUCCESS;
    }
    else
        return ERROR;
}

/**
 *  @name        : void DestroyList(LinkedList *L)
 *	@description : destroy a linked list, free all the nodes
 *	@param		 : L(the head node)
 *	@return		 : None
 *  @notice      : None
 */
void DestroyList(LNode *L) {
    if (L)
    {
        LNode* p = L->next;/*�����ٸý�㣬Ȼ��������еݹ�*/
        free(L);
        DestroyList(p);
    }
}

/**
 *  @name        : Status InsertList(LNode *p, LNode *q)
 *	@description : insert node q after node p
 *	@param		 : p, q
 *	@return		 : Status
 *  @notice      : None
 */
Status InsertList(LNode *p, LNode *q) {
    if (p)
    {
        q->next = p->next;
        p->next = q;
        return SUCCESS;
    }
    else
        return ERROR;
}
/**
 *  @name        : Status DeleteList(LNode *p, ElemType *e)
 *	@description : delete the first node after the node p and assign its value to e
 *	@param		 : p, e
 *	@return		 : Status
 *  @notice      : None
 */
Status DeleteList(LNode *p, ElemType *e) {
    if (p)
    {
        LNode* m = p->next->next;
        *e = p->next->data;
        free(p->next);
        p->next = m;
        return SUCCESS;
    }
    else
        return ERROR;
}

/**
 *  @name        : void TraverseList(LinkedList L, void (*visit)(ElemType e))
 *	@description : traverse the linked list and call the funtion visit
 *	@param		 : L(the head node), visit
 *	@return		 : None
 *  @notice      : None
 */
void TraverseList(LinkedList L, void (*visit)(ElemType e)) {
    if (L)
    {
        visit(L->data);
        TraverseList(L->next, visit);
    }
}

/**
 *  @name        : Status SearchList(LinkedList L, ElemType e)
 *	@description : find the first node in the linked list according to e
 *	@param		 : L(the head node), e
 *	@return		 : Status
 *  @notice      : None
 */
Status SearchList(LinkedList L, ElemType e) {/*�����������û���ҵ��ͷ��ش�������ҵ��ͷ��سɹ�*/
    if (L == NULL)
        return ERROR;
    if (L->data == e)
        return SUCCESS;
    return SearchList(L->next, e);
}

/**
 *  @name        : Status ReverseList(LinkedList *L)
 *	@description : reverse the linked list
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status ReverseList(LinkedList *L) {
    if ((*L)&& (*L)->next)
    {
        LinkedList t1,t2, t3;/*׼����������������洢�������������*/
        t1 = (*L)->next;/*��ͷ���ĵ�һ����ʼ��ʼ��*/
        t2 = t1->next;
        t3 = t2->next;
        t1->next = NULL;
        while (t2)
        {
            t3 = t2->next;/*����t3*/
            t2->next = t1;/*��t2ָ��ǰһ�����*/
            t1 = t2;/*����t1 t2*/
            t2 = t3;
        }
        (*L)->next = t1;
        return SUCCESS;
    }
    else
        return ERROR;
}

/**
 *  @name        : Status IsLoopList(LinkedList L)
 *	@description : judge whether the linked list is looped
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status IsLoopList(LinkedList L) {
    LinkedList quick, slow;/*���ÿ�������ָ��*/
    quick = slow = L;
    while (1)
    {
        if (quick == NULL)/*�����ָ�������������ѭ���������������*/
            return ERROR;
        if (quick == slow)
            return SUCCESS;
        quick = quick->next->next;/*��ָ������������ָ����һ��*/
        slow = slow->next;
    }
}

/**
 *  @name        : LNode* ReverseEvenList(LinkedList *L)
 *	@description : reverse the nodes which value is an even number in the linked list, input: 1 -> 2 -> 3 -> 4  output: 2 -> 1 -> 4 -> 3
 *	@param		 : L(the head node)
 *	@return		 : LNode(the new head node)
 *  @notice      : choose to finish
 */
LNode* ReverseEvenList(LinkedList L) {
    if (L && L->next)/*���ʣ��˫��λ���*/
    {
        LinkedList p = L->next->next, m = L->next;/*p�洢���������*/
        m->next = L;/*�ڶ��������һ����Ϊ��һ�����*/
        L->next = ReverseEvenList(p);/*��һ��������һ���ָ��ݹ����еĺ���*/
        return m;/*���صĵڶ������ĵ�ַ*/
    }
    else /*ʣ�൥��λ�����߿ս���򷵻ظý��*/
        return L;
}

/**
 *  @name        : LNode* FindMidNode(LinkedList *L)
 *	@description : find the middle node in the linked list
 *	@param		 : L(the head node)
 *	@return		 : LNode
 *  @notice      : choose to finish
 */
LNode* FindMidNode(LinkedList *L) {
    LNode* quick, * slow;
    quick = slow = *L;/*�������ָ��*/
    while (quick)
    {
        quick = quick->next->next;/*��ָ����������ָ����һ������ָ�����������ָ���ߵ��е�*/
        slow = slow->next;
    }
    return slow;
}

