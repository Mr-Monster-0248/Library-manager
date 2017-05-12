#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../headers/dates.h"
#include <time.h>


int compare_dates(Date date1, Date date2)
{
	//Comparing the years
	if (date1.year < date2.year)
		return 2;
	else if (date1.year > date2.year)
		return 1;

	//If the years are equal, comparing the months
	if (date1.month < date2.month)
		return 2;
	else if (date1.month > date2.month)
		return 1;

	//If the months are equal, comparing the days
	if (date1.day < date2.day)
		return 2;

	//If date1 is the most recent or both dates are equal, returning date1
	return 1;
}


Date current_date()
{
	Date currentDate;

	time_t tmp;
    struct tm timeDate;

    time(&tmp);
    timeDate = *gmtime(&tmp);

	currentDate.day = timeDate.tm_mday;
	currentDate.month = timeDate.tm_mon + 1;
	currentDate.year = timeDate.tm_year + 1900;

    return currentDate;
}
