#pragma once
#include "types.h"

void initChemistry();
void generateGas(SimState* simState, Vec2* wind);
void getLennardJonesForce(SimState* sim, Vec2* pos, Vec2* out);
