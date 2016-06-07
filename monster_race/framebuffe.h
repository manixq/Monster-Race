#ifndef  FRAMEBUFFER_H_
#define FRAMEBUFFER_H_
#include "GLEW/glew.h"

class Framebuffer
{
public:
	Framebuffer(int w, int h);
	Framebuffer(int w, int h, int x);
	~Framebuffer();
	GLuint OutColor();
 GLuint OutDepth();
	GLuint OutName();
	GLuint* OutNamePong();
	GLuint* OutColorPong();
private:
	GLuint framebuffer_name;
	GLuint colorbuffer;
	GLuint depthrenderbuffer;
	GLuint *pingpongFBO;
	GLuint *pingpongBuffer;
};

#endif
