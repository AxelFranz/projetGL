#include <iostream>
#include "include.h"
#include "shaders/shaders.h"
#include <GL/wglew.h>
#include <GL/glext.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

class View
{
private:
    Shaders::ShaderProgram shaderPrg;
    GLuint vertexbuffer;
    Geometry::VBO vbo;
    Geometry::VAO vao;
    vec3 color;

public:
    GLFWwindow *window;
    float frames;
    View() {}
    void init();
    void draw();
    void imgui_init();
    void imgui_render();
};

void checkOpenGLError()
{
    GLenum error = glGetError();
    while (error != GL_NO_ERROR)
    {
        std::cerr << "OpenGL error: " << error << std::endl;
        error = glGetError();
    }
}

void View::init()
{
    std::vector<vec3> positions;
    positions.push_back(vec3(-1.f, -1.f, 0.f));
    positions.push_back(vec3(1.f, -1.f, 0.f));
    positions.push_back(vec3(0.f, 1.f, 0.f));

    vbo = Geometry::VBO(positions);
    vao = Geometry::VAO(vbo);

    shaderPrg.path("test.vs", "test.fs");

    color = vec3(1.f, 0.f, 0.f);
}

void View::draw()
{
    imgui_init();
    glClearColor(0.5f, 1.f, 1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    shaderPrg.bind();
    glUniform3fv(0, 1, &color[0]);

    // Bind le VAO (contient déjà les informations du VBO et des attributs)
    vao.bind();

    vao.draw();

    glBindVertexArray(0);

    imgui_render();
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void View::imgui_init()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::GetIO().FontGlobalScale = 1.0f;
    ImGui::NewFrame();
    ImGui::Begin("Debug window");
    ImGui::Text("Use this window to debug");
    ImGui::Text("FPS : %.2f", ImGui::GetIO().Framerate);
    ImGui::SetWindowSize({200, 400});

    ImGui::SliderFloat3("Color", &color[0], 0, 1);

    ImGui::End();
}

void View::imgui_render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

int main()
{

    View view;
    if (!glfwInit())
    {
        return 1;
    }

    view.window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "GLProject", NULL, NULL);
    if (!view.window)
    {
        glfwTerminate();
        return 1;
    }
    time_log(stdout, "[init] Window created !\n");

    glfwMakeContextCurrent(view.window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    ImGui_ImplGlfw_InitForOpenGL(view.window, true);
    ImGui_ImplOpenGL3_Init();

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW: " << glewGetErrorString(err) << std::endl;
        properExit(1);
    }

    view.init();

    while (!glfwWindowShouldClose(view.window))
    {
        view.draw();
    }

    properExit(0);
}
