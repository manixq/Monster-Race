#include "framebuffe.h"
#include <windows.h>
#include <cstdio>

Framebuffer::Framebuffer(int w, int h) :pingpongFBO(nullptr), pingpongBuffer(nullptr)
{
	
	glGenFramebuffers(1, &framebuffer_name);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_name);
	
		glGenTextures(1, &colorbuffer);
		for (GLuint i = 0; i < 2; i++)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, colorbuffer);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			// attach texture to framebuffer
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 , GL_TEXTURE_2D, colorbuffer, 0);
		}

		// The depth buffer
		glGenRenderbuffers(1, &depthrenderbuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, w, h);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

		GLuint attachments[1] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, attachments);
		glBindTexture(GL_TEXTURE_2D, 0);
	
}

Framebuffer::Framebuffer(int w, int h, int x) :framebuffer_name(0), depthrenderbuffer(0)
{
	pingpongFBO = new GLuint[x];
	pingpongBuffer = new GLuint[x];
	glGenFramebuffers(x, pingpongFBO);
	glGenTextures(x, pingpongBuffer);
	for (GLuint i = 0; i < x; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
		glBindTexture(GL_TEXTURE_2D, pingpongBuffer[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongBuffer[i], 0);
	}
}

Framebuffer::~Framebuffer()
{
	glDeleteFramebuffers(1, &framebuffer_name);
	delete [] pingpongFBO;
	delete [] pingpongBuffer;
	
}

GLuint Framebuffer::OutColor()
{
	
	return colorbuffer;
}

GLuint Framebuffer::OutName()
{
	return framebuffer_name;
}

GLuint* Framebuffer::OutNamePong()
{
	return pingpongFBO;
}

GLuint* Framebuffer::OutColorPong()
{
	return pingpongBuffer;
}
