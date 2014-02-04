#include "tp1.h"
#include <iostream>

/***************************/
//***TODO
//
//-rajouter un cube sur la roue pour la voir tourner et la faire tourner
//-rajouter lanimation des sciseaux avec la touche correspondante
//-implanter la dynamique de jeu
//-

bool set_time_to_0 = true;
bool game_started = false;
bool you_lost = false;
bool show_welcome_screen = true;
bool createDynamite = true;
bool descent = false;

int timeUnit = 0;
int game_state = 0;
int skipframe = 0;

float RandomNumber(float Min, float Max)
{
	return ((float(rand()) / float(RAND_MAX)) * (Max - Min)) + Min;
}

//SHEAR
mat4 body_initial_shear{
	1, 0, 0, 0,
	-0.5, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1 };
mat4 scissors_initial_shear{
		1, 0, 0, 0,
		0, 1, 0, 0,
		-2, 0, 1, 0,
		0, 0, 0, 1 };
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

	/******* STATIC MATRIX DEFINITIONS ******/
	//VIEW MATRIX
	//Positionnement de la camera.
	//TODO
	//En faire une deuxieme pour des points bonis qui sera toggle par une touche du clavier.
	_viewMatrix = glm::lookAt(glm::vec3(3, 5, 9), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	srand(static_cast<unsigned int>(time(NULL)));
}

void CoreTP1::Render(double dt)
{
	switch (game_state){

	case 0:{

			   DrawText("Get Ready!", vec2(0.5, 0.5));
			   if (timeUnit >= 3000){
				   game_state = 1;
				   timeUnit = 0;
			   }
			   break;
	}
	case 1: {
				if (timeUnit >= 1000) game_started = true;
				if (game_started && createDynamite){
					CreateDynamite();
					CreateDynamite();
					CreateDynamite();
					createDynamite = false;
				}
				

				/******* DYNAMIC MATRIX DEFINITIONS ******/
				//CONSTRAINTS
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

				float wheel_rotation_f = -(truck_movement_f / (2.0f * glm::pi<float>() * 0.18f)) * 2 * glm::pi<float>();

				mat4 truck_movement = glm::translate(glm::mat4(), glm::vec3(truck_movement_f, 0.0, 0.0));
				mat4 wheel_rotation = glm::rotate(glm::mat4(), wheel_rotation_f, glm::vec3(0.0, 0.0, 1.0));
				mat4 cannon_rotation = glm::rotate(glm::mat4(), cannon_rotation_f, glm::vec3(0.0, 1.0, 0.0));
				mat4 cannon_scaling = glm::scale(glm::mat4(), glm::vec3(cannon_scaling_f, 1.0, 1.0));
				mat4 tower_scaling = glm::scale(glm::mat4(), glm::vec3(1.0, tower_scaling_f, 1.0));
				mat4 scissor1_rotation = glm::rotate(glm::mat4(), scissors_rotation_f, glm::vec3(0.0, 1.0, 0.0));
				mat4 scissor2_rotation = glm::rotate(glm::mat4(), -scissors_rotation_f, glm::vec3(0.0, 1.0, 0.0));
				mat4 dynamite_rotdation = glm::rotate(glm::mat4(), -scissors_rotation_f, glm::vec3(0.0, 1.0, 0.0));

				for (unsigned int i = 0; i < dynamites.size(); i++){
					dynamites.at(i).explosion_rotation = glm::rotate(glm::mat4(), dynamites.at(i).dynamite_explosion_rotation_f, glm::vec3(0.0, 0.0, 1.0));
					dynamites.at(i).explosion_scaling = glm::scale(glm::mat4(), glm::vec3(dynamites.at(i).dynamite_explosion_scaling_f, dynamites.at(i).dynamite_explosion_scaling_f, dynamites.at(i).dynamite_explosion_scaling_f));
					dynamites.at(i).fuse_scaling = scale(mat4(), vec3(1.0, dynamites.at(i).fuse_scale_factor, 1.0));
				}


				/******* TRANSFORMATIONS SETTING ******/

				body.SetTransform(
					truck_movement*
					body_initial_translation
					);

				wheel_fl.SetTransform(
					glm::inverse(body_initial_translation)*
					wheel_fl_initial_translation*
					wheel_rotation
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
					wheel_fr_initial_translation*
					wheel_rotation
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
					wheel_rl_initial_translation*
					wheel_rotation
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
					wheel_rr_initial_translation*
					wheel_rotation
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

				SpawnDynamites();
				ExplosionAnimation();
				ScissorsAnimation();
				BlinkAnimation();
				
				CheckCollisionsWithTruck();
				
				FusesAnimations();
				



				if (you_lost){
					if (set_time_to_0){
						timeUnit = 0;
						set_time_to_0 = false;
					}
					if (timeUnit > 300) game_state = 2;
				}
				break;
	}
	case 2: {
				if (timeUnit <= 3000){
					DrawText("You lost dude...", vec2(0.5, 0.5));
				}
				else Reset();
				break;
	}
	}
	timeUnit++;
}
void CoreTP1::FusesAnimations(){
	for (unsigned int i = 0; i < dynamites.size(); i++){
		dynamites.at(i).life_time++;
		float fuse_height = dynamites.at(i).fuse.GetBB().c.y + dynamites.at(i).fuse.GetBB().e.at(1);
		float dynamite_height = dynamites.at(i).body.GetBB().c.y + dynamites.at(i).body.GetBB().e.at(1);
		if (fuse_height > dynamite_height-0.1)
			dynamites.at(i).fuse_scale_factor -= 0.0001;
		else if (dynamites.at(i).life_time > 1){ //bug workaround
			dynamites.at(i).explosion_animation = true;
			you_lost = true;
		}

	}
}

void CoreTP1::BlinkAnimation(){
	for (unsigned int i = 0; i < dynamites.size(); i++){
		if (dynamites.at(i).blink < 300){
			if (dynamites.at(i).blink % 2 == 0){
				dynamites.at(i).show = false;
			}
			else
				dynamites.at(i).show = true;
			dynamites.at(i).blink++;
		}
		else if (dynamites.at(i).blink < 999){
			dynamites.at(i).show = false;
		}
	}
}
void CoreTP1::ScissorsAnimation(){
	if (scissors_animation){
		if (scissors_rotation_f < 1.1 && !descent){
			if (skipframe < 5){
				skipframe++;
			}
			else {
				for (unsigned int i = 0; i < dynamites.size(); i++){
					if (dynamites.at(i).can_cut &&
						(Collisions::OBBDetection(scissor1, dynamites.at(i).fuse) ||
						Collisions::OBBDetection(scissor2, dynamites.at(i).fuse))){
						dynamites.at(i).can_cut = false;
						dynamites.at(i).blink = 0;
					}
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
}

void CoreTP1::ExplosionAnimation(){
	for (unsigned int i = 0; i<dynamites.size(); i++){
		if (dynamites.at(i).explosion_animation) {
			if (dynamites.at(i).dynamite_explosion_scaling_f > 0.03) {
				dynamites.at(i).dynamite_explosion_rotation_f += 0.05 * glm::pi<double>();
				dynamites.at(i).dynamite_explosion_scaling_f -= 0.005;
			}
			else {
				dynamites.at(i).explosion_animation = false;
				dynamites.at(i).show = false;
				dynamites.at(i).dynamite_explosion_rotation_f += 0.05;
				dynamites.at(i).dynamite_explosion_scaling_f = 0.3;
			}
		}
	}
}



void CoreTP1::CreateDynamite(){
	Dynamite dynamite(
		RandomNumber(-3.8, 3.8),
		RandomNumber(-2.8, 2.8),
		RandomNumber(1.4, 2.2),
		RandomNumber(0.6, 1.3));
	dynamites.push_back(dynamite);

}
void CoreTP1::CheckCollisionsWithTruck(){
	bool no_collision = true;
	for (int i = 0; i < dynamites.size(); i++){
		if (dynamites.at(i).show && (Collisions::AABBDetection(dynamites.at(i).fuse, sphere_cannon) ||
			Collisions::AABBDetection(dynamites.at(i).body, body) ||
			Collisions::OBBDetection(cannon, dynamites.at(i).body) ||
			Collisions::OBBDetection(scissor1, dynamites.at(i).fuse) ||
			Collisions::OBBDetection(scissor2, dynamites.at(i).fuse) ||
			Collisions::OBBDetection(cannon, dynamites.at(i).fuse) ||
			Collisions::OBBDetection(scissor1, dynamites.at(i).fuse)|| 
			Collisions::OBBDetection(scissor2, dynamites.at(i).fuse) ||
			Collisions::AABBDetection(dynamites.at(i).body,wheel_fl) || 
			Collisions::AABBDetection(dynamites.at(i).body, wheel_fr) || 
			Collisions::AABBDetection(dynamites.at(i).body, wheel_rl) || 
			Collisions::AABBDetection(dynamites.at(i).body, wheel_rr) ||
			Collisions::OBBDetection(dynamites.at(i).body, wheel_fl_box1)||
			Collisions::OBBDetection(dynamites.at(i).body, wheel_fl_box2)||
			Collisions::OBBDetection(dynamites.at(i).body, wheel_fl_box3)||
			Collisions::OBBDetection(dynamites.at(i).body, wheel_fl_box4)||
			Collisions::OBBDetection(dynamites.at(i).body, wheel_fr_box1)||
			Collisions::OBBDetection(dynamites.at(i).body, wheel_fr_box2)||
			Collisions::OBBDetection(dynamites.at(i).body, wheel_fr_box3)||
			Collisions::OBBDetection(dynamites.at(i).body, wheel_fr_box4)||
			Collisions::OBBDetection(dynamites.at(i).body, wheel_rl_box1)||
			Collisions::OBBDetection(dynamites.at(i).body, wheel_rl_box2)||
			Collisions::OBBDetection(dynamites.at(i).body, wheel_rl_box3)||
			Collisions::OBBDetection(dynamites.at(i).body, wheel_rl_box4)||
			Collisions::OBBDetection(dynamites.at(i).body, wheel_rr_box1)||
			Collisions::OBBDetection(dynamites.at(i).body, wheel_rr_box2)||
			Collisions::OBBDetection(dynamites.at(i).body, wheel_rr_box3)||
			Collisions::OBBDetection(dynamites.at(i).body, wheel_rr_box4)
			))
		{
			no_collision = false;
			if (key_pressed == 'w'){
				movement_forward = false;
			}
			else if (key_pressed == 's'){
				movement_backward = false;
			}
			else if (key_pressed == 'r')
				cannon_scaling_up = false;
			else if (key_pressed == 'a'){
				rotation_counter_clockwise = false;
			}
			else if (key_pressed == 'd'){
				rotation_clockwise = false;
			}
			else if (key_pressed == 'f')
				cannon_scaling_down = false;
			else if (key_pressed == 'q')
				tower_scaling_down = false;
			else if (key_pressed == 'e')
				tower_scaling_up = false;
		}
	}
	if (no_collision){
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
}

void CoreTP1::SpawnDynamites(){
	for (unsigned int i = 0; i < dynamites.size(); i++){
		dynamites.at(i).body.AddChild(&dynamites.at(i).fuse);
		dynamites.at(i).body.SetTransform(
			dynamites.at(i).body_translation*
			dynamites.at(i).explosion_rotation*
			dynamites.at(i).explosion_scaling
			);
		dynamites.at(i).fuse.SetTransform(
			dynamites.at(i).fuse_scaling*
			dynamites.at(i).fuse_translation

			);

		RenderDynamites(i);
		CheckSpawningCollisions(i);
	}
}

void CoreTP1::RenderDynamites(int dynamite_to_render){
	if (dynamites.at(dynamite_to_render).show) {
		dynamites.at(dynamite_to_render).body.Render();
		dynamites.at(dynamite_to_render).fuse.Render();
	}

}
void CoreTP1::CheckSpawningCollisions(int dynamite_to_check){
	bool generateNew = false;
	for (unsigned int j = 0; j < dynamites.size(); j++){
		if (j != dynamite_to_check){
			if (Collisions::OBBDetection(dynamites.at(dynamite_to_check).body, dynamites.at(j).body) &&
				dynamites.at(dynamite_to_check).initialization){
				generateNew = true;
				break;
			}
			else {
				dynamites.at(dynamite_to_check).d_to_d_collision_check = true;
			}
		}
	}
	if (generateNew ||
		((Collisions::OBBDetection(dynamites.at(dynamite_to_check).body, body) ||
		Collisions::OBBDetection(dynamites.at(dynamite_to_check).body, wheel_fl) ||
		Collisions::OBBDetection(dynamites.at(dynamite_to_check).body, wheel_fr) || 
		Collisions::OBBDetection(dynamites.at(dynamite_to_check).body, wheel_rl) || 
		Collisions::OBBDetection(dynamites.at(dynamite_to_check).body, wheel_rr) ||
		Collisions::OBBDetection(dynamites.at(dynamite_to_check).body, wheel_fl_box1) ||
		Collisions::OBBDetection(dynamites.at(dynamite_to_check).body, wheel_fl_box2) ||
		Collisions::OBBDetection(dynamites.at(dynamite_to_check).body, wheel_fl_box3) ||
		Collisions::OBBDetection(dynamites.at(dynamite_to_check).body, wheel_fl_box4) ||
		Collisions::OBBDetection(dynamites.at(dynamite_to_check).body, wheel_fr_box1) ||
		Collisions::OBBDetection(dynamites.at(dynamite_to_check).body, wheel_fr_box2) ||
		Collisions::OBBDetection(dynamites.at(dynamite_to_check).body, wheel_fr_box3) ||
		Collisions::OBBDetection(dynamites.at(dynamite_to_check).body, wheel_fr_box4) ||
		Collisions::OBBDetection(dynamites.at(dynamite_to_check).body, wheel_rl_box1) ||
		Collisions::OBBDetection(dynamites.at(dynamite_to_check).body, wheel_rl_box2) ||
		Collisions::OBBDetection(dynamites.at(dynamite_to_check).body, wheel_rl_box3) ||
		Collisions::OBBDetection(dynamites.at(dynamite_to_check).body, wheel_rl_box4) ||
		Collisions::OBBDetection(dynamites.at(dynamite_to_check).body, wheel_rr_box1) ||
		Collisions::OBBDetection(dynamites.at(dynamite_to_check).body, wheel_rr_box2) ||
		Collisions::OBBDetection(dynamites.at(dynamite_to_check).body, wheel_rr_box3) ||
		Collisions::OBBDetection(dynamites.at(dynamite_to_check).body, wheel_rr_box4) ||
		Collisions::OBBDetection(cannon, dynamites.at(dynamite_to_check).body) ||
		Collisions::OBBDetection(scissor1, dynamites.at(dynamite_to_check).fuse) ||
		Collisions::OBBDetection(scissor2, dynamites.at(dynamite_to_check).fuse) ||
		Collisions::OBBDetection(cannon, dynamites.at(dynamite_to_check).fuse) ||
		Collisions::OBBDetection(scissor1, dynamites.at(dynamite_to_check).fuse) ||
		Collisions::OBBDetection(scissor2, dynamites.at(dynamite_to_check).fuse)
		) &&
		dynamites.at(dynamite_to_check).initialization == true)){
		dynamites.at(dynamite_to_check) = Dynamite(RandomNumber(-3.8, 3.8),
			RandomNumber(-2.8, 2.8),
			RandomNumber(1.4, 2.2),
			RandomNumber(0.3, 0.9));
	}
	
	else if (dynamites.at(dynamite_to_check).d_to_d_collision_check == true){
		dynamites.at(dynamite_to_check).initialization = false;
	}

}

void CoreTP1::Reset(){
	game_state = 0;
	dynamites.clear();
	createDynamite = true;
	game_started = false;
	you_lost = false;
	show_welcome_screen = true;
	set_time_to_0 = true;
	timeUnit = 0;
	cannon_scaling_f = 0.5;
	tower_scaling_f = 1.0;
	cannon_rotation_f = 0;
	
}
CoreTP1::~CoreTP1()
{
}

