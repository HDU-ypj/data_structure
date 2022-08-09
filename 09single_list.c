/************************************
> 作者：杭电羊皮卷
> weixin:QQ2997675141
************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TYPE int

//封装了带头节点的单链表

typedef struct Node{
	TYPE data;
	struct Node* next;
}Node;

Node* create_node(TYPE data)
{
	Node* node = malloc(sizeof(Node));
	node->data = data;
	node->next = NULL;
	return node;
}

//封装一个单链表结构
typedef struct List{
	Node* head;		//头指针
	Node* tail;		//尾指针
	size_t size;	//节点数量
}List;

//创建单链表结构
List* create_list(void)
{
	List* list = malloc(sizeof(List));
	list->size = 0;
	list->head = create_node(0);	//带头节点的链表
	list->tail = NULL;	
	return list;
}

//头添加
void add_head_list(List* list,TYPE val)
{
	Node* node = create_node(val);
	if(0 == list->size)
	{
		list->head->next = node;
		list->tail = node;
	}
	else
	{
		node->next = list->head->next;
		list->head->next = node;
	}
	list->size++;
}

//尾添加
void add_tail_list(List* list,TYPE val)
{
	Node* node = create_node(val);
	if(0 == list->size)
	{
		list->head->next = node;
		list->tail = node;
	}
	else
	{
		list->tail->next = node;
		list->tail = node;
	}
	list->size++;
}

bool del_head_list(List* list)
{
	if(0 == list->size)	return false;
	Node* temp = list->head->next;
	list->head->next = temp->next;
	if(1 == list->size)	//如果只有一个元素可以删除，则需要改变尾指针
	{
		list->tail = NULL;	
	}
	list->size--;
	free(temp);
	return true;
}

bool del_tail_list(List* list)
{
	if(0 == list->size)	return false;
	free(list->tail);
	if(1 == list->size)
	{
		list->head = NULL;
		list->tail = NULL;
	}
	else
	{
		Node* prev = list->head->next;
		while(prev->next != list->tail)
		{
			prev = prev->next;	
		}
		prev->next = NULL;
		list->tail = prev;
	}
}

//要求不能插入到开头和结尾
bool insert_list(List* list,size_t index,TYPE val)
{
	if(0 == index || index >= list->size)	return false;
	Node* node = create_node(val);
	Node* prev = list->head->next;
	for(int i=1; i<index; i++)
	{
		prev = prev->next;
	}
	node->next = prev->next;
	prev->next = node;
	list->size++;
	return true;
}

//按值删除
bool del_value_list(List* list,TYPE val)
{
	if(val == list->head->next->data)
	{
		return del_head_list(list);	
	}
	if(val == list->tail->data)
	{
		return del_tail_list(list);	
	}
	for(Node* n=list->head->next; n->next!=NULL; n=n->next)
	{
		Node* temp = n->next;
		n->next = temp->next;
		free(temp);
		list->size--;
		return true;
	}
	return false;
}

//按位置删除
bool del_index_list(List* list,size_t index)
{
	if(list->size <= index)	return false;
	if(0 == index)	return del_head_list(list);
	if(index == list->size-1)	return del_tail_list(list);
	Node* prev = list->head->next;
	for(int i=1; i<index; i++)
	{
		prev = prev->next;	
	}
	Node* temp = prev->next;
	prev->next = temp->next;
	free(temp);
	list->size--;
	return true;
}

//按位置修改
bool modify_index_list(List* list,size_t index,TYPE val)
{
	if(index >= list->size)	return false;
	Node* n = list->head->next;
	for(int i=0; i<index; i++)
	{
		n=n->next;	
	}
	n->data = val;
	return true;
}
//按值修改
size_t modify_value_list(List* list,TYPE old,TYPE val)
{
	Node* node = list->head->next;
	size_t count=0;
	while(node != NULL)
	{
		if(node->data == old)
		{
			node->data = val;	
			count++;
		}
		node = node->next;
	}
	return count;
}
//查询
int query_list(List* list,TYPE val)
{
	int cnt=0;
	Node* node = list->head->next;
	while(node != NULL)
	{
		if(node->data == val)
		{
			return cnt;	
		}
		cnt++;
		node = node->next;
	}
	return -1;
}
//访问
bool access_list(List* list,size_t index,TYPE* val)
{
	if(index >= list->size)	return false;
	Node* node = list->head->next;
	for(int i=0; i<index; i++)
	{
		node = node->next;
	}
	*val = node->data;
	return true;
}
//排序
void sort_list(List* list)
{
	for(Node* i=list->head->next; i->next!=NULL; i=i->next)
	{
		for(Node* j=i->next; j!=NULL; j=j->next)
		{
			if(i->data >j->data)
			{
				TYPE data = i->data;
				i->data = j->data;
				j->data = data;
			}
		}
	}
}
//清空
void clear_list(List* list)
{
	//while(del_head_list(list));	
	while(list->head->next!=NULL)
	{
		Node* temp = list->head->next;	
		list->head->next = temp->next;
		free(temp);
	}
	list->tail = NULL;
	list->size = 0;
}
//销毁
void destory_list(List* list)
{
	while(del_head_list(list));
	free(list->head);
	free(list);
}

//遍历
void show_list(List* list)
{
	for(Node* n=list->head->next; n!=NULL; n=n->next)
	{
		printf("%d ",n->data);	
	}
	printf("\n");
}
int main(int argc,const char* argv[])
{
	List* list = create_list();
	for(int i=0; i<10; i++)
	{
		add_head_list(list,i);	
	}
	show_list(list);
	insert_list(list,1,45);
	insert_list(list,1,45);
	insert_list(list,1,45);
	//show_list(list);
	del_index_list(list,1);
	del_index_list(list,6);
	show_list(list);
	modify_index_list(list,0,44);
	show_list(list);
	modify_value_list(list,45,0);
	show_list(list);
	return 0;
}
