#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#include "macros.h"
#include "renderer.h"
#include "util.h"
#include "types.h"

SimState simState;

const float LOG_FREQUENCY = 1.f;

float logTimer = LOG_FREQUENCY;

void update(float dt) {
  logTimer -= dt;

  if (logTimer < 0) {
    logTimer = LOG_FREQUENCY;
    // printf("Vehicle accel %.2f,%.2f vel %.2f,%.2f pos %.2f,%.2f\n",
    //   simState.vehicle.acceleration.x, simState.vehicle.acceleration.y,
    //   simState.vehicle.velocity.x, simState.vehicle.velocity.y,
    //   simState.vehicle.position.x, simState.vehicle.position.y);
  }

  // Vec2 accel;
  // if (ERROR == getAccelerationPropIntegDeriv(&simState, dt, &accel)) {
  //   exit(1);
  // } else {
  //   simState.vehicle.acceleration.x = accel.x;
  //   simState.vehicle.acceleration.y = accel.y;
  // }
}

int main (int argc, char **argv) {
  seedRand();

  initRenderer(argc, argv, update, &simState);
}

