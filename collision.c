#include <stdio.h>
#include "types.h"
#include "macros.h"

float fake2DCross(Vec2* a, Vec2* b)
{
    return a->x * b->y - a->y * b->x;
}

int lineSegmentIntersection(LineSegment2* A, LineSegment2* B, Vec2* out) {
  Vec2 r, s;
  r.x = A->to.x - A->from.x;
  r.y = A->to.y - A->from.y;
  s.x = B->to.x - B->from.x;
  s.y = B->to.y - B->from.y;

  float denom = fake2DCross(&r, &s);
  if (denom == 0) {
    return ERROR;
  }

  Vec2 qMinP;
  qMinP.x = B->from.x - A->from.x;
  qMinP.y = B->from.y - A->from.y;

  float tNumer = fake2DCross(&qMinP, &s);
  float uNumer = fake2DCross(&qMinP, &r);

  float t = tNumer / denom;
  float u = uNumer / denom;

  if (t < 0 || t > 1 || u < 0 || u > 1) {
    return ERROR;
  }

  // p + r * t
  // printf("t = %.3f, r.x = %.3f, r.y = %.3f\n", t, r.x, r.y);
  out->x = A->from.x + r.x * t;
  out->y = A->from.y + r.y * t;

  return OK;
}

void testLineSegmentIntersection() {
  Vec2 out;
  LineSegment2 A, B;
  
  A.from.x = 0; A.from.y = 0;
  A.to.x = 10; A.to.y = 0;
  B.from.x = 0; B.from.y = 1;
  B.to.x = 10; B.to.y = 1;
  c_assert(lineSegmentIntersection(&A, &B, &out) == ERROR);
  A.from.x = -1; A.from.y = -1;
  A.to.x = 1; A.to.y = 1;
  B.from.x = -1; B.from.y = 1;
  B.to.x = 1; B.to.y = -1;
  c_assert(lineSegmentIntersection(&A, &B, &out) != ERROR);
  c_assert(out.x == 0);
  c_assert(out.y == 0);
  A.from.x = -1; A.from.y = -1;
  A.to.x = 1; A.to.y = 1;
  B.from.x = 0.9f; B.from.y = 1;
  B.to.x = 3.5f; B.to.y = -1;
  c_assert(lineSegmentIntersection(&A, &B, &out) != ERROR);
  printf("%f,%f\n", out.x, out.y);
  c_assert(out.x == 0.956522);
  c_assert(out.y == 0.956522);
}