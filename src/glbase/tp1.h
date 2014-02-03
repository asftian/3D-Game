#pragma once
#include <main.h>
#include "core.h"
#include "scene.h"
#include "collisions.h"

float RandomNumber(float Min, float Max);
struct Dynamite{
	Dynamite(float x, float z, float height, float fuse_length):
	fuse(0.02, fuse_length, vec3(212.0 / 255, 212.0 / 255, 212.0 / 255)),
	body(0.2, height, vec3(1.0, 0.0, 0.0)),
	body_translation(translate(glm::mat4(), glm::vec3(x, height/2 , z))),
	fuse_translation(translate(glm::mat4(), glm::vec3(0.0, height/2+fuse_length/2, 0.0)))
	{
		body.AddChild(&fuse);
		initialization = true;
	}
	Cylinder body;
	Cylinder fuse;
	bool initialization;
	float x;
	float z;
	float height;
	float fuse_length;
	mat4 body_translation;
	mat4 fuse_translation;
};

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
	std::vector<Dynamite> dynamites;
	std::vector<Node> nodes;	
};

