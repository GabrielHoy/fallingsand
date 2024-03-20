#include <iostream>
#include <testInclude.h>
#include <SDL2/SDL.h>
#include <GLFW/glfw3.h>

int main(int argv, char** args)
{
    std::cout << "Hello, World!" << std::endl;
    testIncludeFunc();
    glfwInit(); 
    std::cout << "GLFW initialized" << std::endl;
    //Create a quick GLFW window just to ensure functionality
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello, World!", NULL, NULL);
    std::cout << "GLFW window created" << std::endl;
    glfwTerminate();
    std::cout << "GLFW terminated" << std::endl;
    return 0;
}