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

#version 330 core

out vec4 FragColor;

struct Light {
    vec3 direction;
    vec3 diffuse;
};

in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D myTexture;
uniform float kc;
uniform float kl;
uniform float kq;
uniform float cutoff;
uniform vec3 ambient;
uniform vec3 light_position;

uniform Light light[3];

void main(){
    // Texture sampling
    vec3 textureColor = texture(myTexture, TexCoord).rgb;
    
    // Initialize result color
    vec3 result = vec3(0.0);

    for (int i = 0; i < 3; i++){
        vec3 lightDir = normalize(light[i].direction);
        
        float theta = dot(lightDir, normalize(-light[i].direction));
        
        // check if lighting is inside the spotlight cone
        if (theta > cutoff){
            float distance = length(light_position - vec3(TexCoord, 0.0));
            float attenuation = 1.0 / (kc + kl * distance + kq * distance * distance);
            float diffuse = max(0.0, dot(Normal, lightDir));

            // Final result
            result += ambient * textureColor + light[i].diffuse * textureColor * diffuse * attenuation;
        }
        
        else{
            // else, use ambient light so scene isn't completely dark outside the spotlight.
            result += ambient * textureColor;
        }
    }
    
    FragColor = vec4(result, 1.0);
}
