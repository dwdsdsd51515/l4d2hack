#pragma once

#include "vmatrix.h"

#define PI 3.14159265358979323846f
#define DEG2RAD( x ) ( ( float )( x ) * ( float )( ( float )( PI ) / 180.0f ) )
#define RAD2DEG( x ) ( ( float )( x ) * ( float )( 180.0f / ( float )( PI ) ) )
#define square( x ) ( x * x )


namespace Math
{
	float sseSqrt(float x);

	void vectorAngles(Vector forward, Vector &angles);

	float DotProduct(const float *v1, const float *v2);

	VOID VectorTransform(const Vector in1, const matrix3x4_t& in2, Vector& out);

	float GetFov(Vector vLocalOrigin, Vector vPosition, Vector vForward);

	void CalcAngle(Vector &vSource, Vector &vDestination, Vector &qAngle);

	void angleVectors(Vector angles, Vector &f);

	float AngleNormalize(float angle);
}
