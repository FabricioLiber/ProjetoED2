#include <stdio.h>
#include <time.h>

int time ()
{
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );

  return asctime(timeinfo);
}
