#include "Matrix.h"

namespace photon
{

	const Matrix Matrix::IDENTITY =
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	Matrix Matrix::LookAtRH(Vector4 position, Vector4 target, Vector4 up)
	{
		Vector4 zAxis = (position - target).Normalize3();
		Vector4 xAxis = Vector4::Cross(up, zAxis).Normalize3();
		Vector4 yAxis = Vector4::Cross(zAxis, xAxis);

		Matrix r = {};
		r[0][0] = xAxis.x;
		r[1][0] = xAxis.y;
		r[2][0] = xAxis.z;
		r[0][1] = yAxis.x;
		r[1][1] = yAxis.y;
		r[2][1] = yAxis.z;
		r[0][2] = -zAxis.x;
		r[1][2] = -zAxis.y;
		r[2][2] = -zAxis.z;
		r[3] = {
			-Vector4::Dot(xAxis,position),
			-Vector4::Dot(yAxis,position),
			-Vector4::Dot(zAxis,position),
			1
		};


		return r;
	}

	Matrix Matrix::PerspectiveRH(float fov, float aspectRatio, float nearPlane, float farPlane)
	{
		float yScale = 1.0f / tanf(fov / 2.0f);
		float xScale = yScale / aspectRatio;

		Matrix r = {};
		r[0][0] = xScale;
		r[1][1] = yScale;
		r[2][2] = farPlane / (nearPlane - farPlane);
		r[3][2] = -1;
		r[2][3] = (farPlane * nearPlane) / (nearPlane - farPlane);
		return r;
	}
}