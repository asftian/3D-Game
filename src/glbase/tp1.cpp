#include "tp1.h"
#include <iostream>

CoreTP1::CoreTP1() : Core(),
body(vec3(1.5, 0.7, 1.0), vec3(0, 217.0/255, 38.0/255)),
plane(vec3(8, 0.1, 6), vec3(1.0, 132.0 / 255, 132.0/255)),
vertical_tower(0.08, 0.7, vec3(1,164.0/255,1)),
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

	/******* STATIC MATRIX DEFINITIONS ******/

	//VIEW MATRIX
	//vue de l'axe des z
	_viewMatrix = glm::lookAt(glm::vec3(3, 3, 6), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	//vue de l'axe des x
	//_viewMatrix = glm::lookAt(glm::vec3(4, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	//vue de l'axe des y
	//_viewMatrix = glm::lookAt(glm::vec3(0, 14,0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	//SHEAR MATRIX
	float shear[16] = {
		1, 0, 0, 0,
		-0.5, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };

	float shearInverted[16] = {
		1, 0, 0, 0,
		0.5, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };

	body_initial_shear = glm::make_mat4(shear);
	children_initial_inverted_shear = glm::make_mat4(shearInverted);

	//TRANSLATION MATRIX
	body_initial_translation = (glm::translate(glm::mat4(), glm::vec3(0, 0.6, 0)));
	vertical_tower_initial_translation = glm::translate(glm::mat4(), glm::vec3(0, 0.6, 0));
	cannon_initial_translation = glm::translate(glm::mat4(), glm::vec3(0.19, 1.5, 0));
	wheel_fl_initial_translation = glm::translate(glm::mat4(), glm::vec3(0.2, 0.3, 0.55));
	wheel_fr_initial_translation = glm::translate(glm::mat4(), glm::vec3(0.2, 0.3, -0.55));
	wheel_rl_initial_translation = glm::translate(glm::mat4(), glm::vec3(-0.7, 0.3, 0.55));
	wheel_rr_initial_translation = glm::translate(glm::mat4(), glm::vec3(-0.7, 0.3, -0.55));
	
	//ROTATION MATRIX
	cannon_initial_rotation = glm::rotate(glm::mat4(),glm::pi<float>()/2.0f, glm::vec3(0, 0, 1));
	wheels_initial_rotation = glm::rotate(glm::mat4(), glm::pi<float>() /2.0f, glm::vec3(1, 0, 0));

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

	
	//plane.Render();

	/******* UPDATING ******/
	f += (float)dt * 2 * glm::pi<float>() * 0.1f;
}

CoreTP1::~CoreTP1()
{
}	
