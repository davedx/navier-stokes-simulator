#pragma once

struct _Vec2 {
  float x;
  float y;
};

typedef struct _Vec2 Vec2;

struct _Vehicle {
  Vec2 position;
  Vec2 velocity;
  Vec2 acceleration;
};

typedef struct _Vehicle Vehicle;

struct _SimState {
  Vehicle vehicle;
  Vec2 windSpeed;
  Vec2 target;
};

typedef struct _SimState SimState;
