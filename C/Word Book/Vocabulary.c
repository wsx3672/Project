//Vocabulary.c
/*
파일명칭:Vocabulary.c
기능:단어들(단아,의미,품사,예문)을 입력받아 단어장을 만들고 관리한다
작성자:박상민
작성일자:2017년6월11일
*/
//매크로선언
#include "Vocabulary.h"
#include "FindingForm.h"
#include "UpdatingForm.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable:4996)

//함수정의
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
함수이름:Create
기능:할당량만큼 단어들을 준비한다
입력:할당량
출력:X
*/
void Create(Vocabulary *vocabulary, Long capacity)
{
	vocabulary->words = (Word(*))calloc(capacity, sizeof(Word));
	vocabulary->capacity = capacity;
	vocabulary->length = 0;
}

/*
함수이름:Record
기능:단어,의미,품사,예문을 입력받아 단어장에 저장한다
입력:단어,의미,품사,예문
출력:줄의위치
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
함수이름:Find
기능:단어를 입력받아 해당하는 줄의 위치를 찾는다
입력:단어
출력:줄의위치들,찾은개수
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
함수이름:Correct
기능:줄의위치,예문을 입력받아 해당하는 줄을 수정한다
입력:줄의위치,예문
출력:줄의위치
*/
Long Correct(Vocabulary *vocabulary, Long index, char *mean, char *partOfSpeech, char(*exampleSentence))
{
	strcpy(vocabulary->words[index].mean, mean);
	strcpy(vocabulary->words[index].partOfSpeech, partOfSpeech);
	strcpy(vocabulary->words[index].exampleSentence, exampleSentence);
	return index;
}
/*
함수이름:Erase
기능:줄의위치를 입력받아 해당줄을 지운다
입력:줄의위치
출력:줄의위치
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
함수이름:Arrange
기능:가나다 순으로 정렬한다.단 지원진 줄들은 뒤쪽으로 배치한다
입력:X
출력:X
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
함수이름:Destroy
기능:단어장들을 할당해제한다
입력:X
출력:X
*/
void Destroy(Vocabulary *vocabulary)
{
	if (vocabulary->words != NULL)
	{
		free(vocabulary->words);
	}

}
/*
함수이름:Load
기능:단어장을 적재한다
입력:단어
출력:줄의개수
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
함수이름:Save
기능:단어장을 저장한다
입력:
출력:줄의개수
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