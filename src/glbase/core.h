#include <main.h>

class Core
{
public:
	Core();
	virtual ~Core();

	void Run();

protected:
	virtual void Render(double dt) abstract;

private:
	void GLFWInit();
	void GLEWInit();
	void CoreInit();

protected:
	GLFWwindow* _window;

	GLuint _shaderProgram;

	GLint _uniform_projectionMatrix, _uniform_viewMatrix;

	glm::mat4 _projectionMatrix, _viewMatrix;
};
