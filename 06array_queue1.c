/************************************
> 作者：杭电羊皮卷
> QQ:2997675141
> weixin:QQ2997675141
************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TYPE int
typedef struct ArrayQueue{
	TYPE* ptr;
	size_t cal;
	size_t front;	//队头下标
	size_t tail;	//指向即将入队的位置
}ArrayQueue;

//创建队列结构
ArrayQueue* create_array_queue(size_t cal)
{
	ArrayQueue* queue = (ArrayQueue* )malloc(sizeof(ArrayQueue));
	//申请内存时多申请一个解决队满和队空的判断问题
	queue->ptr = (TYPE* )malloc(sizeof(TYPE)*(cal+1));
	queue->cal = cal+1;
	queue->front = 0;
	queue->tail = 0;
	return queue;
}

//销毁
void destory_array_queue(ArrayQueue* queue)
{
	free(queue->ptr);
	free(queue);
}
//队空
bool empty_array_queue(ArrayQueue* queue)
{
	return queue->front == queue->tail;	
}
//队满
bool full_array_queue(ArrayQueue* queue)
{
	return (queue->tail+1)%queue->cal == queue->front;	
}

//出队
bool pop_array_queue(ArrayQueue* queue,TYPE* val)
{
	if(empty_array_queue(queue))	return false;
	*val = queue->ptr[queue->front];
	queue->front = (queue->front+1)%queue->cal;
	return true;
}

//入队
bool push_array_queue(ArrayQueue* queue,TYPE val)
{
	if(full_array_queue(queue))	return false;
	queue->ptr[queue->tail] = val;
	queue->tail = (queue->tail+1)%queue->cal;
	return true;
}

//队尾
TYPE back_array_queue(ArrayQueue* queue)
{
	return queue->ptr[(queue->tail-1+queue->cal)%queue->cal];	
}

//队头
TYPE front_array_queue(ArrayQueue* queue)
{
	return queue->ptr[queue->front];	
}

//数量
size_t size_array_queue(ArrayQueue* queue)
{
	return (queue->tail+queue->cal-queue->front)%queue->cal;	
}


int main(int argc,const char* argv[])
{
	ArrayQueue* queue = create_array_queue(10);
	for(int i=0; i<10; i++)
	{
		push_array_queue(queue,i);
		printf("tail = %d\n",back_array_queue(queue));
	}
	return 0;
}
