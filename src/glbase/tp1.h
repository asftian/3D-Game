#pragma once
#include <main.h>
#include "core.h"
#include "scene.h"
#include "collisions.h"

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
	Box wheel_fl_box1;
	Box wheel_fl_box2;
	Box wheel_fl_box3;
	Box wheel_fl_box4;
	Cylinder wheel_fr;
	Box wheel_fr_box1;
	Box wheel_fr_box2;
	Box wheel_fr_box3;
	Box wheel_fr_box4;
	Cylinder wheel_rl;
	Box wheel_rl_box1;
	Box wheel_rl_box2;
	Box wheel_rl_box3;
	Box wheel_rl_box4;
	Cylinder wheel_rr;
	Box wheel_rr_box1;
	Box wheel_rr_box2;
	Box wheel_rr_box3;
	Box wheel_rr_box4;
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

