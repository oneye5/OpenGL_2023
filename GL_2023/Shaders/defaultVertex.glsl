#version 330 core

layout(location = 0) in vec4 position;
//uniform mat4 ProjectionMatrix;
//uniform mat4 ViewMatrix;
//uniform mat4 ModelMatrix;

void main()
{

	gl_Position =  position;
}