#include <math.h>
#include "types.h"

float ONE_ANGSTROM;
float AIR_PARTICLE_SIZE;
float AIR_DISPERSION_ENERGY;
float BOLTZMANN_CONSTANT;
float AIR_DISPERSION_ENERGY_BY_BOLTZMANN_CONSTANT;

void initChemistry() {
  ONE_ANGSTROM = pow(10, -10);
  AIR_PARTICLE_SIZE = 3.55f * ONE_ANGSTROM;
  AIR_DISPERSION_ENERGY = 106.f;
  BOLTZMANN_CONSTANT = 1.38064852f * pow(10, -23);
  AIR_DISPERSION_ENERGY_BY_BOLTZMANN_CONSTANT = AIR_DISPERSION_ENERGY / BOLTZMANN_CONSTANT;
}

// Calculate Lennard-Jones force at a position `pos` in the simulation of particles
void getLennardJonesForce(SimState* sim, Vec2* pos, Vec2* out) {
  float dx, dy, dist, LJFmag;
  float Fx = 0, Fy = 0;
  for (int i = 0; i < NUM_PARTICLES; i++) {
    dx = (sim->particle[i].pos.x - pos->x) / 1000.f; // convert cm to m
    dy = (sim->particle[i].pos.y - pos->y) / 1000.f; // convert cm to m
    // calculate distance from `pos` to this particle
    dist = sqrt(dx * dx + dy * dy);
    // calculate the Lennard-Jones potential for this distance with LJ parameters for air molecules
    LJFmag = 4.f * AIR_DISPERSION_ENERGY_BY_BOLTZMANN_CONSTANT * (pow(AIR_PARTICLE_SIZE / dist, 12) - pow(AIR_PARTICLE_SIZE / dist, 6));
    // normalize the distance vector
    dx /= dist;
    dy /= dist;
    // multiply normal of distance by LJ potential to get a force vector
    dx *= LJFmag;
    dy *= LJFmag;
    // accumulate the intermolecular force between these two positions
    Fx += dx;
    Fy += dy;
  }
  // return the sum of all the intermolecular forces
  out->x = Fx;
  out->y = Fy;
}