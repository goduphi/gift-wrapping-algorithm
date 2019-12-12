#include <stdio.h>
#include <stdlib.h>

//this program is meant to generate random coordinates and write them out to a file

int rand_points(char *size, char *max_val)
{
	FILE *fp = fopen("random.txt", "w");
	int int_size = atoi(size);
	int int_max_val = atoi(max_val);
	fprintf(fp, "%d\n", int_size);
	int i = 0;
	for(i = 0; i < int_size; i++)
		fprintf(fp, "%d %d\n", rand()%int_max_val, rand()%int_max_val);
	fclose(fp);
}

int main(int argc, char *argv[])
{
	if(argc < 3)
		rand_points(argv[1], "100");
	else
		rand_points(argv[1], argv[2]);
	
	return 0;
}