#include "monster_race.h"
//#include "md5load.h"
#include <String>

Shader* podstawowy_shader;
Shader* bloom;
Shader* blur_shader;
Shader* bright_shader;
Shader* blend_shader;
md5load md5object;
md5load ziemia;
md5load potworsmall;
md5load potworbig;
md5load enemy;
md5load sgup;
md5load sgdown;
md5load skateboard;
bool BLOOM = true;
bool LIGHTS = true;
bool keys[256];
GLuint texture[29];
static GLUquadricObj *quadric=nullptr;
double dTime = 0;
//_int64 iTimeStart;
//_int64 iTimeEnd;
//_int64 iFrequency;
int width;
int height;
bool mozna=0;
int DrawGLScene();
float xrota=0.0;
float yrota=0.0,ze=-300;
double tajm = 0;
double cur_frame = 0;
double nex_frame = 1;
POINT pkt;
POINT pktOld;
IDirectSoundBuffer *DSB;
GLfloat loc;
GLint  diffuseTextureId, normalTextureId, heightTextureId, diffuseTextureUniform, normalTextureUniform, heightTextureUniform;
/*
0-ambient
1-diffuse
2-specular
3-shininess
*/
float opcje[4] = {2.0,3.5,2.0,1.8};
GLuint v,v2,f3, f, f2, p,p2,p3;
float lpos[4] = { 1.0, 0.0, 1.0, 0.0 };
int enter = 0;
int up = 0;
int down = 0;
int lefty = 0;
int righty = 0;
int upty = 0;

AUX_RGBImageRec *LoadBMP(std::string Filename)//teksturki
{
	FILE *File;
	File = fopen(Filename.c_str(), "r");//sprawdz czy istnieje
	if (File)
	{
		fclose(File);
		return auxDIBImageLoad(Filename.c_str());
	}
	return nullptr;
}

int LoadGLTexture()
{
	int Status = FALSE;
	std::string tab[29] =
	{ "pliki/guziole/wrocN.bmp", "pliki/guziole/opcjeN.bmp", "pliki/guziole/startN.bmp", "pliki/guziole/wroc.bmp", "pliki/guziole/opcje.bmp",
		"pliki/guziole/start.bmp", "pliki/guziole/suwak.bmp", "pliki/guziole/pasek.bmp", "pliki/guziole/suwakN.bmp", "pliki/guziole/pasekN.bmp",
		"pliki/skyboxes/bottom.bmp", "pliki/skyboxes/left.bmp", "pliki/skyboxes/middle.bmp", "pliki/skyboxes/front.bmp", "pliki/skyboxes/right.bmp",
		"pliki/skyboxes/top.bmp","pliki/textures/ground.bmp","pliki/textures/groundN.bmp","pliki/skyboxes/stars.bmp","pliki/textures/literaq.bmp",
		"pliki/textures/literaw.bmp", "pliki/textures/literae.bmp", "pliki/textures/literar.bmp", "pliki/textures/literaa.bmp", "pliki/textures/literas.bmp",
		"pliki/textures/literad.bmp", "pliki/textures/literaf.bmp", "pliki/textures/back.bmp","pliki/textures/backN.bmp"  };
	AUX_RGBImageRec *TextureImage[29];//rezerwujemy miejsce na teksture
	memset(TextureImage, 0, sizeof(void*) * 1); //ustawiamy na 0
	for (int i = 0; i < 29; i++)
	{
		if ((TextureImage[i] = LoadBMP(tab[i])))
		{
			Status = true;
			glGenTextures(1, &texture[i]);
			glBindTexture(GL_TEXTURE_2D, texture[i]);
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, TextureImage[i]->sizeX, TextureImage[i]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[i]->data);//przypisawanie teksturze danych obrazowych
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//filtrowanie liniowe
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		}
		if (TextureImage[i])
		{
			if (TextureImage[i]->data)
			{
				free(TextureImage[i]->data);//zwolnij pamiec tekstury obrazu
			}
			free(TextureImage[i]);//zwolnij pamiec struktury obrazu
		}
	}
	return Status;
}




genCzastek particless;
Framebuffer* FBO;
Framebuffer* pingpong;
int InitGL(GLvoid)                              // All Setup For OpenGL Goes Here
{	
	srand(time(nullptr));

	if (!LoadGLTexture())                          // Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;                           // If Texture Didn't Load Return FALSE ( NEW )
	}
	
	glewInit(); //bez tego shadery nie rusz¹!
	glEnable(GL_TEXTURE_2D);                        // Enable Texture Mapping ( NEW )
	glShadeModel(GL_SMOOTH);                        // Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);                   // Black Background
	glClearDepth(1.0f);                         // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);                        // Enables Depth Testing
	glDepthFunc(GL_LEQUAL);                         // The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // Really Nice Perspective Calculations

	FBO = new Framebuffer(width,height);
	pingpong = new Framebuffer(width, height,2);

	const char** animacje = new const char*[7];
	animacje[0] = "Pliki/cyberdemon/idle.md5anim";
	animacje[1] = "Pliki/cyberdemon/walk3fix.md5anim";
	animacje[2] = "Pliki/sabaoth/move_start.md5anim";
	animacje[3] = "Pliki/ziemia/ziemia.md5anim";
	animacje[4] = "Pliki/maledict/inhell.md5anim";
	animacje[5] = "Pliki/vagary/walk3fix.md5anim";
	animacje[6] = "Pliki/maledict/inhell2.md5anim";

	ziemia.init("Pliki/ziemia/ziemia.md5mesh", animacje);
	potworbig.init("Pliki/maledict/maledict.md5mesh", animacje);
	potworsmall.init("Pliki/sabaoth/sabaoth.md5mesh", animacje);
	md5object.init("Pliki/cyberdemon/cyberdemonfix.md5mesh", animacje);
	sgup.init("Pliki/stargate/sg1.md5mesh",animacje);
	sgdown.init("Pliki/stargate/sg1empty.md5mesh",animacje);
	enemy.init("Pliki/vagary/vagary.md5mesh", animacje);
 skateboard.init("Pliki/skateboard/skateboard.md5mesh",animacje);

	podstawowy_shader = new Shader(
		"pliki/shaders/podstawowy.vert",
		"pliki/shaders/podstawowy.frag");
	blur_shader = new Shader(
		"pliki/shaders/blur.vert",
		"pliki/shaders/blur.frag");
	bright_shader = new Shader(
		"pliki/shaders/blur.vert",
		"pliki/shaders/bright.frag");
	blend_shader = new Shader(
		"pliki/shaders/blur.vert",
		"pliki/shaders/blend.frag");
	
	return TRUE;                                // Initialization Went OK
}


int iwidth = GetSystemMetrics(16);
int iheight = GetSystemMetrics(17);

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)
{
	if (height == 0) height = 1;//pamietaj cholero nie dziel przez zero

	glViewport(0, 0, width, height);//resetowanie aktualnego widoku

	glMatrixMode(GL_PROJECTION);//ust. macierzy projekcji
	glLoadIdentity();//reset m. proj.

	gluPerspective(20.0f,static_cast<GLfloat>(width) / static_cast<GLfloat>(height), 0.1f, 10000.0f);

	glMatrixMode(GL_MODELVIEW);//macierz modelu
	glLoadIdentity();//reset macierzy modelu
}

HDC hDC = nullptr;//kontekst urzadzenia

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{	
	case WM_MOUSEWHEEL:
		if (HIWORD(wParam) > GET_WHEEL_DELTA_WPARAM(wParam))
			ze += 50;
		else ze -= 50;
		break;
	case WM_CREATE:
		SetCursorPos(GetSystemMetrics(16) / 2, GetSystemMetrics(17) / 2);
		GetCursorPos(&pktOld);
		xrota = 0.0;
		yrota = 0.0;
		tajm = 0;
		cur_frame = 0;
		nex_frame = 1;
		RECT rect;
		if (GetWindowRect(hwnd, &rect))
		{
			 width = rect.right - rect.left;
			 height = rect.bottom - rect.top;
		}
		break;
  
	case WM_TIMER:
  
		switch (wParam)
		{
		case ID_TIMER_REDRAW://wymusznie odmalowania okna
			
			SwapBuffers(hDC);
			if (mozna)
			{
				GetCursorPos(&pkt);
				SetCursorPos(GetSystemMetrics(16) / 2, GetSystemMetrics(17) / 2);
				xrota = float(pkt.x - pktOld.x) + xrota;
				yrota = float(pkt.y - pktOld.y) + yrota;
			}
			else
			{
				xrota = 0.0;
				yrota = 0.0;
			}
			nex_frame++;
			cur_frame++;
			tajm++;//
   
			if (keys[VK_UP])upty = 1;
				else upty = 0;
			if (keys[VK_LEFT])lefty = 1;
				else lefty = 0;
			if (keys[VK_RIGHT])righty = 1;
			else righty = 0;
		
   break;
		case ID_TIMER_REDRAW2:
			DrawGLScene();
			break;
		}
		
		break;
	case WM_PAINT:
		break;
	case WM_SIZE:
		ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_KEYDOWN:
			keys[wParam] = TRUE;
		if (wParam == VK_ESCAPE)
			PostQuitMessage(1);
  
  if (wParam == 'M')
      GAME_OVER = 2;
		break;
	
	case WM_KEYUP:
		keys[wParam] = FALSE;
		if (wParam == VK_RETURN)		enter = !enter;
  if (wParam == 'B') BLOOM = !BLOOM; 
  if (wParam == 'L') LIGHTS = !LIGHTS;
  if (wParam == 'P') mozna = !mozna;
		if (wParam == VK_UP)	up=1;
		if (wParam == VK_DOWN)		down=1;
		break;
	case WM_DESTROY:
		
		delete pingpong;
		delete FBO;
		delete blend_shader;
		delete blur_shader;
		delete podstawowy_shader;
		delete bright_shader;
		KillTimer(hwnd, ID_TIMER_REDRAW);
		md5object.cleanup();
		enemy.cleanup();
		ziemia.cleanup();
		sgdown.cleanup();
		sgup.cleanup();
		potworbig.cleanup();
		potworsmall.cleanup();
  skateboard.cleanup();
		PostQuitMessage(1);		
		atexit(cleanup);
		break;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}


int DrawGLScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//wyzerowanie bufora kolorow i glebokosci	
	glBindFramebuffer(GL_FRAMEBUFFER, FBO->OutName());//tu zaczynam FBO
	glLoadIdentity();

	//unsetShader();

	float proba = yrota / (180 * 90);

	glPushMatrix();
	glUseProgramObjectARB(0);
	glTranslated(0, -2, 0);
	glRotatef(xrota / 180, 0, 1 - proba, proba);
	glRotatef(yrota / 180, 1, 0, 0);

	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	skyBox();
///--------------------------------------->	glUseProgramObjectARB(p);
 if(LIGHTS)
 	podstawowy_shader->Use();
	//system("pause");
	glPopMatrix();
	glTranslatef(-25, -30, ze);
	glRotatef(xrota / 180, 0, 1 - proba, proba);
	glRotatef(yrota / 180, 1, 0, 0);
	static float r = 0;
	glUniform3f(glGetUniformLocation(podstawowy_shader->Out(), "lightPos"), 40 + 50 * sin(r += 0.01), 50, 150);
	glUniform3f(glGetUniformLocation(podstawowy_shader->Out(), "mambient"), opcje[0], opcje[0], opcje[0]);
	glUniform3f(glGetUniformLocation(podstawowy_shader->Out(), "mdiffuse"), opcje[1], opcje[1], opcje[1]);
	glUniform3f(glGetUniformLocation(podstawowy_shader->Out(), "mspecular"), opcje[2], opcje[2], opcje[2]);
	glUniform3f(glGetUniformLocation(podstawowy_shader->Out(), "lambient"), opcje[0], opcje[0], opcje[0]);
	glUniform3f(glGetUniformLocation(podstawowy_shader->Out(), "ldiffuse"), opcje[1] * 2, opcje[1] * 2, opcje[1] * 2);
	glUniform3f(glGetUniformLocation(podstawowy_shader->Out(), "lspecular"), opcje[2] * 2, opcje[2] * 2, opcje[2] * 2);
	glUniform1f(glGetUniformLocation(podstawowy_shader->Out(), "shininess"), opcje[3] * 50);
	menu();	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glUseProgramObjectARB(0);
 if (BLOOM)
 {
  glBindFramebuffer(GL_FRAMEBUFFER, pingpong->OutNamePong()[0]);
  bright_shader->Use();
 }
	glActiveTexture(GL_TEXTURE0);
	
	glBindTexture(GL_TEXTURE_2D, FBO->OutColor());
	glUniform1i(glGetUniformLocation(bright_shader->Out(), "texture"), 0);
	glUniform2f(glGetUniformLocation(bright_shader->Out(), "pixelSize"), 1.0 / width, 1.0 / height);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, 0, 1);
	glNormal3f(0.0, 0.0, 1.0);
	glBegin(GL_TRIANGLE_STRIP);//podobno wydajniej niz quad
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2d(0, 0);	glVertex3d(-1.885, -0.965, 2.25);
	glTexCoord2d(1, 0); glVertex3d(1.915, -0.965, 2.25);
	glTexCoord2d(0, 1); glVertex3d(-1.885, 1.035, 2.25);
	glTexCoord2d(1, 1); glVertex3d(1.915, 1.035, 2.25);
	glEnd();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

 if (BLOOM)
 {
  blur_shader->Use();
  GLuint amount = 6;
  GLboolean horizontal = false, first_iteration = true;
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, FBO->OutDepth());
  glUniform1i(glGetUniformLocation(blur_shader->Out(), "depth"), 1);

  for (GLuint i = 0; i < amount; i++)
  {
   glBindFramebuffer(GL_FRAMEBUFFER, pingpong->OutNamePong()[horizontal]);
   glUniform1i(glGetUniformLocation(blur_shader->Out(), "horizontal"), horizontal);
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, first_iteration ? pingpong->OutColorPong()[0] : pingpong->OutColorPong()[!horizontal]);
   glUniform1i(glGetUniformLocation(blur_shader->Out(), "texture"), 0);


   //RENDER HERE
   glLoadIdentity();
   glOrtho(-1, 1, -1, 1, 0, 1);
   glNormal3f(0.0, 0.0, 1.0);
   glBegin(GL_TRIANGLE_STRIP);
   glNormal3f(0.0, 0.0, 1.0);
   glTexCoord2d(0, 0);	glVertex3d(-1.885, -0.965, 2.25);
   glTexCoord2d(1, 0); glVertex3d(1.915, -0.965, 2.25);
   glTexCoord2d(0, 1); glVertex3d(-1.885, 1.035, 2.25);
   glTexCoord2d(1, 1); glVertex3d(1.915, 1.035, 2.25);
   glEnd();
   //ENDRENDERINGUNG
   horizontal = !horizontal;
   if (first_iteration)
    first_iteration = false;
  }
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
 }
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, 0, 1);

 if(BLOOM)
	 blend_shader->Use();


	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, pingpong->OutColorPong()[1]);
 glActiveTexture(GL_TEXTURE0);
 glBindTexture(GL_TEXTURE_2D, FBO->OutColor());
	glUniform1i(glGetUniformLocation(blend_shader->Out(), "scene"), 0);
	glUniform1i(glGetUniformLocation(blend_shader->Out(), "bloomBlur"), 1);
	glNormal3f(0.0, 0.0, 1.0);
	glBegin(GL_TRIANGLE_STRIP);//podobno wydajniej niz quad
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2d(0, 0);	glVertex3d(-1.885, -0.965, 2.25);
	glTexCoord2d(1, 0); glVertex3d(1.915, -0.965, 2.25);
	glTexCoord2d(0, 1); glVertex3d(-1.885, 1.035, 2.25);
	glTexCoord2d(1, 1); glVertex3d(1.915, 1.035, 2.25);
	glEnd();

	return 1;
}
void cleanup()
{
	enemy.cleanup();
	md5object.cleanup();
	ziemia.cleanup();
	potworbig.cleanup();
	potworsmall.cleanup();
	sgup.cleanup();
	sgdown.cleanup();
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW |CS_OWNDC;
	wc.lpfnWndProc = static_cast<WNDPROC>(WndProc);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(PINGIEL_ICON));
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = "Monster";

	if (!RegisterClass(&wc))	
		return false;

	int horizontal = GetSystemMetrics(16);
	int vertical = GetSystemMetrics(17);

	HWND hWnd = CreateWindow(wc.lpszClassName, "MonsterRace", WS_OVERLAPPED | WS_MAXIMIZE | WS_SYSMENU, 0, 0,horizontal, vertical, nullptr, nullptr, hInstance, nullptr);
	if (hWnd == nullptr)
		return false;

	static PIXELFORMATDESCRIPTOR pfd=  //struktura formatu pixeli
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,//numerwersji
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		16,//tryb koloru
		0,0,0,0,0,0,//ignorowane bity koloru
		0,//brak kanalu alpha
		0,//ignorowanie rpzesuniecia
		0,//brak akumulatora
		0,0,0,0,//ignorowane przesuniecie akumulatora
		16,//16bitowy bufor glebokosci
		0,//no stencil buffer
		0,//no auxiliary buffer
		PFD_MAIN_PLANE,//glowna warstwa rysowania
		0,//zarezerwowane
		0,0,0//ignorowanie warstwy maski

	};

	
	HGLRC hRC = nullptr;//kontekst renderowania
	GLuint PixelFormat;//styl pixeli

	if (!((hDC = GetDC(hWnd)))) return 0;//pobranie kontekstu
	if (!((PixelFormat = ChoosePixelFormat(hDC, &pfd))))return 0;//wyszukiwanie formatu pixeli
	if (!SetPixelFormat(hDC, PixelFormat, &pfd)) return 0;//ust. formatu pixeli
	if (!((hRC = wglCreateContext(hDC))))return 0;//pobvranie kontekstu renderowania
	if (!wglMakeCurrent(hDC, hRC))return 0; //uruchomienie kontekstu renderowania

	ShowWindow(hWnd, iCmdShow);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
	ShowCursor(FALSE);



	//-------------------------DZWIEKI-----------------------------------

	//44.1khz 16bit stereo

	WAVEFORMATEX pcmWaveFormat;					//df formatu dzwieku
	pcmWaveFormat.wFormatTag = WAVE_FORMAT_PCM;	//format probek
	pcmWaveFormat.nChannels = 2;				//liczba kanalow
	pcmWaveFormat.nSamplesPerSec = 44100L;		//probkowanie
	pcmWaveFormat.wBitsPerSample = 16;			//ilosc bitow na probke
	pcmWaveFormat.nAvgBytesPerSec = 176400L;		//ilosc bajtow na sekunde
	pcmWaveFormat.nBlockAlign = 4;
	pcmWaveFormat.cbSize = 0;
	/*
	MMRESULT mmResult;
	HWAVEOUT hwo = nullptr;			//uchwyt do interfejsu urzadzenia odtwarzania
	UINT devId;				//ident. urzadzenia

	for (devId = 0; devId < waveOutGetNumDevs(); devId++)
	{
		mmResult = waveOutOpen(&hwo, devId, &pcmWaveFormat, 0, 0, CALLBACK_NULL);
		if (mmResult == MMSYSERR_NOERROR)break;
	}
	if (mmResult != MMSYSERR_NOERROR)
		{
			MessageBox(hWnd, TEXT("brak karty dzwiekowej o wymaganych parametrach"), TEXT("ERROR"), MB_OK);
			return mmResult;
		}
	*/
	IDirectSound8 *DS8;
	DirectSoundCreate8(nullptr, &DS8, nullptr);
	if (DS8 == nullptr)
	{
		MessageBox(nullptr, TEXT("nie mozna utworzyc direktsound"), TEXT("ERROR"), MB_OK);
	}
	if (DS8->SetCooperativeLevel(hWnd, DSSCL_NORMAL) != DS_OK)
		MessageBox(nullptr, TEXT("nie mozna ustawic wymaganego trybu pracy"), TEXT("ERROR"), MB_OK);

	//przygotowanie probek do odtworzenia
	WAVEHDR whdr;
	ZeroMemory(&whdr, sizeof(WAVEHDR));
	whdr.lpData = new char[pcmWaveFormat.nAvgBytesPerSec * 10];	//ilosc bajtwo na sekunde
	whdr.dwBufferLength = pcmWaveFormat.nAvgBytesPerSec * 10;	//razy ilosc sekund
	whdr.dwUser = 0;
	whdr.dwFlags = 0;
	whdr.dwLoops = 0;
	whdr.dwBytesRecorded = 0;
	whdr.lpNext = nullptr;

	//wypelnienei buffora probek probkami sygnalu ao czestoliwosci 880hz
	for (int i = 0; i < whdr.dwBufferLength; i++)
	{
		whdr.lpData[i] = 128 * sin(i*80.0 / static_cast<double>(pcmWaveFormat.nSamplesPerSec)) + 128;
	}
	/*
	waveOutSetVolume(hwo, 0xFFFFFFFF);
	mmResult = waveOutPrepareHeader(hwo, &whdr, sizeof(WAVEHDR));	//wyslanie naglowska
	if (mmResult != MMSYSERR_NOERROR)									//przygotowanie urzadzenia
	{
		MessageBox(hWnd, TEXT("nie mozna zainisjowac karty"), TEXT("ERROR"), MB_OK);
		return mmResult;
	}
	mmResult = waveOutWrite(hwo, &whdr, sizeof(WAVEHDR));	//wyslanie probek do urzadzenia
	if (mmResult != MMSYSERR_NOERROR)
	{
		MessageBox(hWnd, TEXT("nie idzie zaladowac probek"), TEXT("error"), MB_OK);
		return mmResult;
	}
	while ((whdr.dwFlags&WHDR_DONE) != WHDR_DONE)Sleep(100);//czekanie na koniec
	//zamkniecie urzadzenia
	mmResult = waveOutUnprepareHeader(hwo, &whdr, sizeof(WAVEHDR));
	mmResult = waveOutClose(hwo);
	*/
	IDirectSoundBuffer *DSB;
	DSBUFFERDESC DSBD;
	memset(&DSBD, 0, sizeof(DSBUFFERDESC));
	DSBD.dwSize = sizeof(DSBD);
	DSBD.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY;
	DSBD.dwBufferBytes = whdr.dwBufferLength;
	DSBD.lpwfxFormat = &pcmWaveFormat;
	if (DS8->CreateSoundBuffer(&DSBD, &DSB, nullptr) != DS_OK)
	{
		MessageBox(nullptr, TEXT("nie mozna utworzy direktosoundbuffer"), TEXT("ERROR"), MB_OK);
	};
	DSB->SetVolume(0xFFF0);//ustawienie glosnosci
	void *ptr1, *ptr2;
	DWORD l1, l2;
	DSB->Lock(0, whdr.dwBufferLength, &ptr1, &l1, &ptr2, &l2, DSBLOCK_ENTIREBUFFER);
	if (ptr1)memcpy(ptr1, whdr.lpData, l1);
	if (ptr2)memcpy(ptr2, whdr.lpData + l1, l2);

	DSB->Unlock(ptr1, l1, ptr2, l2);
	//DSB->Play(0, 0, 0);
	
	

delete[]whdr.lpData;//usuniecie bufora z pamieci


	//---------------------------------------------------------------------------------------


	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
									// Reset The Display
		MessageBox(nullptr, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}
	BOOL done = false;
	
	SetTimer(hWnd, ID_TIMER_REDRAW, 16, nullptr);
	SetTimer(hWnd, ID_TIMER_REDRAW2, 8, nullptr);
	MSG msg;
	
	while (!done)
	{
		
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))//czy jest zdarzenie do obslugi?
		{
			if (msg.message == WM_QUIT) done = TRUE;
			else
			{
				
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				
			}
		}
		
	}
	
	if (hRC)
	{
		wglMakeCurrent(nullptr, nullptr);//usuw. kontekstu rend.
		wglDeleteContext(hRC);//usuw. kontekstu rend.
	}
	if (hDC && !ReleaseDC(hWnd, hDC)) {}//wyzerowanie kontekstu
	if (hWnd&& !DestroyWindow(hWnd)){}//wyzerowanie uchwytu okienka

	return 0;
}

