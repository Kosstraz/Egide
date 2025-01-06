#ifndef EGIDE_MATHS_HPP
#define EGIDE_MATHS_HPP

# include "../egide_platform.h"

// For mathematical calculations
namespace Maths
{

inline static constexpr double	Pi = 3.14159265359;

inline float	DegToRad(const float& deg)
{
	return (deg * (static_cast<float>(Maths::Pi) / 180.0f));
}

inline float	RadToDeg(const float& rad)
{
	return (rad * (180.0f / static_cast<float>(Maths::Pi)));
}

}

#endif
