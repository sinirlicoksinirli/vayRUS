#version 330 core
 out vec4 fragColor;

 uniform vec4 uLightColor;

 in vec2 texCoord;
 in vec3 FragPos;  
 in vec3 Normal;

 uniform vec3 lightPos;  

 uniform bool litRender;  

 flat in int vertTextureLevel;

uniform sampler2DArray textures;

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

        switch (vertTextureLevel) {
            case 0:
                fragColor = texture2D(texture0,texCoord)*brightnessLvl;
                break;
            case 1:
                fragColor = texture2D(texture1,texCoord)*brightnessLvl;
                break;
            case 2:
                fragColor = texture2D(texture2,texCoord)*brightnessLvl;
                break;
            case 3:
                fragColor = texture2D(texture3,texCoord)*brightnessLvl;
                break;
            case 4:
                fragColor = texture2D(texture4,texCoord)*brightnessLvl;
                break;
            case 5:
                fragColor = texture2D(texture5,texCoord)*brightnessLvl;
                break;
        }


    }else{
        switch (vertTextureLevel) {
            case 0:
                fragColor = texture2D(texture0,texCoord);
                break;
            case 1:
                fragColor = texture2D(texture1,texCoord);
                break;
            case 2:
                fragColor = texture2D(texture2,texCoord);
                break;
            case 3:
                fragColor = texture2D(texture3,texCoord);
                break;
            case 4:
                fragColor = texture2D(texture4,texCoord);
                break;
            case 5:
                fragColor = texture2D(texture5,texCoord);
                break;
        }
    }
}