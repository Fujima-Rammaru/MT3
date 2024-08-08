#pragma once
#include "Vector3.h"
struct  Plane
{
	Vector3 normal;
	float distance;
};

struct Sphere {
	Vector3 center;
	float radius;
};

struct Segment {
	Vector3 origin;//始点
	Vector3 diff;//終点への差分ベクトル
};