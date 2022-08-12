/************************************
> 作者：杭电羊皮卷
> weixin:QQ2997675141
************************************/
#include "list_queue.h"

Node* create_node(TYPE data)
{
	Node* node = (Node* )malloc(sizeof(Node));
	node->data = data;
	node->next = NULL;
	return node;
}

//创建
ListQueue* create_list_queue(void)
{
	ListQueue* queue = malloc(sizeof(ListQueue));
	queue->front = NULL;
	queue->tail = NULL;
	queue->cnt = 0;
	return queue;
}
//队空
bool empty_list_queue(ListQueue* queue)
{
	return 0 == queue->cnt;	
}

//入队
void push_list_queue(ListQueue* queue,TYPE val)
{
	Node* node = create_node(val);
	if(empty_list_queue(queue))
	{
		queue->front = node;
		queue->tail = node;
	}
	else
	{
		queue->tail->next = node;
		queue->tail = node;
	}
	queue->cnt++;
}

//出队
bool pop_list_queue(ListQueue* queue)
{
	if(empty_list_queue(queue))	return false;
	Node* n = queue->front;
	queue->front = n->next;
	queue->cnt--;
	if(0 == queue->cnt)	queue->tail = NULL;
	free(n);
	return true;
}

//队头
TYPE front_list_queue(ListQueue* queue)
{
	return queue->front->data;	
}

//队尾
TYPE back_list_queue(ListQueue* queue)
{
	return queue->tail->data;	
}

//数量
size_t size_list_queue(ListQueue* queue)
{
	return queue->cnt;	
}


//销毁
void destory_list_queue(ListQueue* queue)
{
	while(pop_list_queue(queue));
	free(queue);
}

