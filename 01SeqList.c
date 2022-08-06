/************************************
> 作者：杭电羊皮卷
> QQ:2997675141
> weixin:QQ2997675141
************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define TYPE int
// 设计顺序表结构

typedef struct Array{
	TYPE* ptr;	//存储元素的内存首地址
	size_t cal;	//表的容量
	size_t cnt;	//已存储元素的数量
}Array;

//创建
Array* create_array(size_t cal);
//销毁
void destory_array(Array* arr);
//清空
void clean_array(Array* arr);
//插入
bool insert_array(Array* arr,int index,TYPE val);
//删除
bool delete_array(Array* arr,size_t index);
//访问
bool access_array(Array* arr,size_t index,TYPE* val);
//查询
int query_array(Array* arr,TYPE val);
//修改
bool modify_array(Array* arr,size_t index,TYPE val);
//排序
void sort_array(Array* arr);
//遍历
void show_array(Array* arr);



//创建
Array* create_array(size_t cal)
{
	//分配顺序表结构的内存
	Array* arr=(Array*)malloc(sizeof(Array));
	if(arr == NULL)
	{
		return NULL;	
	}
	//分配储存元素的内存
	arr->ptr = (TYPE*)malloc(sizeof(TYPE)*cal);
	arr->cal = cal;
	arr->cnt = 0;
	return arr;
}
//销毁
void destory_array(Array* arr)
{
	free(arr->ptr);
	free(arr);
}
//清空
void clean_array(Array* arr)
{
	arr->cnt = 0;	
}
//插入
bool insert_array(Array* arr,int index,TYPE val)
{
	//判断表是否满
	if(arr->cal <= arr->cnt)	return false;
	if(index > arr->cnt || index < 0)	return false;
	/*
	for(int i=arr->cnt; i>index; i--)
	{
		arr->ptr[i] = arr->ptr[i-1];	
	}
	*/
	memmove(arr->ptr+index+1,arr->ptr+index,(arr->cnt-index)*sizeof(TYPE));
	arr->ptr[index] = val;
	arr->cnt++;
	return true;
}
//删除
bool delete_array(Array* arr,size_t index)
{
	if(index >= arr->cnt)	return false;
	/*
	for(int i=index;i<arr->cnt-1;i++)
	{
		arr->ptr[i] = arr->ptr[i+1];	
	}
	*/
	memmove(arr->ptr+index,arr->ptr+index+1,sizeof(TYPE)*arr->cnt-index-1);
	arr->cnt--;
	return true;
}
//访问
bool access_array(Array* arr,size_t index,TYPE* val)
{
	if(index >= arr->cnt)	return false;	
	*val = arr->ptr[index];
	return true;
}
//查询
int query_array(Array* arr,TYPE val)
{
	for(int i=0; i<arr->cnt; i++)
	{
		if(arr->ptr[i] == val)
		{
			return i;	
		}
	}
	return -1;
}
//修改
bool modify_array(Array* arr,size_t index,TYPE val)
{
	if(index >= arr->cnt)	return false;
	arr->ptr[index] = val;
	return true;
}
//排序
void sort_array(Array* arr)
{
	for(int i=0; i<arr->cnt-1; i++)
	{
		for(int j=i+1; j<arr->cnt;j++)
		{
			if(arr->ptr[i]>arr->ptr[j])
			{
				TYPE temp;
				temp = arr->ptr[i];
				arr->ptr[i] = arr->ptr[j];
				arr->ptr[j] = temp;
			}
		}
	}
}
//遍历
void show_array(Array* arr)
{
	if(arr == NULL)	return;
	for(int i=0; i<arr->cnt;i++)
	{
		printf("%d ",arr->ptr[i]);	
	}
	printf("\n");
}


int main(int argc,const char* argv[])
{
	Array* arr;
	arr = create_array(10);
	for(int i=0; i<5; i++)
	{
		insert_array(arr,0,i+1);	
	}
	show_array(arr);
//	insert_array(arr,1,8);	
	delete_array(arr,0);
	show_array(arr);
	TYPE num=0;
	access_array(arr,5,&num);
	printf("%d\n",num);
	printf("%d\n",query_array(arr,3));
	sort_array(arr);
	show_array(arr);
	destory_array(arr);
	arr = NULL;
	return 0;
}
