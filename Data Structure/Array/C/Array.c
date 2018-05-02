//Array.c
/*
�� �� �� : Array.c
��	  �� : �迭 ���̺귯��
�� �� �� : �ڻ��
�ۼ����� : 2017�� 6�� 30��
*/
#include "Array.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

//�Ҵ�
void Create(Array *array, Long capacity, size_t size) {
	array->front = calloc(capacity, size);
	array->capacity = capacity;
	array->length = 0;
}
//�Է�
Long Store(Array *array, Long index, void *object, size_t size) {
	memcpy(((char*)array->front) + (index*size), object, size);
	array->length++;
	return index;
}
//����
Long Insert(Array *array, Long index, void *object, size_t size) {
	void(*temp);
	Long i = 0;
	Long j = 0;

	temp = calloc(array->capacity + 1, size);
	while (i < index) {
		memcpy(((char*)temp) + (j*size), ((char*)array->front)+(i*size), size);
		j++;
		i++;
	}
	j++;
	while (i < array->length) {
		memcpy(((char*)temp) + (j*size), ((char*)array->front) + (i*size), size);
		j++;
		i++;
	}
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	array->front = temp;
	array->capacity++;
	memcpy(((char*)array->front) + (index*size), ((char*)object), size);
	array->length++;
	return index;
}
//ù�ڸ� ����
Long AppendFromFront(Array *array, void *object, size_t size) {
	void(*temp);
	Long index = 0;
	Long i = 0;
	Long j = 1;
	temp = calloc(array->capacity + 1, size);
	while (i < array->length) {
		memcpy(((char*)temp) + (j*size), ((char*)array->front) + (i*size), size);
		j++;
		i++;
	}
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	array->front = temp;
	array->capacity++;
	memcpy(((char*)(array->front)) + (index*size), object, size);
	array->length++;
	return index;
}
//���ڸ� ����
Long AppendFromRear(Array *array, void *object, size_t size) {
	void(*temp);
	Long index;
	Long i = 0;
	temp = calloc(array->capacity + 1, size);
	while (i < array->length) {
		memcpy(((char*)temp) + (i*size), ((char*)array->front) + (i*size), size);
		i++;
	}
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	array->front = temp;
	array->capacity++;
	index = array->capacity - 1;
	memcpy(((char*)array->front) + (index*size), object, size);
	array->length++;
	return index;
}
//����
Long Delete(Array *array, Long index, size_t size) {
	void(*temp) = { 0, };
	Long i = 0;
	Long j = 0;
	if (array->capacity > 1) {
		temp = calloc(array->capacity - 1, size);
	}
	while (i < index) {
		memcpy(((char*)temp) + (j*size), ((char*)array->front) + (i*size), size);
		j++;
		i++;
	}
i++;
while (i < array->length) {
	memcpy(((char*)temp) + (j*size), ((char*)array->front) + (i*size), size);
	j++;
	i++;
}
if (array->front != NULL) {
	free(array->front);
	array->front = NULL;
}
if (array->capacity > 1) {
	array->front = temp;
}
array->length--;
array->capacity--;
index = -1;
return index;
}
//ù�ڸ� ����
Long DeleteFromFront(Array *array, size_t size) {
	void(*temp) = { 0, };
	Long index;
	Long i = 1;
	Long j = 0;
	if (array->capacity > 1) {
		temp = calloc(array->capacity - 1, size);
	}
	while (i < array->length) {
		memcpy(((char*)temp) + (j*size), ((char*)array->front) + (i*size), size);
		j++;
		i++;
	}
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	if (array->capacity > 1) {
		array->front = temp;
	}
	array->length--;
	array->capacity--;
	index = -1;
	return index;
}
//���ڸ� ����
Long DeleteFromRear(Array *array, size_t size) {
	void(*temp) = { 0, };
	Long index;
	Long i = 0;
	if (array->capacity > 1) {
		temp = calloc(array->capacity - 1, size);
	}
	while (i < array->capacity - 1) {
		memcpy(((char*)temp) + (i*size), ((char*)array->front) + (i*size), size);
		i++;
	}
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	if (array->capacity > 1) {
		array->front = temp;
	}
	array->length--;
	array->capacity--;
	index = -1;
	return index;
}
//��ü �����
void Clear(Array *array) {
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	array->capacity = 0;
	array->length = 0;
}
//�����ϱ�
Long Modify(Array *array, Long index, void *object, size_t size) {
	memcpy(((char*)array->front) + (index*size), object, size);
	return index;
}
//�����˻�(������)
Long LinearSearchUnique(Array *array, void *key, size_t size, int(*compare)(void*, void*)) {
	Long index = -1;
	Long i = 0;
	while (i < array->length&&compare(((char*)array->front) + (i*size), key) != 0) {
		i++;
	}
	if (i < array->length) {
		index = i;
	}
	return index;
}
//�ߺ������˻�(������)
void LinearSearchDuplicate(Array *array, void *key, Long *(*indexes), Long *count, size_t size, int(*compare)(void*, void*)) {
	Long i = 0;
	Long j = 0;
	*count = 0;
	*indexes = (Long(*))calloc(array->length, sizeof(Long));
	while (i <= array->length) {
		if (compare(((char*)array->front) + (i*size), key) == 0) {
			(*indexes)[j] = i;
			(*count)++;
			j++;
		}
		i++;
	}
}
//�̺а˻�(������)
Long BinarySearchUnique(Array *array, void *key, size_t size, int(*compare)(void*, void*)) {
	Long center;
	Long max;
	Long min = 0;
	Long index = 0;
	max = array->length;
	center = (max + min) / 2;
	while (max >= min&&compare(((char*)array->front) + (index*size), key) != 0) {
		if (compare(((char*)array->front) + (center*size), key) < 0) {
			min = center + 1;
		}
		else {
			max = center - 1;
		}
		center = (max + min) / 2;
	}
	if (max > min) {
		index = center;
	}
	return index;
}
//�ߺ��̺а˻�(������)
void BinarySearchDuplicate(Array *array, void *key, Long *(*indexes), Long *count, size_t size, int(*compare)(void*, void*)) {
	Long center;
	Long max;
	Long min = 0;
	Long i = 0;
	*count = 0;
	max = array->length;
	*indexes = (Long(*))calloc(array->length, sizeof(Long));
	center = (max + min) / 2;
	while (max > min && compare(((char*)array->front) + (center*size), key) != 0) {
		if (compare(((char*)array->front) + (center*size), key) < 0) {
			min = center + 1;
		}
		else {
			max = center - 1;
		}
		center = (max + min) / 2;
	}
	min = center - 1;
	while(min>=0 && compare(((char*)array->front) + (min*size), key) == 0){
		min--;
	}
	min++;
	while (min <= 0 && compare(((char*)array->front) + (min*size), key) == 0) {
		(*indexes)[i] = min;
		(*count)++;
		i++;
		min++;
	}
}
//��������(������)
void BubbleSort(Array *array, size_t size, int(*compare)(void*, void*)) {
	void *temp;
	Long i = 0;
	Long j;
	temp = malloc(size);
	while (i < array->length - 1) {
		j = 0;
		while (j < array->length - i - 1) {
			if (compare(((char*)array->front) + (j*size), ((char*)(array->front)) + ((j + 1)*size)) > 0) {
				memcpy(temp, ((char*)array->front) + ((j + 1)*size), size);
				memcpy(((char*)array->front) + ((j + 1)*size), ((char*)array->front) + (j*size), size);
				memcpy(((char*)array->front) + (j*size), temp, size);
			}
			j++;
		}
		i++;
	}
	if (temp != NULL) {
		free(temp);
	}
}
//��������(������)
void SelectionSort(Array *array, size_t size, int(*compare)(void*, void*)) {
	void *temp;
	Long i = 0;
	Long j;
	temp = malloc(size);
	while (i < array->length - 1) {
		j = i + 1;
		while (j < array->length) {
			if (compare(((char*)array->front) + (i*size), ((char*)array->front) + (j*size)) > 0) {
				memcpy(temp, ((char*)array->front) + (i*size), size);
				memcpy(((char*)array->front) + (i*size), ((char*)array->front) + (j*size), size);
				memcpy(((char*)array->front) + (j*size), temp, size);
			}
			j++;
		}
		i++;
	}
	if (temp != NULL) {
		free(temp);
	}
}
//��������(������)
void InsertionSort(Array *array, size_t size, int(*compare)(void*, void*)) {
	void *temp;
	Long i = 1;
	Long j;
	temp = malloc(size);
	while (i < array->length) {
		memcpy(temp, ((char*)array->front) + (i*size), size);
		j = i - 1;
		while (j >= 0 && compare(((char*)array->front) + (j*size), temp) > 0) {
			memcpy(((char*)array->front) + ((j + 1)*size), ((char*)array->front) + (j*size), size);
			j--;
		}
		memcpy(((char*)array->front) + ((j+1)*size), temp, size);
		i++;
	}
	if (temp != NULL) {
		free(temp);
	}
}
//��������(������)
void MergeSort(Array *array, Array *one, Array *other, size_t size, int(*compare)(void*, void*)) {
	Long i = 0;
	Long j = 0;
	Long k = 0;
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	array->front = calloc(one->length + other->length, size);
	array->capacity = one->length + other->length;
	array->length = 0;
	while (i < one->length && j < other->length) {
		if (compare(((char*)one->front) + (i*size), ((char*)other->front) + (j*size))<0) {
			memcpy(((char*)array->front) + (k*size), ((char*)one->front) + (i*size), size);
			array->length++;
			k++;
			i++;
		}
		else {
			memcpy(((char*)array->front) + (k*size), ((char*)other->front) + (j*size), size);
			array->length++;
			k++;
			j++;
		}
	}
	while (j < other->length) {
		memcpy(((char*)array->front) + (k*size), ((char*)other->front) + (j*size), size);
		array->length++;
		k++;
		j++;
	}
	while (i < one->length) {
		memcpy(((char*)array->front) + (k*size), ((char*)other->front) + (i*size), size);
		array->length++;
		k++;
		i++;
	}
}
//��������
void GetAt(Array *array, Long index, void *object, size_t size) {
	memcpy(object,((char*)array->front) + (index*size), size);
}
//�Ҵ�����
void Destroy(Array *array) {
	if (array->front != NULL) {
		free(array->front);
	}
}