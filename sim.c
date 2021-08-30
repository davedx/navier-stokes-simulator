#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#include "macros.h"
#include "renderer.h"
#include "util.h"
#include "types.h"
#include "collision.h"

SimState simState;

const float LOG_FREQUENCY = 1.f;

float logTimer = LOG_FREQUENCY;

// HACK! this should derive from the airfoil geometry
Vec2 AF[4];//A, afB, afC, afD;

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

void getDeflected(Vec2* A, Vec2* N, Vec2* out) {
  float dotProduct = getDotProduct(A, N);
  out->x = A->x - 2 * dotProduct * N->x;
  out->y = A->y - 2 * dotProduct * N->y;
}

void moveParticle(Particle* P, float dt) {
  Vec2 newPos;
  Vec2 X;
  newPos.x = P->pos.x + P->vel.x * dt;
  newPos.y = P->pos.y + P->vel.y * dt;

  int log = 0;
  if (P->pos.x > -2.f && P->pos.x < 2.f && P->pos.y > -2.f && P->pos.y < 2.f) {
    log = 1;
  }

  Vec2 norm;
  Vec2 vel;
  int ni;
  LineSegment2 A, B;
  for (int i=0; i<4; i++) {
    A.from.x = P->pos.x;
    A.from.y = P->pos.y;
    A.to.x = newPos.x;
    A.to.y = newPos.y;
    ni = (i+1)%4;
    B.from.x = AF[i].x;
    B.from.y = AF[i].y;
    B.to.x = AF[ni].x;
    B.to.y = AF[ni].y;
    if (OK == lineSegmentIntersection(&A, &B, &X)) {
      getNormal(&AF[i], &AF[ni], &norm);
      // printf("Points: %.2f,%.2f - %.2f,%.2f Normal: %.2f,%.2f\n", AF[i].x,AF[i].y, AF[i+1 % 4].x,AF[i+1 % 4].y, norm.x,norm.y);
      getDeflected(&P->vel, &norm, &vel);
      // printf("Deflected vector: %.2f,%.2f\n", vel.x,vel.y);
      // TODO: recalculate newPos properly
      P->vel.x = vel.x;
      P->vel.y = vel.y;
      newPos.x = P->pos.x + P->vel.x * dt;
      newPos.y = P->pos.y + P->vel.y * dt;
      break;
    }
  }

  P->pos.x = newPos.x;
  P->pos.y = newPos.y;

  // wrap particles to reuse them
  if (P->pos.x > 50.f) {
    P->pos.x = -50.f + rand1() * 1.5f;
  }
}

void update(float dt) {
  logTimer -= dt;

  if (logTimer < 0) {
    logTimer = LOG_FREQUENCY;
    // printf("Vehicle accel %.2f,%.2f vel %.2f,%.2f pos %.2f,%.2f\n",
    //   simState.vehicle.acceleration.x, simState.vehicle.acceleration.y,
    //   simState.vehicle.velocity.x, simState.vehicle.velocity.y,
    //   simState.vehicle.position.x, simState.vehicle.position.y);
  }

  Vec2 pos;
  for (int i=0; i<NUM_PARTICLES; i++) {
    moveParticle(&simState.particle[i], dt);
  }
}

void generateGas() {
  for (int i=0; i<NUM_PARTICLES; i++) {
    simState.particle[i].pos.x = (rand1() * 100.f) - 50.f;
    simState.particle[i].pos.y = (rand1() * 100.f) - 50.f;
    simState.particle[i].vel.x = 2.f; // from wind
    simState.particle[i].vel.y = 0.f; // from wind
  }
}

int main (int argc, char **argv) {
  seedRand();

  // HACK
  //   0
  //  3 1
  //   2
  float LEN = 5.f;
  AF[0].x = 0;
  AF[0].y = -LEN;
  AF[1].x = LEN;
  AF[1].y = 0;
  AF[2].x = 0;
  AF[2].y = LEN;
  AF[3].x = -LEN;
  AF[3].y = 0;
  generateGas();

  simState.wind.x = 10.f;

  Vec2 test;
  getNormal(&AF[1], &AF[2], &test);
  // printf("Normal of %.2f,%.2f %.2f,%.2f = %.2f,%.2f\n", AF[1].x, AF[1].y, AF[2].x, AF[2].y, test.x, test.y);
  // testLineSegmentIntersection();
  initRenderer(argc, argv, update, &simState);
}

