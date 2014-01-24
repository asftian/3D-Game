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
	Shape();
	virtual void Render();
	void SetBoundingBox(std::array<vec3,2> &coordsToBeSet, std::array<vec3, 2> &coords);
	void ApplyTransformation();
	std::array<vec3,2> _GetBoundingBox() const;
	std::array<vec3, 2> _coords;
	std::array<vec3, 2> initial_coords;
	
	void Reset_coords();
	virtual ~Shape();
protected:
	GLuint _vertexBuffer, _indexBuffer, _vao, _vao2;
	vec3 _color;
};

class Box : public Shape
{
public:
	Box(vec3 size, vec3 color);
	void ReInit(const mat4 &transform = mat4());
	virtual void Render() override;
	void setInitialTransformation(mat4 &mat);

protected:
	std::array<VertexPositionNormal, 36> vertices;
	vec3 _size;
};	

class Cylinder : public Shape
{
public:
	static const int slices;
	Cylinder(double radius, double height, vec3 color);
	virtual void Render() override;
	void ReInit(const mat4 &mat = mat4());
protected:
	double _radius, _height;
	std::array<VertexPositionNormal, 1440> vertices;
};
class Sphere : public Shape
{
public:
	Sphere(float radius, vec3 color);
	virtual void Render() override;
protected:
	double _radius, _height;
};

bool IsThereCollision(const Shape  &shape1, const Shape &shape2);