/************************************
> 作者：杭电羊皮卷
> QQ:2997675141
> weixin:QQ2997675141
************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TYPE int
//设计顺序栈结构
typedef struct ArrayStack{
	TYPE* ptr;	//储存元素内存首地址
	size_t cal;	//栈的容量
	size_t top;	//栈顶下标，从零开始，空增栈
}ArrayStack;


//创建
ArrayStack* create_array_stack(size_t cal)
{
	//为栈结构分配内存
	ArrayStack* stack = (ArrayStack* )malloc(sizeof(ArrayStack));
	//分配储存元素的内存
	stack->ptr = (TYPE* )malloc(sizeof(TYPE)*cal);
	//记录栈容量
	stack->cal = cal;
	//记录栈顶位置，接下来要入栈的位置
	stack->top = 0;
	return stack;
}
//销毁
void destory_array_stack(ArrayStack* stack)
{
	free(stack->ptr);
	free(stack);
}
//栈空
bool empty_array_stack(ArrayStack* stack)
{
	return 0 == stack->top;	
}
//栈满
bool full_array_stack(ArrayStack* stack)
{
	return stack->top >= stack->cal;	
}
//入栈
bool push_array_stack(ArrayStack* stack,TYPE val)
{
	if(full_array_stack(stack))	return false;
	stack->ptr[stack->top++] = val;
	return true;
}
//出栈
bool pop_array_stack(ArrayStack* stack)
{
	if(empty_array_stack(stack))	return false;
	stack->top--;
	return true;
}
//栈顶
bool top_array_stack(ArrayStack* stack,TYPE* val)
{
	if(empty_array_stack(stack))	return false;
	*val = stack->ptr[stack->top-1];
	return true;
}
bool is_pop_stack(int *a,int *b,size_t len)
{
	ArrayStack* stack = create_array_stack(len);
	int val=0;
	for(int i=0,j=0; i<len; i++)
	{
		//按照a的顺序一个一个入栈
		push_array_stack(stack,a[i]);
		//按照b的顺序尝试出栈
		while(top_array_stack(stack,&val) && val == b[j])
		{
			pop_array_stack(stack);
			j++;
		}
	}
	bool res = empty_array_stack(stack);
	destory_array_stack(stack);
	return res;
}
int main(int argc,const char* argv[])
{
	TYPE top_num=-100;
	int a1[]={1,2,3,4,5};
	int a2[]={2,3,1,5,4};
	ArrayStack* stack = create_array_stack(10);
	printf("res = %d\n",is_pop_stack(a1,a2,5));
	for(int i=0; i<10; i++)
	{
		push_array_stack(stack,i+1);	
		top_array_stack(stack,&top_num) && printf("%d ",top_num);
	}
	printf("\n");
	for(int i=0; i<10; i++)
	{
		top_array_stack(stack,&top_num) && printf("%d ",top_num);
		pop_array_stack(stack);
	}
	printf("\n");
	return 0;
}
