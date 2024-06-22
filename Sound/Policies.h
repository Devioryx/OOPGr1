#pragma once

#include <exception>
#include <stdexcept>
#include "Sample.hpp"

template<typename T>
struct Amplify
{
	Amplify(const double coefficient)
		: coefficient(coefficient) {}

	Sample<T> operator()(const Sample<T>& sample, const std::size_t index) const
	{
		return Sample<T>(sample.getValue() * coefficient, sample.getLimit());
	};

	double coefficient;
};

template<typename T>
struct Invert
{
	Sample<T> operator()(const Sample<T>& sample, const std::size_t index) const
	{
		T value = sample.getValue();

		return Sample<T>(value > 0 ? -value : value, sample.getLimit());
	}
};