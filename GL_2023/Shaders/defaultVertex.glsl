#version 330 core

in vec4 position;
uniform mat4 V_ProjectionMatrix;
uniform mat4 V_ViewMatrix;
uniform mat4 V_ModelMatrix;

void main()
{
	mat4 finalMat = V_ProjectionMatrix*V_ViewMatrix*V_ModelMatrix;
	gl_Position = finalMat * position;
}