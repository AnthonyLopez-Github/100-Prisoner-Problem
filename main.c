/*
TODO:
- Clean code.
OPTIONAL:
- Add option to run the test n times?
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COUNT 100
#define HALF_COUNT COUNT / 2

int testPrisoner(int prisonerNumber, int boxes[])
{
	printf("Prisoner %d is traversing...\n", prisonerNumber);

	int next = prisonerNumber;
	for(int i = 0 ; i < HALF_COUNT ; i++)
	{
		printf("[%d]:%d->", next, boxes[next - 1]);
		if(boxes[next - 1] != prisonerNumber)
		{
			next = boxes[next - 1];
		} else
		{
			return 0;
		}
	}

	return 1;	
}

int main(void)
{
	srand(time(0));

	FILE *fp = fopen("./test.txt", "r");
	if(!(fp))
	{
		perror("ERROR");
		return 1;
	}

	int right = 0;
	int wrong = 0;

	if(fscanf(fp, "%d,%d", &right, &wrong) != 2)
	{
		fprintf(stderr, "Unable to read values.\n");
		printf("%d,%d\n", right, wrong);
		fclose(fp);
		return 1;
	}

	fclose(fp);
	fp = fopen("./test.txt", "w");

	if(!(fp))
	{
		perror("ERROR");
		return 1;
	}

	int *prisoners = (int *) calloc(COUNT, sizeof(int));
	int *boxes = (int *) calloc(COUNT, sizeof(int));
	int *boolArr = (int *) calloc(COUNT, sizeof(int));

	for(int i = 0 ; i < COUNT ; i++)
	{
		prisoners[i] = i + 1;
		int n = (rand() % COUNT) + 1;
		if(!boolArr[n - 1])
		{
			boxes[i] = n;
			boolArr[n - 1] = 1;
		} else
		{
			i--;
		}
	}

	for(int i = 0 ; i < COUNT ; i++)
	{
		if(testPrisoner(prisoners[i], boxes))
		{
			printf("Prisoners executed.\n\n");
			wrong++;

			free(prisoners);
			free(boxes);
			free(boolArr);

			fprintf(fp, "%d,%d", right, wrong);
			fclose(fp);
			
			// Print current average
			if(wrong > 0) printf("Average survival rate: %.2f\n", (float) right / wrong);

			return 0;
		}
		printf("\n\n");
	}

	right++;
	fprintf(fp, "%d,%d", right, wrong);
	fclose(fp);

	free(prisoners);
	free(boxes);
	free(boolArr);

	// Print current average
	printf("Average survival rate: %.2f\n", (float) right / (right + wrong));
	
	return 0;
}
