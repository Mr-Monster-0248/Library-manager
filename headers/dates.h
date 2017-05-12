#ifndef DEF_DATE
#define DEF_DATE

typedef struct Date
{
    int day;
    int month;
    int year;
} Date;

//return the most recent date(exemple 1900 and 2000 return 2)
int compare_dates(Date date1, Date date2);

//Give current date
Date current_date();

#endif
