#pragma once
#ifndef _VOCABULARY_H //가드
#define _VOCABULARY_H //가드

#define NAME 21
#define MEAN 128
#define PARTOFSPEECH 128
#define EXAMPLESENTENCE 128
//자료형설계
typedef signed long int Long;
typedef struct _word {
	char name[NAME];
	char mean[MEAN];
	char partOfSpeech[PARTOFSPEECH];
	char exampleSentence[EXAMPLESENTENCE];
}Word;
typedef struct _vocabulary {
	Long capacity;
	Long length;
	Word(*words);
}Vocabulary;
void Create(Vocabulary *vocabulary, Long capacity);
Long Record(Vocabulary *vocabulary, char(*name), char(*mean), char(*partOfSpeech), char(*exampleSentence));
void Find(Vocabulary *vocabulary, char(*name), Long*(*indexes), Long *count);
Long Correct(Vocabulary *vocabulary, Long index, char *mean, char *partOfSpeech, char(*exampleSentence));
Long Erase(Vocabulary *vocabulary, Long index);
void Arrange(Vocabulary *vocabulary);
void Destroy(Vocabulary *vocabulary);
Long Load(Vocabulary *vocabulary);
Long Save(Vocabulary *vocabulary);

#endif // !_VOCABULARY_H
