#ifndef DEF_BASIC_FUNCTIONS
	#define DEF_BASIC_FUNCTIONS


	/*###########################################################################
	#													SYSTEM DEPENDANTS CONSTANTS												#
	###########################################################################*/

	//Useful for system(INSTRUCTION) to work on different systems
	#ifdef __WIN32__
		#define CLEAR "cls"
		#define PAUSE system("pause");
	#else
		#ifdef __unix__
			#define PAUSE	printf("Press ENTER key to continue...\n");\
										fflush(stdin);\
										getchar();
			#define CLEAR "clear"
		#endif
	#endif

	/*###########################################################################
	#													USEFUL CONSTANTS																	#
	###########################################################################*/


	//ASCII bounds values for digits
	#define ASCII_0 48
	#define ASCII_9 57

	//ASCII bounds values for alphabets
	#define ASCII_LOWER_A 97
	#define ASCII_LOWER_Z 122
	#define ASCII_UPPER_A 65
	#define ASCII_UPPER_Z 9

	//Limit sizes for different variable types
	#define MAX_CHAR_SIZE	pow(2, sizeof(char))
	#define MAX_INT_VAL 	pow(2, sizeof(int) - 1)
	#define MIN_INT_VAL 	-pow(2, sizeof(int) - 1)
	#define MAX_LONG_VAL	pow(2, sizeof(long) - 1)
	#define MIN_LONG_VAL	-pow(2, sizeof(long) - 1)
	#define MAX_FLOAT_SIZE	pow(2, sizeof(float) - 1)
	#define MIN_FLOAT_SIZE	-pow(2, sizeof(float) - 1)


	/*###########################################################################
	#												FUNCTIONS PROTOTYPES																#
	###########################################################################*/

	//Function that checks if the allocation of memory succeed (needs the pointer to be set to NULL before allocation)
	void check_alloc(void* ptr);

	//Function that frees a 2 dimensional array of any type
	void free_2D_array(void*** array, int arraySize);

	//Function that determines whether a given character is a digit or not
	int is_digit__c(const char c);

	//Function that determines whether a given string is composed only of digits
	int is_digit__s(const char* s);

	//Function that converts a string to an long integer
	long convert_string_long(const char* s);

	//Function that tries to convert a string to an integer, if it is possible
	int convert_string_int(const char* s);

	//Function that determines whether a given string is an integer or not
	int is_int(const char* s);

	//Function that checks whether a given string is a float or not
	int is_float(const char* s);

	//Function that returns the position of the minimum value in an array
	int min_value_subscript(int* array, const int numberValues);

	//Function that returns the position of the maximum value in an array of integers
	int max_value_subscript(int* array, const int numberValues);

	//Function that swaps two values in an array of integers
	void swap_values(int** array, const int pos1, const int pos2);

	//Function that recursively sorts an array of integers
	void sort_int_array(int** array, const int numberValues);

	//Function that returns the minimum value of an array of integers
	int array_min_value(int* array, const int numberValues);

	//Function that returns the maximum value of an array of integers
	int array_max_value(int* array, const int numberValues);

	//Function that returns the position of the first occurence of a given value in an array of integers, -1 if not found
	int first_occurence(const int* array, const int numberValues, const int value);

	//Function that returns the position of the last occurence of a given value in an array of integers, -1 if not found
	int last_occurence(const int* array, int numberValues, const int value);

	//Function that returns the number of occurences of a given value in an array of integers
	int number_of_occurences(const int* array, const int numberValues, const int value);

	//Function that inserts a value at a given position in an array
	int insert_at_position(int** array, int* numberValues, const int position, const int value);

	//Function that shifts values to the left in an integer array from a given position (the value at this position will be overwritten)
	int shift_left(int** array, int* numberValues, const int position);

	//Function that reads and prints the content of a file to a given output file or stream
	void print_file_to(const char* filePath, FILE* output);

	/*###########################################################################
	#													FUNCTIONS MACROS																	#
	###########################################################################*/

	#define print_file(filePath) print_file_to(filePath, stdout);

#endif
