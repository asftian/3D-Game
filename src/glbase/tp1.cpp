#include "tp1.h"
#include <iostream>

/***************************/
//***TODO
//
//-rajouter un cube sur la roue pour la voir tourner et la faire tourner
//-rajouter lanimation des sciseaux avec la touche correspondante
//-implanter la dynamique de jeu
//-
int timeUnit = 0;
bool temp = false;
bool showCountdown = false;
int skipframe = 0;
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

bool descent = false;
//SHEAR
mat4 body_initial_shear = glm::make_mat4(body_shear);
mat4 scissors_initial_shear = glm::make_mat4(scissors_shear);

//TRANSLATION MATRIX
mat4 body_initial_translation = (glm::translate(glm::mat4(), glm::vec3(0.0, 0.6, 0.0)));
mat4 wheel_fl_initial_translation = glm::translate(glm::mat4(), glm::vec3(0.5, 0.31, 0.55));
mat4 wheel_fr_initial_translation = glm::translate(glm::mat4(), glm::vec3(0.5, 0.31, -0.55));
mat4 wheel_rl_initial_translation = glm::translate(glm::mat4(), glm::vec3(-0.4, 0.31, 0.55));
mat4 wheel_rr_initial_translation = glm::translate(glm::mat4(), glm::vec3(-0.4, 0.31, -0.55));
mat4 wheel_box1_initial_translation = glm::translate(glm::mat4(), glm::vec3(0.0, 0.2, 0.0));
mat4 wheel_box2_initial_translation = glm::translate(glm::mat4(), glm::vec3(0.2, 0.0, 0.0));
mat4 wheel_box3_initial_translation = glm::translate(glm::mat4(), glm::vec3(0.0, -0.2, 0.0));
mat4 wheel_box4_initial_translation = glm::translate(glm::mat4(), glm::vec3(-0.2, 0.0, 0.0));
mat4 tower_initial_translation1 = glm::translate(glm::mat4(), glm::vec3(0, 0.35, 0));
mat4 tower_initial_translation2 = glm::translate(glm::mat4(), glm::vec3(0, 0.35, 0));
mat4 sphere_tower_initial_translation = glm::translate(glm::mat4(), glm::vec3(0, 1.6, 0));
mat4 cannon_initial_translation = glm::translate(glm::mat4(), glm::vec3(0.5, 1.6, 0.0));
mat4 sphere_cannon_initial_translation = glm::translate(glm::mat4(), glm::vec3(0.5, 0.0, 0.0));
mat4 scissor1_initial_translation = glm::translate(glm::mat4(), glm::vec3(0.11, 0.0, 0.25));
mat4 scissor2_initial_translation = glm::translate(glm::mat4(), glm::vec3(0.11, 0.0, -0.25));
mat4 dynamite_body_initial_translation = glm::translate(glm::mat4(), glm::vec3(-2, 0.8, 2));
mat4 dynamite_fuse_initial_translation = glm::translate(glm::mat4(), glm::vec3(0.0, 1.05, 0.0));

//ROTATION MATRIX
mat4 cannon_initial_rotation = glm::rotate(glm::mat4(), glm::pi<float>() / 2.0f, glm::vec3(0, 0, 1));
mat4 wheels_initial_rotation = glm::rotate(glm::mat4(), glm::pi<float>() / 2.0f, glm::vec3(1, 0, 0));
mat4 scissor1_initial_rotation = glm::rotate(glm::mat4(), -glm::pi<float>() / 2.5f, glm::vec3(0, 1, 0));
mat4 scissor2_initial_rotation = glm::rotate(glm::mat4(), glm::pi<float>() / 2.5f, glm::vec3(0, 1, 0));


CoreTP1::CoreTP1() :
plane(vec3(8.0, 0.1, 6.0), vec3(1.0, 132.0 / 255, 132.0 / 255)),
body(vec3(1.5, 0.7, 1.0), vec3(0.0, 217.0 / 255, 38.0 / 255), body_initial_shear),
wheel_fl(0.18, 0.1, vec3(48.0 / 255, 48.0 / 255, 48.0 / 255), wheels_initial_rotation),
wheel_fl_box1(vec3(0.1, 0.1, 0.1), vec3(48.0 / 255, 48.0 / 255, 48.0 / 255)),
wheel_fl_box2(vec3(0.1, 0.1, 0.1), vec3(48.0 / 255, 48.0 / 255, 48.0 / 255)),
wheel_fl_box3(vec3(0.1, 0.1, 0.1), vec3(48.0 / 255, 48.0 / 255, 48.0 / 255)),
wheel_fl_box4(vec3(0.1, 0.1, 0.1), vec3(48.0 / 255, 48.0 / 255, 48.0 / 255)),
wheel_fr(0.18, 0.1, vec3(48.0 / 255, 48.0 / 255, 48.0 / 255), wheels_initial_rotation),
wheel_fr_box1(vec3(0.1, 0.1, 0.1), vec3(48.0 / 255, 48.0 / 255, 48.0 / 255)),
wheel_fr_box2(vec3(0.1, 0.1, 0.1), vec3(48.0 / 255, 48.0 / 255, 48.0 / 255)),
wheel_fr_box3(vec3(0.1, 0.1, 0.1), vec3(48.0 / 255, 48.0 / 255, 48.0 / 255)),
wheel_fr_box4(vec3(0.1, 0.1, 0.1), vec3(48.0 / 255, 48.0 / 255, 48.0 / 255)),
wheel_rl(0.18, 0.1, vec3(48.0 / 255, 48.0 / 255, 48.0 / 255), wheels_initial_rotation),
wheel_rl_box1(vec3(0.1, 0.1, 0.1), vec3(48.0 / 255, 48.0 / 255, 48.0 / 255)),
wheel_rl_box2(vec3(0.1, 0.1, 0.1), vec3(48.0 / 255, 48.0 / 255, 48.0 / 255)),
wheel_rl_box3(vec3(0.1, 0.1, 0.1), vec3(48.0 / 255, 48.0 / 255, 48.0 / 255)),
wheel_rl_box4(vec3(0.1, 0.1, 0.1), vec3(48.0 / 255, 48.0 / 255, 48.0 / 255)),
wheel_rr(0.18, 0.1, vec3(48.0 / 255, 48.0 / 255, 48.0 / 255), wheels_initial_rotation),
wheel_rr_box1(vec3(0.1, 0.1, 0.1), vec3(48.0 / 255, 48.0 / 255, 48.0 / 255)),
wheel_rr_box2(vec3(0.1, 0.1, 0.1), vec3(48.0 / 255, 48.0 / 255, 48.0 / 255)),
wheel_rr_box3(vec3(0.1, 0.1, 0.1), vec3(48.0 / 255, 48.0 / 255, 48.0 / 255)),
wheel_rr_box4(vec3(0.1, 0.1, 0.1), vec3(48.0 / 255, 48.0 / 255, 48.0 / 255)),
tower(0.08, 0.7, vec3(1.0, 164.0 / 255, 1.0)),
sphere_tower(0.14, vec3(1.0, 164.0 / 255, 1.0)),
cannon(0.05, 1.0, vec3(1.0, 164.0 / 255, 1.0), cannon_initial_rotation),
sphere_cannon(0.05, vec3(1.0, 164.0 / 255, 1.0)),
scissor1(vec3(0.3, 0.01, 0.090), vec3(0.0, 0.0, 1.0), scissors_initial_shear),
scissor2(vec3(0.3, 0.01, 0.090), vec3(0.0, 0.0, 1.0), inverse(scissors_initial_shear)),
dynamite_body(0.2, 1.6, vec3(1.0, 0.0, 0.0)),
dynamite_fuse(0.02, 0.5, vec3(212.0 / 255, 212.0 / 255, 212.0 / 255)),
Core()
{

	/******* BABY MAKING ******/
	body.AddChild(&wheel_fl);
	wheel_fl.AddChild(&wheel_fl_box1);
	wheel_fl.AddChild(&wheel_fl_box2);
	wheel_fl.AddChild(&wheel_fl_box3);
	wheel_fl.AddChild(&wheel_fl_box4);
	body.AddChild(&wheel_fr);
	wheel_fr.AddChild(&wheel_fr_box1);
	wheel_fr.AddChild(&wheel_fr_box2);
	wheel_fr.AddChild(&wheel_fr_box3);
	wheel_fr.AddChild(&wheel_fr_box4);
	body.AddChild(&wheel_rl);
	wheel_rl.AddChild(&wheel_rl_box1);
	wheel_rl.AddChild(&wheel_rl_box2);
	wheel_rl.AddChild(&wheel_rl_box3);
	wheel_rl.AddChild(&wheel_rl_box4);
	body.AddChild(&wheel_rr);
	wheel_rr.AddChild(&wheel_rr_box1);
	wheel_rr.AddChild(&wheel_rr_box2);
	wheel_rr.AddChild(&wheel_rr_box3);
	wheel_rr.AddChild(&wheel_rr_box4);
	body.AddChild(&tower);
	tower.AddChild(&sphere_tower);
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
	_viewMatrix = glm::lookAt(glm::vec3(3, 5, 9), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}

void CoreTP1::Render(double dt) //dt is the time unit
{	
	if (timeUnit <= 5){
	/*	if (timeUnit <=80 && !showCountdown)
			DrawText("Get Ready!", vec2(0.5,0.5));
		else if (!showCountdown){
			showCountdown = true;
			timeUnit = 0;
		}
		if (showCountdown){
			if (timeUnit <= 100)
				DrawText("5", vec2(0.5, 0.5));
			else if (timeUnit <= 200)
				DrawText("4", vec2(0.5, 0.5));
			else if (timeUnit <= 300)
				DrawText("3", vec2(0.5, 0.5));
			else if (timeUnit <= 400)
				DrawText("2", vec2(0.5, 0.5));
			else if (timeUnit <= 500)
				DrawText("1", vec2(0.5, 0.5));
		}*/
	}

	else {
		bool dontcut = true;
		if (Collisions::AABBDetection(dynamite_fuse, sphere_cannon) ||
			Collisions::AABBDetection(dynamite_body, body) ||
			Collisions::OBBDetection(cannon, dynamite_fuse) ||
			Collisions::OBBDetection(scissor1, dynamite_fuse) ||
			Collisions::OBBDetection(scissor2, dynamite_fuse) ||
			Collisions::OBBDetection(cannon, dynamite_body) ||
			Collisions::OBBDetection(scissor1, dynamite_body) ||
			Collisions::OBBDetection(scissor2, dynamite_body))
		{
			if (key_pressed == 'w'){
				movement_forward = false;

			}
			else if (key_pressed == 's'){
				movement_backward = false;
			}

			else if (key_pressed == 'r')
				cannon_scaling_up = false;
			else if (key_pressed == 'a'){
				cannon_rotation_f -= glm::pi<float>() / 120.0;
				rotation_counter_clockwise = false;
			}

			else if (key_pressed == 'd'){
				rotation_clockwise = false;
				cannon_rotation_f += glm::pi<float>() / 120.0;
			}

			else if (key_pressed == 'f')
				cannon_scaling_down = false;
			else if (key_pressed == 'q')
				tower_scaling_down = false;
			else if (key_pressed == 'e')
				tower_scaling_up = false;

		}
		else{
			movement_forward =
				movement_backward =
				cannon_scaling_up =
				cannon_scaling_down =
				tower_scaling_down =
				tower_scaling_up =
				rotation_clockwise =
				rotation_counter_clockwise =
				true;
		}






		if (scissors_animation){

			if (scissors_rotation_f < 1.1 && !descent){
				if (skipframe < 5){

					skipframe++;
				}
				else {
					if (Collisions::OBBDetection(scissor1, dynamite_fuse) || Collisions::OBBDetection(scissor2, dynamite_fuse)){
						dontcut = false;
					}
				}

				scissors_rotation_f += 0.02;
			}
			else{
				descent = true;
				scissors_rotation_f -= 0.02;
				if (scissors_rotation_f <= 0){
					scissors_animation = false;
					descent = false;
				}
			}
			if (!scissors_animation) skipframe = 0;
		}



		/******* DYNAMIC MATRIX DEFINITIONS ******/
		if (truck_movement_f >= 3.0)
			truck_movement_f = 3.0;
		if (truck_movement_f <= -3.0)
			truck_movement_f = -3.0;
		if (cannon_scaling_f >= 3)
			cannon_scaling_f = 3;
		if (cannon_scaling_f <= 0.1)
			cannon_scaling_f = 0.1;
		if (tower_scaling_f >= 2)
			tower_scaling_f = 2;
		if (tower_scaling_f <= 0.1)
			tower_scaling_f = 0.1;
		mat4 truck_movement = glm::translate(glm::mat4(), glm::vec3(truck_movement_f, 0.0, 0.0));
		mat4 cannon_rotation = glm::rotate(glm::mat4(), cannon_rotation_f, glm::vec3(0.0, 1.0, 0.0));
		mat4 cannon_scaling = glm::scale(glm::mat4(), glm::vec3(cannon_scaling_f, 1.0, 1.0));
		mat4 tower_scaling = glm::scale(glm::mat4(), glm::vec3(1.0, tower_scaling_f, 1.0));
		mat4 scissor1_rotation = glm::rotate(glm::mat4(), scissors_rotation_f, glm::vec3(0.0, 1.0, 0.0));
		mat4 scissor2_rotation = glm::rotate(glm::mat4(), -scissors_rotation_f, glm::vec3(0.0, 1.0, 0.0));


		/******* TRANSFORMATIONS SETTING ******/

		body.SetTransform(
			truck_movement*
			body_initial_translation
			);

		wheel_fl.SetTransform(
			glm::inverse(body_initial_translation)*
			wheel_fl_initial_translation
			);

		wheel_fl_box1.SetTransform(
			wheel_box1_initial_translation
			);

		wheel_fl_box2.SetTransform(
			wheel_box2_initial_translation
			);
		wheel_fl_box3.SetTransform(
			wheel_box3_initial_translation
			);
		wheel_fl_box4.SetTransform(
			wheel_box4_initial_translation
			);

		wheel_fr.SetTransform(
			glm::inverse(body_initial_translation)*
			wheel_fr_initial_translation
			);

		wheel_fr_box1.SetTransform(
			wheel_box1_initial_translation
			);

		wheel_fr_box2.SetTransform(
			wheel_box2_initial_translation
			);
		wheel_fr_box3.SetTransform(
			wheel_box3_initial_translation
			);
		wheel_fr_box4.SetTransform(
			wheel_box4_initial_translation
			);

		wheel_rl.SetTransform(
			glm::inverse(body_initial_translation)*
			wheel_rl_initial_translation
			);

		wheel_rl_box1.SetTransform(
			wheel_box1_initial_translation
			);

		wheel_rl_box2.SetTransform(
			wheel_box2_initial_translation
			);
		wheel_rl_box3.SetTransform(
			wheel_box3_initial_translation
			);
		wheel_rl_box4.SetTransform(
			wheel_box4_initial_translation
			);

		wheel_rr.SetTransform(
			glm::inverse(body_initial_translation)*
			wheel_rr_initial_translation
			);

		wheel_rr_box1.SetTransform(
			wheel_box1_initial_translation
			);

		wheel_rr_box2.SetTransform(
			wheel_box2_initial_translation
			);
		wheel_rr_box3.SetTransform(
			wheel_box3_initial_translation
			);
		wheel_rr_box4.SetTransform(
			wheel_box4_initial_translation
			);

		tower.SetTransform(
			tower_initial_translation1*
			tower_scaling*
			tower_initial_translation2
			);

		sphere_tower.SetTransform(

			sphere_tower_initial_translation*
			cannon_rotation*
			glm::inverse(body_initial_translation)*
			glm::inverse(tower_initial_translation1)*
			glm::inverse(tower_initial_translation2)*
			glm::inverse(tower_scaling)
			);

		cannon.SetTransform(
			glm::inverse(sphere_tower_initial_translation)*
			cannon_scaling*
			cannon_initial_translation

			);

		sphere_cannon.SetTransform(
			sphere_cannon_initial_translation*
			glm::inverse(cannon_scaling)
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
		wheel_fl_box1.Render();
		wheel_fl_box2.Render();
		wheel_fl_box3.Render();
		wheel_fl_box4.Render();
		wheel_fr.Render();
		wheel_fr_box1.Render();
		wheel_fr_box2.Render();
		wheel_fr_box3.Render();
		wheel_fr_box4.Render();
		wheel_rl.Render();
		wheel_rl_box1.Render();
		wheel_rl_box2.Render();
		wheel_rl_box3.Render();
		wheel_rl_box4.Render();
		wheel_rr.Render();
		wheel_rr_box1.Render();
		wheel_rr_box2.Render();
		wheel_rr_box3.Render();
		wheel_rr_box4.Render();
		tower.Render();
		sphere_tower.Render();
		cannon.Render();
		sphere_cannon.Render();
		scissor1.Render();
		scissor2.Render();
		dynamite_body.Render();
		if (dontcut){
			dynamite_fuse.Render();
		}


		///******* CHECKING FOR COLLISIONS ******/
		//if (Collisions::AABBDetection(body, dynamite_body)){
		//	if (key_pressed = 'w')
		//		movement_forward = false;
		//	else
		//		movement_backward = false;
		//}
		//std::cout << Collisions::OBBDetection(dynamite_fuse, cannon);
		//
		//std::cout << Collisions::OBBDetection(scissor1, dynamite_fuse);
		//std::cout << Collisions::AABBDetection(body, dynamite_body);
		//cannon.GetBB().print("cannon");
		//dynamite_fuse.GetBB().print("fuse");

		



	}
	timeUnit++;
}

CoreTP1::~CoreTP1()
{
}

