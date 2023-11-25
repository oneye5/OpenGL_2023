#version 330 core

in vec4 position;
uniform mat4 V_ProjectionMatrix;
uniform mat4 V_ViewMatrix;
uniform mat4 V_ModelMatrix;

void main()
{
	mat4 finalMat = V_ProjectionMatrix*V_ViewMatrix;
	vec4 newPos = (position* finalMat );
	//newPos +=  position;
	newPos.z = 0.0;
	newPos.w = 1.0;
	gl_Position = newPos;
}