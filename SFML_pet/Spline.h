#pragma once
#include <SFML/Graphics.hpp>

namespace my_figures
{

	template <typename ValT>
	class Spline3
	{
	public:
		ValT from;
		ValT mid_1;
		ValT mid_2;
		ValT to;

		ValT GetPoint(float t);
		ValT GetDerivative(float t);
	};

	using Spline3_2d = Spline3<sf::Vector2f>;

	//===vvv template implementations vvv============================================

	template <typename ValT>
	ValT Spline3<ValT>::GetPoint(float t)
	{
		float _t = 1 - t;
		return
			from * (_t * _t * _t) +
			mid_1 * (_t * _t * t * 3) +
			mid_2 * (_t * t * t * 3) +
			to * (t * t * t);
	}

	template <typename ValT>
	ValT Spline3<ValT>::GetDerivative(float t)
	{
		float _t = 1 - t;
		return
			from * (_t * _t * -3) +
			mid_1 * (9 * t * t - 12 * t + 3) +
			mid_2 * (3 * (2 - 3 * t) * t) +
			to * (3 * t * t);
	}
}

