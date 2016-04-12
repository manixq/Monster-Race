#version 330 core
out vec4 FragColor;
in vec2 texcoord;

uniform sampler2D scene;
uniform sampler2D bloomBlur;


void main()
{             
    vec3 hdrColor = texture2D(scene, texcoord).rgb;      
    vec3 bloomColor = texture2D(bloomBlur, texcoord).rgb;
    hdrColor += bloomColor; 
    FragColor = vec4(hdrColor, 1.0f);
}