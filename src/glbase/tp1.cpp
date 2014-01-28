#include "tp1.h"
#include <iostream>

bool temp = false;
float body_shear[16] = {
	1, 0, 0, 0,
	-0.5, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1 };

float scissors_shear[16] = {
	1, 0, 0, 0,
	0, 1, 0, 0,
	-2, 0, 1, 0,
	0, 0, 0, 1 };

//SHEAR
mat4 body_initial_shear = glm::make_mat4(body_shear);
mat4 scissors_initial_shear = glm::make_mat4(scissors_shear);

//TRANSLATION MATRIX
mat4 body_initial_translation = (glm::translate(glm::mat4(), glm::vec3(0.0, 0.6, 0.0)));
mat4 wheel_fl_initial_translation = glm::translate(glm::mat4(), glm::vec3(0.5, 0.3, 0.55));
mat4 wheel_fr_initial_translation = glm::translate(glm::mat4(), glm::vec3(0.5, 0.3, -0.55));
mat4 wheel_rl_initial_translation = glm::translate(glm::mat4(), glm::vec3(-0.4, 0.3, 0.55));
mat4 wheel_rr_initial_translation = glm::translate(glm::mat4(), glm::vec3(-0.4, 0.3, -0.55));
mat4 vertical_tower_initial_translation = glm::translate(glm::mat4(), glm::vec3(0, 0.6, 0));
mat4 sphere_tower_initial_translation = glm::translate(glm::mat4(), glm::vec3(0, 1.5, 0));
mat4 cannon_initial_translation = glm::translate(glm::mat4(), glm::vec3(0.5, 1.5, 0.0));
mat4 sphere_cannon_initial_translation = glm::translate(glm::mat4(), glm::vec3(0.5, 0.0, 0.0));
mat4 scissor1_initial_translation = glm::translate(glm::mat4(), glm::vec3(0.12, 0.0, 0.15));
mat4 scissor2_initial_translation = glm::translate(glm::mat4(), glm::vec3(0.12, 0.0, -0.15));
mat4 dynamite_body_initial_translation = glm::translate(glm::mat4(), glm::vec3(2, 0.0, 0.0));
mat4 dynamite_fuse_initial_translation = glm::translate(glm::mat4(), glm::vec3(0.0, 1.4, 0.0));

//ROTATION MATRIX
mat4 cannon_initial_rotation = glm::rotate(glm::mat4(), glm::pi<float>() / 2.0f, glm::vec3(0, 0, 1));
mat4 wheels_initial_rotation = glm::rotate(glm::mat4(), glm::pi<float>() / 2.0f, glm::vec3(1, 0, 0));
mat4 scissor1_initial_rotation = glm::rotate(glm::mat4(), -glm::pi<float>() / 3.0f, glm::vec3(0, 1, 0));
mat4 scissor2_initial_rotation = glm::rotate(glm::mat4(), glm::pi<float>() / 3.0f, glm::vec3(0, 1, 0));


CoreTP1::CoreTP1() :
plane(vec3(8.0, 0.1, 6.0), vec3(1.0, 132.0 / 255, 132.0 / 255)),
body(vec3(1.5, 0.7, 1.0), vec3(0.0, 217.0 / 255, 38.0 / 255), body_initial_shear),
wheel_fl(0.18, 0.1, vec3(48.0 / 255, 48.0 / 255, 48.0 / 255)),
wheel_fr(0.18, 0.1, vec3(48.0 / 255, 48.0 / 255, 48.0 / 255)),
wheel_rl(0.18, 0.1, vec3(48.0 / 255, 48.0 / 255, 48.0 / 255)),
wheel_rr(0.18, 0.1, vec3(48.0 / 255, 48.0 / 255, 48.0 / 255)),
vertical_tower(0.08, 0.7, vec3(1.0, 164.0 / 255, 1.0)),
sphere_tower(0.14, vec3(1.0, 164.0 / 255, 1.0)),
cannon(0.05, 1.0, vec3(1.0, 164.0 / 255, 1.0)),
sphere_cannon(0.05, vec3(1.0, 164.0 / 255, 1.0)),
scissor1(vec3(0.25, 0.01, 0.065), vec3(0.0, 0.0, 1.0), scissors_initial_shear),
scissor2(vec3(0.25, 0.01, 0.065), vec3(0.0, 0.0, 1.0), inverse(scissors_initial_shear)),
dynamite_body(0.2, 2.4, vec3(1.0, 0.0, 0.0)),
dynamite_fuse(0.02, 0.5, vec3(212.0 / 255, 212.0 / 255, 212.0 / 255)),
Core()
{
	
	/******* BABY MAKING ******/
	body.AddChild(&wheel_fl);
	body.AddChild(&wheel_fr);
	body.AddChild(&wheel_rl);
	body.AddChild(&wheel_rr);
	body.AddChild(&vertical_tower);
	vertical_tower.AddChild(&sphere_tower);
	sphere_tower.AddChild(&cannon);
	cannon.AddChild(&sphere_cannon);
	sphere_cannon.AddChild(&scissor1);
	sphere_cannon.AddChild(&scissor2);
	dynamite_body.AddChild(&dynamite_fuse);

	/******* STATIC MATRIX DEFINITIONS ******/

	//VIEW MATRIX
	//Positionnement de la camera.
	//TODO
	//En faire une deuxieme pour des points bonis qui sera toggle par une touche du clavier.
	_viewMatrix = glm::lookAt(glm::vec3(3, 4, 10), glm::vec3(0, 1.5, 0), glm::vec3(0, 1, 0));

	
}

void CoreTP1::Render(double dt) //dt is the time unit
{
	/******* DYNAMIC MATRIX DEFINITIONS ******/
	mat4 truck_movement = glm::translate(glm::mat4(), glm::vec3(truck_movement_f, 0.0, 0.0));
	mat4 cannon_rotation = glm::rotate(glm::mat4(), cannon_rotation_f, glm::vec3(0.0, 1.0, 0.0));
	mat4 cannon_scaling = glm::scale(glm::mat4(), glm::vec3(cannon_scaling_f, 1.0, 1.0));
	mat4 scissor1_rotation = glm::rotate(glm::mat4(), scissors_rotation_f, glm::vec3(0.0, 1.0, 0.0));
	mat4 scissor2_rotation = glm::rotate(glm::mat4(), -scissors_rotation_f, glm::vec3(0.0, 1.0, 0.0));


	/******* TRANSFORMATIONS SETTING ******/

	body.SetTransform(
		truck_movement*
		body_initial_translation
		);

	wheel_fl.SetTransform(
		glm::inverse(body_initial_translation)*
		wheel_fl_initial_translation*
		wheels_initial_rotation
		);

	wheel_fr.SetTransform(
		glm::inverse(body_initial_translation)*
		wheel_fr_initial_translation*
		wheels_initial_rotation
		);

	wheel_rl.SetTransform(
		glm::inverse(body_initial_translation)*
		wheel_rl_initial_translation*
		wheels_initial_rotation
		);

	wheel_rr.SetTransform(
		glm::inverse(body_initial_translation)*
		wheel_rr_initial_translation*
		wheels_initial_rotation
		);

	vertical_tower.SetTransform(
		vertical_tower_initial_translation
		);

	sphere_tower.SetTransform(
		glm::inverse(body_initial_translation)*
		glm::inverse(vertical_tower_initial_translation)*
		cannon_rotation*
		sphere_tower_initial_translation
		);

	cannon.SetTransform(
		glm::inverse(sphere_tower_initial_translation)*
		cannon_scaling*
		cannon_initial_translation*
		cannon_initial_rotation
		);

	sphere_cannon.SetTransform(
		glm::inverse(cannon_initial_rotation)*
		//glm::inverse(cannon_scaling)*
		sphere_cannon_initial_translation
		);

	scissor1.SetTransform(
		scissor1_rotation*
		scissor1_initial_translation*
		scissor1_initial_rotation
		);

	scissor2.SetTransform(
		scissor2_rotation*
		scissor2_initial_translation*
		scissor2_initial_rotation
		);

	dynamite_body.SetTransform(
		dynamite_body_initial_translation
		);

	dynamite_fuse.SetTransform(
		dynamite_fuse_initial_translation
		);


	/******* RENDERING ******/
	plane.Render();
	body.Render();
	wheel_fl.Render();
	wheel_fr.Render();
	wheel_rl.Render();
	wheel_rr.Render();
	vertical_tower.Render();
	sphere_tower.Render();
	cannon.Render();
	sphere_cannon.Render();
	scissor1.Render();
	scissor2.Render();
	dynamite_body.Render();
	dynamite_fuse.Render();


	/******* CHECKING FOR COLLISIONS ******/
	if (Collisions::AABBDetection(body, dynamite_body)){
		if (key_pressed = 'w')
			movement_forward = false;
		else
			movement_backward = false;
	}
}

CoreTP1::~CoreTP1()
{
}

