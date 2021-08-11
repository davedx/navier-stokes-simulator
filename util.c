#include <stdlib.h>
#include <time.h>
#include <stdio.h>
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

int linesIntersection(Vec2* A, Vec2* B, Vec2* C, Vec2* D, Vec2* out, int log)
{
  // Line AB represented as a1x + b1y = c1
  float a1 = B->y - A->y;
  float b1 = A->x - B->x;
  float c1 = a1*(A->x) + b1*(A->y);
  
  // Line CD represented as a2x + b2y = c2
  float a2 = D->y - C->y;
  float b2 = C->x - D->x;
  float c2 = a2*(C->x)+ b2*(C->y);
  
  float determinant = a1*b2 - a2*b1;
  
  if (determinant == 0)
  {
      // lines are parallel
      return ERROR;
  }
  else
  {
      float x = (b2*c1 - b1*c2)/determinant;
      float y = (a1*c2 - a2*c1)/determinant;
      // if (log == 1) {
      //   printf("%.2f %.2f\n", x, y);
      // }
      if ((x > B->x && x > A->x) || (x < B->x && x < A->x)) {
        return ERROR;
      }
      if ((y > B->y && y > A->y) || (y < B->y && y < A->y)) {
        return ERROR;
      }
      if ((x > C->x && x > D->x) || (x < C->x && x < D->x)) {
        return ERROR;
      }
      if ((y > C->y && y > D->y) || (y < C->y && y < D->y)) {
        return ERROR;
      }
      out->x = x;
      out->y = y;
      return OK;
  }
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
