#ifndef SORT_H
#define SORT_H

typedef int (*Compare_t)(const void* ,const void*);


void sort_bubble(void* arr,size_t size,size_t len,Compare_t compare);

void sort_select(void* arr,size_t size,size_t len,Compare_t compare);

void sort_insert(void* arr,size_t size,size_t len,Compare_t compare);

void sort_shell(void* arr,size_t size,size_t len,Compare_t compare);

void sort_fast(void* arr,size_t size,size_t len,Compare_t compare);

#endif
