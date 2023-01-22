#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int count_words(FILE *file)
{
	unsigned int total = 0;
	char ch;

	if (file == NULL)
	{
		printf("Failed to read file");
		exit(98);
	}

	while(!feof(file))
	{
		ch = fgetc(file);
		if (ch == ',')
		{
			total += 1;
		}
	}

	total += 1;

	return (total);

}

char *get_word(FILE *file, char *str, int index)
{
	char ch;
	char terminate = '\0';
	int total = 0;

	if (file == NULL)
	{
		printf("Failed to read file");
		exit(98);
	}

	while(!feof(file))
	{
		ch = fgetc(file);
		if (ch >= 97 && ch <= 122)
		{
			strncat(str, &ch, 1);

		}
		if (ch == ',')
		{
			total += 1;
			strncat(str, &terminate, 1);

			if (total != index)
			{
				str[0] = 0;
			}

		}

		if (total == index)
		{
			break;
		}
	}

	return (str);


}
int main(void)
{
	FILE *file;
	int size;
	char *quiz;

	file = fopen("Hangman_wordbank", "r");

	if (file == NULL)
	{
		printf("Cannot read file \n");
		return (1);
	}
	
	quiz = malloc(sizeof(char *) * 50);

	if (quiz == NULL)
	{
		printf("Failed to allocate memory\n");
		return (2);
	}

	quiz = get_word(file, quiz, 1000);
	printf("Word is %s\n", quiz);
	fseek(file, 0, SEEK_SET);
	size = count_words(file);
	printf("Total words in file %d\n", size);

	fclose(file);
	return (0);
}
