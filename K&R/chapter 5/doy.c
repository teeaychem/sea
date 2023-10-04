#include <stdio.h>


int main()
{
  int day_of_year(int year, int month, int day);
  void month_day(int year, int yearday, int *pmonth, int *pday);

  int year = 2023;
  int month = 2;
  int day = 29;
  int yearday = day_of_year(year, month, day);

  if (yearday < 0) {
    printf("Error. The following is not possible.\n"
	   "Year:\t%d\n"
	   "Month:\t%d\n"
	   "Day:\t%d\n",
	   year,
	   month,
	   day);
  } else {
    printf("%d/%d/%d is %d days into the year.\n",
	   year,
	   month,
	   day,
	   yearday
	   );
  }

  int *pmonth;
  int *pday;

  yearday = 366;
  year = 2024;
  month_day(year, yearday, pmonth, pday);

  if (*pmonth == -1) {
    printf("Error. The following is not possible.\n"
	   "Year:\t\t%d\n"
	   "Yearday:\t%d\n",
	   year,
	   yearday);
  } else {
    printf("%d/%d/%d is %d days into the year.\n",
	   year,
	   *pmonth,
	   *pday,
	   yearday
	   );
  }


  return 0;
}

static char daytab[2][13] = {
  {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month day */
int day_of_year(int year, int month, int day)
{
  int i, leap;
  if (month < 1 || 12 < month)
    return -1;

  leap = year%4 == 0 &year%100 != 0 || year%400 == 0;

  if (day < 1 || daytab[leap][month] < day)
    return -1;

  for (i = 1; i < month; i++)
    day += daytab[leap][i];
  return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
  int i, leap;

  leap = year%4 == 0 &year%100 != 0 || year%400 == 0;

  if ((leap && yearday > 366) || (!leap && yearday > 365)) {
    *pmonth = -1;
    *pday = -1;
  } else {
    for (i = 1; yearday > daytab[leap][i]; i++)
      yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
  }
}
