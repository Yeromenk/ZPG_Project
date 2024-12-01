#version 330

in vec2 fragTexCoord;                   

out vec4 frag_colour;

uniform sampler2D textureUnitID;      

void main() {
   
    vec4 texColor = texture(textureUnitID, fragTexCoord);

    frag_colour = texColor;
}