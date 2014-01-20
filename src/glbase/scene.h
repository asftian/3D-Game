#pragma once

#include <main.h>

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
	void AddChild(Node &child);
	Node* GetParent();
protected:
	glm::mat4 fullTransform();

	mat4 _transform;
	std::vector<Node> _children;
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
	GLuint _vertexBuffer, _indexBuffer, _vao;
	vec3 _color;
};

class Box : public Shape
{
public:
	Box(vec3 size, vec3 color);

	virtual void Render() override;
protected:
	vec3 _size;
};

class Cylinder : public Shape
{
public:
	Cylinder(float radius, float height, vec3 color);

	virtual void Render() override;
protected:
	float _radius, _height;
};
class Sphere : public Shape
{
public:
	Sphere(float radius, vec3 color);
	virtual void Render() override;
protected:
	float _radius;
};