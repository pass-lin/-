#include "../head/duLinkedList.h"
#include<stdlib.h>
/**
 *  @name        : Status InitList_DuL(DuLinkedList *L)
 *	@description : initialize an empty linked list with only the head node
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status InitList_DuL(DuLinkedList *L) {/*定义并初始化头结点*/
    *L = (DuLinkedList)malloc(sizeof(DuLNode));
    (*L)->next = (*L)->prior = NULL;
    return SUCCESS;
}

/**
 *  @name        : void DestroyList_DuL(DuLinkedList *L)
 *	@description : destroy a linked list
 *	@param		 : L(the head node)
 *	@return		 : status
 *  @notice      : None
 */
void DestroyList(DuLNode *L) {
    if (L)
    {
        DuLNode* p = L->next;/*先销毁该结点，然后将领结点进行递归*/
        free(L);
        DestroyList(p);
    }
}

/**
 *  @name        : Status InsertBeforeList_DuL(DuLNode *p, LNode *q)
 *	@description : insert node q before node p
 *	@param		 : p, q
 *	@return		 : status
 *  @notice      : None
 */
Status InsertBeforeList_DuL(DuLNode *p, DuLNode *q) {
    if (p && q)
    {
        DuLNode* m = p->prior;
        if (m)
            m->next = q;
        m->next = q;
        q->prior = m;
        q->next = p;
        p->prior = q;
        return SUCCESS;
    }
    else
        return ERROR;
}

/**
 *  @name        : Status InsertAfterList_DuL(DuLNode *p, DuLNode *q)
 *	@description : insert node q after node p
 *	@param		 : p, q
 *	@return		 : status
 *  @notice      : None
 */
Status InsertAfterList_DuL(DuLNode *p, DuLNode *q) {
    if (p && q)
    {
        DuLNode* m = p->next;
        if (m)
            m->prior = q;
        q->next = m;
        q->prior = p;
        p->next = q;
        return SUCCESS;
    }
    else
        return ERROR;
}

/**
 *  @name        : Status DeleteList_DuL(DuLNode *p, ElemType *e)
 *	@description : delete the first node after the node p and assign its value to e
 *	@param		 : p, e
 *	@return		 : status
 *  @notice      : None
 */
Status DeleteList_DuL(DuLNode *p, ElemType *e) {
    if (p)
    {
        DuLNode* m = p->next->next;
        *e = p->next->data;
        free(p->next);
        p->next = m;
        if (m)
            m->prior = p;
        return SUCCESS;
    }
    else
        return ERROR;
}

/**
 *  @name        : void TraverseList_DuL(DuLinkedList L, void (*visit)(ElemType e))
 *	@description : traverse the linked list and call the funtion visit
 *	@param		 : L(the head node), visit
 *	@return		 : Status
 *  @notice      : None
 */
void TraverseList_DuL(DuLinkedList L, void (*visit)(ElemType e)) {
    if (L)
    {
        visit(L->data);
        TraverseList_DuL(L->next, visit);
    }
}
