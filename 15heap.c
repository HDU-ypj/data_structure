/**************************************************
>	作	  者：杭电羊皮卷
>   文件名称: heap.c
>	联系方式：weixin:QQ2997675141
>   创建日期：2022年08月16日
>   描    述：堆的相关操作，排序,堆还可用于有限队列的创建
**************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//定义交换宏函数
#define SWAP(a,b)	{typeof(a) t=(a);(a)=(b);(b)=t;}

/**************************************************
 @func向下调整堆结构
 @arr:需要调整数组
 @start:开始调整的下标
 @end:结束调整的下标
**************************************************/
void change_down(int* arr,int start,int end)
{
	int parent = start;		//parent始终是父亲节点的下标
	int child = parent*2+1;	//child是左孩子的下标
	while(child<=end)
	{
		//判断是否越界，同时比较左右孩子的大小值，更新child
		if(child+1<=end && arr[child]<arr[child+1])
		{
			child++;
		}
		//如果父节点比孩子节点还要大，则不需要调整了
		if(arr[parent]>arr[child])
		{
			return;
		}
		//否则交换父亲节点和最大孩子节点的值
		SWAP(arr[parent],arr[child]);
		//刷新父亲孩子节点的下标值
		parent = child;
		child = 2*parent+1;
	}
}

/**************************************************
 @func:向上调整
 @arr:需要调整的数组
 @start:需要调整的节点下标
**************************************************/
void change_up(int* arr,int start)
{
	int child = start;			//孩子节点的下标
	int parent = (child-1)/2;	//父亲节点的下标
	while(child>0)
	{
		if(arr[parent]<arr[child])
		{
			SWAP(arr[parent],arr[child]);
			child = parent;
			parent = (child-1)/2;
		}
		else
		{
			break;
		}
	}
}

/**************************************************
 @func:向上调整法创建堆结构
 @arr:需要调整的数组
 @len:数组的长度
**************************************************/
void create_heap_up(int* arr,int len)
{
	for(int i=1; i<len; i++)
	{
		change_up(arr,i);
	}
}

/**************************************************
 @func:向下调整法创建堆结构
 @arr:传入需要成堆的数组
 @len:数组的长度
**************************************************/
void create_heap_down(int* arr,int len)
{
	//从最后一个父亲节点开始，依次向下调整
	for(int i=len/2-1; i>=0; i--)
	{
		change_down(arr,i,len-1);
	}
}

/**************************************************
 @func:堆排序
 @arr:传入需要堆排序的数组
 @len:数组长度
**************************************************/
void heap_sort(int* arr,int len)
{
	//创建堆结构
	create_heap_up(arr,len);
	//每次交换最后和开头，从0开始往下调整
	for(int i=len-1; i>0; i--)
	{
		SWAP(arr[i],arr[0]);
		change_down(arr,0,i-1);
	}
}

/**************************************************
 @func:打印数组
 @arr:需要打印的数组
 @len:数组长度
**************************************************/
void arr_show(int* arr,int len)
{
	for(int i=0; i<len; i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
}



int main(int argc,const char* argv[])
{
	int arr[]={1,8,5,4,7,9,6,8,5,4,3};
	heap_sort(arr,sizeof(arr)/sizeof(arr[0]));
	arr_show(arr,sizeof(arr)/sizeof(arr[0]));
	return 0;
}
