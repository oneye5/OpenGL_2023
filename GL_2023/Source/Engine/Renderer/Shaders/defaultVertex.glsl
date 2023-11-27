#version 330 core

out vec4 worldPosition;
in vec4 position;
uniform mat4 V_ProjectionMatrix;
uniform mat4 V_ViewMatrix;
uniform mat4 V_ModelMatrix;

void main()
{
	worldPosition = position;

/*
	vec4 newPos = position; 
	newPos.w = 1.0;
	mat4 finalMat = V_ProjectionMatrix*V_ViewMatrix;
	newPos = (newPos* finalMat );
	newPos /= newPos.w;
	newPos.w = 1.0;
	gl_Position = newPos;
	*/
	vec4 newPos = vec4(position.x,position.y,position.z,1.0);
    gl_Position = V_ProjectionMatrix * V_ViewMatrix * newPos;
	
}