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
	Box b;
	Box b2;
	Box plane;
	Cylinder c1;
	float f;
	glm::mat4 b_set_pos;
	glm::mat4 b2_set_pos;
	glm::mat4 plan_set_pos;
	glm::mat4 c1_set_pos;
	glm::mat4 shear_matrix;
	glm::mat4 shear_matrix_inv;
	std::vector<Node> nodes;
};
