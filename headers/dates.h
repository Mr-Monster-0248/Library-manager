#ifndef DEF_DATE
#define DEF_DATE

typedef struct Date
{
    int day;
    int month;
    int year;
} Date;

//return the most recent date
Date compare_dates(Date date1, Date date2);

//retrun the closest date from tooday
Date closest_date(Date currentDate, Date date1, Date date2);

//chach if a date exist return 0 if not
int check_date_validity(Date date);

Date ask_date(const char* message);

//Give current date
Date current_date();
