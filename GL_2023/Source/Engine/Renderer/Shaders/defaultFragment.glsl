#version 330 core

in vec4 worldPosition;
in vec2 UV;
out vec4 color;


//uniform vec4 u_Color;
uniform mat4 F_ProjectionMatrix;
uniform mat4 F_ViewMatrix;
uniform mat4 F_ModelMatrix;
uniform sampler2D Texture_0; //albedo 
uniform sampler2D Texture_1; //normal 
uniform sampler2D Texture_2; //placeholders
uniform sampler2D Texture_3;

void main()
{
    
   
  //  gl_FragColor = vec4(sin(worldPosition.x),sin(worldPosition.y),sin(worldPosition.z),1.0);
  vec4 colorFromTexture = texture(Texture_0,UV);
  color = colorFromTexture;
  if(colorFromTexture == vec4(0,0,0,1) || colorFromTexture == vec4(0,0,0,0))
    gl_FragColor = vec4(0.5,0.5,0.5,1);
   else
   gl_FragColor = colorFromTexture;
 }