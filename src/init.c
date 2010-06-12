#include <GL/glut.h>

#include "gui.h"
#include "init.h"

const int width = 800;
const int height = 600;
  

int mouse_x;
int mouse_y;
int getMouseX() { return mouse_x; }
int getMouseY() { return mouse_y; }

void loop()
{
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  draw();

  glutSwapBuffers();

  update();
}

void mouse_move_inverse_y(int x, int y)
{
  mouse_x = x;
  mouse_y = height - y;
  mouse_move();
}

void key_press_aux(unsigned char key, int x, int y)
{
  key_press(key);
}

void mouse_click_aux(int button, int state, int x, int y)
{
  if(state == GLUT_DOWN)
  {
    if(button == GLUT_LEFT_BUTTON)
      mouse_left_click();
    else
      mouse_right_click();
  }
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitWindowSize(width, height);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutCreateWindow("Computing roots of Bezier polynomials");
  
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glEnable(GL_DEPTH_TEST);
  glOrtho(0.0f, width, 0.0f, height, -1.0f, 1.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  // antialiasing
  //glEnable (GL_LINE_SMOOTH);
  //glEnable (GL_BLEND);
  //glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  //glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
  //glHint (GL_POLYGON_SMOOTH_HINT, GL_DONT_CARE);
  //glHint (GL_POINT_SMOOTH_HINT, GL_DONT_CARE);
  
  glutIdleFunc(loop);
  glutKeyboardFunc(key_press_aux);
  glutMouseFunc(mouse_click_aux);
  glutPassiveMotionFunc(mouse_move_inverse_y);
  
  init();
  
  //glutSetCursor(GLUT_CURSOR_NONE);
  mouse_x = mouse_y = 0;
  
  glutMainLoop();

  return 0;
}
