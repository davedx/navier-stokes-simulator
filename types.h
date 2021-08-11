#pragma once

#define OK 0
#define ERROR -1

#define NUM_PARTICLES 10000

struct _Vec2 {
  float x;
  float y;
};
typedef struct _Vec2 Vec2;

struct _LineSegment2 {
  Vec2 from;
  Vec2 to;
};
typedef struct _LineSegment2 LineSegment2;

struct _Particle {
  Vec2 pos;
  Vec2 vel;
};
typedef struct _Particle Particle;

struct _SimState {
  Vec2 wind;
  Particle particle[NUM_PARTICLES];
};
typedef struct _SimState SimState;
