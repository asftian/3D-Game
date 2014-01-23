#pragma once

#include <main.h>
#include <array>
#include <algorithm>

using namespace glm;

struct VertexPositionNormal
{
	vec3 position;
	vec3 normal;
};

class Node
{
public:
	static void InitializePreLink(GLuint program);
	static void InitializePostLink(GLuint program);

	Node();
	void SetTransform(const mat4 &transform);
	void AddChild(Node *child);
	Node* GetParent();
protected:
	glm::mat4 fullTransform();

	mat4 _transform;
	std::vector<Node*> _children;
	Node* _parent;

	static GLint uniform_model, uniform_color;
	static GLint attribute_position, attribute_normal;
};

class Shape : public Node
{
public:
	virtual void Render();
	virtual ~Shape();
protected:
	GLuint _vertexBuffer, _indexBuffer, _vao, _vao2;
	vec3 _color;
};

class Box : public Shape
{
public:
	Box(vec3 size, vec3 color);

	std::array<glm::vec3, 8> GetCorners();
	virtual void Render() override;

protected:
	vec3 _size;
	std::array<glm::vec3,8> corners;
};	

class Cylinder : public Shape
{
public:
	static const int slices;
	Cylinder(double radius, double height, vec3 color);
	std::array<float,4> GetXZRadiusHeight();
	
	virtual void Render() override;
protected:
	double _radius, _height;
	std::array<glm::vec3, 3> coords;//center-top, center-bottom, side-top
};
class Sphere : public Shape
{
public:
	Sphere(float radius, vec3 color);
	virtual void Render() override;
protected:
	double _radius, _height;
};

bool IsThereCollision(Cylinder c, Box b);

bool IsThereCollision(Cylinder c1, Cylinder c2);
bool IsFuzeCutByScissors(Cylinder fuse, Box scissorl, Box scissorr);