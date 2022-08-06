/************************************
> 作者：杭电羊皮卷
> QQ:2997675141
> weixin:QQ2997675141
************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TYPE int
//设计链表中节点的类型
typedef struct Node{
	TYPE data;			//节点数据域
	struct Node* next;	//节点指针域
}Node;

//创建节点
Node* create_node(TYPE data)
{
	//分配节点所需要的内存
	Node* node = (Node* )malloc(sizeof(Node));
	node->data = data;
	node->next = NULL;
}

void add_head_list(Node* head,TYPE val)
{
	Node* node = create_node(val);
	node->next = head->next;
	head->next = node;
}
void add_tail_list(Node* head,TYPE val)
{
	while(head->next != NULL)
	{
		head = head->next;	
	}
	Node* node = create_node(val);
	head->next = node;
}
bool del_value_list(Node* head,TYPE val)
{
	while(head->next != NULL)
	{
		if(head->next->data == val)
		{
			Node* temp;
			temp = head->next;
			head->next = temp->next;
			free(temp);
			return true;
		}
	}
	return false;
}
bool del_index_list(Node* head,size_t index)
{
	Node* n = head;
	if(NULL == n->next)	return false;
	for(int i=0; i<index; i++)
	{
		if(NULL == n->next)	return false;
		n=n->next;	
	}
	if(NULL == n->next)	return false;
	Node* temp = n->next;
	n->next = temp->next;
	free(temp);
	return true;
}
bool insert_list(Node* head,size_t index,TYPE val)
{
	Node* n = head;
	if(n->next == NULL || index == 0)	return false;
	for(int i=0; i<index; i++)
	{
		n = n->next;
		if(NULL == n->next)	return false;
	}
	Node* node = create_node(val);
	node->next = n->next;
	n->next = node;
	return true;
}
bool modify_list(Node* head,TYPE old,TYPE new)
{
	for(Node* n=head; NULL!=n; n=n->next)
	{
		if(n->data == old)
		{
			n->data = new;
			return true;
		}
	}
	return false;
}
bool access_list(Node* head,size_t index,TYPE* val)
{
	Node* n = head->next;
	if(NULL == n)	return false;
	for(int i=0; i<index; i++)
	{
		n = n->next;
		if(NULL == n)	return false;	
	}
	*val = n->data;
	return true;
}
int query_list(Node* head,TYPE val)
{
	Node* n = head->next;
	for(int i=0; NULL!=n; i++)
	{
		if(n->data == val)	return i;	
		n = n->next;
	}
	return -1;
}
void sort_list(Node* head)
{
	for(Node* i=head->next; i->next!=NULL; i=i->next)
	{
		for(Node* j=i->next; j!=NULL; j=j->next)
		{
			if(i->data > j->data)
			{
				TYPE t= j->data;
				j->data = i->data;
				i->data = t;
			}
		}
	}
}
void show_list(Node* head)
{
	for(Node* node = head->next; node!=NULL; node=node->next)
	{
		printf("%d ",node->data);	
	}
	printf("\n");
}
int main()
{
	//head就是带头节点链表的头节点
	//head->next永远指向第一个有效数据的节点
	Node* head = create_node(0);
	for(int i=0;i<10;i++)
	{
		add_tail_list(head,rand()%100);
//		add_head_list(head,rand()%100);	
	}
	show_list(head);
//	del_index_list(head,10);
//	show_list(head);
	insert_list(head,2,15);
	show_list(head);

}
