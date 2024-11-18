#ifndef NSL_VECTOR3F_HPP
#define NSL_VECTOR3F_HPP

# include <cmath>
# include "TypesCap.hpp"
# include "../NSLSIMDplatform.h"
# include "../NSLplatform.h"

// Class vector3f is a powerful mathematical structure
// Calcul with float
//
// Todo: Produit mixte (Triple produit scalaire)
// Todo: Projection d'un vecteur vers un autre
class alignas(16) Vector3f
{
public:
	Vector3f();
	Vector3f(Vector3f&&);
	Vector3f(const Vector3f&);
	Vector3f(float&&, float&& = 0.0, float&& = 0.0);
	Vector3f(const float&, const float& = 0.0, const float& = 0.0);

	Vector3f	Cross	(const Vector3f& other)	const	noexcept;
	Vector3f	Normalize()						const	noexcept;

	float	Norm()							const	noexcept;
	// Return angle in Radian
	float	GetAngle(const Vector3f& other)	const	noexcept;
	float	Distance(const Vector3f& other)	const	noexcept;
	float	Dot		(const Vector3f& other)	const	noexcept;
	float	Scalar	(const Vector3f& other,
					 const float&	angle = 0.0)	const	noexcept;

	bool	SameDirection		(const Vector3f& other,
								 const float& angle = 0.0)	const noexcept;
	bool	OppositeDirection	(const Vector3f& other,
								 const float& angle = 0.0)	const noexcept;
	bool	IsOrthogonal		(const Vector3f& other,
								 const float& angle = 0.0)	const noexcept;

public:
	float	x;
	float	y;
	float	z;

private:
	float	w;

public:
	Vector3f&	operator=(const Vector3f&)  noexcept;
	Vector3f&	operator+=(const Vector3f&) noexcept;
	Vector3f&	operator-=(const Vector3f&) noexcept;
	Vector3f&	operator*=(const Vector3f&) noexcept;
	Vector3f&	operator/=(const Vector3f&) noexcept;

	Vector3f		operator+(const Vector3f&) const noexcept;
	Vector3f		operator-(const Vector3f&) const noexcept;
	Vector3f		operator*(const Vector3f&) const noexcept;
	Vector3f		operator/(const Vector3f&) const noexcept;


	Vector3f&	operator=(const float&)  noexcept;
	Vector3f&	operator+=(const float&) noexcept;
	Vector3f&	operator-=(const float&) noexcept;
	Vector3f&	operator*=(const float&) noexcept;
	Vector3f&	operator/=(const float&) noexcept;

	Vector3f		operator+(const float&) const noexcept;
	Vector3f		operator-(const float&) const noexcept;
	Vector3f		operator*(const float&) const noexcept;
	Vector3f		operator/(const float&) const noexcept;

	Vector3f		operator+() const noexcept;
	Vector3f		operator-() const noexcept;

	bool		operator==(const Vector3f&) const noexcept;
	bool		operator!=(const Vector3f&) const noexcept;

	bool		operator==(const float&) const noexcept;
	bool		operator!=(const float&) const noexcept;
};

#endif
