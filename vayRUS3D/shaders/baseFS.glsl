#version 330 core
 out vec4 fragColor;

 uniform vec4 uLightColor;

 in vec2 texCoord;
 in vec3 FragPos;  
 in vec3 Normal;

 uniform vec3 lightPos;  

 uniform bool litRender;  

 uniform sampler2D inTexture;

 void main()
{
    if(litRender){
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);  
        vec4 lc = vec4(1.0f,1.0f,1.0f,1.0f);

        float diff = max(dot(norm, lightDir), 0.0);
        vec4 diffuse = diff * lc;

        float brightness = 0.2;
        vec4 brightnessLvl = (brightness+diffuse) * lc;

        fragColor = texture2D(inTexture,texCoord)*brightnessLvl;

    }else{
        fragColor = texture2D(inTexture,texCoord);
    }
}