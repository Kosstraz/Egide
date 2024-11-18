#ifndef NSL_VECTOR3D_HPP
#define NSL_VECTOR3D_HPP

# include <cmath>
# include "TypesCap.hpp"
# include "../NSLSIMDplatform.h"
# include "../NSLplatform.h"

// Class vector3d is a powerful mathematical structure
// Calcul with double
//
// Todo: Produit mixte (Triple produit scalaire)
// Todo: Projection d'un vecteur vers un autre
class alignas(32) Vector3d
{
public:
	Vector3d();
	Vector3d(Vector3d&&);
	Vector3d(const Vector3d&);
	Vector3d(double&&, double&& = 0.0, double&& = 0.0);
	Vector3d(const double&, const double& = 0.0, const double& = 0.0);

	Vector3d	Cross	(const Vector3d& other)	const	noexcept;
	Vector3d	Normalize()						const	noexcept;

	double	Norm()							const	noexcept;
	// Return angle in Radian
	double	GetAngle(const Vector3d& other)	const	noexcept;
	double	Distance(const Vector3d& other)	const	noexcept;
	double	Dot		(const Vector3d& other)	const	noexcept;
	double	Scalar	(const Vector3d& other,
					 const double&	angle = 0.0)	const	noexcept;

	bool	SameDirection		(const Vector3d& other,
								 const double& angle = 0.0)	const noexcept;
	bool	OppositeDirection	(const Vector3d& other,
								 const double& angle = 0.0)	const noexcept;
	bool	IsOrthogonal		(const Vector3d& other,
								 const double& angle = 0.0)	const noexcept;

public:
	double	x;
	double	y;
	double	z;

private:
	double	w;

public:
	Vector3d&	operator=(const Vector3d&)  noexcept;
	Vector3d&	operator+=(const Vector3d&) noexcept;
	Vector3d&	operator-=(const Vector3d&) noexcept;
	Vector3d&	operator*=(const Vector3d&) noexcept;
	Vector3d&	operator/=(const Vector3d&) noexcept;

	Vector3d		operator+(const Vector3d&) const noexcept;
	Vector3d		operator-(const Vector3d&) const noexcept;
	Vector3d		operator*(const Vector3d&) const noexcept;
	Vector3d		operator/(const Vector3d&) const noexcept;


	Vector3d&	operator=(const double&)  noexcept;
	Vector3d&	operator+=(const double&) noexcept;
	Vector3d&	operator-=(const double&) noexcept;
	Vector3d&	operator*=(const double&) noexcept;
	Vector3d&	operator/=(const double&) noexcept;

	Vector3d		operator+(const double&) const noexcept;
	Vector3d		operator-(const double&) const noexcept;
	Vector3d		operator*(const double&) const noexcept;
	Vector3d		operator/(const double&) const noexcept;

	Vector3d		operator+() const noexcept;
	Vector3d		operator-() const noexcept;

	bool		operator==(const Vector3d&) const noexcept;
	bool		operator!=(const Vector3d&) const noexcept;

	bool		operator==(const double&) const noexcept;
	bool		operator!=(const double&) const noexcept;
};

#endif
