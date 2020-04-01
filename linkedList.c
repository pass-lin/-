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
        *L = (LinkedList)malloc(sizeof(LNode));/*如果输入的不是空地址则生成一个头结点*/
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
        LNode* p = L->next;/*先销毁该结点，然后将领结点进行递归*/
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
Status SearchList(LinkedList L, ElemType e) {/*如果遍历链表都没有找到就返回错误，如果找到就返回成功*/
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
        LinkedList t1,t2, t3;/*准备三个变量，方便存储连续的三个结点*/
        t1 = (*L)->next;/*从头结点的第一个开始初始化*/
        t2 = t1->next;
        t3 = t2->next;
        t1->next = NULL;
        while (t2)
        {
            t3 = t2->next;/*更新t3*/
            t2->next = t1;/*让t2指向前一个结点*/
            t1 = t2;/*更新t1 t2*/
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
    LinkedList quick, slow;/*设置快慢两个指针*/
    quick = slow = L;
    while (1)
    {
        if (quick == NULL)/*如果快指针遍历完链表不是循环，如果相遇则是*/
            return ERROR;
        if (quick == slow)
            return SUCCESS;
        quick = quick->next->next;/*快指针走两步，慢指针走一步*/
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
    if (L && L->next)/*如果剩余双数位结点*/
    {
        LinkedList p = L->next->next, m = L->next;/*p存储第三个结点*/
        m->next = L;/*第二个结点下一个改为第一个结点*/
        L->next = ReverseEvenList(p);/*第一个结点的下一结点指向递归运行的函数*/
        return m;/*返回的第二个结点的地址*/
    }
    else /*剩余单数位结点或者空结点则返回该结点*/
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
    quick = slow = *L;/*定义快慢指针*/
    while (quick)
    {
        quick = quick->next->next;/*快指针走两步慢指针走一步，快指针遍历完则慢指针走到中点*/
        slow = slow->next;
    }
    return slow;
}

