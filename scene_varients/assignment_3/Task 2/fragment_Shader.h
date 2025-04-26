#version 330 core

out vec4 FragColor;

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
};

in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D myTexture;
uniform float kc;
uniform float kl;
uniform float kq;

uniform Light light;

void main(){
    // Diffuse light calculation
    vec3 lightPos = normalize(light.position - vec3(TexCoord, 0.0));
    float distance = length(light.position - vec3(TexCoord, 0.0));
    float attenuation = 1.0 / (kc + kl * distance + kq * distance * distance);
    float diffuse = max(0.0, dot(Normal, lightPos));

    // Texture sampling
    vec3 textureColor = texture(myTexture, TexCoord).rgb;

    // Final result
    vec3 result = light.ambient * textureColor + light.diffuse * textureColor * diffuse * attenuation;

    FragColor = vec4(result, 1.0);
}
