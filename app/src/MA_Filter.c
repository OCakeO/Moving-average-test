#include "MA_Filter.h"
#include "stdint.h"
#include "stddef.h"
#include <stdio.h>
#include <string.h>


// TODO: Feel free to supplement and modify any of the following code
// Не совсем понял суть 4-FiltersAreIndependent теста
// В 4 тесте все зависит от выделенной памяти и к ней обращаются

struct MA_FilterStruct
{
	unsigned int size;
	int sum;
	int *buffer;
	unsigned int head;
};

iMA_Filter MA_FilterCreate(unsigned int size)
{
	iMA_Filter f;
	
	f = (iMA_Filter) malloc(sizeof(struct MA_FilterStruct));

	f->head = 0; 
	f->size = size;
	f->sum = 0;
	f->buffer = (int*) malloc(sizeof(int)*f->size);
	memset(f->buffer, 0, sizeof(int)*f->size); // массив нулей

	return f;
}

void MA_FilterDestroy(iMA_Filter f)
{	
	if(!f || f == NULL )
		return;

	free(f->buffer);
	free(f);
	
}

void MA_FilterReset(iMA_Filter f)
{
	if(f == NULL)
		return;

	f->head = 0;
	f->sum = 0;
	
}

void MA_FilterPush(iMA_Filter f, int value)
{
	if(f == NULL)
		return;

	if (f->size != 0){ // не выполнять лишние операции
		
		if(f->size == 1) // UnitySizeFilterReturnsLastValue
			f->sum = value;	
		else{
			if (f->head == f->size)
				f->head = 0;
			
			f->sum -= f->buffer[f->head];	// Скользящее среднее
			f->buffer[f->head] = value;
			f->sum += value;
			f->head++;
		}	
	}
	
}

int MA_FilterGetValue(iMA_Filter f)
{
	if(f == NULL)	
		return 0;
	
	if (f->size != 0){
		return f->sum / f->size;
	}
}

