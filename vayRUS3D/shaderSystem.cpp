#include"shaderSystem.hpp"
#include<glm/mat3x3.hpp>
ShaderProgram::ShaderProgram()
{
	programID = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(programID);
}

void ShaderProgram::link()
{
	glLinkProgram(programID);

	int isLinkd;
	char log[512];
	glGetProgramiv(programID, GL_LINK_STATUS, &isLinkd);
    
	if (!isLinkd) {
		glGetProgramInfoLog(programID, 512, 0, log);
		std::cout << "Linking Error!" << std::endl << log << std::endl;
	}
}

void ShaderProgram::use()
{
	glUseProgram(programID);
}

void ShaderProgram::addUniform(const std::string& varName)
{
	m_UniformVars[varName] = glGetUniformLocation(programID, varName.c_str());
}

void ShaderProgram::setFloat(const std::string& varName, float val)
{
	glUniform1f(m_UniformVars[varName], val);
}

void ShaderProgram::setBool(const std::string& varName, bool val)
{
	glUniform1i(m_UniformVars[varName], val);
}

void ShaderProgram::setVec3(const std::string& varName, glm::vec3& val)
{
	glUniform3f(m_UniformVars[varName], val.x,val.y,val.z);
}

void ShaderProgram::setVec4(const std::string& varName, glm::vec4& val)
{
	glUniform4f(m_UniformVars[varName], val.x,val.y,val.z,val.w);
}

void ShaderProgram::setMat3(const std::string& varName, glm::mat3* val)
{
	glUniformMatrix3fv(m_UniformVars[varName],1,false,(GLfloat*)val);
}

void ShaderProgram::setMat4(const std::string& varName, glm::mat4* val)
{
	glUniformMatrix4fv(m_UniformVars[varName],1,false, (GLfloat*)val);
}

 void ShaderProgram::attachShader(const char* fileName, unsigned int shaderType)
{
	 unsigned int shaderID = glCreateShader(shaderType);
	 std::string data = getShaderFromFile(fileName);
	 const char* sourceCode = &data[0];

	 glShaderSource(shaderID, 1, &sourceCode, 0);

	 glCompileShader(shaderID);

	 int isCompl;
	 char log[512];
	 glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompl);
	 if (!isCompl) {
		 glGetShaderInfoLog(shaderID, 512, 0, log);
		 std::cout << "ShaderType:" << shaderType << std::endl << log << std::endl;
	 }

	 glAttachShader(programID, shaderID);

	 glDeleteShader(shaderID);
}

 std::string ShaderProgram::getShaderFromFile(const char* fileName)
 {
	 std::ifstream file(fileName);
	 std::string data;

	 if (file.is_open()) {
		 char readingChar;
		 while ((readingChar = file.get()) != EOF) {
			 data += readingChar;
		 }
		 file.close();
	 }

	 return data;
 }