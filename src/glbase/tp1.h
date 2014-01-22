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

protected:
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
	float f;
	glm::mat4 body_initial_translation;
	glm::mat4 scissor1_initial_translation;
	glm::mat4 scissor2_initial_translation;
	glm::mat4 scissor1_initial_rotation;
	glm::mat4 scissor2_initial_rotation;
	glm::mat4 scissor1_initial_shear;
	glm::mat4 scissor2_initial_shear;
	glm::mat4 vertical_tower_initial_translation;
	glm::mat4 cannon_initial_rotation;
	glm::mat4 cannon_initial_translation;
	glm::mat4 wheels_initial_rotation;
	glm::mat4 wheel_fl_initial_translation;
	glm::mat4 wheel_fr_initial_translation;
	glm::mat4 wheel_rl_initial_translation;
	glm::mat4 wheel_rr_initial_translation;
	glm::mat4 body_initial_shear;
	glm::mat4 children_initial_inverted_shear;
	glm::mat4 dynamite_body_initial_translation;
	glm::mat4 dynamite_fuse_initial_translation;
	std::vector<Node> nodes;
};
