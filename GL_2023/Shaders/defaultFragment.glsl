#version 330 core
out vec4 color;
//uniform vec4 u_Color;
uniform mat4 F_ProjectionMatrix;
uniform mat4 F_ViewMatrix;
uniform mat4 F_ModelMatrix;

void main()
{
    
   
    gl_FragColor = vec4(0.5,0.5,0.5,1);
 }