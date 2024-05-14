#include "MatrixFunction.h"
#include<cmath>
#include<assert.h>

Matrix4x4 MatrixFunction::MakeTranslateMatrix(const Vector3& translate)
{
	Matrix4x4 result;
	result.m[0][0] = 1;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = 1;
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = 1;
	result.m[2][3] = 0;

	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	result.m[3][3] = 1;

	return result;
}

Matrix4x4 MatrixFunction::MakeScaleMatrix(const Vector3& scale)
{
	Matrix4x4 result;
	result.m[0][0] = scale.x;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = scale.y;
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = scale.z;
	result.m[2][3] = 0;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;

	return result;
}

Vector3 MatrixFunction::Transform(const Vector3& vector, const Matrix4x4& matrix)
{
	Vector3 result;

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;
}

Matrix4x4 MatrixFunction::MakeRotateXMatrix(float radian)
{
	Matrix4x4 result;

	result.m[0][0] = 1;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = std::cos(radian);
	result.m[1][2] = std::sin(radian);
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = -std::sin(radian);
	result.m[2][2] = std::cos(radian);
	result.m[2][3] = 0;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;

	return result;
}

Matrix4x4 MatrixFunction::MakeRotateYMatrix(float radian)
{
	Matrix4x4 result;
	result.m[0][0] = std::cos(radian);
	result.m[0][1] = 0;
	result.m[0][2] = -std::sin(radian);
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = 1;
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = std::sin(radian);
	result.m[2][1] = 0;
	result.m[2][2] = std::cos(radian);
	result.m[2][3] = 0;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;

	return result;
}

Matrix4x4 MatrixFunction::MakeRotateZMatrix(float radian)
{
	Matrix4x4 result;
	result.m[0][0] = std::cos(radian);
	result.m[0][1] = std::sin(radian);
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = -std::sin(radian);
	result.m[1][1] = std::cos(radian);
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = 1;
	result.m[2][3] = 0;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;

	return result;
}

Matrix4x4 MatrixFunction::MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate)
{
	Matrix4x4 result1;
	Matrix4x4 resultScale;
	Matrix4x4 resultRX;
	Matrix4x4 resultRY;
	Matrix4x4 resultRZ;
	Matrix4x4 rotateXYZMatrix;

	//scale
	//===========================
	resultScale.m[0][0] = scale.x;
	resultScale.m[0][1] = 0;
	resultScale.m[0][2] = 0;
	resultScale.m[0][3] = 0;
	resultScale.m[1][0] = 0;
	resultScale.m[1][1] = scale.y;
	resultScale.m[1][2] = 0;
	resultScale.m[1][3] = 0;
	resultScale.m[2][0] = 0;
	resultScale.m[2][1] = 0;
	resultScale.m[2][2] = scale.z;
	resultScale.m[2][3] = 0;
	resultScale.m[3][0] = 0;
	resultScale.m[3][1] = 0;
	resultScale.m[3][2] = 0;
	resultScale.m[3][3] = 1;
	//===========================


	//rotateX
	//===========================
	resultRX.m[0][0] = 1;
	resultRX.m[0][1] = 0;
	resultRX.m[0][2] = 0;
	resultRX.m[0][3] = 0;
	resultRX.m[1][0] = 0;
	resultRX.m[1][1] = std::cos(rotate.x);
	resultRX.m[1][2] = std::sin(rotate.x);
	resultRX.m[1][3] = 0;
	resultRX.m[2][0] = 0;
	resultRX.m[2][1] = -std::sin(rotate.x);
	resultRX.m[2][2] = std::cos(rotate.x);
	resultRX.m[2][3] = 0;
	resultRX.m[3][0] = 0;
	resultRX.m[3][1] = 0;
	resultRX.m[3][2] = 0;
	resultRX.m[3][3] = 1;
	//rotateY
	//===========================
	resultRY.m[0][0] = std::cos(rotate.y);
	resultRY.m[0][1] = 0;
	resultRY.m[0][2] = -std::sin(rotate.y);
	resultRY.m[0][3] = 0;
	resultRY.m[1][0] = 0;
	resultRY.m[1][1] = 1;
	resultRY.m[1][2] = 0;
	resultRY.m[1][3] = 0;
	resultRY.m[2][0] = std::sin(rotate.y);
	resultRY.m[2][1] = 0;
	resultRY.m[2][2] = std::cos(rotate.y);
	resultRY.m[2][3] = 0;
	resultRY.m[3][0] = 0;
	resultRY.m[3][1] = 0;
	resultRY.m[3][2] = 0;
	resultRY.m[3][3] = 1;
	//rotateZ
	//===========================
	resultRZ.m[0][0] = std::cos(rotate.z);
	resultRZ.m[0][1] = std::sin(rotate.z);
	resultRZ.m[0][2] = 0;
	resultRZ.m[0][3] = 0;
	resultRZ.m[1][0] = -std::sin(rotate.z);
	resultRZ.m[1][1] = std::cos(rotate.z);
	resultRZ.m[1][2] = 0;
	resultRZ.m[1][3] = 0;
	resultRZ.m[2][0] = 0;
	resultRZ.m[2][1] = 0;
	resultRZ.m[2][2] = 1;
	resultRZ.m[2][3] = 0;
	resultRZ.m[3][0] = 0;
	resultRZ.m[3][1] = 0;
	resultRZ.m[3][2] = 0;
	resultRZ.m[3][3] = 1;

	//=========================
	rotateXYZMatrix = Multiply(resultRX, Multiply(resultRY, resultRZ));//全軸の回転行列


	//=========================
	result1.m[0][0] = resultScale.m[0][0] * rotateXYZMatrix.m[0][0];
	result1.m[0][1] = resultScale.m[0][0] * rotateXYZMatrix.m[0][1];
	result1.m[0][2] = resultScale.m[0][0] * rotateXYZMatrix.m[0][2];
	result1.m[0][3] = 0;

	result1.m[1][0] = resultScale.m[1][1] * rotateXYZMatrix.m[1][0];
	result1.m[1][1] = resultScale.m[1][1] * rotateXYZMatrix.m[1][1];
	result1.m[1][2] = resultScale.m[1][1] * rotateXYZMatrix.m[1][2];
	result1.m[1][3] = 0;

	result1.m[2][0] = resultScale.m[2][2] * rotateXYZMatrix.m[2][0];
	result1.m[2][1] = resultScale.m[2][2] * rotateXYZMatrix.m[2][1];
	result1.m[2][2] = resultScale.m[2][2] * rotateXYZMatrix.m[2][2];
	result1.m[2][3] = 0;

	result1.m[3][0] = translate.x;
	result1.m[3][1] = translate.y;
	result1.m[3][2] = translate.z;
	result1.m[3][3] = 1;
	return result1;
}

Matrix4x4 MatrixFunction::Multiply(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result;
	result.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0];
	result.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0];
	result.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0];
	result.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0];

	result.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1];
	result.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1];
	result.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1];
	result.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1];

	result.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2];
	result.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2];
	result.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2];
	result.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2];

	result.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3];
	result.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3];
	result.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3];
	result.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3];
	return result;
}

//正射影行列
Matrix4x4 MatrixFunction::MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip)
{
	Matrix4x4 result;
	result.m[0][0] = 2 / (right - left);
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = 2 / (top - bottom);
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = 1 / (farClip - nearClip);
	result.m[2][3] = 0;

	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (top + bottom) / (bottom - top);
	result.m[3][2] = nearClip / (nearClip - farClip);
	result.m[3][3] = 1;

	return result;
}

//透視投影行列
Matrix4x4 MatrixFunction::MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip)
{
	Matrix4x4 result;
	float cot = 1 / std::tan(fovY / 2);
	result.m[0][0] = 1 / aspectRatio * cot;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = cot;
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = farClip / (farClip - nearClip);
	result.m[2][3] = 1;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = (-nearClip * farClip) / (farClip - nearClip);
	result.m[3][3] = 0;

	return result;
}

//ビューポート変換行列
Matrix4x4 MatrixFunction::MakeViewPortMatrix(float left, float top, float width, float height, float minDepth, float maxDepth)
{
	Matrix4x4 result;
	result.m[0][0] = width / 2;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = -height / 2;
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = maxDepth - minDepth;
	result.m[2][3] = 0;

	result.m[3][0] = left + (width / 2);
	result.m[3][1] = top + (height / 2);
	result.m[3][2] = minDepth;
	result.m[3][3] = 1;



	return result;

}
