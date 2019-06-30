#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 Color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    Color = aColor;

    //lamp with size 10
    gl_PointSize = 10.0;
    //apply transformations to the vertex
	gl_Position = projection * view * model * vec4(aPos, 1.0);
}
