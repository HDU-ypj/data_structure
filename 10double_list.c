/************************************
> 作者：杭电羊皮卷
> weixin:QQ2997675141
************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TYPE int

//封装双向链表
typedef struct Node{
	struct Node* prev;//前趋
	TYPE data;
	struct Node* next;//后继
}Node;

//双向链表都是循环的
Node* create_node(TYPE data)
{
	Node* node = malloc(sizeof(Node));
	node->data = data;
	node->next = node;
	node->prev = node;//在循环链表中不可能出现指向NULL，指针指向自己表示循环
}

//双向链表
typedef struct DoubleList{
	Node* head;
	size_t size;
}DoubleList;

//创建链表
DoubleList* create_double_list(void)
{
	DoubleList* list = malloc(sizeof(DoubleList));
	list->head = create_node(0);	//创建带头节点
	list->size = 0;
}

//依赖函数：在前趋和后继之间添加一个新节点
static void _add_list(Node* p,Node* n,TYPE val)
{
	Node* node = create_node(val);
	node->next = n;
	node->prev = p;
	p->next = node;
	n->prev = node;
}

//依赖函数：删除当前节点
static void _del_list(Node* node)
{
	node->prev->next = node->next;
	node->next->prev = node->prev;
	free(node);
}

//依赖函数：返回指定值的节点
static Node* _value_list(DoubleList* list,TYPE data)
{
	for(Node* n = list->head->next; n!=list->head; n=n->next)
	{
		if(data == n->data)	return n;	
	}
	return NULL;
}
//依赖函数：返回指定位置的节点
static Node* _index_list(DoubleList* list,size_t index)
{
	if(index >= list->size)	return NULL;
	if(index < list->size/2)
	{
		//从前往后找
		Node* n=list->head->next;
		while(index--)
		{
			n = n->next;	
		}
		return n;
	}
	else
	{
		//从后往前找
		Node* n = list->head->prev;	
		while(++index < list->size)
		{
			n = n->prev;	
		}
		return n;
	}
}





//头添加
void add_head_list(DoubleList* list,TYPE val)
{
	_add_list(list->head,list->head->next,val);
	list->size++;
}

//尾添加
void add_tail_list(DoubleList* list,TYPE val)
{
	_add_list(list->head->prev,list->head,val);
	list->size++;
}

//插入
bool inset_list(DoubleList* list,size_t index,TYPE val)
{
	Node* node = _index_list(list,index);	
	if(NULL == node)	return false;
	_add_list(node->prev,node,val);
	list->size++;
	return true;
}

//按位置修改
bool modify_index_list(DoubleList* list,size_t index,TYPE val)
{
	Node* node = _index_list(list,index);
	if(NULL == node)	return false;
	node->data = val;
	return true;
}

//按值修改
size_t modify_value_list(DoubleList* list,TYPE old,TYPE val)
{
	size_t cnt=0;
	for(Node* n = list->head->next; n!=list->head; n=n->next)
	{
		if(old == n->data)
		{
			n->data = val;
			cnt++;
		}
	}
	return cnt;	
}

//访问
bool access_list(DoubleList* list,size_t index,TYPE* val)
{
	Node* node = _index_list(list,index);
	if(NULL == node)	return false;
	*val = node->data;
	return true;
}

//查询
int query_list(DoubleList* list,TYPE val)
{
	Node* n = list->head->next;
	for(int i=0; i<list->size; i++)	
	{
		if(val == n->data)
		{
			return i;	
		}
		n = n->next;
	}
	return -1;
}

//按位置删除
bool del_index_list(DoubleList* list,size_t index)
{
	Node* node = _index_list(list,index);
	if(NULL == node)	return false;
	_del_list(node);
	list->size--;
	return true;
}

//按值删除
bool del_value_list(DoubleList* list,TYPE val)
{
	Node* node = _value_list(list,val);	
	if(NULL == node)	return false;
	_del_list(node);
	list->size--;
	return true;
}

//遍历
void show_list(DoubleList* list)
{
	for(Node* n = list->head->next; n!=list->head; n=n->next)
	{
		printf("%d ",n->data);	
	}
	printf("\n");
}
//清空
void clear_list(DoubleList* list)
{
	Node* n = list->head->next;
	while(n!=list->head)
	{
		Node* temp = n;
		n = n->next;
		free(temp);
	}
	//头节点还原
	list->head->next = list->head;
	list->head->prev = list->head;
	list->size = 0;
}

//销毁
void destroy_list(DoubleList* list)
{
	clear_list(list);
	free(list->head);
	free(list);
}


int main(int argc,char* argv[])
{
	DoubleList* list = create_double_list();
	for(int i=0; i<10; i++)
	{
		add_tail_list(list,i);	
	}
	show_list(list);
	inset_list(list,6,88);
	show_list(list);
	TYPE num=-100;
	access_list(list,1,&num);
	printf("%d\n",num);
	modify_value_list(list,3,88);
	show_list(list);
	del_index_list(list,1);
	show_list(list);
	del_value_list(list,5);
	show_list(list);
	modify_value_list(list,88,-1);
	show_list(list);
	printf("index = %d\n",query_list(list,90));
	return 0;	
}
