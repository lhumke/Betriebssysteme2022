#include "kernel/types.h"
#include "kernel/net.h"
#include "kernel/stat.h"
#include "user/user.h"

#define GT +2

// see https://datatracker.ietf.org/doc/html/rfc1361
char *month[] = {"Jan", "Feb", "Mar", "Apr", "Mai", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dez"};
int daysOfMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void
printDate(uint32 sec)
{
    uint32 min = sec / 60;
    uint32 h   = min / 60;
    uint32 d   = h   / 24;
    uint32 y   = 1900;
    int i = 0;

    uint32 comp_val = ((y+1) % 4 != 0) ? 365 : 366;
    while (d >= comp_val) {
        d -= comp_val;
        y++;
        comp_val = ((y+1) % 4 != 0) ? 365 : 366;
    }
    d++; // d=0 -> 1 Jan
    while (d > daysOfMonth[i] || (i == 1 && y % 4 == 0 && d > daysOfMonth[i])) {
        d -= daysOfMonth[i];
        if (i == 1 && y % 4 == 0)
            d--;
        i++;
    }

    printf("Date: %l %s. %l, %l:%l:%l\n", d, month[i], y, (h%24) + GT, min%60, sec%60);
}


void
sntp(void) 
{
    
}

int
main(int argc, char *argv[])
{
  if(argc < 1){
    fprintf(2, "Usage: sntp");
    exit(1);
  }
  sntp();
  exit(0);
}