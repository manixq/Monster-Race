#ifndef SHADER_H_
#define SHADER_H_
#define _CRT_SECURE_NO_WARNINGS
#include "GLEW/glew.h"

class Shader
{
public:
	Shader(char* v,char* f);
	~Shader();
	char *textFileRead(char *fn);
	GLuint Out();
	void Use();
private:
	GLuint vertex_shader_;
	GLuint fragment_shader_;
	GLuint program_;
};
#endif//SHADER_H_
