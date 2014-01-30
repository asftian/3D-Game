#include <main.h>
#include "texture.h"

class Core
{
public:
	Core();
	virtual ~Core();
	
	void Run();
	
protected:
	virtual void Render(double dt) abstract;
	char key_pressed;
	float truck_movement_f;
	bool movement_forward;
	bool movement_backward;
	float cannon_rotation_f;
	bool rotation_counter_clockwise;
	bool rotation_clockwise;
	float cannon_scaling_f;
	bool cannon_scaling_up;
	bool cannon_scaling_down;
	float tower_scaling_f;
	bool tower_scaling_up;
	bool tower_scaling_down;
	float scissors_rotation_f;
	bool scissors_closed;
	bool scissors_animation;

	virtual void OnKeyW(bool down) {
		key_pressed = 'w';
		
		if (movement_forward==true)
			truck_movement_f += 0.04;
		//_LOG_INFO() << "W " << (down ? "down." : "up.") << std::endl;
	}

	virtual void OnKeyS(bool down) {
		key_pressed = 's';
		
		cannon_scaling_up = true;
		if (movement_backward == true)
			truck_movement_f -= 0.04;
		//_LOG_INFO() << "S " << (down ? "down." : "up.") << std::endl;
	}

	virtual void OnKeyA(bool down) {
		key_pressed = 'a';
		
		if (rotation_counter_clockwise == true)
			cannon_rotation_f += glm::pi<float>() / 120.0;
		//_LOG_INFO() << "A " << (down ? "down." : "up.") << std::endl;
	}

	virtual void OnKeyD(bool down) {
		key_pressed = 'd';
		
		if (rotation_clockwise == true)
			cannon_rotation_f -= glm::pi<float>() / 120.0;
		//_LOG_INFO() << "D " << (down ? "down." : "up.") << std::endl;
	}

	virtual void OnKeyR(bool down) {
		
		key_pressed = 'r';
		
		if (cannon_scaling_up == true)
			cannon_scaling_f += 0.05;
		//_LOG_INFO() << "R " << (down ? "down." : "up.") << std::endl;
	}

	virtual void OnKeyF(bool down) {
		key_pressed = 'f';
		
		
		if (cannon_scaling_down == true){
			if (cannon_scaling_f > 0.15)
				cannon_scaling_f -= 0.05;
		}
		//_LOG_INFO() << "F " << (down ? "down." : "up.") << std::endl;
	}

	virtual void OnKeyQ(bool down) {
		key_pressed = 'q';
		
		if (tower_scaling_down == true){
			if (tower_scaling_f > 0.15)
				tower_scaling_f -= 0.05;
		}
		//_LOG_INFO() << "Q " << (down ? "down." : "up.") << std::endl;
	}

	virtual void OnKeyE(bool down) {
		key_pressed = 'e';
		
		if (tower_scaling_up == true)
			tower_scaling_f += 0.05;
		//_LOG_INFO() << "E " << (down ? "down." : "up.") << std::endl;
	}

	virtual void OnKeyTAB(bool down) { _LOG_INFO() << "TAB " << (down ? "down." : "up.") << std::endl; }

	virtual void OnKeySPACE(bool down) {
		key_pressed = 'S';
		if (down) {
			scissors_animation = true;
				//scissors_rotation_f = 1.0;
		}
		else {
				//scissors_rotation_f = 0.0;
		}
		//_LOG_INFO() << "SPACE " << (down ? "down." : "up.") << std::endl;
	}

	virtual void OnMouseMove(float x, float y) { /*_LOG_INFO() << "Mouse x=" << x << ", y=" << y << std::endl;*/ }
	virtual void OnMouseLeft(bool down) { _LOG_INFO() << "LMB " << (down ? "down." : "up.") << std::endl; }
	virtual void OnMouseRight(bool down) { _LOG_INFO() << "RMB " << (down ? "down." : "up.") << std::endl; }
	virtual void OnMouseWheel(double dx, double dy) { _LOG_INFO() << "Wheel dx=" << dx << ", dy=" << dy << std::endl; }

	enum TextAlign
	{
		ALIGN_LEFT,
		ALIGN_RIGHT,
		ALIGN_CENTER
	};

	void DrawText(const char* text, glm::vec2 position, const glm::vec4 &color = glm::vec4(1, 1, 1, 1), unsigned int pixel_size = 32, TextAlign align = ALIGN_LEFT);

private:
	void GLFWInit();
	void GLEWInit();
	void TextInit();
	void CoreInit();

	static void MouseClickCallback(GLFWwindow* w, int button, int action, int modifiers);
	static void MouseScrollCallback(GLFWwindow* w, double dx, double dy);
	static void MouseMoveCallback(GLFWwindow* w, double x, double y);

	static void KeyCallback(GLFWwindow* w, int key, int scancode, int action, int mods);

	static Core* _callback_object;

protected:
	GLFWwindow* _window;

	GLuint _shaderProgram;

	GLint _uniform_projectionMatrix, _uniform_viewMatrix;

	glm::mat4 _projectionMatrix, _viewMatrix;

	// Text rendering

	GLuint _textVAO;

	GLuint _textVertexBuffer, _textUVBuffer;

	GLuint _textProgram;

	GLint _uniform_textSampler, _uniform_textColor;
	GLint _attribute_textPosition, _attribute_textUV;

	std::unique_ptr<Texture> _fontTexture;
};