#version 330 core

out vec4 FragColor;

struct Light {
    vec3 direction;
    vec3 diffuse;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D myTexture;
uniform float kc;
uniform float kl;
uniform float kq;
uniform float cutoff;
uniform vec3 ambient;
uniform vec3 lightPos;

uniform Light light[3];

void main(){
    // Texture sampling
    vec3 textureColor = texture(myTexture, TexCoord).rgb;
    
    // Initialize result color
    vec3 result = vec3(0.0f, 0.0f, 0.0f);

    for (int i = 0; i < 3; i++){
        vec3 lightDir = normalize(lightPos - FragPos);
        
        float theta = dot(lightDir, normalize(-light[i].direction));
        
        // check if lighting is inside the spotlight cone
        if (theta > cutoff){
            float distance = length(lightPos - FragPos);
            float attenuation = 1.0 / (kc + kl * distance + kq * distance * distance);
            float diffuse = max(0.0, dot(Normal, lightDir));

            // Final result
            result += ambient * textureColor + light[i].diffuse * textureColor * attenuation * diffuse;
        }
        
        else{
            // else, use ambient light so scene isn't completely dark outside the spotlight.
            result += ambient * textureColor;
        }
    }
    
    FragColor = vec4(result, 1.0);
}
