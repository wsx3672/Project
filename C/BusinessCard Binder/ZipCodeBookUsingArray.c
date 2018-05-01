//ZipCodeBookUsingArray.c

//매크로선언
#include "Array.h"
#include "ZipCodeBookUsingArray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable:4996)
//함수정의
/*
int main(int argc, char *argv[]) {
	
	
	ZipCodeBook zipCodeBook;
	Long count;
	Long(*indexes);
	Address address;
	Long i = 0;

	ZipCodeBook_Create(&zipCodeBook, 100000);
	
	Load(&zipCodeBook);
	
	Find(&zipCodeBook, "서초1동", &indexes, &count);

	while (i < count) {
		address = ZipCodeBook_GetAt(&zipCodeBook, indexes[i]);
		printf("%s %s %s %s %s %s %s %s %s\n", address.seq, address.sido, address.gugun, address.dong, address.ri, address.bldg, address.st_bunji, address.ed_bunji, address.zipCode);
		i++;
	}
	if (indexes != NULL) {
		free(indexes);
		indexes = NULL;
	}
	
	ZipCodeBook_Destroy(&zipCodeBook);
	
	return 0;
	
}
*/

void ZipCodeBook_Create(ZipCodeBook *zipCodeBook, Long capacity) {
	Create(&zipCodeBook->addresses, capacity, sizeof(Address));
	zipCodeBook->capacity = capacity;
	zipCodeBook->length = 0;
}

Long ZipCodeBook_Load(ZipCodeBook *zipCodeBook) {
	FILE *file;
	char line[256];
	Long i;
	Long j;
	Long order;
	char temp[43];
	Address address;
	Long index = 0;

	file = fopen("ZipCodeBook.txt", "rt");
	if (file != NULL) {
		fgets(line, 256, file);
		fgets(line, 256, file);
		while (!feof(file)) {
			i = 0;
			order = 1;
			while (line[i] != '\0') {
				j = 0;
				while (line[i] != '\t' && line[i] != '\n') {
					temp[j] = line[i];
					j++;
					i++;
				}
				temp[j] = '\0';
				if (order >= 1 && order <= 9) {
					switch (order) {
					case 1: strcpy(address.zipCode, temp); break;
					case 2: strcpy(address.sido, temp); break;
					case 3: strcpy(address.gugun, temp); break;
					case 4: strcpy(address.dong, temp); break;
					case 5: strcpy(address.ri, temp); break;
					case 6: strcpy(address.bldg, temp); break;
					case 7: strcpy(address.st_bunji, temp); break;
					case 8: strcpy(address.ed_bunji, temp); break;
					case 9: strcpy(address.seq, temp); break;
					default: break;
					}
				}
				order++;
				i++;
			}
			if (zipCodeBook->length < zipCodeBook->capacity) {
				Store(&zipCodeBook->addresses, index, &address, sizeof(Address));
			}
			else {
				AppendFromRear(&zipCodeBook->addresses, &address, sizeof(Address));
				zipCodeBook->capacity++;
			}
			zipCodeBook->length++;
			index++;
			fgets(line, 256, file);
		}
		fclose(file);
	}
	return zipCodeBook->length;
}


void ZipCodeBook_Find(ZipCodeBook *zipCodeBook, char(*dong), Long*(*indexes), Long *count) {
	LinearSearchDuplicate(&zipCodeBook->addresses, dong, indexes, count, sizeof(Address), CompareDongs);
}


Address ZipCodeBook_GetAt(ZipCodeBook *zipCodeBook, Long index) {
	Address address;
	GetAt(&zipCodeBook->addresses, index, &address, sizeof(Address));
	return address;
}

int CompareDongs(void *one, void *other) {
	char tempDong[27];
	char compDong[27];
	Long size=0;
	Long i = 0;

	while (((char(*))other)[i] != '\0') {
		size++;
		i++;
	}
	i = 0;
	while (i < size - 2) {
		compDong[i] = ((char(*))other)[i];
		i++;
	}
	compDong[i] = '\0';
	i = 0;
	while (i < size - 2) {
		tempDong[i] = ((Address*)one)->dong[i];
		i++;
	}
	tempDong[i] = '\0';

	return strcmp(tempDong, compDong);
}


void ZipCodeBook_Destroy(ZipCodeBook *zipCodeBook) {
	Destroy(&zipCodeBook->addresses);
}

