#include "scene.h"
#include <iostream>
#include <cmath>
#include "BoundingBox.h"
#pragma region NODE
 int x = 0;
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
Shape::Shape() :bbox_coords({ { vec3(0, 0, 0), vec3(0, 0, 0) } }), initial_bbox_coords({ { vec3(0, 0, 0), vec3(0, 0, 0) } })
{}
void Shape::Render()
{ 
	glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(fullTransform()));
	ApplyTransformation();
	
	glUniform3fv(uniform_color, 1, glm::value_ptr(_color));
	
}

void Shape::SetBoundingBox(std::array<vec3,2> &coordsToBeSet, std::array<vec3,2>& coords){
	coordsToBeSet = coords;
}
void Shape::ApplyTransformation(){

		glm::vec4 v4_1(initial_bbox_coords[0],1);
		glm::vec4 v4_2(initial_bbox_coords[1],1);

		v4_1 = (_transform*v4_1);
		v4_2 = (_transform*v4_2);

		glm::vec3 v3_1(v4_1);
		glm::vec3 v3_2(v4_2);
		
		this->bbox_coords[0] = v3_1;
		this->bbox_coords[1] = v3_2;
}

std::array<vec3,2> Shape::GetBoundingBox() const{
	return bbox_coords;
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
	 vertices =  
	{ {
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
	} };
	
	for (unsigned int x = 0; x < 36; x++){
		vertices[x].position = (vertices[x].position - 0.5f) * _size;
	}
	
}

void Box::Render()
{
	Shape::Render();
	//perm_vertices = reset_vertices;
	//ApplyTransformation();
	
	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Box::Init(const mat4 &mat){
	for (int i = 0; i < 36; i++){
		glm::vec4 v4_1(vertices[i].position, 1);
		v4_1 = (mat*v4_1);

		glm::vec3 v3_1(v4_1);

		vertices[i].position = v3_1;
	}

	SetBoundingBox(initial_bbox_coords, GetBoundingBoxFromVertices(vertices));
	bbox_coords = initial_bbox_coords;
	// Create Vertex Array Objects
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


#pragma endregion

#pragma region CYLINDER
const int Cylinder::slices = 360;
Cylinder::Cylinder(double radius, double height, vec3 color) : _radius(radius), _height(height)
{
	_vertexBuffer = _indexBuffer = BAD_BUFFER;
	_color = color;
	
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

}

void Cylinder::Render()
{
	Shape::Render();
	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLE_FAN, 0, slices);
	glDrawArrays(GL_TRIANGLE_FAN, slices, slices);
	glDrawArrays(GL_TRIANGLE_STRIP, slices * 2, slices * 2);
}

 #pragma endregion

void Cylinder::Init(const mat4 &mat){
	for (int i = 0; i < 1440; i++){
		glm::vec4 v4_1(vertices[i].position, 1);
		v4_1 = (mat*v4_1);
		glm::vec3 v3_1(v4_1);
		vertices[i].position = v3_1;
	}
	SetBoundingBox(initial_bbox_coords, GetBoundingBoxFromVertices(vertices));
	bbox_coords = initial_bbox_coords;

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

bool IsThereCollision(const Shape &shape1,const Shape &shape2){
	
	std::array<vec3, 2> b1 = shape1.GetBoundingBox();
	std::array<vec3, 2> b2 = shape2.GetBoundingBox();
	
	//std::cout << "Le point max du body est " << b1[0].x << std::endl;
	//std::cout << "Le point min de la dynamite est " << b2[1].x << std::endl;

	return(b1[0].x > b2[1].x &&
		b1[1].x < b2[0].x &&
		b1[0].y > b2[1].y &&
		b1[1].y < b2[0].y &&
		b1[0].z > b2[1].z &&
		b1[1].z < b2[0].z);

}

