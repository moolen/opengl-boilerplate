#ifndef TEST_INPUTHANDLER_H
#define TEST_INPUTHANDLER_H

#include "../display/display.h"

class Inputhandler{
public:
	Inputhandler(Display* display);
	virtual ~Inputhandler();
	void HandleKey(int key, int scancode, int action, int mods);

protected:
	Display* m_display;
};

#endif