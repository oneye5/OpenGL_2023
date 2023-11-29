#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uv;

out vec2 UV;
out vec4 worldPosition;

uniform mat4 V_ProjectionMatrix;
uniform mat4 V_ViewMatrix;
uniform mat4 V_ModelMatrix;

void main() {
    vec4 worldPos = V_ModelMatrix * position;
    worldPosition = worldPos;
    gl_Position = V_ProjectionMatrix * V_ViewMatrix * worldPos;
    UV = vec2( sin(position.x + position.y + position.z),cos(position.x + position.y + position.z) );
}