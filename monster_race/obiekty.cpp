#include "monster_race.h"


unsigned int img;
int selectOpt[5] = { 0, 0, 0, 0, 15 };
bool menuSnd = false, graSnd = true;
double speed = 3;
double alpha = 90;//kierunek wzdloz osi X
int GAME_OVER = 0;
double z = 150;//srodek pola start
double x = 150;//srodek pola start
double zE = 150;
double xE = 200;
int random = 0;
int randomNum = 0;
double kontE = 90;
bool kurz=false;
void Restart()
{
	speed = 3;
	 alpha = 90;//kierunek wzdloz osi X
	GAME_OVER = 0;
	z = 150;//srodek pola start
	x = 150;//srodek pola start
	zE = 150;
	xE = 200;
	random = 0;
	randomNum = 0;
	kontE = 90;
}
void teksturnik(int tex, int normalTex)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture[tex]);
	glUniform1i(glGetUniformLocation(podstawowy_shader->Out(), "img"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture[normalTex]);
	glUniform1i(glGetUniformLocation(podstawowy_shader->Out(), "normalmap"), 1);
}
int xs = 0;
void skyBox()
{
//	glColor4f(0.45,0.45,0.45, 1);
	if (menuSnd||GAME_OVER==2)
	{
		glPushMatrix();
		glTranslated(0, -2, 0);
		glRotated(alpha, 0, 1, 0);  //obracam i przesuwam mape, a nie gracza
		glDepthMask(0);

		teksturnik(18, 18);
		/* Front Face */
		glBegin(GL_TRIANGLE_STRIP);//podobno wydajniej niz quad
		glNormal3f(0.0, 0.0, -1.0);
		glTexCoord2d(0, 0);	glVertex3d(-10, -10, 10);
		glTexCoord2d(0, 10); glVertex3d(10, -10, 10);
		glTexCoord2d(10, 0); glVertex3d(-10, 10, 10);
		glTexCoord2d(10, 10); glVertex3d(10, 10, 10);
		glEnd();


		//teksturnik(15, 15);
		/* top Face */
		glBegin(GL_TRIANGLE_STRIP);//podobno wydajniej niz quad
		glNormal3f(0.0, -1.0, 0.0);
		glTexCoord2d(0, 0);	glVertex3d(-10, 10, -10);
		glTexCoord2d(10, 0); glVertex3d(10, 10, -10);
		glTexCoord2d(0, 10); glVertex3d(-10, 10, 10);
		glTexCoord2d(10, 10); glVertex3d(10, 10, 10);
		glEnd();


		//teksturnik(10, 10);
		/* bot Face */
		glNormal3f(0.0, 1.0, 0.0);
		glBegin(GL_TRIANGLE_STRIP);//podobno wydajniej niz quad
		glNormal3f(0.0, -1.0, 0.0);
		glTexCoord2d(0, 0);	glVertex3d(-10, -10, -10);
		glTexCoord2d(10, 0); glVertex3d(10, -10, -10);
		glTexCoord2d(0, 10); glVertex3d(-10, -10, 10);
		glTexCoord2d(10, 10); glVertex3d(10, -10, 10);
		glEnd();

	//	teksturnik(11, 11);
		/* left Face */
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_TRIANGLE_STRIP);//podobno wydajniej niz quad
		glNormal3f(0.0, -1.0, 0.0);
		glTexCoord2d(0, 0);	glVertex3d(-10, -10, 10);
		glTexCoord2d(0, 10); glVertex3d(-10, -10, -10);
		glTexCoord2d(10, 0); glVertex3d(-10, 10, 10);
		glTexCoord2d(10, 10); glVertex3d(-10, 10, -10);
		glEnd();

		//teksturnik(14, 14);
		/* right Face */
		glNormal3f(-1.0, 0.0, 0.0);
		glBegin(GL_TRIANGLE_STRIP);//podobno wydajniej niz quad
		glNormal3f(-1.0, 0.0, 0.0);
		glTexCoord2d(0, 0);	glVertex3d(10, -10, -10);
		glTexCoord2d(10, 0); glVertex3d(10, -10, 10);
		glTexCoord2d(0, 10); glVertex3d(10, 10, -10);
		glTexCoord2d(10, 10); glVertex3d(10, 10, 10);
		glEnd();

		//teksturnik(12, 12);
		/* mid Face */
		glNormal3f(0.0, 0.0, 1.0);
		glBegin(GL_TRIANGLE_STRIP);//podobno wydajniej niz quad
		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2d(0, 0);	glVertex3d(-10, -10, -10);
		glTexCoord2d(10, 0); glVertex3d(10, -10, -10);
		glTexCoord2d(0, 10); glVertex3d(-10, 10, -10);
		glTexCoord2d(10, 10); glVertex3d(10, 10, -10);
		glEnd();

		glDepthMask(1);
		glPopMatrix();
	}
	else
	{

	
	glPushMatrix();
	glTranslated(0, -2, 0);
	glRotated(alpha, 0, 1, 0);  //obracam i przesuwam mape, a nie gracza
	glDepthMask(0);

	teksturnik(13, 13);
	/* Front Face */
	glBegin(GL_TRIANGLE_STRIP);//podobno wydajniej niz quad
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2d(1, 0);	glVertex3d(-10, -10, 10);
	glTexCoord2d(0, 0); glVertex3d(10, -10, 10);
	glTexCoord2d(1, 1); glVertex3d(-10, 10, 10);
	glTexCoord2d(0, 1); glVertex3d(10, 10, 10);
	glEnd();


	teksturnik(15, 15);
	/* top Face */
	glBegin(GL_TRIANGLE_STRIP);//podobno wydajniej niz quad
	glNormal3f(0.0, -1.0, 0.0);
	glTexCoord2d(0, 0);	glVertex3d(-10, 10, -10);
	glTexCoord2d(1, 0); glVertex3d(10, 10, -10);
	glTexCoord2d(0, 1); glVertex3d(-10, 10, 10);
	glTexCoord2d(1, 1); glVertex3d(10, 10, 10);
	glEnd();


	teksturnik(10, 10);
	/* bot Face */
	glNormal3f(0.0, 1.0, 0.0);
	glBegin(GL_TRIANGLE_STRIP);//podobno wydajniej niz quad
	glNormal3f(0.0, -1.0, 0.0);
	glTexCoord2d(0, 0);	glVertex3d(-10, -10, -10);
	glTexCoord2d(1, 0); glVertex3d(10, -10, -10);
	glTexCoord2d(0, 1); glVertex3d(-10, -10, 10);
	glTexCoord2d(1, 1); glVertex3d(10, -10, 10);
	glEnd();

	teksturnik(11, 11);
	/* left Face */
	glNormal3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLE_STRIP);//podobno wydajniej niz quad
	glNormal3f(0.0, -1.0, 0.0);
	glTexCoord2d(0, 0);	glVertex3d(-10, -10, 10);
	glTexCoord2d(1, 0); glVertex3d(-10, -10, -10);
	glTexCoord2d(0, 1); glVertex3d(-10, 10, 10);
	glTexCoord2d(1, 1); glVertex3d(-10, 10, -10);
	glEnd();

	teksturnik(14, 14);
	/* right Face */
	glNormal3f(-1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLE_STRIP);//podobno wydajniej niz quad
	glNormal3f(-1.0, 0.0, 0.0);
	glTexCoord2d(0, 0);	glVertex3d(10, -10, -10);
	glTexCoord2d(1, 0); glVertex3d(10, -10, 10);
	glTexCoord2d(0, 1); glVertex3d(10, 10, -10);
	glTexCoord2d(1, 1); glVertex3d(10, 10, 10);
	glEnd();

	teksturnik(12, 12);
	/* mid Face */
	glNormal3f(0.0, 0.0, 1.0);
	glBegin(GL_TRIANGLE_STRIP);//podobno wydajniej niz quad
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2d(0, 0);	glVertex3d(-10, -10, -10);
	glTexCoord2d(1, 0); glVertex3d(10, -10, -10);
	glTexCoord2d(0, 1); glVertex3d(-10, 10, -10);
	glTexCoord2d(1, 1); glVertex3d(10, 10, -10);
	glEnd();

	glDepthMask(1);
	glPopMatrix();
	}
	glColor4f(1, 1, 1, 1);
}


void gracz(int x, int y, int z, int anim)
{
	
	glPushMatrix();	
	glUniform3f(glGetUniformLocation(podstawowy_shader->Out(), "lightPos"), -cos(alpha / 180 * 3.1415926) * 100, 100, sin(alpha / 180 * 3.1415926) * 100);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	md5object.draw(x, y - 5, z, 0.3, anim,11);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
	
}

void inne(int x, int y, int z, int anim,md5load& inne,int velocity)
{

	glPushMatrix();
	
	glUniform3f(glGetUniformLocation(podstawowy_shader->Out(), "lightPos"), -100, 100, 100);
	if (anim == 3)
		glUniform3f(glGetUniformLocation(podstawowy_shader->Out(), "lightPos"), 0, 0, 700);
	if (anim==4)
		glUniform3f(glGetUniformLocation(podstawowy_shader->Out(), "lightPos"), -400, 50, 50);
	if (anim==NULL)
		glUniform3f(glGetUniformLocation(podstawowy_shader->Out(), "lightPos"), -10, 0, 0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	inne.draw(x, y - 5, z, 0.3, anim,velocity);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();


}
/*
void ball(GLUquadricObj *quadric,double x, double y, double z, int r)
{
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textures[1]);
		glTranslatef(x, y, z);
		gluSphere(quadric, r, 10, 5);
	glPopMatrix();
}
*/


void menuDraw()
{	
	if ((!menuSnd || GAME_OVER == 2) && graSnd == true)
	{
		PlaySound("Pliki/witcher3/LadiesOfTheWoods", nullptr, SND_LOOP | SND_ASYNC);
		menuSnd = true;
		graSnd = false;
	}
	if (up)
	{
		up = 0;
		xs = 0;
	}
	if (down)
	{
		down = 0;
		xs = 1;
	}
	//t³o
	if (xs)
	{
		teksturnik(4,1);
		//opcje

		glBegin(GL_TRIANGLE_STRIP);//podobno wydajniej niz quad
		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2d(0, 0);	glVertex3d(0, 0, 40);
		glTexCoord2d(1, 0); glVertex3d(50, 0, 40);
		glTexCoord2d(0, 1); glVertex3d(0, 25, 40);
		glTexCoord2d(1, 1); glVertex3d(50, 25, 40);
		glEnd();
		//start
		teksturnik(5, 2);
		glBegin(GL_TRIANGLE_STRIP);//podobno wydajniej niz quad
		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2d(0, 0);	glVertex3d(0, 35, 0);
		glTexCoord2d(1, 0); glVertex3d(50, 35, 0);
		glTexCoord2d(0, 1); glVertex3d(0, 60, 0);
		glTexCoord2d(1, 1); glVertex3d(50, 60, 0);
		glEnd();
		//wyjdz

		inne(-18, 0, 20, 2,potworsmall,2);
		inne(70, 0, 20, 2,potworsmall,2);
	}
	else
	{
		teksturnik(4, 1);
		//opcje
		glBegin(GL_TRIANGLE_STRIP);//podobno wydajniej niz quad
		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2d(0, 0);	glVertex3d(0, 0, 0);
		glTexCoord2d(1, 0); glVertex3d(50, 0, 0);
		glTexCoord2d(0, 1); glVertex3d(0, 25, 0);
		glTexCoord2d(1, 1); glVertex3d(50, 25, 0);
		glEnd();
		//start
		teksturnik(5, 2);
		glBegin(GL_TRIANGLE_STRIP);//podobno wydajniej niz quad
		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2d(0, 0);	glVertex3d(0, 35, 40);
		glTexCoord2d(1, 0); glVertex3d(50, 35, 40);
		glTexCoord2d(0, 1); glVertex3d(0, 60, 40);
		glTexCoord2d(1, 1); glVertex3d(50, 60, 40);
		glEnd();
		inne(-18, 35, 0, 2,potworsmall,2);
		inne(70, 35, 0, 2,potworsmall,2);
	}
}
void przedzDraw(int x,int y,int z)
{
	glPushMatrix();
	glTranslatef(x, y, 0);
	if (z == 0)
	{
		glTranslatef(0, 1.5, 0);
		glScalef(0.5f, 0.5f, 1.0f);
	}
	glBegin(GL_TRIANGLE_STRIP);//podobno wydajniej niz quad
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2d(0, 0);	glVertex3d(0, -1, 42);
	glTexCoord2d(1, 0); glVertex3d(5, -1, 42);
	glTexCoord2d(0, 1); glVertex3d(0, 6, 42);
	glTexCoord2d(1, 1); glVertex3d(5, 6, 42);
	glEnd();
	glPopMatrix();
}

void WypiszWymaluj(GLfloat x, GLfloat y, GLfloat z, string yes)
{
	glPushMatrix();
	glTranslatef(x,y,z);
	glScalef(0.02f, 0.02f, 0.02f);
	int i = 0;
	while (yes[i])
	{
		glTranslated(1, 0,0);
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, yes[i]);
		i++;
	}
	glPopMatrix();
}

void opcjeDraw()
{
	if (keys[VK_BACK])
		Restart();
	static int i = 4;
	if (down && (i > 0))
	{
		down = 0;
		--i;
		selectOpt[i+1] = 0;
		selectOpt[i] = 25;
	}
	
	if (up&&(i<4))
	{
		up = 0;
		++i;
		selectOpt[i-1] = 0;
		selectOpt[i] = 25;
	}
	if (lefty && i!=4 && opcje[i]>0)
	{
		opcje[i] -= 0.1;
	}
	if (righty && i != 4 && opcje[i]<8)
	{
		opcje[i] += 0.1;
	}
	static float r = 0.0;
	glPushMatrix();
	glTranslatef(50, -10, 0);

	WypiszWymaluj(0, 62, 40, "'Backspace' - restart");
	WypiszWymaluj(0, 58, 40, "'P' - odblokuj mysz");
	WypiszWymaluj(0, 52, 40,"shininess");
	WypiszWymaluj(0, 22, 40, "diffuse");
	WypiszWymaluj(0, 37, 40, "specular");
	WypiszWymaluj(0, 7, 40, "ambient");

	teksturnik(27, 28);
	glBegin(GL_TRIANGLE_STRIP);//BACK BUTTON
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2d(0, 0);	glVertex3d(-5, -5, 39);
	glTexCoord2d(1, 0); glVertex3d(55, -5, 39);
	glTexCoord2d(0, 1); glVertex3d(-5, 85,39);
	glTexCoord2d(1, 1); glVertex3d(55, 85, 39);
	glEnd();

	teksturnik(6,8);//suwak

	przedzDraw(opcje[0] * 5, 0, selectOpt[0]);
	przedzDraw(opcje[1] * 5, 15, selectOpt[1]);
	przedzDraw(opcje[2] * 5, 30, selectOpt[2]);
	przedzDraw(opcje[3] * 5, 45, selectOpt[3]);

	teksturnik(3, 0);//opcje

	glBegin(GL_TRIANGLE_STRIP);//BACK BUTTON
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2d(0, 0);	glVertex3d(0, 65, 40 );
	glTexCoord2d(1, 0); glVertex3d(50, 65, 40);
	glTexCoord2d(0, 1); glVertex3d(0, 80, 40 );
	glTexCoord2d(1, 1); glVertex3d(50, 80, 40);
	glEnd();

	teksturnik(7, 9);//pasek

	glBegin(GL_TRIANGLE_STRIP);//podobno wydajniej niz quad
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2d(0, 0);	glVertex3d(0, 0, 40);
	glTexCoord2d(1, 0); glVertex3d(50, 0, 40);
	glTexCoord2d(0, 1); glVertex3d(0, 5, 40);
	glTexCoord2d(1, 1); glVertex3d(50, 5, 40);
	glEnd();
	
	glBegin(GL_TRIANGLE_STRIP);//podobno wydajniej niz quad
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2d(0, 0);	glVertex3d(0, 15, 40);
	glTexCoord2d(1, 0); glVertex3d(50, 15, 40);
	glTexCoord2d(0, 1); glVertex3d(0, 20, 40);
	glTexCoord2d(1, 1); glVertex3d(50, 20, 40);
	glEnd();
	
	glBegin(GL_TRIANGLE_STRIP);//podobno wydajniej niz quad
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2d(0, 0);	glVertex3d(0, 30, 40);
	glTexCoord2d(1, 0); glVertex3d(50, 30, 40);
	glTexCoord2d(0, 1); glVertex3d(0, 35, 40);
	glTexCoord2d(1, 1); glVertex3d(50, 35, 40);
	glEnd();
	
	glBegin(GL_TRIANGLE_STRIP);//podobno wydajniej niz quad
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2d(0, 0);	glVertex3d(0, 45, 40);
	glTexCoord2d(1, 0); glVertex3d(50, 45, 40);
	glTexCoord2d(0, 1); glVertex3d(0, 50, 40);
	glTexCoord2d(1, 1); glVertex3d(50, 50, 40);
	glEnd();
	glPopMatrix();
	glUniform3f(glGetUniformLocation(podstawowy_shader->Out(), "lightPos"),80 * sin(r += 0.05)+80, 70, 85);
	
	glTranslated(30, 0, 0);
	glPushMatrix();
	glScaled(0.5, 0.5, 0.5);
	gracz(0, 0, 0, 0);
	glPopMatrix();
	static double kont = 90.0;
	glTranslated(-150, -100, -700);

	glPushMatrix();
	glRotatef(kont, 0, 1, 0);
	inne(0, 0, 0, 3, ziemia,3);
	glPopMatrix();
	kont += 0.01;
}

void menu()
{
	int s = enter;
	if (!s)
		menuDraw();
	if(s)
	{
		if (!xs)
			plansza();
		if (xs)
			opcjeDraw();
	}
}

int mapa[][26] = 
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2		//0
, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0		//1
, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0		//2
, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0		//3
, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0		//4
, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0		//5
, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0		//6
, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0		//7
, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0		//8
, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0		//9
, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0		//10
, 0, 1, 0, 0, 2, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0		//11
, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0		//12
, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0		//13
, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0		//14
, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0		//15
, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0		//16
, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0		//17
, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0		//18
, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };	//19



void mapBlok()
{
	glPushMatrix();
	glBegin(GL_TRIANGLE_STRIP);//podobno wydajniej niz quad
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2d(0, 0);	glVertex3d(0, -10000, 100);
	glTexCoord2d(1, 0); glVertex3d(0, 0, 100);
	glTexCoord2d(0, 1); glVertex3d(100, -10000, 100);
	glTexCoord2d(1, 1); glVertex3d(100, 0, 100);

	glTexCoord2d(1, 0); glVertex3d(100, -10000, 0);
	glTexCoord2d(0, 0); glVertex3d(100,0, 0);

	glTexCoord2d(1, 1); glVertex3d(0, -10000, 0);
	glTexCoord2d(0, 1); glVertex3d(0, 0, 0);

	glTexCoord2d(1, 0); glVertex3d(0, -10000, 100);
	glTexCoord2d(1, 1); glVertex3d(0, 0, 100);
	glEnd();
	
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2d(0, 0);	glVertex3d(0, 0, 100);
	glTexCoord2d(0, 1); glVertex3d(100, 0, 100);
	glTexCoord2d(1, 0); glVertex3d(0, 0, 0);
	glTexCoord2d(1, 1); glVertex3d(100, 0, 0);
	glEnd();
	glPopMatrix();
}

bool detektorKolizji(int z, int x)
{
	z = z / 100;
	x = x / 100;

	x = ceil(x);//zaokragla w gore
	z = ceil(z);

	if (z > 19 || x > 25)
		return false;
	if (mapa[z][x] == 1)
		return true;
	return false;
}


void enemyAI(double& xE,double& zE)
{
	glTranslated(xE, 0, zE);	
	glPushMatrix();
	zE += 5* cos(kontE / 180 * 3.1415926);
	xE += 5*sin(kontE/180*3.1415926);
	if (!detektorKolizji(ceil(zE), ceil(xE)))
	{
		zE -= 5*cos(kontE / 180 * 3.1415926);
		xE -= 5 * sin(kontE / 180 * 3.1415926);
		double xxE = xE + 100 * sin((kontE + 90) / 180 * 3.1415926);
		double zzE = zE + 100 * cos((kontE + 90) / 180 * 3.1415926);
		if (!detektorKolizji(ceil(zzE), ceil(xxE)))
		{
			xxE = xE + 99 * sin((kontE - 90) / 180 * 3.1415926);
			zzE = zE + 99 * cos((kontE - 90) / 180 * 3.1415926);
			if (detektorKolizji(ceil(zzE), ceil(xxE)))
				kontE = kontE - 90;
		}
		else
			kontE = kontE + 90;
	}
	glRotated(kontE, 0, 1, 0);
	inne(0,0,0,5,enemy,4);
	glPopMatrix();
	
}

char litery[8] = {'Q','W','E','R','A','S','D','F'};


void speedUp(int rnd)
{
	
	if (tajm >= -2)
	{
		random = 0;
		speed = 3;
	}
	if (keys[litery[rnd]])
	{
		tajm = 0;
		random = 0;
		speed++;
	}
	glPushMatrix();
	glUseProgramObjectARB(0);
	glTranslated(20, 50, 0);
	teksturnik(rnd + 19, 0);
	glBegin(GL_TRIANGLE_STRIP);//BACK BUTTON
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2d(0, 0);	glVertex3d(-5, -5, 0 );
	glTexCoord2d(1, 0); glVertex3d(5, -5, 0);
	glTexCoord2d(0, 1); glVertex3d(-5, 5, 0 );
	glTexCoord2d(1, 1); glVertex3d(5, 5, 0);
	glEnd();
	podstawowy_shader->Use();
	glPopMatrix();
}

void winner()
{
	if (graSnd)
	{
		PlaySound("Pliki/witcher3/LadiesOfTheWoods", NULL, SND_LOOP | SND_ASYNC);
		graSnd = 0;
		menuSnd = 1;
	}
	glPushMatrix();
	teksturnik(27, 28);
	glBegin(GL_TRIANGLE_STRIP);//BACK BUTTON
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2d(0, 0);	glVertex3d(-80, 60, -39);
	glTexCoord2d(1, 0); glVertex3d(-20, 60, -39);
	glTexCoord2d(0, 1); glVertex3d(-80, 80, -39);
	glTexCoord2d(1, 1); glVertex3d(-20, 80, -39);
	glEnd();
	glTranslated(-75, 68, -38);
	glScalef(3, 3, 3);
	WypiszWymaluj(0, 0, 0, "Wygrana!");
	glPopMatrix();
	static double kont = 90;
	glRotated(90, 0, 1, 0);
	glPushMatrix();
	glScaled(10, 1, 10);
	teksturnik(16, 17);
	glUniform3f(glGetUniformLocation(podstawowy_shader->Out(), "lightPos"), 0, 10, 0);
	mapBlok();
	glPopMatrix();
	glTranslated(50, 0, 50);
	glPushMatrix();
	glRotated(240, 0, 1, 0);
	gracz(0, 0, 0, 0);
	inne(50, 0, 0, 2, potworsmall, 2);
	glTranslated(-400, 100, -1500);
	glRotated(kont, 0, 1, 0);
	inne(0, 0, 0, 3, ziemia, 3);
	glPopMatrix();
	
	glPushMatrix();
	glTranslated(80, 0, -20);
	glRotated(0, 0, 1, 0);
	inne(0, 0, 0, 4, potworbig, 2);
	glPopMatrix();
	kont += 0.01;
}
void plansza()
{
	if (keys[VK_BACK])
		Restart();
	if (((x > 100 && x < 200 && z>300 && z < 450) || GAME_OVER == 2)&&GAME_OVER!=1)
	{
		GAME_OVER = 2;
		winner();
	}
	else
	{
		if (random == 0)
		{
			tajm = 0;
			random = rand() % 100 + 200;
			randomNum = rand() % 8;
		}
		if (tajm >= random)	tajm = -50 * 3 / speed;
		if (tajm < 0)	speedUp(randomNum);

		if (!graSnd)
		{
			PlaySound("Pliki/witcher3/HuntOrBeHunted", NULL, SND_LOOP | SND_ASYNC);
			menuSnd = false;
			graSnd = true;
		}

		bool animka = 0;
		
		if (lefty)
			alpha -= speed;
		if (righty)
			alpha += speed;
		
		if (upty)
		{
			
			animka = 1;
			z -= speed*cos(alpha / 180 * 3.1415926);
			x += speed*sin(alpha / 180 * 3.1415926);

			if (!detektorKolizji(ceil(z), ceil(x)))
			{
				animka = 0;
				z += speed*cos(alpha / 180 * 3.1415926);
				x -= speed*sin(alpha / 180 * 3.1415926);
			}
		}
		


		glPushMatrix();
		glRotated(180, 0, 1, 0);
		glScaled(0.5, 0.5, 0.5);
		gracz(0, 5, 0, animka);
		glPopMatrix();

		glRotated(alpha, 0, 1, 0);  //obracam i przesuwam mape, a nie gracza
		glTranslated(-x, 0, -z);

		glUseProgramObjectARB(0);
		glPushMatrix();
		glTranslated(-1, 35, 0);
		particless.rysuj(x,z,animka);
		glTranslated(2, 0, 0);
		particless.rysuj(x,z,animka);
		glPopMatrix();
		podstawowy_shader->Use();
		glPushMatrix();
		teksturnik(16, 17);
		for (int i = 0; i < 20; i++)
		{
			
			for (int j = 0; j < 26; j++)
			{
				glUniform3f(glGetUniformLocation(podstawowy_shader->Out(), "lightPos"), 50, 80, -50);
				teksturnik(16, 17);
				if (mapa[i][j] == 2)
				{
					glTranslated(0, 300, 0);
					inne(0, 0, 0, 4, potworbig, 1);
					mapBlok();
					glTranslated(0, -300, 0);
					teksturnik(16, 17);
				}
				if (mapa[i][j] == 1)
					mapBlok();
				glTranslatef(100.0f, 0, 0);
			}
			glTranslatef(-2600, 0, 100.0f);
		}
		glTranslatef(0, 0, -2000);
		if (GAME_OVER == 0)
			enemyAI(xE, zE);
		glPopMatrix();

		glTranslated(150, 70, 350);
		glPushMatrix();
		glScaled(15, 15, 15);
		if (GAME_OVER == 0)
		{
			inne(0, 0, 0, NULL, sgup, 0);
			if (xE > 100 && xE < 200 && zE>300 && zE < 450)
				GAME_OVER = 1;
		}
		else
			inne(0, 0, 0, NULL, sgdown, 0);
		glPopMatrix();
	}
}