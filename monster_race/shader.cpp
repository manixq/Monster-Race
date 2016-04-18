#include "shader.h"
#include <cstdlib>
#include <cstdio>

Shader::Shader(char* v,char* f) :
vertex_shader_(glCreateShader(GL_VERTEX_SHADER)),
fragment_shader_(glCreateShader(GL_FRAGMENT_SHADER))
{
	v = textFileRead(v);
	f = textFileRead(f);
	const char* kv = v;
	const char* kf = f;
	glShaderSource(vertex_shader_, 1, &kv, nullptr);
	glShaderSource(fragment_shader_, 1, &kf, nullptr);
	free(v);
	free(f);
	glCompileShader(vertex_shader_);
	glCompileShader(fragment_shader_);
	program_ = glCreateProgram();
	glAttachShader(program_, vertex_shader_);
	glAttachShader(program_, fragment_shader_);
	glLinkProgram(program_);
	glUseProgramObjectARB(0);
}

Shader::~Shader()
{
	glDetachShader(program_, vertex_shader_);
	glDetachShader(program_, fragment_shader_);
	glDeleteShader(vertex_shader_);
	glDeleteShader(fragment_shader_);
	glDeleteProgram(program_);
}

char* Shader::textFileRead(char* fn)
{
	FILE *fp;
	char *content = nullptr;

	int count;

	if (fn != nullptr) {
		fp = fopen(fn, "rt");

		if (fp != nullptr) {

			fseek(fp, 0, SEEK_END);
			count = ftell(fp);
			rewind(fp);

			if (count > 0) {
				content = static_cast<char *>(malloc(sizeof(char) * (count + 1)));
				count = fread(content, sizeof(char), count, fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	return content;
}
GLuint Shader::Out()
{
	return program_;
}
void Shader::Use()
{
	glUseProgramObjectARB(program_);
}
