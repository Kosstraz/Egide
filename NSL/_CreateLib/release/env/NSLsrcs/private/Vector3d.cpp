#include "../Vector3d.hpp"

Vector3d::Vector3d() : x(0.0), y(0.0), z(0.0), w(0.0)
{
}
Vector3d::Vector3d(const Vector3d& other) : x(other.x), y(other.y), z(other.z), w(0.0)
{
}
Vector3d::Vector3d(Vector3d&& other) : x(other.x), y(other.y), z(other.z), w(0.0)
{
}

Vector3d::Vector3d(double&& x, double&& y, double&& z) : x(x), y(y), z(z), w(0.0)
{
}
Vector3d::Vector3d(const double& x, const double& y, const double& z) : x(x), y(y), z(z), w(0.0)
{
}


#if defined(AVX2)
Vector3d
Vector3d::Cross(const Vector3d& other) const noexcept
{
	double256	vA		= _mm256_load_pd(&this->x);
	double256	vB		= _mm256_load_pd(&other.x);
	double256	a_vYZX	= _mm256_permute4x64_pd(vA, _MM_SHUFFLE(3, 1, 2, 0));
	double256	a_vZXY	= _mm256_permute4x64_pd(vA, _MM_SHUFFLE(3, 2, 0, 1));
	double256	b_vYZX	= _mm256_permute4x64_pd(vB, _MM_SHUFFLE(3, 1, 2, 0));
	double256	b_vZXY	= _mm256_permute4x64_pd(vB, _MM_SHUFFLE(3, 2, 0, 1));
	Vector3d		ret;
	_mm256_store_pd(static_cast<double*>(&ret.x),
					_mm256_sub_pd(	_mm256_mul_pd(a_vYZX, b_vZXY),
									_mm256_mul_pd(a_vZXY, b_vYZX)
								)
					);
	return (ret);
}
#else
Vector3d
Vector3d::Cross(const Vector3d& other) const noexcept
{
	Vector3d	ret;
	ret.x = this->y * other.z - this->z * other.y;
	ret.y = this->z * other.x - this->x * other.z;
	ret.z = this->x * other.y - this->y * other.x;
	return (ret);
}
#endif


Vector3d
Vector3d::Normalize() const noexcept
{
	double	norm = this->Norm();
	if (norm > 0)
		return (*this / norm);
	return (*this);
}

double
Vector3d::Norm() const noexcept
{
	return (sqrt(this->x * this->x + this->y * this->y + this->z * this->z));
}

double
Vector3d::GetAngle(const Vector3d& other) const noexcept
{
	double	norms	= this->Norm() * other.Norm();
	return (acos(this->Dot(other) / norms));
}

#if defined(AVX)
double
Vector3d::Distance(const Vector3d& other) const noexcept
{
	Vector3d	ret;
	ret = other - *this;
	double256	load = _mm256_load_pd(&ret.x);
	_mm256_store_pd(static_cast<double*>(&ret.x), _mm256_mul_pd(load, load));
	return (sqrt(ret.x + ret.y + ret.z));	// <-- Le potentiel à optimiser
}
#else
double
Vector3d::Distance(const Vector3d& other) const noexcept
{
	return (sqrt((other.x - this->x) * (other.x - this->x) +
				 (other.y - this->y) * (other.y - this->y) +
				 (other.z - this->z) * (other.z - this->z)));
}
#endif

#if defined(AVX2)
// Potentiel à optimiser -->
//  Convertir le int256 en int128 (et faire une permutation de bits)
//  Puis faire une addition de s=(x + y) et de (s + z)
//  Stocker le tout dans un double simple et le renvoyer.
double
Vector3d::Dot(const Vector3d& other) const noexcept
{
	Vector3d	ret;
	_mm256_store_pd(&ret.x, _mm256_mul_pd(	_mm256_load_pd(&this->x),
											_mm256_load_pd(&other.x)
											)
					);
	return (ret.x + ret.y + ret.z);	// <-- Le potentiel à optimiser
}
#else
double
Vector3d::Dot(const Vector3d& other) const noexcept
{
	Vector3d	ret;
	ret.x *= other.x;
	ret.y *= other.y;
	ret.z *= other.z;
	return (ret.x + ret.y + ret.z);
}
#endif

double
Vector3d::Scalar(const Vector3d& other, const double& angle) const noexcept
{
	return (this->Norm() * other.Norm() * sin(angle));
}

bool
Vector3d::SameDirection(const Vector3d& other, const double& angle) const noexcept
{
	return (this->Scalar(other, angle) > 0.0);
}

bool
Vector3d::OppositeDirection(const Vector3d& other, const double& angle) const noexcept
{
	return (this->Scalar(other, angle) < 0.0);
}

bool
Vector3d::IsOrthogonal(const Vector3d& other, const double& angle) const noexcept
{
	return (this->Scalar(other, angle) == 0.0);
}
