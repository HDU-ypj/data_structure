#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"

static void swap(void* s1,void* s2,size_t size)
{
	void* buf = malloc(size);
	memcpy(buf,s1,size);
	memcpy(s1,s2,size);
	memcpy(s2,buf,size);
	free(buf);
}

void sort_bubble(void* arr,size_t size,size_t len,Compare_t compare)
{
	int flag = 1;
	for(int i=len-1; i>0 && flag; i--)
	{
		flag = 0;
		for(int j=0; j<i; j++)
		{
			if(compare(arr+j*size,arr+(j+1)*size) >0)
			{
				swap(arr+j*size,arr+(j+1)*size,size);	
				flag = 1;
			}
		}
	}
}

void sort_select(void* arr,size_t size,size_t len,Compare_t compare)
{
	for(int i=0; i<len-1; i++)
	{
		int min = i;
		for(int j=i+1; j<len; j++)
		{
			if(compare(arr+j*size,arr+min*size) <0) min = j;	
		}
		if(i!=min) swap(arr+i*size,arr+min*size,size);
	}
}

void sort_insert(void* arr,size_t size,size_t len,Compare_t compare)
{
	for(int i=1; i<len; i++)
	{
		for(int j=i;j>0 && compare(arr+j*size,arr+(j-1)*size)<0; j--)
		{
			swap(arr+j*size,arr+(j-1)*size,size);
		}
	}
}

void sort_shell(void* arr,size_t size,size_t len,Compare_t compare)
{
	for(int step=len/2; step>0; step/=2)
	{
		for(int i=step; i<len; i++)
		{
			for(int j=i; j>=step && compare(arr+j*size,arr+(j-step)*size)<0; j-=step)
			{
				swap(arr+(j-step)*size,arr+j*size,size);
			}
		}
	}
}


void _quick_sort(void* arr,size_t size,int start,int end,Compare_t compare)
{
	if(start>=end)	return;
	int l = start,r = end;
	
	void* temp = malloc(size);
	memcpy(temp,arr+start*size,size);

	while(l<r)
	{
		while(r>start && compare(arr+r*size,temp) >=0)	r--;
		while(l<end && compare(arr+l*size,temp) <=0)	l++;
		if(l>=r)	break;
		swap(arr+r*size,arr+l*size,size);
	}
	swap(arr+r*size,arr+start*size,size);
	free(temp);
	_quick_sort(arr,size,start,r-1,compare);
	_quick_sort(arr,size,r+1,end,compare);
}

void sort_fast(void* arr,size_t size,size_t len,Compare_t compare)
{
	_quick_sort(arr,size,0,len-1,compare);
}


