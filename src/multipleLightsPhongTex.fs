#version 330 core
out vec4 FragColor;

/*
struct Material {
    sampler2D diffuse; //it's probably a bool that indicates if there is or not diffuse effect
    sampler2D specular; //it's probably a bool that indicates if there is or not diffuse effect
    float shininess; //ns
}; 
*/

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define MAX_POINT_LIGHT_NUMBER 100

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform PointLight pointLights[MAX_POINT_LIGHT_NUMBER];
uniform int numberOfPointLights;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform float shininess; //ns

// function prototypes
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, float ka, float kd, float ks);

void main()
{    
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    float ka = 0.01;
    float kd = 0.1;
    float ks = 0.1;
    
    // sum the point lights contribution
    vec3 result = vec3(0.0);
    if(numberOfPointLights == 0){
        result = vec3(1.0, 0.5, 0.31);

    }else{
        for(int i = 0; i < numberOfPointLights; i++){
            result += CalcPointLight(pointLights[i], norm, FragPos, viewDir, ka, ks, kd);    
        }
    }

    
    FragColor = vec4(result, 1.0);
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, float ka, float kd, float ks){
    // L (Light vector)
    vec3 lightDir = normalize(light.position - fragPos);
    // N * L (diffuse shading)
    float diff = max(dot(normal, lightDir), 0.0);
    // R (reflection vector)
    vec3 reflectDir = reflect(-lightDir, normal);
    // (N * R)^ns (specular shading)
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    // calculate the distance between the light and the fragment
    float distance = length(light.position - fragPos);
    // calculate attenuation
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results

    vec3 diffuseTexture = vec3(texture(texture_diffuse1, TexCoords));
    vec3 specularTexture = vec3(texture(texture_specular1, TexCoords));
    /*
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    */

    vec3 ambient = ka * light.ambient * diffuseTexture;
    vec3 diffuse = kd * light.diffuse * diff * diffuseTexture;
    vec3 specular = ks * light.specular * spec * specularTexture;

    return (ambient + diffuse + specular) * attenuation;
}

