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
#include <sys/stat.h>

#include <GL/freeglut.h>

/* function prototypes */
int main(int argc, char **argv);

off_t fsize(const char *filename);
size_t load_shader(const char *filename, char **buffer);

void setup(void);
void cleanup(void);

void cb_keyboard(unsigned char key, int x, int y);
void cb_special(int key, int x, int y);
void cb_reshape(int w, int h);
void cb_display(void);


/* ---------------------------------------------------------------------
 *
 * main entry point
 *
 * --------------------------------------------------------------------- */
int main(int argc, char **argv)
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
 * calculate file size
 *
 * --------------------------------------------------------------------- */
off_t fsize(const char *filename)
{
  struct stat st; 
  
  if (stat(filename, &st) == 0)
    {
      return st.st_size;
    }
  
  return -1;
}

/* ---------------------------------------------------------------------
 *
 * load a file into a buffer
 *
 * --------------------------------------------------------------------- */
size_t load_shader(const char *filename, char **buffer)
{
  static off_t filesizelimit = 64 * 1024 * 1024;
  FILE *fp;
  size_t size;
  size_t total = 0;
  size_t bytes;
  
  off_t filesize = fsize(filename);
  if (filesize == -1) 
    {
      fprintf(stderr, "[Error] failed to get filesize!\n");
      return -1;
    }
  if (filesize > filesizelimit)
    {
      fprintf(stderr, "[Error] filesize is over limit!\n");
      return -1;
    }

  size = (size_t) filesize; // unnecessary, but they are different types

  *buffer = calloc(1, size+1); // add extra space, e.g. terminate with NULL
  if ((*buffer) == NULL)
    {
      fprintf(stderr, "[Error] calloc failed!\n");
      return -1;
    }

  fp = fopen(filename, "rb");
  if (fp == NULL)
    {
      fprintf(stderr, "[Error] cannot open file!\n");
      free(*buffer);
      *buffer = NULL;
      return -1;
    }
  
  do
    {
      bytes = fread((*buffer)+total, 1, size-total, fp);
      total += bytes;
    }
  while(!feof(fp) && (size != total));

  if (size != total)
    {
      fprintf(stderr,
	      "[Error] size does not match (%zd<>%zd)!\n",
	      size, total);
      free(*buffer);
      buffer = NULL;
      size = -1;
    }

  fclose(fp);

  return size;
}

/* ---------------------------------------------------------------------
 *
 * setup OpenGL environment
 *
 * --------------------------------------------------------------------- */
void setup(void)
{
#if 0
  // NOTE: this is just for debugging "load_shader"!!!
  size_t size;
  char *buffer;

  size = load_shader("../shaders/basic.vert", &buffer);
  if (size == -1)
    {
      fprintf(stderr, "[Error] Failed to load shader!\n");
      exit(-1);
    }
  else
    {
      printf("* size: %zd, buffer: %p\n", size, buffer);
      printf("Shader loaded:\n--- BEGIN ---\n%s--- END ---\n",
	     buffer);
      free(buffer);
    }
#endif
  
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
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
  
  // prevent divide by zero
  if(h == 0) {
    h = 1;
  }
  
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
  gluPerspective(40.0, (GLfloat) w / (GLfloat) h, 1.0, 20.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

/* ---------------------------------------------------------------------
 *
 * callback to render the scene
 *
 * --------------------------------------------------------------------- */
void cb_display(void)
{
  /* clear scene */
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT |
	  GL_DEPTH_BUFFER_BIT |
	  GL_STENCIL_BUFFER_BIT);

  /* render scene */
  // add light
  //glPush

  // add teapot
  glColor3f(1.0f, 1.0f, 1.0f);
  glutSolidTeapot(1.0);

  /* flush and redraw */
  glutSwapBuffers();
  //glutPostRedisplay();
}

/* =====================================================================
 *
 * End Of File
 *
 * ===================================================================== */
