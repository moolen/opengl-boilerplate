#ifndef BOILERPLATE_DEBUG_H
#define BOILERPLATE_DEBUG_H

#include "../mesh/mesh_model.h"

class Debug{

public:
	Debug();
	void RenderAxis();
	virtual ~Debug();
protected:
	MeshModel m_model;
};

#endif