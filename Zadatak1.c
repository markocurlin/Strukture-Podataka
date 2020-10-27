#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
	char first_name[20];
	char last_name[20];
	int points;
}student;

int Count_Students(char* name)
{
	FILE *f;
	int number=0;

	f=fopen(name, "r");

	if (f==NULL)
		perror("Error!");

	while(feof(f)==0){
		if (getc(f)=='\n')
			number++;
	}

	fclose(f);

	return number;

}

double Relevant_Points(int points) {
	return (double)points/60*100;
}

int Print_Students(student s) {
	printf("%s\t%s\t%lf\n", s.first_name, s.last_name, Relevant_Points(s.points));
	return 0;
}

int Read_From_File(char *name, int number)
{
	FILE *f;
	student *s;
	int i;

	f=fopen(name, "r");

	if (f==NULL)
		perror("Error!");

	s=(student*)malloc(number*sizeof(student));

	if (s==NULL)
		perror("Error!");

	rewind(f);

	for(i=0; i<number; i++) 
		fscanf(f, "%s %s %d", s[i].first_name, s[i].last_name, &s[i].points);

	printf("FIRST NAME\tLAST NAME\tPOINTS\n");

	for(i=0; i<number; i++)
		Print_Students(s[i]);

	fclose(f);
	free(s);

	return 0;
}



int main()
{
	int number_of_students=0;
	char name[20];
	
	scanf("%s", name);
	strcat(name,".txt");
	
	number_of_students=Count_Students(name);

	Read_From_File(name, number_of_students);

	return 0;
}