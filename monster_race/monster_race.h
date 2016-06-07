#define _CRT_SECURE_NO_DEPRECATE//bez tego blad fopen
#define PINGIEL_ICON 1
#define ID_TIMER_REDRAW 501
#define ID_TIMER_REDRAW2 502
#include <Windows.h>
#include "GLEW\glew.h"
#include "GLEW\wglew.h"
#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\GLAux.h>
#include <stdio.h>
#include <gl/glut.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string.h>
#include <math.h>
#include"md5load.h"
#include"particles.h"
#include "shader.h"
#include "framebuffe.h"
#include "dsound.h"
#pragma comment(lib,"glew32.lib")
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"glaux.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"Dsound.lib")

GLuint* wyslij();

void rysuj(IDirectSoundBuffer* dzwiek,GLUquadricObj *quadric);
void setFog();
void plansza();
void gracz(int x, int y, int z,int a);
void ball(GLUquadricObj *quadric,double x, double y, double z, int r);
void init(const char *filename,int x, int z);
void cleanup();
void mouseMovement(int button, int state, int x, int y);
GLuint loadTga(char *fileName);
void menu();
void skyBox();
extern bool keys[];
extern float xrota;
extern float yrota;
extern float opcje[4];
extern double tajm;
extern double cur_frame;
extern double nex_frame;
extern md5load md5object;
extern md5load ziemia;
extern md5load potworsmall;
extern md5load potworbig;
extern md5load enemy;
extern md5load sgup;
extern md5load sgdown;
extern genCzastek particless;
extern Shader* podstawowy_shader;
extern GLfloat loc;
extern int enter;
extern int up;
extern int down;
extern int lefty;
extern int righty;
extern int upty;
extern GLuint texture[];
extern double speed;
extern bool BLOOM;
extern bool LIGHTS;
extern int GAME_OVER;