#version 330 core
out vec4 FragColor;

in vec3 LightingColor;

void main()
{
    vec3 color = vec3(1.0, 0.5, 0.31);
	FragColor = vec4(LightingColor * color, 1.0);
	//FragColor = vec4(LightingColor, 1.0) * texture(texture_diffuse1, TexCoords);
}


