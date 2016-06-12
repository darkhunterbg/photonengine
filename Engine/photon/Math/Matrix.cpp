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
		Vector4 zAxis = (target - position).Normalize3();
		Vector4 xAxis = Vector4::Cross(zAxis, up).Normalize3();
		Vector4 yAxis = Vector4::Cross(xAxis, zAxis);

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
			Vector4::Dot(zAxis,position),
			1
		};


		return    r;
	}

	Matrix Matrix::PerspectiveRH(float fov, float aspectRatio, float nearPlane, float farPlane)
	{
		float yScale = 1.0f / tan(fov / 2.0f);
		float xScale = yScale / aspectRatio;

		Matrix r;
		r[0] = { xScale,0,0,0 };
		r[1] = { 0,yScale,0,0 };
		r[2] = { 0,0, -(farPlane + nearPlane) / (farPlane - nearPlane), -1 };
		r[3] = { 0,0, (- farPlane * nearPlane) / (farPlane - nearPlane),0 };

		return r;
	}
}