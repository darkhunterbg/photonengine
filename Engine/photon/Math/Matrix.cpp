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
		r[0] = xAxis;
		r[1] = yAxis;
		r[2] = zAxis;
		r[0][3] = -Vector4::Dot(xAxis, position);
		r[1][3] = -Vector4::Dot(yAxis, position);
		r[2][3] = -Vector4::Dot(zAxis, position);
		r[3][3] = 1;


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