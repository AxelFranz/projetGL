#include "shaders.h"

using namespace Shaders;

// Error handling from Khronos doc
void ShaderProgram::create(const char *vertexPath, const char *fragmentPath)
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string vCode;
    std::string fCode;
    std::string vPath = SHADER_PATH + vertexPath;
    std::string fPath = SHADER_PATH + fragmentPath;

    std::ifstream vStream(vPath.c_str(), std::ios::in);
    if (vStream.is_open())
    {
        std::stringstream sstr;
        sstr << vStream.rdbuf();
        vCode = sstr.str();
        vStream.close();
    }
    else
    {
        fprintf(stderr, "[shader] Vertex shader %s could not be found !\n", vPath.c_str());
        glfwTerminate();
        exit(1);
    }

    std::ifstream fStream(fPath.c_str(), std::ios::in);
    if (fStream.is_open())
    {
        std::stringstream sstr;
        sstr << fStream.rdbuf();
        fCode = sstr.str();
        fStream.close();
    }
    else
    {
        fprintf(stderr, "[shader] Fragment Shader %s could not be found !\n", fPath.c_str());
        glfwTerminate();
        exit(1);
    }

    time_log(stdout, "[shader] Compiling vertex shader...\n");
    char const *vStr = vCode.c_str();
    glShaderSource(vertexShader, 1, &vStr, NULL);
    glCompileShader(vertexShader);

    GLint isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

        glDeleteShader(vertexShader);


        printf("%s\n",&infoLog[0]);

        programID = -1;
        return;
    }

    time_log(stdout, "[shader] Vertex shader compiled !\n");

    time_log(stdout, "[shader] Compiling fragment shader...\n");
    char const *fStr = fCode.c_str();
    glShaderSource(fragmentShader, 1, &fStr, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

        glDeleteShader(fragmentShader);
        glDeleteShader(vertexShader);

        printf("%s\n",&infoLog[0]);

        programID = -1;
        return;
    }

    time_log(stdout, "[shader] Fragment shader compiled !\n");

    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);

    GLint isLinked = 0;
    glGetProgramiv(programID, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(programID, maxLength, &maxLength, &infoLog[0]);

        glDeleteProgram(programID);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        printf("%s\n",&infoLog[0]);

        return;
    }
    time_log(stdout, "[shader] Shader program created !\n");

    glDetachShader(programID, vertexShader);
    glDetachShader(programID, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void ShaderProgram::path(const char *vertexPath, const char *fragmentPath)
{
    create(vertexPath,fragmentPath);
    if(programID == -1) {
        glfwTerminate();
        exit(1);
    }
}

void ShaderProgram::bind() {
    glUseProgram(programID);
}
