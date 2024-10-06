#include <iostream>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "shaders/shaders.h"

class View
{
private:
public:
    View() {}
    void draw();
};

int main()
{
    std::cout << "Hello World" << std::endl;
    GLFWwindow *window;
    if (!glfwInit())
    {
        return 1;
    }

    window = glfwCreateWindow(800, 600, "GLProject", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    View view;

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        view.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

void View::draw()
{
    glBegin(GL_TRIANGLES);
    glVertex2d(-0.75, -0.75);
    glVertex2d(-0.0, 0.75);
    glVertex2d(0.75, -0.75);
    glEnd();
}