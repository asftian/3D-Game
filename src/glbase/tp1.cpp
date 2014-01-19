#include "tp1.h"

CoreTP1::CoreTP1() : Core(), b(vec3(1, 1, 1), vec3(1, 0, 0)), f(0)
{
	_viewMatrix = glm::lookAt(glm::vec3(0, 1, -3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}

//dt is the time unit. Called in Core::run. 
void CoreTP1::Render(double dt)
{
	b.SetTransform(glm::rotate(glm::mat4(), f, glm::normalize(glm::vec3(0.5f, 0.5f, 0.5f))));
	b.Render();

	f += (float)dt * 2 * glm::pi<float>() * 0.1f;
}

CoreTP1::~CoreTP1()
{
}	
