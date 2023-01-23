#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
  * count_words - counts number of words in file
  * @file: file to be read
  * Return: total number of words in file
  */
int count_words(FILE *file)
{
	unsigned int total = 0;
	char ch;

	if (file == NULL)
	{
		printf("Failed to read file");
		exit(98);
	}

	while (!feof(file))
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

/**
  * get_word - finds word in a file according to its index in file
  * @file: file to be read
  * @str: pointer to string
  * @index: position of string
  * Return: pointer to str
  */

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

	while (!feof(file))
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

/**
  * print_answer - prints to stdout
  * @answer: pointer to string to print
  * @len: length of string
  * Return: void
  */

void print_answer(char *answer, int len)
{
	int x;

	for (x = 0; x < len; x++)
	{
		if (answer[x] >= 97 && answer[x] <= 122)
		{
			printf("%c ", answer[x]);
		} else
		{
			printf("__ ");
		}
	}
	printf("\n");
}
/**
  * is_answer - checks that user input is part of quiz string
  * @quiz: pointer to string
  * @answer: pointer to string
  * @input: user char input
  * Return: 0 if input is not in quiz, 1 if input is in quiz
  */
int is_answer(char *quiz, char *answer, int input)
{
	int x, len, return_value = 0;

	len = strlen(quiz);
	for (x = 0; x < len; x++)
	{
		if (answer[x] == input)
		{
			return (1);
		}
		if (input == *(quiz + x))
		{
			answer[x] = input;
			(return_value = 1);
		}
	}

	return (return_value);
}
/**
  * main - entry point
  * Return: 0 (always success)
  */

int main(void)
{
	FILE *file;
	char *quiz;
	char *answer;
	char user_input;
	int num_of_guesses = 5;
	int _is_answer, words;
	time_t t1;
	int continue_game = 1;
	char input;

	file = fopen("Hangman_wordbank", "r");
	while (continue_game)
	{

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

	answer = malloc(sizeof(char *) * 50);

	if (answer == NULL)
	{
		printf("Failed to allocate memory\n");
		return (2);
	}
	
	words = count_words(file);
	fseek(file, 0, SEEK_SET);

	srand((unsigned int) time(&t1));

	quiz = get_word(file, quiz, (rand() % words + 1));
	print_answer(answer, strlen(quiz));

	while (num_of_guesses >= 1)
	{
		printf("Enter your guess: ");
		scanf(" %c", &user_input);
		_is_answer = is_answer(quiz, answer, user_input);

		if (!_is_answer)
		{
			num_of_guesses--;
		}

		if (!strcmp(quiz, answer))
		{
			break;
		}

		print_answer(answer, strlen(quiz));
	}

	if (!strcmp(quiz, answer))
	{
		printf("You won the game\n");
	} else
	{
		printf("You lost the game.\nThe correct word is: %s\n", quiz);
	}

	free(quiz);
	free(answer);
	printf("Enter c to play new game.\nEnter q to quit game.\n");
	
	scanf(" %c", &input);
	if (input == 'q')
	{
		continue_game = 0;
	}
	
	num_of_guesses = 5;

	}
	fclose(file);
	return (0);
}
