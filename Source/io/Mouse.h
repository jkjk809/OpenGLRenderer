#pragma once
#ifndef MOUSE_H
#define MOUSE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Camera.h"

class Mouse
{
public:

	Mouse(Camera* cam);

	static void cursorPosCallback(GLFWwindow* window, double _x, double _y);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void mouseWheelCallback(GLFWwindow* window, double dx, double dy);

	static double getMouseX();
	static double getMouseY();

	static double getDX();
	static double getDY();

	static double getScrollDX();
	static double getScrollDY();

	static bool button(int button);
	static bool buttonChanged(int button);
	static bool buttonWentUp(int button);
	static bool buttonWentDown(int button);

private:
	static double x;
	static double y;
	static double lastX;
	static double lastY;

	static double dx;
	static double dy;
	
	static double scrollDX;
	static double scrollDY;

	static bool firstMouse;

	static bool buttons[];
	static bool buttonsChanged[];

	static Camera* camera;
};


#endif