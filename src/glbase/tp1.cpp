#include "tp1.h"
#include <iostream>

CoreTP1::CoreTP1() :
body(vec3(1.5, 0.7, 1.0), vec3(0, 217.0 / 255, 38.0 / 255)),
plane(vec3(8, 0.1, 6), vec3(1.0, 132.0 / 255, 132.0 / 255)),
scissor1(vec3(0.3, 0.01, 0.045), vec3(0, 0, 1.0)),
scissor2(vec3(0.3, 0.01, 0.045), vec3(0, 0, 1.0)),
vertical_tower(0.08, 0.7, vec3(1, 164.0 / 255, 1)),
cannon(0.05, 0.5, vec3(1, 164.0 / 255, 1)),
wheel_fl(0.18, 0.1, vec3(48.0 / 255, 48.0 / 255, 48.0 / 255)),
wheel_fr(0.18, 0.1, vec3(48.0 / 255, 48.0 / 255, 48.0 / 255)),
wheel_rl(0.18, 0.1, vec3(48.0 / 255, 48.0 / 255, 48.0 / 255)),
wheel_rr(0.18, 0.1, vec3(48.0 / 255, 48.0 / 255, 48.0 / 255)),
dynamite_body(0.2, 0.6, vec3(1, 0, 0)),
dynamite_fuse(0.02, 0.3, vec3(1, 1, 1)),
f(0)
{
	/******* BABY MAKING ******/
	body.AddChild(&vertical_tower);
	vertical_tower.AddChild(&cannon);
	body.AddChild(&wheel_fl);
	body.AddChild(&wheel_fr);
	body.AddChild(&wheel_rl);
	body.AddChild(&wheel_rr);
	cannon.AddChild(&scissor1);
	cannon.AddChild(&scissor2);

	/******* STATIC MATRIX DEFINITIONS ******/

	//VIEW MATRIX
	//vue de l'axe des z
	_viewMatrix = glm::lookAt(glm::vec3(3, 5, 6), glm::vec3(0, 1.5, 0), glm::vec3(0, 1, 0));
	//_viewMatrix = glm::lookAt(glm::vec3(0, 2, 4), glm::vec3(0, 2, 0), glm::vec3(0, 1, 0));
	//vue de l'axe des x
	//_viewMatrix = glm::lookAt(glm::vec3(6, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	//vue de l'axe des y
	//_viewMatrix = glm::lookAt(glm::vec3(0, 14,0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	//SHEAR MATRIX
	float body_shear[16] = {
		1, 0, 0, 0,
		-0.5, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };

	float body_shear_inv[16] = {
		1, 0, 0, 0,
		0.5, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };

	float scissor1_shear[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		-2, 0, 1, 0,
		0, 0, 0, 1 };
	float scissor2_shear[16]= {
		1, 0, 0, 0,
		0, 1, 0, 0,
		2, 0, 1, 0,
		0, 0, 0, 1 };;

	body_initial_shear = glm::make_mat4(body_shear);
	scissor1_initial_shear = glm::make_mat4(scissor1_shear);
	scissor2_initial_shear = glm::make_mat4(scissor2_shear);
	children_initial_inverted_shear = glm::make_mat4(body_shear_inv);


	//TRANSLATION MATRIX
	body_initial_translation = (glm::translate(glm::mat4(), glm::vec3(0, 0.6, 0)));

	vertical_tower_initial_translation = glm::translate(glm::mat4(), glm::vec3(0, 0.6, 0));
	cannon_initial_translation = glm::translate(glm::mat4(), glm::vec3(0.19, 1.5, 0));
	wheel_fl_initial_translation = glm::translate(glm::mat4(), glm::vec3(0.2, 0.3, 0.55));
	wheel_fr_initial_translation = glm::translate(glm::mat4(), glm::vec3(0.2, 0.3, -0.55));
	wheel_rl_initial_translation = glm::translate(glm::mat4(), glm::vec3(-0.7, 0.3, 0.55));
	wheel_rr_initial_translation = glm::translate(glm::mat4(), glm::vec3(-0.7, 0.3, -0.55));
	scissor1_initial_translation = glm::translate(glm::mat4(), glm::vec3(0.3, 0.0, 0.15));
	scissor2_initial_translation = glm::translate(glm::mat4(), glm::vec3(0.3, 0.0, -0.15));

	//ROTATION MATRIX
	cannon_initial_rotation = glm::rotate(glm::mat4(), glm::pi<float>() / 2.0f, glm::vec3(0, 0, 1));
	wheels_initial_rotation = glm::rotate(glm::mat4(), glm::pi<float>() / 2.0f, glm::vec3(1, 0, 0));
	scissor1_initial_rotation = glm::rotate(glm::mat4(), -glm::pi<float>() / 3.0f, glm::vec3(0, 1, 0));
	scissor2_initial_rotation = glm::rotate(glm::mat4(), glm::pi<float>() / 3.0f, glm::vec3(0, 1, 0));

}

void CoreTP1::Render(double dt) //dt is the time unit
{

	/******* DYNAMIC MATRIX DEFINITIONS ******/
	glm::mat4 rotating_matrix = glm::rotate(glm::mat4(), f, glm::normalize(glm::vec3(0.5f, 0.5f, 0.5f)));

	/******* TRANSFORMATIONS SETTING ******/

	body.SetTransform(
		body_initial_translation *
		body_initial_shear
		);

	vertical_tower.SetTransform(
		vertical_tower_initial_translation *
		children_initial_inverted_shear
		);

	cannon.SetTransform(
		glm::inverse(body_initial_translation)*
		glm::inverse(vertical_tower_initial_translation)*
		cannon_initial_translation*
		cannon_initial_rotation
		);
	wheel_fl.SetTransform(
		glm::inverse(body_initial_translation)*
		children_initial_inverted_shear*
		wheel_fl_initial_translation*
		wheels_initial_rotation

		);
	wheel_fr.SetTransform(
		glm::inverse(body_initial_translation)*
		children_initial_inverted_shear*
		wheel_fr_initial_translation*
		wheels_initial_rotation

		);
	wheel_rl.SetTransform(
		glm::inverse(body_initial_translation)*
		children_initial_inverted_shear*
		wheel_rl_initial_translation*
		wheels_initial_rotation

		);
	wheel_rr.SetTransform(
		glm::inverse(body_initial_translation)*
		children_initial_inverted_shear*
		wheel_rr_initial_translation*
		wheels_initial_rotation

		);

	scissor1.SetTransform(
		glm::inverse(cannon_initial_rotation)*
		scissor1_initial_translation*
		scissor1_initial_rotation*
		scissor1_initial_shear
		);
	scissor2.SetTransform(
		glm::inverse(cannon_initial_rotation)*
		scissor2_initial_translation*
		scissor2_initial_rotation*
		scissor2_initial_shear
		);

	//1.SetTransform(c1_set_pos*rotating_matrix);

	/******* RENDERING ******/
	body.Render();
	plane.Render();
	vertical_tower.Render();
	cannon.Render();
	wheel_fl.Render();
	wheel_fr.Render();
	wheel_rl.Render();
	wheel_rr.Render();
	scissor1.Render();
	scissor2.Render();


	//plane.Render();

	/******* UPDATING ******/
	f += (float)dt * 2 * glm::pi<float>() * 0.1f;
}

CoreTP1::~CoreTP1()
{
}
