#ifndef LIST_QUEUE_H
#define LIST_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TYPE int

typedef struct Node{
	TYPE data;
	struct Node* next;
}Node;
typedef struct ListQueue{
	Node* front;//对头节点
	Node* tail;	//队尾节点
	size_t cnt;	//节点数量
}ListQueue;

//创建
ListQueue* create_list_queue(void);
//队空
bool empty_list_queue(ListQueue* queue);
//入队
void push_list_queue(ListQueue* queue,TYPE val);
//出队
bool pop_list_queue(ListQueue* queue);
//队头
TYPE front_list_queue(ListQueue* queue);
//队尾
TYPE back_list_queue(ListQueue* queue);

//数量
size_t size_list_queue(ListQueue* queue);
//销毁
void destory_list_queue(ListQueue* queue);
#endif

