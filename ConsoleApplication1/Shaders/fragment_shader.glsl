#version 330

in vec2 fragTexCoord;                   // UV ���������� �� ���������� �������

out vec4 frag_colour;

uniform sampler2D textureUnitID;        // ��������

void main() {
    // ������� ����� �� �������� �� UV �����������
    vec4 texColor = texture(textureUnitID, fragTexCoord);

    // ������������� ����� �������� ��� ���������
    frag_colour = texColor;
}