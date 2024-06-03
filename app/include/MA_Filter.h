#ifndef MA_FILTER_H_
#define MA_FILTER_H_


typedef struct MA_FilterStruct* iMA_Filter;


iMA_Filter MA_FilterCreate(unsigned int size);
void MA_FilterDestroy(iMA_Filter);

void MA_FilterReset(iMA_Filter);
void MA_FilterPush(iMA_Filter, int value);
int MA_FilterGetValue(iMA_Filter);

#endif