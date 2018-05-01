//ZipCodeBookUsingArray.h

//가드선언
#ifndef _ZIPCODEBOOKUSINGARRAY_H
#define _ZIPCODEBOOKUSINGARRAY_H
#include "Array.h"

typedef struct _address {
	char zipCode[8];
	char sido[5];
	char gugun[18];
	char dong[27];
	char ri[16];
	char bldg[43];
	char st_bunji[10];
	char ed_bunji[10];
	char seq[6];
} Address;

typedef struct _zipCodeBook {
	Array addresses;
	Long capacity;
	Long length;
} ZipCodeBook;

//함수선언
void ZipCodeBook_Create(ZipCodeBook *zipCodeBook, Long capacity);

Long ZipCodeBook_Load(ZipCodeBook *zipCodeBook);

void ZipCodeBook_Find(ZipCodeBook *zipCodeBook, char(*dong), Long*(*indexes), Long *count);

Address ZipCodeBook_GetAt(ZipCodeBook *zipCodeBook, Long index);

int CompareDongs(void *one, void *other);

void ZipCodeBook_Destroy(ZipCodeBook *zipCodeBook);

#endif // _ZIPCODEBOOKUSINGARRAY_H