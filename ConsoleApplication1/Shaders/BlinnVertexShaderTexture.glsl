#version 400

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;
layout(location = 2) in vec2 in_TexCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

out vec3 ex_worldPosition;
out vec3 ex_worldNormal;
out vec2 ex_TexCoord;

void main(void) {
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0f);
    ex_worldPosition = vec3(modelMatrix * vec4(in_Position, 1.0f));
    ex_worldNormal = normalMatrix * in_Normal;
    ex_TexCoord = in_TexCoord;
}