#ifndef INPUT_HPP
#define INPUT_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "InputState.hpp"

#include "ui.hpp"
#include "Camera.hpp"
 
class Input {
	public:
		Input() {};

		InputState _inputState;
		
};
Input& getInput();

void processInput(GLFWwindow *window);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
 




#endif