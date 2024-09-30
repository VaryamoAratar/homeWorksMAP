#pragma once

enum class TypeShape {
	LINE,
	RECTANGLE,
	PARALLELEPIPED,
	CIRCLE,
	CYLINDER,
	UNDEFINED
 };

class Shape
{
public:
	Shape();
	TypeShape getType() { return type; }

protected:
	TypeShape type = TypeShape::UNDEFINED;
};