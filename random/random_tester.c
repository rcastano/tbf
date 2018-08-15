#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

time_t seconds = 0;
DEFINE_CONST_OFFSET time_t offset

unsigned int get_rand_seed() {
  struct timespec curr_time;
  clock_gettime(CLOCK_REALTIME, &curr_time);
  return curr_time.tv_nsec;
}

void input(void * var, size_t var_size, const char * var_name) {
  if (seconds == 0) {
    seconds = time(NULL) + offset;
  }
  if (time(NULL) > seconds) {
    exit(0);
  }

  srand(get_rand_seed());
  FILE *vector = fopen("vector.test", "a+");
  size_t int_size = sizeof(int);
  unsigned char * new_val = malloc(var_size);

  fprintf(vector, "%s: 0x", var_name);
  for (int i = 0; i < var_size; i++) {
    new_val[var_size - i] = (char) (rand() & 255);
    fprintf(vector, "%.2x", new_val[var_size - i]);
  }
  memcpy(new_val, var, var_size);

  fprintf(vector, "\n");
  fclose(vector);
}
