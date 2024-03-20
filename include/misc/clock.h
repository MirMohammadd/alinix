#ifndef __CLOCK_H
#define __CLOCK_H

#define SECOND_RTC 0x00
#define MINUTE_RTC 0x02
#define HOUR_RTC 0x04
#define DAY_W_RTC 0x06
#define DAY_M_RTC 0x07
#define MONTH_RTC 0x08
#define YEAR_RTC 0x09

int get_second();
int get_hour();
int get_minute();
int get_second();
int get_day_m();
int get_month();
int get_year();
int get_day_w();
char* get_month_lng();
char* get_day_lng();
void date();


#endif