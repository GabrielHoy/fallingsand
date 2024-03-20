#include <iostream>
#include <testInclude.h>
#include <SDL2/SDL.h>
#include <GLFW/glfw3.h>

int maina(int argv, char** args)
{
    std::cout << "Hello, World!" << std::endl;
    //testIncludeFunc();
    //glfwInit(); 
    //glfwTerminate();
    //Create a quick GLFW window just to ensure functionality
    //GLFWwindow* window = glfwCreateWindow(640, 480, "Hello, World!", NULL, NULL);
    std::cout << "GLFW initialized" << std::endl;
    return 0;
}