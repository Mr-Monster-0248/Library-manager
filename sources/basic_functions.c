#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "../headers/basic_functions.h"

//Function that checks if the allocation of memory succeed (needs the pointer to be set to NULL before allocation)
void check_alloc(void* ptr)
{
	if (ptr == NULL)
	{
		fprintf(stderr, "MEMORY ERROR: Memory allocation failed, exiting program... May cause memory leaks\n");

		exit(EXIT_FAILURE);
	}
}


//Function that frees a 2 dimensional array of any type
void free_2D_array(void*** array, int arraySize)
{
	if (arraySize > 0)
	{
		//Freeing subarrays
		while(--arraySize >= 0)
			free((*array)[arraySize]);

		//Freeing main array
		free(*array);
	}
}


//Function that determines whether a given character is a digit or not
int is_digit__c(const char c)
{
	if (c >= ASCII_0 && c <= ASCII_9)
		return 1;
	return 0;
}


//Function that determines whether a given string is composed only of digits
int is_digit__s(const char* s)
{
	int i = 0;

	while(s[i] != '\0')
		if (!is_digit__c(s[i])) //Checking if each character is a digit
			return 0; //If at least one character is not a digit, returning 0
	return 1;
}


//Function that converts a string to an long integer
long convert_string_long(const char* s)
{
	if (is_digit__s(s))
		return strtol(s, NULL, 10);

	fprintf(stderr, "ERROR: cannot convert \"%s\" to long, returning %f (smaller possible value for your computer) instead\n", s, MIN_LONG_VAL);
	return MIN_LONG_VAL;
}


//Function that tries to convert a string to an integer, if it is possible
int convert_string_int(const char* s)
{
	if (is_int(s) == 1)
		return (int) convert_string_long(s);

	fprintf(stderr, "ERROR: cannot convert \"%s\" to int, returning %f (smaller possible value for your computer) instead\n", s, MIN_INT_VAL);
	return MIN_INT_VAL;
}


//Function that determines whether a given string is an integer or not
int is_int(const char* s)
{
	long val;

	if (is_digit__s(s))
	{
		val = convert_string_long(s);

		if (val - 1 < MIN_INT_VAL)
			return -1; //NOT DIGIT

		if (val < MIN_INT_VAL || val > MAX_INT_VAL)
			return 0; //OVERFLOW

		return 1;
	}

	return 0;
}


//Function that checks whether a given string is a float or not
int is_float(const char* s)
{
	int dots = 0, i = 0;

	if (is_digit__s(s))
		return 0; //Not a float, no dot in the string

	while (s[i + 1] != '\0')
	{
		if (is_digit__c(s[i]))
		{
			i++;
			continue;
		}

		//Checking the number of dots already detected, if too high, returning 0
		if (dots > 1)
			return 0;

		//Counting the dots
		if (s[i] == '.')
		{
			dots++;
			i++;
			continue;
		}

		//If the character is not a digit and neither a dot, returning 0
		return 0;
	}

	//Checking if the last character of the string is a digit too
	if (is_digit__c(s[i]))
		return 1;

	//If not, returning 0
	return 0;
}


//Function that returns the position of the minimum value in an array of integers
int min_value_subscript(int* array, const int numberValues)
{
	int min = 0, i = 1;

	for (i = 1; i < numberValues; i++)
		if (array[i] < array[min])
			min = i;

	return min;
}


//Function that returns the position of the maximum value in an array of integers
int max_value_subscript(int* array, const int numberValues)
{
	int max = 0, i = 1;

	for (i = 1; i < numberValues; i++)
		if (array[max] < array[i])
			max = i;

	return max;
}



//Function that swaps two values in an array of integers
void swap_values(int** array, const int pos1, const int pos2)
{
	int swap = (*array)[pos1];

	if (pos1 >= 0 && pos2 >= 0)
	{
		(*array)[pos1] = (*array)[pos2];
		(*array)[pos2] = swap;
	}	else	{
		fprintf(stderr, "ERROR: values not swapped\n");
	}
}


//Function that recursively sorts an array of integers
void sort_int_array(int** array, const int numberValues)
{
	int swap = 0, i = 0;

	do
	{
		swap = 0;
		for (i = 0; i < numberValues - 1; i++)
			if ((*array)[i] > (*array)[i+1])
			{
				swap = 1;
				swap_values(array, i, i+1);
			}
	} while (swap != 0);
}


//Function that returns the minimum value of an array of integers
int array_min_value(int* array, const int numberValues)
{
	return array[min_value_subscript(array, numberValues)];
}


//Function that returns the maximum value of an array of integers
int array_max_value(int* array, const int numberValues)
{
	return array[max_value_subscript(array, numberValues)];
}


//Function that returns the position of the first occurence of a given value in an array of integers, -1 if not found
int first_occurence(const int* array, const int numberValues, const int value)
{
	int i = 0;

	for (i = 0; i < numberValues; i++)
		if (array[i] == value)
			return i;

	return -1;
}


//Function that returns the position of the last occurence of a given value in an array of integers, -1 if not found
int last_occurence(const int* array, int numberValues, const int value)
{
	while (--numberValues >= 0)
		if (array[numberValues] == value)
			return numberValues;

	return -1;
}


//Function that returns the number of occurences of a given value in an array of integers
int number_of_occurences(const int* array, const int numberValues, const int value)
{
	int occurences = 0, i = 0;

	for (i = 0; i < numberValues; i++)
		if (array[i] == value)
			occurences++;

	return occurences;
}


//Function that inserts a value at a given position in an array
int insert_at_position(int** array, int* numberValues, const int position, const int value)
{
	int i = position;

	//If inserting a value in the array
	if (position >= 0 && position <= *numberValues)
	{
		*array = (int*) realloc(*array, ++(*numberValues) * sizeof(int));
		check_alloc(*array);

		//Shifting values
		for (i = *numberValues - 1; i != position; i--)
			(*array)[i] = (*array)[i - 1];

		(*array)[position] = value;

		return 1; //Success
	}

	return 0; //Cannot insert or add value to the array
}


//Function that shifts values to the left in an integer array from a given position (the value at this position will be overwritten)
int shift_left(int** array, int* numberValues, const int position)
{
	int i = position;

	if (position < 0 || position >= *numberValues)
		return 0; //Failure, cannot shift values from that subscript

	for (i = position; i < *numberValues - 1; i++)
		(*array)[i] = (*array)[i + 1];

	(*numberValues)--;

	return 1; //Success, values shifted
}


//Function that reads and prints the content of a file to a given output file or stream
void print_file_to(const char* filePath, FILE* output)
{
	FILE* file = NULL;
	file = fopen(filePath, "r");

	//Checking if both file and stream are correctly open
	if (!file || !output)
	{
		fprintf(stderr, "ERROR: cannot read or print file %s\n\n", filePath);
		return;
	}

	while(!feof(file))
		fprintf(output, "%c", fgetc(file)); //Reading a character from the file and printing it to the output stream of file

		fclose(file); //Closing the file
}

//Function to remove any char at the end of a string (recursive function)
void remove_end_char(char* string, const char c)
{
    if (string[strlen(string) - 1] == c)
    {
        string[strlen(string) - 1] = '\0';
        remove_end_char(string);
    }
}
