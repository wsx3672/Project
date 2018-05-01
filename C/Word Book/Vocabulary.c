//Vocabulary.c
/*
���ϸ�Ī:Vocabulary.c
���:�ܾ��(�ܾ�,�ǹ�,ǰ��,����)�� �Է¹޾� �ܾ����� ����� �����Ѵ�
�ۼ���:�ڻ��
�ۼ�����:2017��6��11��
*/
//��ũ�μ���
#include "Vocabulary.h"
#include "FindingForm.h"
#include "UpdatingForm.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable:4996)

//�Լ�����
/*
int main(int argc, char *argv[]) {
Vocabulary vocabulary;
Long menu;
Create(&vocabulary, 60000);
DisplayMenu(); scanf("%d", &menu);
while (menu != 0)
{
switch (menu)
{
case 1:FormForRecording(&vocabulary); break;
case 2:FormForFinding(&vocabulary); break;
case 3:FormForCorrecting(&vocabulary); break;
case 4:FormForErasing(&vocabulary); break;
case 5:FormForArranging(&vocabulary); break;
case 6:FormForViewAll(&vocabulary); break;
default:break;
}
DisplayMenu(); scanf("%d", &menu);
}
Destroy(&vocabulary);
return 0;
}
*/

/*
�Լ��̸�:Create
���:�Ҵ緮��ŭ �ܾ���� �غ��Ѵ�
�Է�:�Ҵ緮
���:X
*/
void Create(Vocabulary *vocabulary, Long capacity)
{
	vocabulary->words = (Word(*))calloc(capacity, sizeof(Word));
	vocabulary->capacity = capacity;
	vocabulary->length = 0;
}

/*
�Լ��̸�:Record
���:�ܾ�,�ǹ�,ǰ��,������ �Է¹޾� �ܾ��忡 �����Ѵ�
�Է�:�ܾ�,�ǹ�,ǰ��,����
���:������ġ
*/
Long Record(Vocabulary *vocabulary, char(*name), char(*mean), char(*partOfSpeech), char(*exampleSentence))
{
	Long index;
	Long i = 0;
	Long j = 0;
	Word(*temps);
	while (i < vocabulary->capacity && strcmp(vocabulary->words[i].name, "") != 0)
	{
		i++;
	}
	if (i >= vocabulary->capacity)
	{
		temps = (Word(*))calloc(vocabulary->capacity + 1, sizeof(Word));
		while (j < vocabulary->length)
		{
			temps[j] = vocabulary->words[j];
			j++;
		}
		if (vocabulary->words != NULL)
		{
			free(vocabulary->words);
		}
		vocabulary->words = temps;
		(vocabulary->capacity)++;
	}
	index = i;
	strcpy(vocabulary->words[index].name, name);
	strcpy(vocabulary->words[index].mean, mean);
	strcpy(vocabulary->words[index].partOfSpeech, partOfSpeech);
	strcpy(vocabulary->words[index].exampleSentence, exampleSentence);
	(vocabulary->length)++;
	return index;
}
/*
�Լ��̸�:Find
���:�ܾ �Է¹޾� �ش��ϴ� ���� ��ġ�� ã�´�
�Է�:�ܾ�
���:������ġ��,ã������
*/
void Find(Vocabulary *vocabulary, char(*name), Long*(*indexes), Long *count)
{
	Long index = 0;
	Long i = 0;
	*count = 0;


	while (index < vocabulary->length)
	{
		if (strcmp(vocabulary->words[index].name, name) == 0)
		{
			(*count)++;
		}
		index++;
	}
	if (*count > 0)
	{
		*indexes = (Long(*))calloc((*count), sizeof(Long));
	}
	index = 0;
	while (index < vocabulary->length && i<*count)
	{
		if (strcmp(vocabulary->words[index].name, name) == 0)
		{
			(*indexes)[i] = index;
			i++;
		}
		index++;
	}
}
/*
�Լ��̸�:Correct
���:������ġ,������ �Է¹޾� �ش��ϴ� ���� �����Ѵ�
�Է�:������ġ,����
���:������ġ
*/
Long Correct(Vocabulary *vocabulary, Long index, char *mean, char *partOfSpeech, char(*exampleSentence))
{
	strcpy(vocabulary->words[index].mean, mean);
	strcpy(vocabulary->words[index].partOfSpeech, partOfSpeech);
	strcpy(vocabulary->words[index].exampleSentence, exampleSentence);
	return index;
}
/*
�Լ��̸�:Erase
���:������ġ�� �Է¹޾� �ش����� �����
�Է�:������ġ
���:������ġ
*/
Long Erase(Vocabulary *vocabulary, Long index)
{
	Long i = 0;
	Long j = 0;
	Word(*temps);
	if (vocabulary->capacity > 1)
	{
		temps = (Word(*))calloc(vocabulary->capacity - 1, sizeof(Word));
	}
	while (j < vocabulary->length)
	{
		if (j != index)
		{
			temps[i] = vocabulary->words[i];
			i++;
		}
		j++;
	}


	if (vocabulary->words != NULL)
	{
		free(vocabulary->words);
		vocabulary->words = NULL;
	}
	if (vocabulary->capacity > 1)
	{
		vocabulary->words = temps;
	}
	(vocabulary->length)--;
	(vocabulary->capacity)--;
	index = -1;
	return index;
}

/*
�Լ��̸�:Arrange
���:������ ������ �����Ѵ�.�� ������ �ٵ��� �������� ��ġ�Ѵ�
�Է�:X
���:X
*/
void Arrange(Vocabulary *vocabulary)
{
	Word word;
	Long i = 0;
	Long j;
	while (i < vocabulary->length)
	{
		j = i - 1;
		word = vocabulary->words[i];
		while (j >= 0 && strcmp(word.name, vocabulary->words[j].name) < 0)
		{
			vocabulary->words[j + 1] = vocabulary->words[j];
			j--;
		}
		vocabulary->words[j + 1] = word;
		i++;
	}
}
/*
�Լ��̸�:Destroy
���:�ܾ������ �Ҵ������Ѵ�
�Է�:X
���:X
*/
void Destroy(Vocabulary *vocabulary)
{
	if (vocabulary->words != NULL)
	{
		free(vocabulary->words);
	}

}
/*
�Լ��̸�:Load
���:�ܾ����� �����Ѵ�
�Է�:�ܾ�
���:���ǰ���
*/
Long Load(Vocabulary *vocabulary) {
	Long count = 0;
	Long i;
	Long index;
	Word word;
	Word(*temps);
	FILE *file;
	int flag;

	file = fopen("Vocabulary.dat", "rb");
	if (file != NULL)
	{
		flag = fread(&word, sizeof(Word), 1, file);
		while (!feof(file) && flag != 0)
		{
			if (vocabulary->length >= vocabulary->capacity)
			{
				temps = (Word(*))calloc(vocabulary->capacity + 1, sizeof(Word));
				i = 0;
				while (i < vocabulary->length)
				{
					temps[i] = vocabulary->words[i];
					i++;
				}
				if (vocabulary->words != NULL)
				{
					free(vocabulary->words);
					vocabulary->words = NULL;
				}
				vocabulary->words = temps;
				(vocabulary->capacity)++;
			}
			index = vocabulary->length ;
			vocabulary->words[index] = word;
			(vocabulary->length)++;
			count++;
			flag = fread(&word, sizeof(Word), 1, file);
		}
		fclose(file);
	}
	return count;
}
/*
�Լ��̸�:Save
���:�ܾ����� �����Ѵ�
�Է�:
���:���ǰ���
*/
Long Save(Vocabulary *vocabulary) {
	Long i=0;
	FILE *file;
	Long count = 0;

	file = fopen("Vocabulary.dat", "wb");
	{
		if (file != NULL)
		{
			while (i < vocabulary->length)
			{
				fwrite(vocabulary->words + i, sizeof(Word), 1, file);
				count++;
				i++;
			}
		}
		fclose(file);
	}
	return count;
}