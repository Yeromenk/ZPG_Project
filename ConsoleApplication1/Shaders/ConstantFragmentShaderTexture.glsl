#version 400
#define MAX_LIGHTS 4

in vec3 ex_worldPosition;
in vec3 ex_worldNormal;
in vec2 ex_TexCoord;

out vec4 out_Color;

struct Light {
    int type;  
    vec4 position;  
    vec4 direction;  
    vec4 diffuse;  
    float attenuation;  
    float cutoff;  
};

struct Material {
    vec3 ambient;
    vec3 diffuse;
};

uniform Light lights[MAX_LIGHTS];
uniform int numberOfLights;
uniform vec3 viewPos;
uniform Material material;
uniform sampler2D textureUnitID;

void main(void) {
    vec3 ambient = material.ambient;
    vec3 texColor = texture(textureUnitID, ex_TexCoord).rgb;
    out_Color = vec4(ambient * texColor, 1.0);
}