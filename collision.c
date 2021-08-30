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
  out->x = A->from.x + r.x * t;
  out->y = A->from.y + r.y * t;

  return OK;
}
