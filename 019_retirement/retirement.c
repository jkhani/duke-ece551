#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
   int months;
   double contribution;
   double rate_of_return;
};

typedef struct _retire_info retire_info;

double calcBalance (int startMonth, double currBalance, retire_info savingsInfo) {
  int months = savingsInfo.months;
  double contribution = savingsInfo.contribution;
  double rofReturn = savingsInfo.rate_of_return;

  for (int currMonth = startMonth; currMonth < (months + startMonth); currMonth++) {
    printf("Age %3d month %2d you have $%.2lf\n",(currMonth/12),(currMonth % 12), currBalance);

    currBalance = (currBalance * (1 + rofReturn)) + contribution;
  }

  return currBalance;
}

void retirement (int startAge,//in months
		 double initial, //initial savings in dollars
		 retire_info working, //info about working
		 retire_info retired) //info about being retired
{

  double newBalance = calcBalance(startAge, initial, working);

  int retiredMonth = startAge + working.months;

  newBalance = calcBalance(retiredMonth, newBalance, retired);
}

int main (void) {

  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045/12;

  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01/12;

  int startAge = 327;
  double initial = 21345;

  retirement(startAge, initial, working, retired);

  return 0;
}
