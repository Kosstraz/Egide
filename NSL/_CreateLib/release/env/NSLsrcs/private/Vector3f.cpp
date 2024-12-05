#include "../Vector3f.hpp"

Vector3f::Vector3f() : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
{
}
Vector3f::Vector3f(const Vector3f& other) : x(other.x), y(other.y), z(other.z), w(0.0f)
{
}
Vector3f::Vector3f(Vector3f&& other) : x(other.x), y(other.y), z(other.z), w(0.0f)
{
}

Vector3f::Vector3f(float&& x, float&& y, float&& z) : x(x), y(y), z(z), w(0.0f)
{
}
Vector3f::Vector3f(const float& x, const float& y, const float& z) : x(x), y(y), z(z), w(0.0f)
{
}


#if defined(AVX)
Vector3f
Vector3f::Cross(const Vector3f& other) const noexcept
{
	float128	vA		= _mm_load_ps(&this->x);
	float128	vB		= _mm_load_ps(&other.x);
	float128	aYZX	= _mm_permute_ps(vA, _MM_SHUFFLE(3, 1, 2, 0));
	float128	aZXY	= _mm_permute_ps(vA, _MM_SHUFFLE(3, 2, 0, 1));
	float128	bYZX	= _mm_permute_ps(vB, _MM_SHUFFLE(3, 1, 2, 0));
	float128	bZXY	= _mm_permute_ps(vB, _MM_SHUFFLE(3, 2, 0, 1));
	Vector3f	ret;
	_mm_store_ps(static_cast<float*>(&ret.x),
				_mm_sub_ps(	_mm_mul_ps(aYZX, bZXY),
							_mm_mul_ps(aZXY, bYZX)
							)
				);
	return (ret);
}
#else
Vector3f
Vector3f::Cross(const Vector3f& other) const noexcept
{
	Vector3f	ret;
	ret.x = this->y * other.z - this->z * other.y;
	ret.y = this->z * other.x - this->x * other.z;
	ret.z = this->x * other.y - this->y * other.x;
	return (ret);
}
#endif

Vector3f
Vector3f::Normalize() const noexcept
{
	double	norm = this->Norm();
	if (norm > 0)
		return (*this / norm);
	return (*this);
}

float
Vector3f::Norm() const noexcept
{
	return (sqrtf(this->x * this->x + this->y * this->y + this->z * this->z));
}

float
Vector3f::GetAngle(const Vector3f& other) const noexcept
{
	float norms	= this->Norm() * other.Norm();
	return (acos(this->Dot(other) / norms));
}

float
Vector3f::Distance(const Vector3f& other) const noexcept
{
	return (sqrtf((other.x - this->x) * (other.x - this->x) +
				 (other.y - this->y) * (other.y - this->y) +
				 (other.z - this->z) * (other.z - this->z)));
}

#if defined(SSE)
// Potentiel à optimiser -->
//  Convertir le int256 en int128 (et faire une permutation de bits)
//  Puis faire une addition de s=(x + y) et de (s + z)
//  Stocker le tout dans un double simple et le renvoyer.
float
Vector3f::Dot(const Vector3f& other) const noexcept
{
	Vector3f	ret;
	_mm_store_ps(&ret.x, _mm_mul_ps(_mm_load_ps(&this->x),
									_mm_load_ps(&other.x)
									)
				);
	return (ret.x + ret.y + ret.z);	// <-- Le potentiel à optimiser
}
#else
float
Vector3f::Dot(const Vector3f& other) const noexcept
{
	Vector3f	ret;
	ret.x *= other.x;
	ret.y *= other.y;
	ret.z *= other.z;
	return (ret.x + ret.y + ret.z);
}
#endif

float
Vector3f::Scalar(const Vector3f& other, const float& angle) const noexcept
{
	return (this->Norm() * other.Norm() * sin(angle));
}

bool
Vector3f::SameDirection(const Vector3f& other, const float& angle) const noexcept
{
	return (this->Scalar(other, angle) > 0.0);
}

bool
Vector3f::OppositeDirection(const Vector3f& other, const float& angle) const noexcept
{
	return (this->Scalar(other, angle) < 0.0);
}

bool
Vector3f::IsOrthogonal(const Vector3f& other, const float& angle) const noexcept
{
	return (this->Scalar(other, angle) == 0.0);
}
