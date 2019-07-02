#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 LightingColor;

uniform sampler2D texture_diffuse1;

void main()
{
   //FragColor = vec4(LightingColor * objectColor, 1.0);
   FragColor = vec4(LightingColor, 1.0) * texture(texture_diffuse1, TexCoords);
}


