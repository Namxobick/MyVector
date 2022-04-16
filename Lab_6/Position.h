#pragma once
#include <iostream>
#include <cmath>
#include <assert.h>
#include "MyVector.h"

template<class T>

class Position : public MyVector<T>
{
public:
	Position() : MyVector<T>({ 0, 0, 0 }) {};
	Position(T element1, T element2, T element3 = 0) : MyVector<T>({ element1, element2, element3 }) {};
	Position(const Position<T>& position) : MyVector<T>(position) {};
	Position(const MyVector<T>& vector) : MyVector<T>(vector) {};

	void Set(T element1, T element2, T element3 = 0)
	{
		this->_array[0] = element1;
		this->_array[1] = element2;
		this->_array[2] = element3;
	}

	T* Get()
	{
		T* newArray = new T[this->_size];
		for (size_t i = 0; i < this->_size; i++)
			newArray[i] = this->_array[i];
		return newArray;
	}

	T X()
	{
		return this->_array[0];
	}

	T Y()
	{
		return this->_array[1];
	}

	T Z()
	{
		return this->_array[2];
	}

	void Move(MyVector<T> direction)
	{
		*this = (*this + direction);
	}

	void Move(T x, T y, T z)
	{
		*this = (*this + Position(x, y, z));
	}

	void Move(MyVector<T> direction, double space)
	{
		*this = *this + direction.GetNormalized() * space;
	}
};