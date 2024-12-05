#include "../Vector3d.hpp"

#pragma region Operations
					//		=
#if defined(AVX2)
Vector3d&
Vector3d::operator=(const Vector3d& o) noexcept
{

	_mm256_store_pd(&this->x, _mm256_load_pd(&o.x));
	return (*this);
}
#else
Vector3d&
Vector3d::operator=(const Vector3d& o) noexcept
{
	this->x = o.x;
	this->y = o.y;
	this->z = o.z;
	return (*this);
}
#endif
					//		+=
#if defined(AVX2)
Vector3d&
Vector3d::operator+=(const Vector3d& o) noexcept
{
	_mm256_store_pd(static_cast<double*>(&this->x), _mm256_add_pd(
		_mm256_load_pd(&this->x),
		_mm256_load_pd(&o.x)
	));
	return (*this);
}
#else
Vector3d&
Vector3d::operator+=(const Vector3d& o) noexcept
{
	this->x += o.x;
	this->y += o.y;
	this->z += o.z;
	return (*this);
}
#endif
					//		-=
#if defined(AVX2)
Vector3d&
Vector3d::operator-=(const Vector3d& o) noexcept
{
	_mm256_store_pd(static_cast<double*>(&this->x), _mm256_sub_pd(
		_mm256_load_pd(&this->x),
		_mm256_load_pd(&o.x)
	));
	return (*this);
}
#else
Vector3d&
Vector3d::operator-=(const Vector3d& o) noexcept
{
	this->x -= o.x;
	this->y -= o.y;
	this->z -= o.z;
	return (*this);
}
#endif
					//		*=
Vector3d&
Vector3d::operator*=(const Vector3d& o) noexcept
{
	*this = this->Cross(o);
	return (*this);
}
					//		/=
#if defined(AVX2)
Vector3d&
Vector3d::operator/=(const Vector3d& o) noexcept
{
	_mm256_store_pd(static_cast<double*>(&this->x), _mm256_div_pd(
		_mm256_load_pd(&this->x),
		_mm256_load_pd(&o.x)
	));
	return (*this);
}
#else
Vector3d&
Vector3d::operator/=(const Vector3d& o) noexcept
{
	this->x /= o.x;
	this->y /= o.y;
	this->z /= o.z;
	return (*this);
}
#endif

					//		+
#if defined(AVX2)
Vector3d
Vector3d::operator+(const Vector3d& o) const noexcept
{
	Vector3d	ret;
	_mm256_store_pd(static_cast<double*>(&ret.x), _mm256_add_pd(
		_mm256_load_pd(&this->x),
		_mm256_load_pd(&o.x)
	));
	return (ret);
}
#else
Vector3d
Vector3d::operator+(const Vector3d& o) const noexcept
{
	Vector3d	ret;
	ret.x = this->x + o.x;
	ret.y = this->y + o.y;
	ret.z = this->z + o.z;
	return (ret);
}
#endif
					//		-
#if defined(AVX2)
Vector3d
Vector3d::operator-(const Vector3d& o) const noexcept
{
	Vector3d	ret;
	_mm256_store_pd(static_cast<double*>(&ret.x), _mm256_sub_pd(
		_mm256_load_pd(&this->x),
		_mm256_load_pd(&o.x)
	));
	return (ret);
}
#else
Vector3d
Vector3d::operator-(const Vector3d& o) const noexcept
{
	Vector3d	ret;
	ret.x = this->x - o.x;
	ret.y = this->y - o.y;
	ret.z = this->z - o.z;
	return (ret);
}
#endif
					//		*
Vector3d
Vector3d::operator*(const Vector3d& o) const noexcept
{
	return (this->Cross(o));
}
					//		/
#if defined(AVX2)
Vector3d
Vector3d::operator/(const Vector3d& o) const noexcept
{
	Vector3d	ret;
	_mm256_store_pd(static_cast<double*>(&ret.x), _mm256_div_pd(
		_mm256_load_pd(&this->x),
		_mm256_load_pd(&o.x)
	));
	return (ret);
}
#else
Vector3d
Vector3d::operator/(const Vector3d& o) const noexcept
{
	Vector3d	ret;
	ret.x = this->x / o.x;
	ret.y = this->y / o.y;
	ret.z = this->z / o.z;
	return (ret);
}
#endif
#pragma endregion





#pragma region OpeWithDouble
#if defined(AVX2)
Vector3d&
Vector3d::operator=(const double& d) noexcept
{

	_mm256_store_pd(&this->x, _mm256_set1_pd(d));
	return (*this);
}
#else
Vector3d&
Vector3d::operator=(const double& d) noexcept
{
	this->x = d;
	this->y = d;
	this->z = d;
	return (*this);
}
#endif
					//		+=
#if defined(AVX2)
Vector3d&
Vector3d::operator+=(const double& d) noexcept
{
	_mm256_store_pd(static_cast<double*>(&this->x),
					_mm256_add_pd(
									_mm256_load_pd(&this->x),
									_mm256_set1_pd(d)
	));
	return (*this);
}
#else
Vector3d&
Vector3d::operator+=(const double& d) noexcept
{
	this->x += d;
	this->y += d;
	this->z += d;
	return (*this);
}
#endif
					//		-=
#if defined(AVX2)
Vector3d&
Vector3d::operator-=(const double& d) noexcept
{
	_mm256_store_pd(static_cast<double*>(&this->x),
					_mm256_sub_pd(
									_mm256_load_pd(&this->x),
									_mm256_set1_pd(d)
	));
	return (*this);
}
#else
Vector3d&
Vector3d::operator-=(const double& d) noexcept
{
	this->x -= d;
	this->y -= d;
	this->z -= d;
	return (*this);
}
#endif
					//		*=
#if defined(AVX2)
Vector3d&
Vector3d::operator*=(const double& d) noexcept
{
	_mm256_store_pd(static_cast<double*>(&this->x),
					_mm256_mul_pd(
									_mm256_load_pd(&this->x),
									_mm256_set1_pd(d)
	));
	return (*this);
}
#else
Vector3d&
Vector3d::operator*=(const double& d) noexcept
{
	this->x *= d;
	this->y *= d;
	this->z *= d;
	return (*this);
}
#endif
					//		/=
#if defined(AVX2)
Vector3d&
Vector3d::operator/=(const double& d) noexcept
{
	_mm256_store_pd(static_cast<double*>(&this->x),
					_mm256_div_pd(
									_mm256_load_pd(&this->x),
									_mm256_set1_pd(d)
	));
	return (*this);
}
#else
Vector3d&
Vector3d::operator/=(const double& d) noexcept
{
	this->x /= d;
	this->y /= d;
	this->z /= d;
	return (*this);
}
#endif

					//		+
#if defined(AVX2)
Vector3d
Vector3d::operator+(const double& d) const noexcept
{
	Vector3d	ret;
	_mm256_store_pd(static_cast<double*>(&ret.x),
					_mm256_add_pd(
									_mm256_load_pd(&this->x),
									_mm256_set1_pd(d)
	));
	return (ret);
}
#else
Vector3d
Vector3d::operator+(const double& d) const noexcept
{
	Vector3d	ret;
	ret.x = this->x + d;
	ret.y = this->y + d;
	ret.z = this->z + d;
	return (ret);
}
#endif
					//		-
#if defined(AVX2)
Vector3d
Vector3d::operator-(const double& d) const noexcept
{
	Vector3d	ret;
	_mm256_store_pd(static_cast<double*>(&ret.x),
					_mm256_sub_pd(
									_mm256_load_pd(&this->x),
									_mm256_set1_pd(d)
	));
	return (ret);
}
#else
Vector3d
Vector3d::operator-(const double& d) const noexcept
{
	Vector3d	ret;
	ret.x = this->x - d;
	ret.y = this->y - d;
	ret.z = this->z - d;
	return (ret);
}
#endif
					//		*
#if defined(AVX2)
Vector3d
Vector3d::operator*(const double& d) const noexcept
{
	Vector3d	ret;
	_mm256_store_pd(static_cast<double*>(&ret.x),
					_mm256_mul_pd(
									_mm256_load_pd(&this->x),
									_mm256_set1_pd(d)
	));
	return (ret);
}
#else
Vector3d
Vector3d::operator*(const double& d) const noexcept
{
	Vector3d	ret;
	ret.x = this->x * d;
	ret.y = this->y * d;
	ret.z = this->z * d;
	return (ret);
}
#endif
					//		/
#if defined(AVX2)
Vector3d
Vector3d::operator/(const double& d) const noexcept
{
	Vector3d	ret;
	_mm256_store_pd(static_cast<double*>(&ret.x),
					_mm256_div_pd(
									_mm256_load_pd(&this->x),
									_mm256_set1_pd(d)
	));
	return (ret);
}
#else
Vector3d
Vector3d::operator/(const double& d) const noexcept
{
	Vector3d	ret;
	ret.x = this->x / d;
	ret.y = this->y / d;
	ret.z = this->z / d;
	return (ret);
}
#endif
#pragma endregion







Vector3d
Vector3d::operator+() const noexcept
{
	return (*this);
}

Vector3d
Vector3d::operator-() const noexcept
{
	Vector3d	ret;
	ret.x = -this->x;
	ret.y = -this->y;
	ret.z = -this->z;
	return (ret);
}

#if defined(AVX2)
bool
Vector3d::operator==(const Vector3d& other) const noexcept
{
	Vector3d	ret;
	_mm256_store_pd(&ret.x, _mm256_cmp_pd(_mm256_load_pd(&this->x), _mm256_load_pd(&other.x), 0x0));
	return (ret.x != 0.0 && ret.y != 0.0 && ret.z != 0.0);
}
#else
bool
Vector3d::operator==(const Vector3d& other) const noexcept
{
	return (this->x == other.x &&
			this->y == other.y &&
			this->z == other.z);
}
#endif

bool
Vector3d::operator!=(const Vector3d& other) const noexcept
{
	return (!this->operator==(other));
}



#if defined(AVX2)
bool
Vector3d::operator==(const double& d) const noexcept
{
	Vector3d	ret;
	_mm256_store_pd(&ret.x, _mm256_cmp_pd(_mm256_load_pd(&this->x), _mm256_set1_pd(d), 0x0));
	return (ret.x != 0.0 && ret.y != 0.0 && ret.z != 0.0);
}
#else
bool
Vector3d::operator==(const double& d) const noexcept
{
	return (this->x == d &&
			this->y == d &&
			this->z == d);
}
#endif

bool
Vector3d::operator!=(const double& d) const noexcept
{
	return (!this->operator==(d));
}
