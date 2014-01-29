#include "scene.h"

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
Shape::Shape()
{}
void Shape::Render()
{
	glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(fullTransform()));
	
	bb.SetTransform(fullTransform());
	
	


	glUniform3fv(uniform_color, 1, glm::value_ptr(_color));

}

BoundingBox Shape::GetBB() const {
	return bb;
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
Box::Box(vec3 size, vec3 color, mat4 init_transf) : _size(size)
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
		glm::vec4 v4(vertices[x].position, 1);
		v4 = (init_transf*v4);
		vec3 v3(v4);
		vertices[x].position = v3;
	}
	bb = BoundingBox(GetAABBFromVertices(vertices));



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

void Box::Render()
{
	Shape::Render();
	
	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}


#pragma endregion

#pragma region CYLINDER
const int Cylinder::slices = 360;
Cylinder::Cylinder(double radius, double height, vec3 color, mat4& init_transf) : _radius(radius), _height(height)
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
	for (unsigned int x = 0; x < 1440; x++){
		glm::vec4 v4(vertices[x].position, 1);
		glm::vec4 v4n(vertices[x].normal, 1);
		v4 = (init_transf*v4);
		v4n = (init_transf*v4n);
		vec3 v3(v4);
		vec3 v3n(v4n);
		vertices[x].position = v3;
		vertices[x].normal = v3n;
	}

	bb = BoundingBox(GetAABBFromVertices(vertices));

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
	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLE_FAN, 0, slices);
	glDrawArrays(GL_TRIANGLE_FAN, slices, slices);
	glDrawArrays(GL_TRIANGLE_STRIP, slices * 2, slices * 2);
}

#pragma endregion
#pragma region SPHERE

Sphere::Sphere(double radius, vec3 color) : _radius(radius)
{
	_vertexBuffer = _indexBuffer = BAD_BUFFER;
	_color = color;

	const int nStacks = 40;
	const int nSlices = 40;

	std::array<VertexPositionNormal,9360> vertices;
	int n = 0;

	for (int stack = 0; stack < nStacks; stack++)
	{
		// Vertical angle between the stacks
		double theta1 = ((double)(stack) / nStacks) * glm::pi<double>();
		double theta2 = ((double)(stack + 1) / nStacks) * glm::pi<double>();

		for (int slice = 0; slice < nSlices; slice++)
		{
			// Horizontal angle between the slices
			double phi1 = ((double)(slice) / nSlices) * 2 * glm::pi<double>();
			double phi2 = ((double)(slice + 1) / nSlices) * 2 * glm::pi<double>();

			// Top stack
			if (stack == 0)
			{
				// One triangle per slice, connected to the top vertex
				vec3 vertex1 = vec3(_radius*glm::sin(theta1)*glm::cos(phi1), _radius*glm::sin(theta1)*glm::sin(phi1), _radius*glm::cos(theta1));
				vec3 vertex2 = vec3(_radius*glm::sin(theta2)*glm::cos(phi2), _radius*glm::sin(theta2)*glm::sin(phi2), _radius*glm::cos(theta2));
				vec3 vertex3 = vec3(_radius*glm::sin(theta2)*glm::cos(phi1), _radius*glm::sin(theta2)*glm::sin(phi1), _radius*glm::cos(theta2));
				vec3 normal = -glm::normalize(glm::cross(vertex2 - vertex1, vertex3 - vertex1));
				vertices[n] = { vertex1, normal };
				vertices[n + 1] = { vertex2, normal };
				vertices[n + 2] = { vertex3, normal };
				n += 3;
			}
			// Bottom stack
			else if (stack + 1 == nStacks)
			{
				// One triangle per slice, connected to the bottom vertex
				vec3 vertex1 = vec3(_radius*glm::sin(theta2)*glm::cos(phi2), _radius*glm::sin(theta2)*glm::sin(phi2), _radius*glm::cos(theta2));
				vec3 vertex2 = vec3(_radius*glm::sin(theta1)*glm::cos(phi1), _radius*glm::sin(theta1)*glm::sin(phi1), _radius*glm::cos(theta1));
				vec3 vertex3 = vec3(_radius*glm::sin(theta1)*glm::cos(phi2), _radius*glm::sin(theta1)*glm::sin(phi2), _radius*glm::cos(theta1));
				vec3 normal = -glm::normalize(glm::cross(vertex2 - vertex1, vertex3 - vertex1));
				vertices[n] = { vertex1, normal };
				vertices[n + 1] = { vertex2, normal };
				vertices[n + 2] = { vertex3, normal };
				n += 3;
			}
			else
			{
				// Two triangles per slice, forming a rectangle
				// First triangle
				vec3 vertex1 = vec3(_radius*glm::sin(theta1)*glm::cos(phi1), _radius*glm::sin(theta1)*glm::sin(phi1), _radius*glm::cos(theta1));
				vec3 vertex2 = vec3(_radius*glm::sin(theta1)*glm::cos(phi2), _radius*glm::sin(theta1)*glm::sin(phi2), _radius*glm::cos(theta1));
				vec3 vertex3 = vec3(_radius*glm::sin(theta2)*glm::cos(phi1), _radius*glm::sin(theta2)*glm::sin(phi1), _radius*glm::cos(theta2));
				vec3 normal1 = -glm::normalize(glm::cross(vertex2 - vertex1, vertex3 - vertex1));
				vertices[n] = { vertex1, normal1 };
				vertices[n + 1] = { vertex2, normal1 };
				vertices[n + 2] = { vertex3, normal1 };

				// Second triangle
				vec3 vertex4 = vec3(_radius*glm::sin(theta1)*glm::cos(phi2), _radius*glm::sin(theta1)*glm::sin(phi2), _radius*glm::cos(theta1));
				vec3 vertex5 = vec3(_radius*glm::sin(theta2)*glm::cos(phi2), _radius*glm::sin(theta2)*glm::sin(phi2), _radius*glm::cos(theta2));
				vec3 vertex6 = vec3(_radius*glm::sin(theta2)*glm::cos(phi1), _radius*glm::sin(theta2)*glm::sin(phi1), _radius*glm::cos(theta2));
				vec3 normal2 = -glm::normalize(glm::cross(vertex2 - vertex1, vertex3 - vertex1));
				vertices[n + 3] = { vertex4, normal2 };
				vertices[n + 4] = { vertex5, normal2 };
				vertices[n + 5] = { vertex6, normal2 };
				n += 6;
			}
		}
	}
	
	bb = BoundingBox(GetAABBFromVertices(vertices));
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
void Sphere::Init(const mat4& mat){

}
void Sphere::Render()
{
	Shape::Render();
	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, 9360);

}
#pragma endregion

bool Collisions::AABBDetection(const Shape& shape1, const Shape& shape2){

	std::array<vec3, 2> b1 = shape1.GetBB().GetAABB();
	std::array<vec3, 2> b2 = shape2.GetBB().GetAABB();
	/*
	std::cout << "Le point min du cannon est " << b1[1].x << std::endl;
	std::cout << "Le point max de la fuse est " << b2[0].x << std::endl;
	std::cout << (b1[0].x > b2[1].x) << std::endl;
	std::cout << (b1[1].x < b2[0].x) << std::endl;
	std::cout << (b1[0].y > b2[1].y) << std::endl;
	std::cout << (b1[1].y < b2[0].y) << std::endl;
	std::cout << (b1[0].z > b2[1].z) << std::endl;
	std::cout << (b1[1].z < b2[0].z) << "\n\n";*/

	return(b1[0].x > b2[1].x &&
		b1[1].x < b2[0].x &&
		b1[0].y > b2[1].y &&
		b1[1].y < b2[0].y &&
		b1[0].z > b2[1].z &&
		b1[1].z < b2[0].z);

}
bool Collisions::OBBDetection(const Shape& shape1, const Shape& shape2){
	//TODO
	BoundingBox& A = shape1.GetBB();
	BoundingBox& B = shape2.GetBB();
	
	vec3 D = B.GetCenter() - A.GetCenter();

	float a0 = A.GetExtents().at(0);
	float a1 = A.GetExtents().at(1);
	float a2 = A.GetExtents().at(2);

	vec3 A0 = A.GetNormals().at(0);
	vec3 A1 = A.GetNormals().at(1);
	vec3 A2 = A.GetNormals().at(2);

	float b0 = B.GetExtents().at(0); 
	float b1 = B.GetExtents().at(1);
	float b2 = B.GetExtents().at(2);

	vec3 B0 = B.GetNormals().at(0);
	vec3 B1 = B.GetNormals().at(1);
	vec3 B2 = B.GetNormals().at(2);
	
	float c00 = dot(A.GetNormals().at(0), B.GetNormals().at(0));
	float c01 = dot(A.GetNormals().at(0), B.GetNormals().at(1));
	float c02 = dot(A.GetNormals().at(0), B.GetNormals().at(2));
	float c10 = dot(A.GetNormals().at(1), B.GetNormals().at(0));
	float c11 = dot(A.GetNormals().at(1), B.GetNormals().at(1));
	float c12 = dot(A.GetNormals().at(1), B.GetNormals().at(2));
	float c20 = dot(A.GetNormals().at(2), B.GetNormals().at(0));
	float c21 = dot(A.GetNormals().at(2), B.GetNormals().at(1));
	float c22 = dot(A.GetNormals().at(2), B.GetNormals().at(2));

	//A0
	float R0 = a0;
	float R1 = b0*abs(c00) + b1*abs(c01) + b2*abs(c02);
	float R = abs(dot(A0, D));
	if (R > (R0 + R1)) return false;
	//A1
	R0 = a1;
	R1 = b0*abs(c10) + b1*abs(c11) + b2*abs(c12);
	R = abs(dot(A1, D));
	if (R > (R0 + R1)) return false;
	//A2
	R0 = a2;
	R1 = b0*abs(c20) + b1*abs(c21) + b2*abs(c22);
	R = abs(dot(A2, D));
	if (R > (R0 + R1)) return false;
	//B0
	R0 = a0*abs(c00) + a1*abs(c10) + a2*abs(c20);
	R1 = b0;
	R = abs(dot(B0, D));
	if (R > (R0 + R1)) return false;
	//B1
	R0 = a0*abs(c01) + a1*abs(c11) + a2*abs(c21);
	R1 = b1;
	R = abs(dot(B1, D));
	if (R > (R0 + R1)) return false;
	//B2
	R0 = a0*abs(c02) + a1*abs(c12) + a2*abs(c22);
	R1 = b2;
	R = abs(dot(B2, D));
	if (R > (R0 + R1)) return false;
	//A0 x B0
	R0 = a1 * abs(c20) + a2 * abs(c10);
	R1 = b1*abs(c02) + b2*abs(c01);
	R = abs(dot(c10*A2, D) - dot(c20*A1, D));
	if (R > (R0 + R1)) return false;
	//A0 x B1
	R0 = a1 * abs(c21) + a2 * abs(c11);
	R1 = b0*abs(c02) + b2*abs(c00);
	R = abs(dot(c11*A2, D) - dot(c21*A1, D));
	if (R > (R0 + R1)) return false;
	//A0 x B2
	R0 = a1 * abs(c22) + a2 * abs(c12);
	R1 = b0*abs(c01) + b1*abs(c00);
	R = abs(dot(c12*A2, D) - dot(c22*A1, D));
	if (R > (R0 + R1)) return false;
	//A1 x B0
	R0 = a0 * c20 + a2 * c00;
	R1 = b1*abs(c12) + b2*abs(c11);
	R = abs(dot(c20*A0, D) - dot(c00*A2, D));
	if (R > (R0 + R1)) return false;
	//A1 x B1
	R0 = a0 * abs(c21) + a2 * abs(c01);
	R1 = b0*abs(c12) + b2*abs(c10);
	R = abs(dot(c21*A0, D) - dot(c01*A2, D));
	if (R > (R0 + R1)) return false;
	//A1 x B2
	R0 = a0 * abs(c22) + a2 * abs(c02);
	R1 = b0*abs(c11) + b1*abs(c10);
	R = abs(dot(c22*A0, D) - dot(c02*A2, D));
	if (R > (R0 + R1)) return false;
	//A2 x B0
	R0 = a0 * abs(c10) + a1 * abs(c00);
	R1 = b1*abs(c22) + b2*abs(c21);
	R = abs(dot(c00*A1, D) - dot(c10*A0, D));
	if (R > (R0 + R1)) return false;
	//A2 x B1
	R0 = a0 * abs(c11) + a1 * abs(c01);
	R1 = b0*abs(c22) + b2*abs(c20);
	R = abs(dot(c01*A1, D) - dot(c11*A0, D));
	if (R > (R0 + R1)) return false;
	//A2 x B2
	R0 = a0 * abs(c12) + a1 * abs(c02);
	R1 = b0*abs(c21) + b1*abs(c20);
	R = abs(dot(c02*A1, D) - dot(c12*A0, D));
	if (R > (R0 + R1)) return false;
	return true;
}

