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

	Box plane;
	Box body;
	Cylinder wheel_fl;
	Cylinder wheel_fr;
	Cylinder wheel_rl;
	Cylinder wheel_rr;
	Cylinder tower;
	Sphere sphere_tower;
	Cylinder cannon;
	Sphere sphere_cannon;
	Box scissor1;
	Box scissor2;	
	Cylinder dynamite_body;
	Cylinder dynamite_fuse;	

	std::vector<Node> nodes;	
};

