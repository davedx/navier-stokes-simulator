#include <stdio.h>
#include "macros.h"
#include "types.h"
#include "chemistry.h"
#include "collision.h"
#include "util.h"

void test_getNormal() {
  Vec2 a, b, out;
  a.x = 0;
  a.y = 0;
  b.x = 1;
  b.y = 0;
  getNormal(&a, &b, &out);
  c_assert_float(out.x, 0.f);
  c_assert_float(out.y, -1.f);
  a.x = 1.f;
  a.y = 1.f;
  b.x = 0;
  b.y = 0;
  getNormal(&a, &b, &out);
  c_assert_float(out.x, -0.707107f);
  c_assert_float(out.y, 0.707107f);
}

void test_lineSegmentIntersection() {
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
  c_assert_float(out.x, 0.f);
  c_assert_float(out.y, 0.f);
  A.from.x = -1; A.from.y = -1;
  A.to.x = 1; A.to.y = 1;
  B.from.x = 0.9f; B.from.y = 1;
  B.to.x = 3.5f; B.to.y = -1;
  c_assert(lineSegmentIntersection(&A, &B, &out) != ERROR);
  c_assert_float(out.x, 0.956522f);
  c_assert_float(out.y, 0.956522f);
}

void test_lennard_jones() {
  initChemistry();
  Vec2 loc, force;
  SimState simState;
  Vec2 wind;
  wind.x = 2.f;
  wind.y = 0;
  generateGas(&simState, &wind);

  loc.x = 0; loc.y = 0;
  force.x = 0; force.y = 0;

  getLennardJonesForce(&simState, &loc, &force);
  printf("LJ force at %.3f, %.3f: %.15f, %.15f\n", loc.x, loc.y, force.x, force.y);
  loc.x = -51.f; loc.y = -51.f;
  getLennardJonesForce(&simState, &loc, &force);
  printf("LJ force at %.3f, %.3f: %.15f, %.15f\n", loc.x, loc.y, force.x, force.y);
  loc.x = 51.f; loc.y = 51.f;
  getLennardJonesForce(&simState, &loc, &force);
  printf("LJ force at %.3f, %.3f: %.15f, %.15f\n", loc.x, loc.y, force.x, force.y);
}

int main (int argc, char **argv) {
  printf("Running unit tests\n");

  test_getNormal();
  test_lineSegmentIntersection();
  test_lennard_jones();

  return 0;
}
