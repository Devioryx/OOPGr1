#pragma once
#include "Effect.h"
#include "Policies.h"

template<typename T>
class Effects
{
public:

	static Effect<T, Amplify<T>> amplifyEffect(const Sound<T>& sound, const double coefficient)
	{
		Amplify<T> amplifyPolicy(coefficient);
		return Effect<T, Amplify<T>>(sound, amplifyPolicy);
	};

	static Effect<T, Invert<T>> invertEffect(const Sound<T>& sound)
	{
		Invert<T> invertPolicy;
		return Effect<T, Invert<T>>(sound, invertPolicy);
	};
};