#pragma once
#include <main.h>
#include "core.h"
#include "scene.h"


class CoreTP1 : public Core
{
public:
	CoreTP1();
	
	virtual ~CoreTP1() override;


protected:
	virtual void Render(double dt) override;

	Box body;
	Box plane;
	Box scissor1;
	Box scissor2;
	Cylinder vertical_tower;
	Cylinder cannon;
	Cylinder wheel_fl;
	Cylinder wheel_fr;
	Cylinder wheel_rl;
	Cylinder wheel_rr;
	Cylinder dynamite_body;
	Cylinder dynamite_fuse;
	Sphere sphere_tower;
	Sphere sphere_cannon;
	

	std::vector<Node> nodes;

	
};

