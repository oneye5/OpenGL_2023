#version 330 core

in vec4 worldPosition;
in vec2 UV;
out vec4 FragColor;


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
   vec4 textureColor = texture(Texture_0, UV);
    
    // Output the sampled color to FragColor
    FragColor = textureColor;
 }