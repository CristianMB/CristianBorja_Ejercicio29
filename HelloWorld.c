#include <stdio.h>
#include <omp.h>

int main(int argc, char **argv)
{
#pragma omp parallel
  {
    int thread_id = omp_get_thread_num();
    int thread_count = omp_get_num_threads();
    printf("Hello from thread number: %d out of: %d\n",
           thread_id, thread_count);
  }
  return 0;
}
