#ifndef TEST_DISPLAY_H
#define TEST_DISPLAY_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Display
{
public:
	Display(int width, int height, std::string title);
	void Update();
	void Clear(float r = 0.0, float g = 0.15, float b = 0.3, float a = 1.0);
	int getKey();
	GLFWwindow* getWindow();
	int getWidth();
	int getHeight();
	virtual ~Display();
protected:
private:
	void setupOpenGL();
	GLFWwindow *m_window;
	int m_width;
	int m_height;
};

#endif