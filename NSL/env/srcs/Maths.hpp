#ifndef NSL_MATHS_HPP
#define NSL_MATHS_HPP

# include "../NSLplatform.h"

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
