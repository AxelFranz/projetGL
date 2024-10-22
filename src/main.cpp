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
    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f,
        -1.0f,
        0.0f,
        1.0f,
        -1.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
    };
    // This will identify our vertex buffer
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
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

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

    glVertexAttribPointer(
        0,        // attribute 0
        3,        // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0,        // stride
        (void *)0 // array buffer offset
    );

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

    glDisableVertexAttribArray(0);
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
