#pragma once

float minf(float a, float b);

float maxf(float a, float b);

float clampf(float min, float a, float max);

float getMag(Vec2* A);

void getNormal(Vec2* A, Vec2* B, Vec2* out);

float getDotProduct(Vec2* A, Vec2* B);

void seedRand();

float rand1();