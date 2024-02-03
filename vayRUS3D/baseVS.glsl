#version 330 core

 layout (location = 0) in vec3 inPosition;
 layout (location = 1) in vec2 inTexCoord;

 uniform vec3 uTranslation;
 uniform vec3 uRotation;
 uniform mat4 uScale;

 uniform mat4 uMtxProj;
 uniform mat4 uMtxCamPos;
 uniform vec3 uCamRot;
 uniform mat4 uMtxCam;

 out vec2 texCoord;

 mat4 rotationX( in float angle ) {
	return mat4(	1.0,		0,			0,			0,
			 		0, 	cos(angle),	-sin(angle),		0,
					0, 	sin(angle),	 cos(angle),		0,
					0, 			0,			  0, 		1);
}

mat4 rotationY( in float angle ) {
	return mat4(	cos(angle),		0,		sin(angle),	0,
			 				0,		1.0,			 0,	0,
					-sin(angle),	0,		cos(angle),	0,
							0, 		0,				0,	1);
}

mat4 rotationZ( in float angle ) {
	return mat4(	cos(angle),		-sin(angle),	0,	0,
			 		sin(angle),		cos(angle),		0,	0,
							0,				0,		1,	0,
							0,				0,		0,	1);
}

 void main()
{
    mat4 translMatr;
	mat4 rotMatr;

	mat4 camRotMatr;

    translMatr[0][0]=1;
    translMatr[1][1]=1;
    translMatr[2][2]=1;
    translMatr[3]=vec4(uTranslation, 1.0);

	rotMatr = rotationX(radians(uRotation.x))*rotationY(radians(uRotation.y))*rotationZ(radians(uRotation.z));

	camRotMatr=rotationX(radians(uCamRot.x))*rotationY(radians(uCamRot.y))*rotationZ(radians(uCamRot.z));

    gl_Position = uMtxProj*camRotMatr*uMtxCam*inverse(uMtxCamPos)*translMatr*rotMatr*uScale*vec4(inPosition, 1.0);
    texCoord = inTexCoord;
}