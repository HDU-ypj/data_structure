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

//头添加
void add_head_list(Node** head,int val)
{
	Node* node = create_node(val);
	node->next = *head;
	*head = node;
}

//按值删除
bool del_value_list(Node** head,TYPE data)
{
	if(data == (*head)->data)
	{
		Node* temp = *head;	
		*head = (*head)->next;
		free(temp);
		return true;
	}
	for(Node* n=*head; n->next!=NULL; n=n->next)
	{
		if(n->next->data == data)
		{
			Node* temp = n->next;
			n->next = temp->next;
			free(temp);
			return true;
		}
	}
	return false;
}

bool del_index_list(Node** head,size_t index)
{
	if(index == 0)
	{
		Node* node = *head;
		*head = node->next;
		free(node);
		return true;
	}
	Node* pre=*head;
	/*
	while(0 < --index)
	{
		pre = pre->next;
		if(NULL == pre->next)
		{
			return false;	
		}
	}
	*/
	for(int i=0;i<index-1;i++)
	{
		pre = pre->next;
		if(pre == NULL)
		{
			return false;	
		}
	}
	Node* temp = pre->next;
	pre->next = temp->next;
	free(temp);
	return true;
}
//排序
void sort_list(Node* head)
{
	for(Node* i=head; i->next!=NULL; i=i->next)
	{
		for(Node* j=i->next;j!=NULL;j=j->next)
		{
			if(i->data > j->data)
			{
				TYPE temp = i->data;
				i->data = j->data;
				j->data = temp;
			}
		}
	}
}
//遍历
void show_list(Node* head)
{
	for(Node* n=head; n!=NULL; n=n->next)
	{
		printf("%d ",n->data);
	}
	printf("\n");
}
//访问
bool access_list(Node* head,int index,TYPE* val)
{
	Node* node = head;
	for(int i=0; i<index; i++)
	{
		node = node->next;
		if(node == NULL)	return false;
	}
	*val = node->data;
	return true;
}
int main(int argc,const char* argv[])
{
	Node* head = NULL;
	for(int i=0; i<10; i++)
	{
		add_head_list(&head,i+1);	
	}
	show_list(head);
	del_value_list(&head,4);
	show_list(head);
	sort_list(head);
	show_list(head);
	TYPE num = 0;
	access_list(head,8,&num);
	printf("%d\n",num);
	del_index_list(&head,2);
	show_list(head);
	/*
	Node* n1 = create_node(1);
	Node* n2 = create_node(2);
	Node* n3 = create_node(3);
	Node* n4 = create_node(4);
	Node* n5 = create_node(5);

	n1->next = n2;
	n2->next = n3;
	n3->next = n4;
	n4->next = n5;

	for(Node* n=n1; n!=NULL; n=n->next)
	{
		printf("%d ",n->data);	
	}
	*/

	return 0;
}
