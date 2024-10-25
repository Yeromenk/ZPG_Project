#version 330
in vec3 fragNormal;
out vec4 frag_colour;
void main () {
     vec3 color = fragNormal * 0.5 + 0.5;
     frag_colour = vec4(color, 1.0);
}
