#include <stdio.h>
#include <stdlib.h>
#include <math.h>


Date compare_dates(Date date1, Date date2)
{
	//Comparing the years
	if (date1.y < date2.y)
		return date2;
	else if (date1.y > date2.y)
		return date1;

	//If the years are equal, comparing the months
	if (date1.m < date2.m)
		return date2;
	else if (date1.m > date2.m)
		return date1;

	//If the months are equal, comparing the days
	if (date1.d < date2.d)
		return date2;

	//If date1 is the most recent or both dates are equal, returning date1
	return date1;
}

//NEED TO ADD RECOGNITION OF THE CURRENT DATE


Date closest_date(Date currentDate, Date date1, Date date2)
{
	//Comparing with the years
	if (fabs(currentDate.y - date1.y) < fabs(currentDate.y - date2.y))
		return date1;
	else if (fabs(currentDate.y - date1.y) > fabs(currentDate.y - date2.y))
		return date2;

	//Comparing with the months if the years are equal
	if (fabs(currentDate.m - date1.m) < fabs(currentDate.m - date2.m))
		return date1;
	else if (fabs(currentDate.m - date1.m) > fabs(currentDate.m - date2.m))
		return date2;

	//Comparing with the days if both years are equal
	if (fabs(currentDate.d - date1.d) < fabs(currentDate.d - date2.d))
		return date1;

	return date2; //If both dates are the same or date2 is the closest to the current date
}


int check_date_validity(Date date)
{
	if (date.m > 0 && date.m <= 12)
	{
		if (date.m <= 7)
		{
			switch(date.m % 2)
			{
				case 1:
					if (date.d < 0 || date.d > 31)
						return 0;
					return 1;
					break;

				case 0:
					if (date.m == 2)
					{
						if ((date.y % 4 == 0 && date.y % 100 != 0)  || date.y % 400 == 0) //If year is bisextile
						{

							if (date.d < 0 || date.d > 29)
								return 0;

							return 1;

							break;
						} else {
							if (date.d < 0 || date.d > 28)
								return 0;

							return 1;

							break;
						}
					}

					if (date.d < 0 || date.d > 30)
						return 0;
					return 1;
					break;

				default:
					return 0;
					break;
			}
		}

		switch(date.m % 2)
		{
			case 1:
				if (date.m < 0 || date.m > 30)
					return 0;
				return 1;
				break;

			case 0:
				if (date.m < 0 || date.m > 31)
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

	date.y = 1998;
	date.m = -1;
	date.d = -1;

	while(1)
	{
		fflush(stdin);
		printf("%s", message);
		scanf("%d/%d/%d", &(date.d), &(date.m), &(date.y));

		if (check_date_validity(date))
			break;
		else
			printf("This date does not exist!\n");
	}

	return date;
}
