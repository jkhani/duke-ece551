#include <stdio.h>
#include <stdlib.h>

 typedef struct _retire_info {
   int MONTHS;
   double CONTRIBUTION;
   double RATE_OF_RETURN;
 } retire_info;

double calcBalance (int startMonth, double currBalance, retire_info savingsInfo) {
  int months = savingsInfo.MONTHS;
  double contribution = savingsInfo.CONTRIBUTION;
  double rofReturn = savingsInfo.RATE_OF_RETURN;

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

  int retiredMonth = startAge + working.MONTHS;

  newBalance = calcBalance(retiredMonth, newBalance, retired);
}

int main (void) {

  retire_info working;
  working.MONTHS = 489;
  working.CONTRIBUTION = 1000;
  working.RATE_OF_RETURN = 0.045/12;

  retire_info retired;
  retired.MONTHS = 384;
  retired.CONTRIBUTION = -4000;
  retired.RATE_OF_RETURN = 0.01/12;

  int startAge = 327;
  double initial = 21345;

  retirement(startAge, initial, working, retired);

  return 0;
}
