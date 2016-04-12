#version 120
varying vec3 position;
varying vec3 normal;
varying vec2 texcoord;
uniform vec3 lightPos;
varying vec3 tangentSurface2light;
varying vec3 tangentSurface2view;

void main()
{
	vec3 lightPos2=vec3(gl_ModelViewMatrix*vec4(lightPos,1.0));
	gl_Position=gl_ModelViewProjectionMatrix*gl_Vertex;
	position=vec3(gl_ModelViewMatrix*gl_Vertex);
	normal=gl_NormalMatrix*gl_Normal;
	texcoord=gl_MultiTexCoord0.xy;
	
	vec3 tangent;
	vec3 v1=cross(gl_Normal,vec3(0.0,0.0,1.0));
	vec3 v2=cross(gl_Normal,vec3(0.0,1.0,0.0));
	if(length(v1)>length(v2))
		tangent=v1;
	else
		tangent=v2;
	vec3 n=normalize(gl_NormalMatrix*gl_Normal);
	vec3 t=normalize(gl_NormalMatrix*tangent);
	vec3 b=cross(n,t);
	mat3 mat=mat3(t.x,b.x,n.x,t.y,b.y,n.y,t.z,b.z,n.z);
	
	vec3 vector=normalize(lightPos2-position);
	tangentSurface2light=mat*vector;
	
	vector=normalize(-position);
	tangentSurface2view=mat*vector;
	
	
}