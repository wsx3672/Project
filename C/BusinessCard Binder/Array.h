//Array.h
#ifndef _ARRAY_H
#define _ARRAY_H
#include <stddef.h>

typedef signed long int Long;
typedef struct _array{
	void(*front);
	Long capacity;
	Long length;
}Array;

//�Լ�����
void Create(Array *array, Long capacity, size_t size);
Long Store(Array *array, Long index, void *object, size_t size);
Long Insert(Array *array, Long index, void *object, size_t size);
Long AppendFromFront(Array *array, void *object, size_t size);
Long AppendFromRear(Array *array, void *object, size_t size);
Long Delete(Array *array, Long index, size_t size);
Long DeleteFromFront(Array *array, size_t size);
Long DeleteFromRear(Array *array, size_t size);
void Clear(Array *array);
Long Modify(Array *array, Long index, void *object, size_t size);
Long LinearSearchUnique(Array *array, void *key, size_t size,int (*compare)(void*,void*));
void LinearSearchDuplicate(Array *array, void *key, Long *(*indexes), Long *count, size_t size, int(*compare)(void*, void*));
Long BinarySearchUnique(Array *array, void *key, size_t size, int(*compare)(void*, void*));
void BinarySearchDuplicate(Array *array, void *key, Long *(*indexes), Long *count, size_t size, int(*compare)(void*, void*));
void BubbleSort(Array *array, size_t size, int(*compare)(void*, void*));
void SelectionSort(Array *array, size_t size, int(*compare)(void*, void*));
void InsertionSort(Array *array, size_t size, int(*compare)(void*, void*));
void MergeSort(Array *array, Array *one, Array *other, size_t size, int(*compare)(void*, void*));
void GetAt(Array *array, Long index, void *object, size_t size);
void Destroy(Array *array);

#endif // !_ARRAY_H
