#version 330 core
out vec4 color;
in vec4 worldPosition;
//uniform vec4 u_Color;
uniform mat4 F_ProjectionMatrix;
uniform mat4 F_ViewMatrix;
uniform mat4 F_ModelMatrix;

void main()
{
    
   
    gl_FragColor = vec4(sin(worldPosition.x),sin(worldPosition.y),sin(worldPosition.z),1.0);
 }