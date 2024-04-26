#pragma once
#include"Matrix4x4.h"
#include"Vector3.h"

class MatrixFunction {

public:

	Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

	Matrix4x4 MakeScaleMatrix(const Vector3& scale);

	Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

	Matrix4x4 MakeRotateXMatrix(float radian);

	Matrix4x4 MakeRotateYMatrix(float radian);

	Matrix4x4 MakeRotateZMatrix(float radian);

	Matrix4x4 Multiply(Matrix4x4 m1, Matrix4x4 m2);

private:

};