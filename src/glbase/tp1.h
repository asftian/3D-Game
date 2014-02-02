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
	void ScissorsAnimation(int i);
	void ExplosionAnimation(int i);
	void CheckCollisions(int i);

	Box plane;
	Box body;
	float dynamite_position;
	int random;
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
	float posX;
	float posZ;
	float height;
	float fuse_height;
	std::vector<Cylinder> dynamites;
	std::vector<mat4> dynamites_transformations;
	std::vector<mat4> fuses_transformations;
	std::vector<Cylinder> fuses;

	std::vector<Node> nodes;	
};

