#ifndef TEST_INPUTHANDLER_H
#define TEST_INPUTHANDLER_H

#include "../display/display.h"
#include "event_emitter.h"

class Inputhandler : public EventEmitter{
public:
	const static int W = 1;
	const static int A = 2;
	const static int D = 3;
	const static int S = 4;
	const static int MOUSEMOVE = 5;

	Inputhandler(Display* display);
	virtual ~Inputhandler();
	void HandleKey(int key, int scancode, int action, int mods);
	void HandleMouse(double xpos, double ypos);

protected:
	Display* m_display;
	double m_xpos;
	double m_ypos;
};

#endif