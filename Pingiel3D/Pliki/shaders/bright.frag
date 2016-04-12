#version 330 core
layout (location = 1) out vec4 FragColor;
layout (location = 0) out vec4 BrightColor;
uniform sampler2D texture;
uniform vec2 pixelSize;
varying vec2 texcoord;

void main()
{            
	vec2 pos=gl_FragCoord.xy*pixelSize;
    vec4 result=texture2D(texture,pos);
	FragColor = result;//vec4(1.0,0.0,0.0,0.5);
   
    float brightness = dot(FragColor.rgb, vec3(1,1,1));
	float particles = dot(FragColor.rgb, vec3(1,1,0));
    if(brightness == 3 || particles > 0.9)
        BrightColor = vec4(FragColor.rgb, 1.0);
}