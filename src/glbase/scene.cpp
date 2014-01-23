#include "scene.h"
#include <iostream>
#include <cmath>

#pragma region NODE

GLint Node::uniform_model = -1, Node::uniform_color = -1;
GLint Node::attribute_position = 1, Node::attribute_normal = 2;

void Node::InitializePreLink(GLuint program)
{
	glBindAttribLocation(program, attribute_position, "in_position");
	glBindAttribLocation(program, attribute_normal, "in_normal");
}

void Node::InitializePostLink(GLuint program)
{
	uniform_model = glGetUniformLocation(program, "model");
	uniform_color = glGetUniformLocation(program, "color");
}

Node::Node()
	: _transform(), _children(), _parent(nullptr)
{
	
}

void Node::SetTransform(const mat4 &transform)
{
	_transform = transform;
}

void Node::AddChild(Node *child)
{
	_children.push_back(child);
	child->_parent = this;
}

Node* Node::GetParent()
{
	return _parent;
}

glm::mat4 Node::fullTransform()
{
	if (_parent == nullptr)
		
		return _transform;
	else
		return _parent->fullTransform() * _transform;
}


#pragma endregion

#pragma region SHAPE

void Shape::Render()
{
	glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(fullTransform()));
	glUniform3fv(uniform_color, 1, glm::value_ptr(_color));
}

Shape::~Shape()
{
	if (_vertexBuffer != BAD_BUFFER)
		glDeleteBuffers(1, &_vertexBuffer);

	if (_indexBuffer != BAD_BUFFER)
		glDeleteBuffers(1, &_indexBuffer);
}

#pragma endregion

#pragma region BOX
Box::Box(vec3 size, vec3 color) : _size(size)
{	
	
	_vertexBuffer = _indexBuffer = BAD_BUFFER;
	_color = color;
	std::array<int, 20000> test;
	VertexPositionNormal vertices[36] =  
	{
		{ vec3(0, 0, 0), vec3(0, -1, 0) },
		{ vec3(1, 0, 0), vec3(0, -1, 0) },
		{ vec3(0, 0, 1), vec3(0, -1, 0) },

		{ vec3(0, 0, 1), vec3(0, -1, 0) },
		{ vec3(1, 0, 0), vec3(0, -1, 0) },
		{ vec3(1, 0, 1), vec3(0, -1, 0) },


		{ vec3(1, 0, 0), vec3(1, 0, 0) },
		{ vec3(1, 1, 0), vec3(1, 0, 0) },
		{ vec3(1, 0, 1), vec3(1, 0, 0) },

		{ vec3(1, 0, 1), vec3(1, 0, 0) },
		{ vec3(1, 1, 0), vec3(1, 0, 0) },
		{ vec3(1, 1, 1), vec3(1, 0, 0) },


		{ vec3(1, 1, 0), vec3(0, 1, 0) },
		{ vec3(0, 1, 1), vec3(0, 1, 0) },
		{ vec3(1, 1, 1), vec3(0, 1, 0) },

		{ vec3(0, 1, 0), vec3(0, 1, 0) },
		{ vec3(0, 1, 1), vec3(0, 1, 0) },
		{ vec3(1, 1, 0), vec3(0, 1, 0) },


		{ vec3(0, 1, 1), vec3(-1, 0, 0) },
		{ vec3(0, 1, 0), vec3(-1, 0, 0) },
		{ vec3(0, 0, 1), vec3(-1, 0, 0) },

		{ vec3(0, 1, 0), vec3(-1, 0, 0) },
		{ vec3(0, 0, 0), vec3(-1, 0, 0) },
		{ vec3(0, 0, 1), vec3(-1, 0, 0) },


		{ vec3(0, 0, 1), vec3(0, 0, 1) },
		{ vec3(1, 0, 1), vec3(0, 0, 1) },
		{ vec3(0, 1, 1), vec3(0, 0, 1) },

		{ vec3(1, 0, 1), vec3(0, 0, 1) },
		{ vec3(1, 1, 1), vec3(0, 0, 1) },
		{ vec3(0, 1, 1), vec3(0, 0, 1) },


		{ vec3(0, 0, 0), vec3(0, 0, -1) },
		{ vec3(0, 1, 0), vec3(0, 0, -1) },
		{ vec3(1, 0, 0), vec3(0, 0, -1) },

		{ vec3(1, 0, 0), vec3(0, 0, -1) },
		{ vec3(0, 1, 0), vec3(0, 0, -1) },
		{ vec3(1, 1, 0), vec3(0, 0, -1) }
	};
    
	corners = { {
		vec3(0, 0, 0),
		vec3(1, 0, 0),
		vec3(0, 1, 0),
		vec3(0, 0, 1),
		vec3(1, 1, 0),
		vec3(1, 0, 1),
		vec3(0, 1, 1),
		vec3(1, 1, 1)
	} };
	
	for (unsigned int x = 0; x < 36; x++){
		vertices[x].position = (vertices[x].position - 0.5f) * _size;
		
	}
	for (int x = 0; x < 8; x++){
		corners[x] = (corners[x] - 0.5f) * _size;
	}
	
	
	
	
	
	// Create Vertex Array Objects
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	// Generate Vertex Buffer
	glGenBuffers(1, &_vertexBuffer);
	
	// Fill Vertex Buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Set Vertex Attributes
	glEnableVertexAttribArray(attribute_position);
	glVertexAttribPointer(attribute_position, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionNormal), (const GLvoid*)0);
	glEnableVertexAttribArray(attribute_normal);
	glVertexAttribPointer(attribute_normal, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionNormal), (const GLvoid*)(0 + sizeof(vec3)));

	glBindVertexArray(0);

	debugGLError();
}

void Box::Render()
{
	Shape::Render();
	for (int i = 0; i < 8; i++){
		glm::vec4 v4(corners[i], 0);
		v4.p = 1.0;
		v4 = (_transform*v4);
		glm::vec3 v3(v4);
		corners[i] = v3;
	}
	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
std::array<glm::vec3,8> Box::GetCorners(){
	return corners;
}

#pragma endregion

#pragma region CYLINDER
const int Cylinder::slices = 360;
Cylinder::Cylinder(double radius, double height, vec3 color) : _radius(radius), _height(height)
{
	_vertexBuffer = _indexBuffer = BAD_BUFFER;
	_color = color;
	VertexPositionNormal vertices[slices * 4];
	// Middle vertex of top circle
	vertices[0] = { vec3(0, _height / 2, 0), vec3(0, 1, 0) };
	// Middle vertex of bottom circle
	vertices[slices] = { vec3(0, -(_height / 2), 0), vec3(0, -1, 0) };

	for (int i = 1; i < slices; i++)

	{
		double theta = 2 * glm::pi<double>() / slices - i;
		//vertices of top circle
		vertices[i] = { vec3(sin(theta)*_radius, _height / 2, cos(theta)*_radius), vec3(0, 1, 0) };
		//vertices of bottom circle
		vertices[i + slices] = { vec3(sin(theta)*_radius, -(_height / 2), cos(theta)*_radius), vec3(0, -1, 0) };
		//vertices of sides
		vertices[2 * i + slices * 2] = { vec3(sin(theta)*_radius, _height / 2, cos(theta)*_radius), glm::normalize(vec3(sin(theta)*_radius, 0, cos(theta)*_radius)) };
		vertices[2 * i + (slices * 2 + 1)] = { vec3(sin(theta)*_radius, -(_height / 2), cos(theta)*_radius), glm::normalize(vec3(sin(theta)*_radius, 0, cos(theta)*_radius)) };
	}
	coords[0] = vertices[0].position;
	coords[1] = vertices[slices + 1].position;
	coords[2] = vertices[1].position;

	// Create Vertex Array Object
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	// Generate Vertex Buffer
	glGenBuffers(1, &_vertexBuffer);

	// Fill Vertex Buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	// Set Vertex Attributes
	glEnableVertexAttribArray(attribute_position);
	glVertexAttribPointer(attribute_position, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionNormal), (const GLvoid*)0);
	glEnableVertexAttribArray(attribute_normal);
	glVertexAttribPointer(attribute_normal, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionNormal), (const GLvoid*)(0 + sizeof(vec3)));

	glBindVertexArray(0);

	debugGLError();
}

void Cylinder::Render()
{
	Shape::Render();
	for (int i = 0; i < 3; i++){
		
		glm::vec4 v4(coords[i], 0);
		v4.p = 1.0;
		v4 = (_transform*v4);
		glm::vec3 v3(v4);
		coords[i] = v3;
		//coords[i] = coords[i] * _transform;
	}
	
	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLE_FAN, 0, slices);
	glDrawArrays(GL_TRIANGLE_FAN, slices, slices);
	glDrawArrays(GL_TRIANGLE_STRIP, slices * 2, slices * 2);
	

}
//std::array<float,4> Cylinder::GetXZRadiusHeight(){
//	float x = 
//	return 0;
//}
//
 #pragma endregion
bool IsThereCollision(Cylinder c, Box b){
	return false;
}
bool IsThereCollision(Cylinder c1, Cylinder c2){
	return false;
}
bool IsFuzeCutByScissors(Cylinder fuse, Box scissorl, Box scissorr){
	return false;
}