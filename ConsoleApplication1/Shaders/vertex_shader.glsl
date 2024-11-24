#version 330

layout(location=0) in vec3 vp;          // Позиция вершины
layout(location=1) in vec3 normal;      // Нормаль вершины
layout(location=2) in vec2 texCoord;    // UV координаты

out vec3 fragNormal;                    // Нормаль для фрагментного шейдера
out vec2 fragTexCoord;                  // UV координаты для фрагментного шейдера

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);
    fragNormal = normal;
    fragTexCoord = texCoord;            // Передача UV координат во фрагментный шейдер
}