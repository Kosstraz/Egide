#include "../Vector3f.hpp"

#pragma region Operations
					//		=
#if defined(SSE)
Vector3f&
Vector3f::operator=(const Vector3f& o) noexcept
{
	_mm_store_ps(&this->x, _mm_load_ps(&o.x));
	return (*this);
}
#else
Vector3f&
Vector3f::operator=(const Vector3f& o) noexcept
{
	this->x = o.x;
	this->y = o.y;
	this->z = o.z;
	return (*this);
}
#endif
					//		+=
#if defined(SSE)
Vector3f&
Vector3f::operator+=(const Vector3f& o) noexcept
{
	_mm_store_ps(	static_cast<float*>(&this->x),
					_mm_add_ps(
								_mm_load_ps(&this->x),
								_mm_load_ps(&o.x)
	));
	return (*this);
}
#else
Vector3f&
Vector3f::operator+=(const Vector3f& o) noexcept
{
	this->x += o.x;
	this->y += o.y;
	this->z += o.z;
	return (*this);
}
#endif
					//		-=
#if defined(SSE)
Vector3f&
Vector3f::operator-=(const Vector3f& o) noexcept
{
	_mm_store_ps(	static_cast<float*>(&this->x),
					_mm_sub_ps(
								_mm_load_ps(&this->x),
								_mm_load_ps(&o.x)
	));
	return (*this);
}
#else
Vector3f&
Vector3f::operator-=(const Vector3f& o) noexcept
{
	this->x -= o.x;
	this->y -= o.y;
	this->z -= o.z;
	return (*this);
}
#endif
					//		*=
Vector3f&
Vector3f::operator*=(const Vector3f& o) noexcept
{
	*this = this->Cross(o);
	return (*this);
}
					//		/=
#if defined(SSE)
Vector3f&
Vector3f::operator/=(const Vector3f& o) noexcept
{
	_mm_store_ps(	static_cast<float*>(&this->x),
					_mm_div_ps(
								_mm_load_ps(&this->x),
								_mm_load_ps(&o.x)
	));
	return (*this);
}
#else
Vector3f&
Vector3f::operator/=(const Vector3f& o) noexcept
{
	this->x /= o.x;
	this->y /= o.y;
	this->z /= o.z;
	return (*this);
}
#endif

					//		+
#if defined(SSE)
Vector3f
Vector3f::operator+(const Vector3f& o) const noexcept
{
	Vector3f	ret;
	_mm_store_ps(	static_cast<float*>(&ret.x),
					_mm_add_ps(
								_mm_load_ps(&this->x),
								_mm_load_ps(&o.x)
	));
	return (ret);
}
#else
Vector3f
Vector3f::operator+(const Vector3f& o) const noexcept
{
	Vector3f	ret;
	ret.x = this->x + o.x;
	ret.y = this->y + o.y;
	ret.z = this->z + o.z;
	return (ret);
}
#endif
					//		-
#if defined(SSE)
Vector3f
Vector3f::operator-(const Vector3f& o) const noexcept
{
	Vector3f	ret;
	_mm_store_ps(	static_cast<float*>(&ret.x),
					_mm_sub_ps(
								_mm_load_ps(&this->x),
								_mm_load_ps(&o.x)
	));
	return (ret);
}
#else
Vector3f
Vector3f::operator-(const Vector3f& o) const noexcept
{
	Vector3f	ret;
	ret.x = this->x - o.x;
	ret.y = this->y - o.y;
	ret.z = this->z - o.z;
	return (ret);
}
#endif
					//		*
Vector3f
Vector3f::operator*(const Vector3f& o) const noexcept
{
	return (this->Cross(o));
}
					//		/
#if defined(SSE)
Vector3f
Vector3f::operator/(const Vector3f& o) const noexcept
{
	Vector3f	ret;
	_mm_store_ps(	static_cast<float*>(&ret.x),
					_mm_div_ps(
								_mm_load_ps(&this->x),
								_mm_load_ps(&o.x)
	));
	return (ret);
}
#else
Vector3f
Vector3f::operator/(const Vector3f& o) const noexcept
{
	Vector3f	ret;
	ret.x = this->x / o.x;
	ret.y = this->y / o.y;
	ret.z = this->z / o.z;
	return (ret);
}
#endif
#pragma endregion





#pragma region OpeWithFloat
#if defined(SSE)
Vector3f&
Vector3f::operator=(const float& d) noexcept
{
	_mm_store_ps(&this->x, _mm_set1_ps(d));
	return (*this);
}
#else
Vector3f&
Vector3f::operator=(const float& d) noexcept
{
	this->x = d;
	this->y = d;
	this->z = d;
	return (*this);
}
#endif
					//		+=
#if defined(SSE)
Vector3f&
Vector3f::operator+=(const float& d) noexcept
{
	_mm_store_ps(	static_cast<float*>(&this->x),
					_mm_add_ps(
								_mm_load_ps(&this->x),
								_mm_set1_ps(d)
	));
	return (*this);
}
#else
Vector3f&
Vector3f::operator+=(const float& d) noexcept
{
	this->x += d;
	this->y += d;
	this->z += d;
	return (*this);
}
#endif
					//		-=
#if defined(SSE)
Vector3f&
Vector3f::operator-=(const float& d) noexcept
{
	_mm_store_ps(	static_cast<float*>(&this->x),
					_mm_sub_ps(
								_mm_load_ps(&this->x),
								_mm_set1_ps(d)
	));
	return (*this);
}
#else
Vector3f&
Vector3f::operator-=(const float& d) noexcept
{
	this->x -= d;
	this->y -= d;
	this->z -= d;
	return (*this);
}
#endif
					//		*=
#if defined(SSE)
Vector3f&
Vector3f::operator*=(const float& d) noexcept
{
	_mm_store_ps(	static_cast<float*>(&this->x),
					_mm_mul_ps(
								_mm_load_ps(&this->x),
								_mm_set1_ps(d)
	));
	return (*this);
}
#else
Vector3f&
Vector3f::operator*=(const float& d) noexcept
{
	this->x *= d;
	this->y *= d;
	this->z *= d;
	return (*this);
}
#endif
					//		/=
#if defined(SSE)
Vector3f&
Vector3f::operator/=(const float& d) noexcept
{
	_mm_store_ps(	static_cast<float*>(&this->x),
					_mm_div_ps(
								_mm_load_ps(&this->x),
								_mm_set1_ps(d)
	));
	return (*this);
}
#else
Vector3f&
Vector3f::operator/=(const float& d) noexcept
{
	this->x /= d;
	this->y /= d;
	this->z /= d;
	return (*this);
}
#endif

					//		+
#if defined(SSE)
Vector3f
Vector3f::operator+(const float& d) const noexcept
{
	Vector3f	ret;
	_mm_store_ps(	static_cast<float*>(&ret.x),
					_mm_add_ps(
								_mm_load_ps(&this->x),
								_mm_set1_ps(d)
	));
	return (ret);
}
#else
Vector3f
Vector3f::operator+(const float& d) const noexcept
{
	Vector3f	ret;
	ret.x = this->x + d;
	ret.y = this->y + d;
	ret.z = this->z + d;
	return (ret);
}
#endif
					//		-
#if defined(SSE)
Vector3f
Vector3f::operator-(const float& d) const noexcept
{
	Vector3f	ret;
	_mm_store_ps(	static_cast<float*>(&ret.x),
					_mm_sub_ps(
								_mm_load_ps(&this->x),
								_mm_set1_ps(d)
	));
	return (ret);
}
#else
Vector3f
Vector3f::operator-(const float& d) const noexcept
{
	Vector3f	ret;
	ret.x = this->x - d;
	ret.y = this->y - d;
	ret.z = this->z - d;
	return (ret);
}
#endif
					//		*
#if defined(SSE)
Vector3f
Vector3f::operator*(const float& d) const noexcept
{
	Vector3f	ret;
	_mm_store_ps(	static_cast<float*>(&ret.x),
					_mm_mul_ps(
								_mm_load_ps(&this->x),
								_mm_set1_ps(d)
	));
	return (ret);
}
#else
Vector3f
Vector3f::operator*(const float& d) const noexcept
{
	Vector3f	ret;
	ret.x = this->x * d;
	ret.y = this->y * d;
	ret.z = this->z * d;
	return (ret);
}
#endif
					//		/
#if defined(SSE)
Vector3f
Vector3f::operator/(const float& d) const noexcept
{
	Vector3f	ret;
	_mm_store_ps(	static_cast<float*>(&ret.x),
					_mm_div_ps(
								_mm_load_ps(&this->x),
								_mm_set1_ps(d)
	));
	return (ret);
}
#else
Vector3f
Vector3f::operator/(const float& d) const noexcept
{
	Vector3f	ret;
	ret.x = this->x / d;
	ret.y = this->y / d;
	ret.z = this->z / d;
	return (ret);
}
#endif
#pragma endregion







Vector3f
Vector3f::operator+() const noexcept
{
	return (*this);
}

Vector3f
Vector3f::operator-() const noexcept
{
	Vector3f	ret;
	ret.x = -this->x;
	ret.y = -this->y;
	ret.z = -this->z;
	return (ret);
}

#if defined(AVX)
bool
Vector3f::operator==(const Vector3f& other) const noexcept
{
	Vector3f	ret;
	_mm_store_ps(&ret.x, _mm_cmp_ps(_mm_load_ps(&this->x), _mm_load_ps(&other.x), 0x0));
	return (ret.x != 0.0 && ret.y != 0.0 && ret.z != 0.0);
}
#else
bool
Vector3f::operator==(const Vector3f& other) const noexcept
{
	return (this->x == other.x &&
			this->y == other.y &&
			this->z == other.z);
}
#endif

bool
Vector3f::operator!=(const Vector3f& other) const noexcept
{
	return (!this->operator==(other));
}



#if defined(AVX)
bool
Vector3f::operator==(const float& d) const noexcept
{
	Vector3f	ret;
	_mm_store_ps(&ret.x, _mm_cmp_ps(_mm_load_ps(&this->x), _mm_set1_ps(d), 0x0));
	return (ret.x != 0.0 && ret.y != 0.0 && ret.z != 0.0);
}
#else
bool
Vector3f::operator==(const float& d) const noexcept
{
	return (this->x == d &&
			this->y == d &&
			this->z == d);
}
#endif

bool
Vector3f::operator!=(const float& d) const noexcept
{
	return (!this->operator==(d));
}
