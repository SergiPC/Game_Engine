#pragma once
#include "MathGeoLib\MathGeoLib.h"
#include "Color.h"

enum GeometryTypes
{
	Point,
	Line,
	Plane,
	Cube,
	Sphere,
	Cylinder
};

class Geometry
{
public:

	Geometry();

	virtual void	Render() const;
	virtual void	InnerRender() const;
	void			SetPos(float x, float y, float z);
	void			SetRotation(float angle, const float3 &u);
	void			Scale(float x, float y, float z);
	GeometryTypes	GetType() const;

public:

	Color color;
	float4x4 transform;
	bool axis, wire;

protected:
	GeometryTypes type;
};