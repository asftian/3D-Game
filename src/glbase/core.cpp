#include "core.h"
#include "scene.h"

Core::Core() : _window(nullptr)
{
	GLFWInit();
	GLEWInit();

	// Clear possible error from GLFW/GLEW initialization
	glGetError();

	CoreInit();

	_LOG_INFO() << "Main initialization sequence completed.";
}

Core::~Core()
{
	glDeleteProgram(_shaderProgram);

	glfwTerminate();
}

void Core::Run()
{
	double time = glfwGetTime();
	glClearColor(1.0f, 1.0f, 1.0f, 0.5f);

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(_window))
	{
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		glUseProgram(_shaderProgram);

		//glUniformMatrix is used to modify a matrix or an array of matrix
		//void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
		glUniformMatrix4fv(_uniform_projectionMatrix, 1, GL_FALSE, glm::value_ptr(_projectionMatrix));
		glUniformMatrix4fv(_uniform_viewMatrix, 1, GL_FALSE, glm::value_ptr(_viewMatrix));

		double ntime = glfwGetTime();

		Render(ntime - time);

		time = ntime;

		glfwSwapBuffers(_window);

		glfwPollEvents();
	}
}

void Core::GLFWInit()
{
	// Set GLFW error callback
	glfwSetErrorCallback(onGLFWError);

	// Initialize window manager first
	if (!glfwInit())
	{
		_LOG_CRIT() << "GLFW initialization failed!";
	}

	_LOG_INFO() << "GLFW initialized.";
	glfwWindowHint(GLFW_SAMPLES,4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

#ifdef DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

	_window = glfwCreateWindow(1024, 768, "IFT3355", NULL, NULL);

	if (!_window)
	{
		glfwTerminate();
		_LOG_CRIT() << "GLFW: Could not create window!";
	}

	_LOG_INFO() << "Window created successfully.";

	glfwMakeContextCurrent(_window);
}

void Core::GLEWInit()
{
	glewExperimental = GL_TRUE;
	GLenum glew_error = glewInit();
	if (glew_error != GLEW_OK)
	{
		_LOG_CRIT() << "GLEW initialization failed (code " << glew_error << "):" << glewGetErrorString(glew_error);
	}

	if (!glewIsSupported("GL_VERSION_3_2") && (!glewIsSupported("GL_ARB_vertex_buffer_object") || !glewIsSupported("GL_ARB_vertex_array_object")))
	{
		_LOG_CRIT() << "ARB_vertex_buffer_object not supported!";
	}

	_LOG_INFO() << "GLEW initialized.";
}

void Core::CoreInit()
{
	GLint link_ok = GL_FALSE;

	_shaderProgram = glCreateProgram();

	GLuint vs = loadShader("../shaders/vertex.glsl", GL_VERTEX_SHADER);
	GLuint fs = loadShader("../shaders/fragment.glsl", GL_FRAGMENT_SHADER);

	glAttachShader(_shaderProgram, vs);
	glAttachShader(_shaderProgram, fs);

	Shape::InitializePreLink(_shaderProgram);
	glLinkProgram(_shaderProgram);
	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &link_ok);
	if (!link_ok)
	{
		GLint maxLength = 0;
		glGetProgramiv(_shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);
		if (maxLength == 0)
		{
			_LOG_CRIT() << "Could not link primary shader: No errors reported." << std::endl;
		}

		{
			GLchar* link_error = new GLchar[(unsigned int)maxLength];
			glGetProgramInfoLog(_shaderProgram, maxLength, &maxLength, link_error);
			_LOG_CRIT() << "Could not link primary shader: " << std::endl << link_error << std::endl;
		}
	}

	Shape::InitializePostLink(_shaderProgram);

	_uniform_projectionMatrix = glGetUniformLocation(_shaderProgram, "projection");
	_uniform_viewMatrix = glGetUniformLocation(_shaderProgram, "view");

	_projectionMatrix = glm::perspective(glm::pi<float>() / 4.0f, 1.0f, 0.1f, 15.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	debugGLError();
}
