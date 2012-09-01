/* =====================================================================
 *
 * file: oglbasic.c
 * info: OpenGL basic program using freeglut
 *
 * ===================================================================== */

/* header files */
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include <GL/freeglut.h>

/* function prototypes */
int main(int, char**);

void setup(void);
void cleanup(void);

void cb_keyboard(unsigned char, int, int);
void cb_special(int, int, int);
void cb_reshape(int, int);
void cb_display(void);


/* ---------------------------------------------------------------------
 *
 * main entry point
 *
 * --------------------------------------------------------------------- */
int main(int argc, char** argv)
{
  printf("OpenGL basic: started.\n");
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
  glutInitWindowSize(1280, 720);
  glutCreateWindow("OpenGL Basic");
  
  glutKeyboardFunc(cb_keyboard);
  glutSpecialFunc(cb_special);
  glutReshapeFunc(cb_reshape);
  glutDisplayFunc(cb_display);

  setup();

  glutMainLoop();

  return 0;
}

/* ---------------------------------------------------------------------
 *
 * setup OpenGL environment
 *
 * --------------------------------------------------------------------- */
void setup(void)
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

/* ---------------------------------------------------------------------
 *
 * teardown OpenGL environment
 *
 * --------------------------------------------------------------------- */
void cleanup(void)
{
      printf("OpenGL basic: terminating...\n");
}

/* ---------------------------------------------------------------------
 *
 * callback for "normal" key(board) events
 *
 * --------------------------------------------------------------------- */
void cb_keyboard(unsigned char key, int x, int y)
{
  switch(key)
    {
    case 0x1b:
      cleanup();
      glutLeaveMainLoop();
      break;
    default:
      fprintf(stderr,
	      "[info] cb_keyboard: unhandled key \"%c\" (0x%02x).\n",
	      isgraph(key)?key:'?', key);
      break;
    }
}

/* ---------------------------------------------------------------------
 *
 * callback for "special" key(board) events
 *
 * --------------------------------------------------------------------- */
void cb_special(int key, int x, int y)
{
  switch(key)
    {
    default:
      fprintf(stderr,
	      "[info] cb_special: unhandled key 0x%02x.\n",
	      key);
      break;
    }
}

/* ---------------------------------------------------------------------
 *
 * callback to handle window resize
 *
 * --------------------------------------------------------------------- */
void cb_reshape(int w, int h)
{
  fprintf(stderr,
	  "[info] cb_reshape: width=%d and height=%d.\n",
	  w, h);
}

/* ---------------------------------------------------------------------
 *
 * callback to render the scene
 *
 * --------------------------------------------------------------------- */
void cb_display(void)
{
  /* clear scene */
  glClear(GL_COLOR_BUFFER_BIT |
	  GL_DEPTH_BUFFER_BIT |
	  GL_STENCIL_BUFFER_BIT);

  /* render scene */


  /* flush and redraw */
  glutSwapBuffers();
  //glutPostRedisplay();
}

/* =====================================================================
 *
 * End Of File
 *
 * ===================================================================== */
