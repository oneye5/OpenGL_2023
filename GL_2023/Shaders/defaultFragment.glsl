#version 330 core
out vec4 color;
uniform vec4 u_Color;


void main()
{
   // Use a seed value (you can use any value here)
    float seed = 123.0;

   
    gl_FragColor = u_Color;
 }