#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include "types.h"

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

float getMag(Vec2* A) {
  return sqrt(A->x * A->x + A->y * A->y);
}

void getNormal(Vec2* A, Vec2* B, Vec2* out) {
  float dx = B->x - A->x;
  float dy = B->y - A->y;
  float N1x = -dy;
  float N1y = dx;
  float N2x = dy;
  float N2y = -dx;
  out->x = N2x - N1x;
  out->y = N2y - N1y;
  float mag = getMag(out);
  out->x /= mag;
  out->y /= mag;
}

float getDotProduct(Vec2* A, Vec2* B) {
  return A->x * B->x + A->y * B->y;
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
