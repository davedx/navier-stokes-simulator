
/* Copyright (c) Mark J. Kilgard, 1997. */

/* This program is freely distributable without licensing fees 
   and is provided without guarantee or warrantee expressed or 
   implied. This program is -not- in the public domain. */

/* This program was requested by Patrick Earl; hopefully someone else
   will write the equivalent Direct3D immediate mode program. */
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <stdio.h>
#include "types.h"

GLfloat light_diffuse[] = {1.0, 0.0, 0.0, 1.0};  /* Red diffuse light. */
GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};  /* Infinite light location. */
GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
  {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
  {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };
GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
  {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
  {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };
GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */

void (*__updateFunc)(float);

SimState* __simState = NULL;

void
drawBox(void)
{
  int i;

  for (i = 0; i < 6; i++) {
    glBegin(GL_QUADS);
    glNormal3fv(&n[i][0]);
    glVertex3fv(&v[faces[i][0]][0]);
    glVertex3fv(&v[faces[i][1]][0]);
    glVertex3fv(&v[faces[i][2]][0]);
    glVertex3fv(&v[faces[i][3]][0]);
    glEnd();
  }
}

int timeSinceStart = 0;

void
display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0, 0.0, 100.0,
    0.0, 0.0, 0.0,
    0.0, 1.0, 0.);

  glRotatef(90, 1.0, 0.0, 0.0);

  if (__simState) {
    // Render the vehicle
    glPushMatrix();
    glTranslatef(__simState->vehicle.position.x, -1, __simState->vehicle.position.y);
    drawBox();
    glPopMatrix();

    // Render the target
    glPushMatrix();
    glTranslatef(__simState->target.x, -1, __simState->target.y);
    glScalef(0.5f, 0.5f, 0.5f);
    drawBox();
    glPopMatrix();

    // Render the vehicle acceleration as a point (an arrow would be better)
    glPushMatrix();
    float ax = __simState->vehicle.position.x + __simState->vehicle.acceleration.x;
    float ay = __simState->vehicle.position.y + __simState->vehicle.acceleration.y;
    glTranslatef(ax, -1, ay);
    glScalef(0.2f, 0.2f, 0.2f);
    drawBox();
    glPopMatrix();
  }

  glutSwapBuffers();
}

int oldTimeSinceStart = 0;

void idle(void)
{
  timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
  int deltaTime = timeSinceStart - oldTimeSinceStart;
  oldTimeSinceStart = timeSinceStart;

  float deltaInSeconds = (float)deltaTime/1000.f;
  // if we lose window context, we get 0 deltas which results in nans in our simulator
  if (deltaInSeconds <= 0) {
    deltaInSeconds = 0.0001f;
  }
  __updateFunc(deltaInSeconds);

  glutPostRedisplay();
}

void
initRenderer(int argc, char **argv, void (*updateFunc)(float), SimState *simState)
{
  int width = 1200;
  int height = 800;

  __updateFunc = updateFunc;
  __simState = simState;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("simulation renderer");
  glutDisplayFunc(display);
  glutIdleFunc(idle);

  /* Setup cube vertex data. */
  v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1;
  v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1;
  v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1;
  v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1;
  v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1;
  v[1][2] = v[2][2] = v[5][2] = v[6][2] = -1;

  /* Enable a single OpenGL light. */
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);

  /* Use depth buffering for hidden surface elimination. */
  glEnable(GL_DEPTH_TEST);

  /* Setup the view of the cube. */
  glutReshapeWindow(width, height);
  float aspectRatio = (float)width / (float)height;
  glMatrixMode(GL_PROJECTION);
  gluPerspective(40.0,
    aspectRatio,
    1.0, 200.0);

  glutMainLoop();
}
