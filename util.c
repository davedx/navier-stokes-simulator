#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

float minf(float a, float b) {
  return a < b ? a : b;
}

float maxf(float a, float b) {
  return a > b ? a : b;
}

float clampf(float min, float a, float max) {
  if (a < min) a = min;
  if (a > max) a = max;
  return a;
}

long generateRandomSeed() {
  struct timeval tv;

  gettimeofday(&tv, NULL);

  return tv.tv_usec;
}

void seedRand() {
  srand(generateRandomSeed());
}

float rand1() {
  return (float)rand() / RAND_MAX;
}
