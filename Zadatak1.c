#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NAME_SIZE 256
#define FILE_SIZE 256

typedef struct student {
	char firstName[NAME_SIZE];
	char lastName[NAME_SIZE];
	int points;
}Student;

int countFromFile(char* fileName);
int readFromFile(char* fileName, int br);
int print(Student s);
double countPoints(int points);

int main()
{
	char fileName[FILE_SIZE];
	int number_of_students;

	printf("Insert name of file: ");
	scanf("%s", fileName);

	number_of_students = countFromFile(fileName);
	readFromFile(fileName, number_of_students);

	return 0;
}

int readFromFile(char* fileName, int br) {
	FILE* f;
	Student *s;
	int i;

	f = fopen(fileName, "r");

	if ( f == NULL ) {
		perror("Error opening file!\n");
		return 0;
	}

	s = (Student*)malloc(br*sizeof(Student));

	if ( s == NULL )
		perror("Error!");

	rewind(f);

	for(i = 0; i < br; i++) {
		fscanf(f, "%s %s %d", (s+i)->firstName, (s+i)->lastName, &(s+i)->points);
	}

	for(i = 0; i < br; i++) {
		print(*(s+i));
	}

	fclose(f);
	free(s);

	return 0;
}

int countFromFile(char* fileName) {
	FILE* f;
	int br = 0;

	f = fopen(fileName, "r");

	if ( f == NULL ) {
		perror("Error opening file!\n");
		return 0;
	}

	while(!feof(f)) {
		if (getc(f) == '\n') 
			br++;
	}

	fclose(f);

	return br;
}

int print(Student s) {

	printf("%s\t%s\t%d\t%lf\n", s.firstName, s.lastName, s.points, countPoints(s.points));

	return 0;
}

double countPoints(int points) {
	return (double)points/50 * 100;
}