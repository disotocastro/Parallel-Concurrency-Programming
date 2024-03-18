#include <stdio.h>
#include <statistics.h>

int main(int argc, char const *argv[])
{
  statistics_t* statistics = statistics_create();

  int error = statistics_run(statistics, argc, argv);
  statistics_destroy(statistics);
  
  return error;
}

