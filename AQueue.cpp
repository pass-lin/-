#include"AQueue.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
extern char type;
extern char datatype[MAXQUEUE];
/**
 *  @name        : void InitAQueue(AQueue *Q)
 *    @description : 初始化队列
 *    @param         Q 队列指针Q
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
 *    @description : 销毁队列
 *    @param         Q 队列指针Q
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
 *    @description : 检查队列是否已满
 *    @param         Q 队列指针Q
 *    @return         : 满-TRUE; 未满-FALSE
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
 *    @description : 检查队列是否为空
 *    @param         Q 队列指针Q
 *    @return         : 空-TRUE; 未空-FALSE
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
 *    @description : 查看队头元素
 *    @param         Q 队列指针Q，存放元素e
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否空
 */
Status GetHeadAQueue(AQueue* Q, void* e)
{
    if (IsEmptyAQueue(Q))
        return FALSE;
    memcpy(e, Q->data[Q->front],MAXQUEUE);
}

/**
 *  @name        : int LengthAQueue(AQueue *Q)
 *    @description : 确定队列长度
 *    @param         Q 队列指针Q
 *    @return         : 队列长度count
 *  @notice      : None
 */
int LengthAQueue(AQueue* Q)
{
    return  (Q->rear - Q->front + Q->length) % Q->length;
}

/**
 *  @name        : Status EnAQueue(AQueue *Q, void *data)
 *    @description : 入队操作
 *    @param         Q 队列指针Q,入队数据指针data
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否满了或为空
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
 *    @description : 出队操作
 *    @param         Q 队列指针Q
 *    @return         : 成功-TRUE; 失败-FALSE
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
 *    @description : 清空队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void ClearAQueue(AQueue* Q)
{
    Q->rear = Q->front = 0;
}
/**
 *  @name        : Status TraverseAQueue(const AQueue *Q, void (*foo)(void *q))
 *    @description : 遍历函数操作
 *    @param         Q 队列指针Q，操作函数指针foo
 *    @return         : None
 *  @notice      : None
 */
Status TraverseAQueue(const AQueue* Q, void (*foo)(void* q))
{
    if(IsEmptyAQueue(Q))
        return FALSE;
    for (int i = Q->front; i != Q->rear; i = (i + 1) % Q->length)
    {
        type = datatype[i];/*处理当前的类型type*/
        foo(Q->data[i]);
        
    }
    printf("\n");
    return TRUE;
}

/**
 *  @name        : void APrint(void *q)
 *    @description : 操作函数
 *    @param         q 指针q
 *  @notice      : None
 */
void APrint(void* q)
{
    printf("%c", type);
    switch (type)
    {/*先利用type判断类型再打印*/
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

