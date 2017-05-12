#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../headers/dates.h"
#include <time.h>


Date compare_dates(Date date1, Date date2)
{
	//Comparing the years
	if (date1.year < date2.year)
		return date2;
	else if (date1.year > date2.year)
		return date1;

	//If the years are equal, comparing the months
	if (date1.month < date2.month)
		return date2;
	else if (date1.month > date2.month)
		return date1;

	//If the months are equal, comparing the days
	if (date1.day < date2.day)
		return date2;

	//If date1 is the most recent or both dates are equal, returning date1
	return date1;
}

//NEED TO ADD RECOGNITION OF THE CURRENTDATE


Date closest_date(Date currentDate, Date date1, Date date2)
{
	//Comparing with the years
	if (fabs(currentDate.year - date1.year) < fabs(currentDate.year - date2.year))
		return date1;
	else if (fabs(currentDate.year - date1.year) > fabs(currentDate.year - date2.year))
		return date2;

	//Comparing with the months if the years are equal
	if (fabs(currentDate.month - date1.month) < fabs(currentDate.month - date2.month))
		return date1;
	else if (fabs(currentDate.month - date1.month) > fabs(currentDate.month - date2.month))
		return date2;

	//Comparing with the days if both years are equal
	if (fabs(currentDate.day - date1.day) < fabs(currentDate.day - date2.day))
		return date1;

	return date2; //If both dates are the same or date2 is the closest to the current date
}


int check_date_validity(Date date)
{
	if (date.month > 0 && date.month <= 12)
	{
		if (date.month <= 7)
		{
			switch(date.month % 2)
			{
				case 1:
					if (date.day < 0 || date.day > 31)
						return 0;
					return 1;
					break;

				case 0:
					if (date.month == 2)
					{
						if ((date.year % 4 == 0 && date.year % 100 != 0)  || date.year % 400 == 0) //If year is bisextile
						{

							if (date.day < 0 || date.day > 29)
								return 0;

							return 1;

							break;
						} else {
							if (date.day < 0 || date.day > 28)
								return 0;

							return 1;

							break;
						}
					}

					if (date.day < 0 || date.day > 30)
						return 0;
					return 1;
					break;

				default:
					return 0;
					break;
			}
		}

		switch(date.month % 2)
		{
			case 1:
				if (date.month < 0 || date.month > 30)
					return 0;
				return 1;
				break;

			case 0:
				if (date.month < 0 || date.month > 31)
					return 0;
				return 1;
				break;

			default:
				return 0;
				break;
		}
	}

	return 0;
}


Date ask_date(const char* message)
{
	Date date;

	date.year = 1998;
	date.month = -1;
	date.day = -1;

	while(1)
	{
		fflush(stdin);
		printf("%s", message);
		scanf("%d/%d/%d", &(date.day), &(date.month), &(date.year));

		if (check_date_validity(date))
			break;
		else
			printf("This date does not exist!\n");
	}

	return date;
}


Date current_date()
{
	Date currentDate

	time_t tmp;
    struct tm currentDate;

    time(&tmp);
    timeDate = *gmtime(&tmp);

	currentDate.day = timeDate.tm_day;
	currentDate.month = timeDate.tm_mon + 1;
	currentDate.year = timeDate.tm_year + 1900;

    return currentDate;
}
