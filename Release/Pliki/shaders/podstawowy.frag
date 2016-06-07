#version 120

uniform sampler2D img;
uniform sampler2D normalmap;
varying vec2 texcoord;

varying vec3 position;
varying vec3 normal;

uniform vec3 lightPos;

uniform vec3 mambient;	//gl_FrontMaterial
uniform vec3 mdiffuse;
uniform vec3 mspecular;
uniform float shininess;

uniform vec3 lambient;	//gl_LightSource[0]
uniform vec3 ldiffuse;
uniform vec3 lspecular;
varying vec3 tangentSurface2light;
varying vec3 tangentSurface2view;


void main()
{

	vec3 lightPos2=vec3(gl_ModelViewMatrix*vec4(lightPos,1.0));
	vec3 texcolor=vec3(texture2D(img,texcoord));

	float dist=length(position-lightPos2);
	float att=1.0/(1.0+0.01*dist+0.001*dist*dist);
	vec3 ambient=texcolor*lambient;
	
	vec3 surf2light=normalize(tangentSurface2light);
	vec3 norm=normalize(texture2D(normalmap,texcoord).xyz*2.0-1.0);
	float dcont=max(0.0,dot(norm,surf2light));
	vec3 diffuse=dcont*(texcolor*ldiffuse);
	
	vec3 surf2view=normalize(tangentSurface2view);
	vec3 reflection=reflect(-surf2light,norm);
	
	float scont=pow(max(0.0,dot(surf2view,reflection)),shininess);
	vec3 specular=scont*lspecular*mspecular;
	




	gl_FragColor=vec4((ambient+diffuse+specular)*att,1.0);
	//gl_FragColor=vec4(1.0,0.0,0.0,0.5);
}