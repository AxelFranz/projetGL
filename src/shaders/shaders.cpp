#include "shaders.h"


using namespace Shaders;

void ShaderProgram::create(const char* vertexPath, const char* fragmentPath)
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string vCode;
    std::string fCode;
    std::string vPath = SHADER_PATH + vertexPath;
    std::string fPath = SHADER_PATH + fragmentPath;
    

    // Get string from shader taken from http://www.opengl-tutorial.org
    std::cout << vPath << std::endl;
    std::ifstream vStream(vPath.c_str(), std::ios::in);
    if(vStream.is_open()) {
		std::stringstream sstr;
        sstr << vStream.rdbuf();
		vCode = sstr.str();
		vStream.close();    
    } else {
        fprintf(stderr,"[shader] Vertex shader %s could not be found !\n", vPath.c_str());
        glfwTerminate();
        exit(1);
    }

    std::ifstream fStream(fPath.c_str(), std::ios::in);
    if(fStream.is_open()) {
		std::stringstream sstr;
        sstr << fStream.rdbuf();
		fCode = sstr.str();
		fStream.close();    
    } else {
        fprintf(stderr,"[shader] Fragment Shader %s could not be found !\n", fPath.c_str());
        glfwTerminate();
        exit(1);
    }

    time_log(stdout,"[shader] Compiling vertex shader...\n");
    char const* vStr = vCode.c_str();
    glShaderSource(vertexShader,1,&vStr,NULL);
    glCompileShader(vertexShader);
    time_log(stdout,"[shader] Vertex shader compiled !\n"); 

    time_log(stdout,"[shader] Compiling fragment shader...\n");
    char const* fStr = fCode.c_str();
    glShaderSource(fragmentShader,1,&fStr,NULL);
    glCompileShader(fragmentShader);
    time_log(stdout,"[shader] Fragment shader compiled !\n");

    programID = glCreateProgram();
    glAttachShader(programID,vertexShader);
    glAttachShader(programID,fragmentShader);
    glLinkProgram(programID);
    time_log(stdout, "[shader] Shader program created !\n");

    glDetachShader(programID,vertexShader);
    glDetachShader(programID,fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


}

