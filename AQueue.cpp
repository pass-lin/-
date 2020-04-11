#include"AQueue.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
extern char type;
extern char datatype[MAXQUEUE];
/**
 *  @name        : void InitAQueue(AQueue *Q)
 *    @description : ��ʼ������
 *    @param         Q ����ָ��Q
 *  @notice      : None
 */
void InitAQueue(AQueue* Q)
{
    for (int i = 0; i < MAXQUEUE; i++)
        Q->data[i] = malloc(MAXQUEUE);
    Q->front = Q->rear= 0;
    Q->length = MAXQUEUE;
}
/**
 *  @name        : void DestoryAQueue(AQueue *Q)
 *    @description : ���ٶ���
 *    @param         Q ����ָ��Q
 *  @notice      : None
 */
void DestoryAQueue(AQueue* Q)
{
    for (int i = 0; i < MAXQUEUE; i++)
        free(Q->data[i]);
    Q->front = Q->rear = 0;
    Q->length = 0;
}
/**
 *  @name        : Status IsFullAQueue(const AQueue *Q)
 *    @description : �������Ƿ�����
 *    @param         Q ����ָ��Q
 *    @return         : ��-TRUE; δ��-FALSE
 *  @notice      : None
 */
Status IsFullAQueue(const AQueue* Q)
{
    if (Q->front == (Q->rear + 1) % Q->length)
        return TRUE;
    else  return FALSE;
}
/**
 *  @name        : Status IsEmptyAQueue(const AQueue *Q)
 *    @description : �������Ƿ�Ϊ��
 *    @param         Q ����ָ��Q
 *    @return         : ��-TRUE; δ��-FALSE
 *  @notice      : None
 */
Status IsEmptyAQueue(const AQueue* Q)
{
    if (Q->front == Q->rear)
        return TRUE;
    else  return FALSE;
}

/**
 *  @name        : Status GetHeadAQueue(AQueue *Q, void *e)
 *    @description : �鿴��ͷԪ��
 *    @param         Q ����ָ��Q�����Ԫ��e
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : �����Ƿ��
 */
Status GetHeadAQueue(AQueue* Q, void* e)
{
    if (IsEmptyAQueue(Q))
        return FALSE;
    memcpy(e, Q->data[Q->front],MAXQUEUE);
}

/**
 *  @name        : int LengthAQueue(AQueue *Q)
 *    @description : ȷ�����г���
 *    @param         Q ����ָ��Q
 *    @return         : ���г���count
 *  @notice      : None
 */
int LengthAQueue(AQueue* Q)
{
    return  (Q->rear - Q->front + Q->length) % Q->length;
}

/**
 *  @name        : Status EnAQueue(AQueue *Q, void *data)
 *    @description : ��Ӳ���
 *    @param         Q ����ָ��Q,�������ָ��data
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : �����Ƿ����˻�Ϊ��
 */
Status EnAQueue(AQueue* Q, void* data)
{
    if (! IsFullAQueue(Q))
    {
        memcpy(Q->data[Q->rear], data, MAXQUEUE);
        Q->rear = (Q->rear + 1) % Q->length;
        return TRUE;
    }
    return FALSE;
}
/**
 *  @name        : Status DeAQueue(AQueue *Q)
 *    @description : ���Ӳ���
 *    @param         Q ����ָ��Q
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : None
 */
Status DeAQueue(AQueue* Q,void*data)
{
    if (IsEmptyAQueue(Q))
        return FALSE;
    memcpy(data, Q->data[Q->front], MAXQUEUE);
    Q->front = (Q->front + 1) % Q->length;
    return TRUE;
}
/**
 *  @name        : void ClearAQueue(Queue *Q)
 *    @description : ��ն���
 *    @param         Q ����ָ��Q
 *  @notice      : None
 */
void ClearAQueue(AQueue* Q)
{
    Q->rear = Q->front = 0;
}
/**
 *  @name        : Status TraverseAQueue(const AQueue *Q, void (*foo)(void *q))
 *    @description : ������������
 *    @param         Q ����ָ��Q����������ָ��foo
 *    @return         : None
 *  @notice      : None
 */
Status TraverseAQueue(const AQueue* Q, void (*foo)(void* q))
{
    if(IsEmptyAQueue(Q))
        return FALSE;
    for (int i = Q->front; i != Q->rear; i = (i + 1) % Q->length)
    {
        type = datatype[i];/*����ǰ������type*/
        foo(Q->data[i]);
        
    }
    printf("\n");
    return TRUE;
}

/**
 *  @name        : void APrint(void *q)
 *    @description : ��������
 *    @param         q ָ��q
 *  @notice      : None
 */
void APrint(void* q)
{
    printf("%c", type);
    switch (type)
    {/*������type�ж������ٴ�ӡ*/
    case 'd':printf("-->%d", *(int*)q); break;
    case 'c':printf("-->%c", *(char*)q); break;
    case 'f':printf("-->%f", *(float*)q); break;
    case 's':printf("-->%s", (char*)q); break;
    }
}

/**************************************************************
 *    End-Multi-Include-Prevent Section
 **************************************************************/
//#endif // AQUEUE_H_INCLUDED

