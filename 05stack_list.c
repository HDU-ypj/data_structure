/************************************
> 作者：杭电羊皮卷
> QQ:2997675141
> weixin:QQ2997675141
************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TYPE int

typedef struct Node{
	TYPE data;
	struct Node* next;
}Node;

//创建节点
Node* create_node(TYPE data)
{
	Node* node = malloc(sizeof(Node));
	node->data = data;
	node->next = NULL;
	return node;
}

//设计链式栈结构
typedef struct ListStack{
	Node* top;
	size_t cnt;
}ListStack;

//创建栈结构
ListStack* create_list_stack(void)
{
	ListStack* stack = malloc(sizeof(ListStack));
	stack->top = NULL;
	stack->cnt = 0;
	return stack;
}


//入栈
void push_list_stack(ListStack* stack,TYPE val)
{
	Node* node = create_node(val);
	node->next = stack->top;
	stack->top = node;
	stack->cnt++;
}

//栈顶
TYPE top_list_stack(ListStack* stack)
{
	return stack->top->data;	
}

//栈空
bool empty_list_stack(ListStack* stack)
{
	return stack->cnt == 0;	
}
//出栈
bool pop_list_stack(ListStack* stack)
{
	if(empty_list_stack(stack))	return false;
	Node* temp = stack->top;
	stack->top = stack->top->next;
	stack->cnt--;
	free(temp);
	return true;
}
//数量 保持数据结构的封装行不被打破
size_t size_list_stack(ListStack* stack)
{
	return stack->cnt;	
}
//销毁栈
void destory_list_stack(ListStack* stack)
{
	//把所有节点释放
	while(pop_list_stack(stack));
	//释放栈结构
	free(stack);
}
int main(int argc,const char* argv[])
{
	ListStack* stack = create_list_stack();
	for(int i=0; i<10; i++)
	{
		push_list_stack(stack,i+1);
		printf("top:%d\n",top_list_stack(stack));
	}
	while(!empty_list_stack(stack))
	{
		printf("top:%d\n",top_list_stack(stack));
		pop_list_stack(stack);
	}
	destory_list_stack(stack);
	ListStack* s = create_list_stack();
	push_list_stack(stack,10);
	printf("s=%d\n",top_list_stack(stack));
	stack = NULL;
	return 0;
}
