/************************************
> 作者：杭电羊皮卷
> weixin:QQ2997675141
************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//遍历链表
#define list_for_each(n,head)\
	for(n = head->next; head!=n; n=n->next)

//计算结构成员member所在结构中距离首地址的字节数
#define offset(type,member)\
	((int)&(((type*)0)->member))

//计算返回结构成员指针所在结构变量的首地址
#define node_to_obj(node,type,member)\
	((type*)((char* )node-offset(type,member)))

//第二种遍历方式
#define list_for_each_entery(obj,head,member)\
	for(obj = node_to_obj(head->next,typeof(*obj),member);\
		head!=&obj->member;\
		obj=node_to_obj(obj->member.next,typeof(*obj),member))

typedef struct Node{
	struct Node* prev;
	struct Node* next;
}Node;

//创建链表
Node* create_list(void)
{
	Node* head = malloc(sizeof(Node));
	head->next = head;
	head->prev = head;
	return head;
}

void _add_list(Node* prev,Node* next,Node* node)
{
	node->next = next;
	node->prev = prev;
	prev->next = node;
	next->prev = node;
}

//头添加
void add_head_list(Node* head,Node* node)
{
	_add_list(head,head->next,node);	
}

//尾添加
void add_tail_list(Node* head,Node* node)
{
	_add_list(head->prev,head,node);	
}

//删除节点
void _del_list(Node* node)
{
	node->next->prev = node->prev;
	node->prev->next = node->next;
	node->next = node;
	node->prev = node;
}

//判断链表是否为空
bool empty_list(Node* head)
{
	return head->next == head;	
}

//头删除
Node* del_head_list(Node* head)
{
	if(empty_list(head))	return NULL;
	Node* temp = head->next;
	_del_list(temp);
	return temp;
}
//尾删除
Node* del_tail_list(Node* head)
{
	if(empty_list(head))	return NULL;
	Node* temp = head->prev;
	_del_list(temp);
	return temp;
}
/*		下面为用户编写的代码	*/
typedef struct Student{
	char name[20];
	char sex;
	Node node;
	char age;
	float score;
	int id;
}Student;
int main(int argc,const char* argv[])
{
	Node* head = create_list();
	Student* s = malloc(sizeof(Student));
	for(int i=0; i<10; i++)
	{
		Student* s = malloc(sizeof(Student));
		sprintf(s->name,"str%d",i);
		s->sex = i%2?'w':'m';
		s->age = i+18;
		s->score = rand()%100;
		s->id = 1000+i*10;
		//add_head_list(head,&s->node);
		add_tail_list(head,&s->node);
	}
	Student* stu=NULL;
	list_for_each_entery(stu,head,node)
	{
		printf("%s %c %hhd %g %d\n",stu->name,stu->sex,stu->age,stu->score,stu->id);
	}

/*	
	Node* n =NULL;
	list_for_each(n,head)
	{
		Student* stu = node_to_obj(n,Student,node);//这里使用到地址偏移找到结构体入口
		printf("%s %c %hhd %g %d\n",stu->name,stu->sex,stu->age,stu->score,stu->id);
	}
	*/
//	Student* s1 = (Student* )del_tail_list(head);
/*
	n=NULL;
	printf("-------------------\n");
	list_for_each(n,head)
	{
		Student* stu = (Student* )n;
		printf("%s %c %hhd %g %d\n",stu->name,stu->sex,stu->age,stu->score,stu->id);
	}
	printf("%s %c %hhd %g %d\n",s1->name,s1->sex,s1->age,s1->score,s1->id);
	*/

	return 0;
}
