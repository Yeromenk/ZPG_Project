#version 330

in vec2 fragTexCoord;                   // UV координаты из вершинного шейдера

out vec4 frag_colour;

uniform sampler2D textureUnitID;        // Текстура

void main() {
    // Выборка цвета из текстуры по UV координатам
    vec4 texColor = texture(textureUnitID, fragTexCoord);

    // Использование цвета текстуры для фрагмента
    frag_colour = texColor;
}