#include "tp1.h"

CoreTP1::CoreTP1() : Core(),
b(vec3(1.0, 0.5, 1), vec3(1, 0, 0)), 
plane(vec3(4,0.1f,4), vec3(0,1,0)), 
f(0)
{
	_viewMatrix = glm::lookAt(glm::vec3(0, 1, -3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	
}

//dt is the time unit. Called in Core::run. 
void CoreTP1::Render(double dt)
{
	b.SetTransform(glm::rotate(glm::mat4(), f, glm::normalize(glm::vec3(0.5f, 0.5f, 0.5f))));
	float shear[16] = {
		1, 0, 0, 0,
		-0.2, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };
	glm::mat4 shear_matrix = glm::make_mat4(shear);
	b.SetTransform(shear_matrix);
	plane.SetTransform(glm::translate(glm::mat4(), glm::vec3(0, -0.8, 0)));
	b.Render();
	plane.Render();

	f += (float)dt * 2 * glm::pi<float>() * 0.1f;
}

CoreTP1::~CoreTP1()
{
}	
