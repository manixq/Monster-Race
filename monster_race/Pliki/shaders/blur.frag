#version 330 core
out vec4 FragColor;
uniform vec2 pixelSize;
uniform sampler2D texture;
uniform sampler2D depth;
varying vec2 texcoord;
uniform bool horizontal;



void main()
{             
	float weight[5] = float[] (126,84,36,9,1);//pascal
    vec2 tex_offset =5.0 / textureSize(texture, 0); // co piaty piksel daje podobny efekt jak dla 4krotnie zwiekszonej ilosci iteracji
    vec3 result = texture2D(texture, texcoord).rgb * weight[0]/400; 
    if(horizontal)
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture2D(texture, texcoord + vec2(tex_offset.x * i, 0.0)).rgb * weight[i]/400;
            result += texture2D(texture, texcoord - vec2(tex_offset.x * i, 0.0)).rgb * weight[i]/400;

        }
    }
    else
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture2D(texture, texcoord + vec2(0.0, tex_offset.y * i)).rgb * weight[i]/400;
            result += texture2D(texture, texcoord - vec2(0.0, tex_offset.y * i)).rgb * weight[i]/400;
        }
    }
    FragColor = vec4(result, 1.0);// vec4(1.0,0.0,0.0,0.5);
}
	



