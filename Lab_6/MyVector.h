#pragma once
#include <iostream>
#include <cmath>
#include <assert.h>

# define PI 3.14159265358979323846 
# define Enter '\n'

template<class T>

class MyVector
{
protected:
	size_t _maxSize, _size;
	T* _array;

	void ExpandMemory();

	template<class T1>
	friend std::ostream& operator << (std::ostream& out, const MyVector<T1>& vector);

	template<class T1>
	friend std::istream& operator >> (std::istream& in, MyVector<T1>& vector);

public:
	MyVector();
	MyVector(T element);
	MyVector(size_t size);
	MyVector(std::initializer_list<T> array);
	MyVector(T* array, size_t size);
	MyVector(const MyVector<T>& vector);
	~MyVector();

	void Add(T object);
	size_t Size() const;

	T& operator[](const size_t i) const;
	MyVector<T>operator+(const MyVector<T>& vector) const;
	MyVector<T>operator-(const MyVector<T>& vector) const;
	MyVector<T> operator* (const MyVector<T>& vector) const;
	MyVector<T> operator* (const T& vector) const;
	MyVector<T>& operator=(const MyVector<T>& vector);

	template<class T1>
	operator MyVector<T1>()
	{
		MyVector<T1> vector((size_t)_size);

		for (size_t i = 0; i < _size; i++)
		{
			vector[i] = (T1)(_array[i]);
		}
		return vector;
	}

	T DotProduct(const MyVector<T>& vector) const;
	double GetMagnitude() const;
	MyVector<T> GetNormalized() const;
	double Angle(const MyVector<T>& vector) const;
};

template<class T>
inline void MyVector<T>::ExpandMemory()
{
	_maxSize *= 2;

	T* array = new T[_size];
	array = _array;

	_array = new T[_maxSize];

	for (size_t i = 0; i < _size; i++)
		_array[i] = array[i];
}

template<class T>
inline MyVector<T>::MyVector()
{
	_size = 0;
	_maxSize = 2;
	_array = new T[_maxSize];
}

template<class T>
inline MyVector<T>::MyVector(T element)
{
	_size = 0;
	_maxSize = 1 + _size * 2;
	_array = new T[_maxSize];
	this->Add(element);
}

template<class T>
inline MyVector<T>::MyVector(size_t size)
{
	_size = size;
	_maxSize = 1 + _size * 2;
	_array = new T[_maxSize];
}

template<class T>
inline MyVector<T>::MyVector(std::initializer_list<T> array)
{
	_size = 0;
	_maxSize = 1 + array.size() * 2;
	_array = new T[_maxSize];

	for (auto element : array)
		this->Add(element);
}

template<class T>
inline MyVector<T>::MyVector(T* array, size_t size)
{
	_size = size;
	_maxSize = 1 + _size * 2;
	_array = new T[_maxSize];

	for (size_t i = 0; i < _size; i++)
	{
		_array[i] = array[i];
	}
}

template<class T>
inline MyVector<T>::MyVector(const MyVector<T>& vector)
{
	_size = vector._size;
	_maxSize = vector._maxSize;
	_array = new T[_maxSize];

	for (size_t i = 0; i < _size; i++)
	{
		_array[i] = vector._array[i];
	}
}

template<class T>
inline MyVector<T>::~MyVector()
{
	delete [] _array;
}

template<class T>
inline void MyVector<T>::Add(T object)
{
	if (_size == _maxSize)
		ExpandMemory();

	_array[_size] = object;
	_size++;
}

template<class T>
inline size_t MyVector<T>::Size() const
{
	return _size;
}

template<class T>
inline T& MyVector<T>::operator[](const size_t i) const
{
	assert (i < _size);
	return _array[i];
}

template<class T>
inline MyVector<T> MyVector<T>::operator+(const MyVector<T>& vector) const
{
	MyVector<T> sum;

	int size = std::min(_size, vector._size);

	for (size_t i = 0; i < size; i++)
	{
		sum.Add(vector._array[i] + _array[i]);
	}

	for (size_t i = size; i < _size; i++)
	{
			sum.Add(_array[i]);
	}
		
	for (size_t i = size; i < vector._size; i++)
	{
			sum.Add(vector._array[i]);
	}

	return sum;
}

template<class T>
inline MyVector<T> MyVector<T>::operator-(const MyVector<T>& vector) const
{
	MyVector<T> difference;

	if (_size > vector._size)
	{
		for (size_t i = 0; i < _size - vector._size; i++)
		{
			vector.Add(0);
		}
	}
	else
	{
		for (size_t i = 0; i < vector._size - _size; i++)
		{
			Add(0);
		}
	}

	for (size_t i = 0; i < _size; i++)
	{
		difference.Add(_array[i] - vector._array[i]);
	}

	return difference;
}

template<class T>
inline MyVector<T> MyVector<T>::operator*(const MyVector<T>& vector) const
{
	MyVector<T> product;
	size_t size = std::min(_size, vector._size);
	if (_size != vector._size)
		std::cout << "Vectors of different lengths. The resulting vector has a minimum size (size = " << size << ")" << std::endl;


	for (size_t i = 0; i < size; i++)
	{
		product.Add(vector._array[i] * _array[i]);
	}

	return product;
}

template<class T>
inline MyVector<T> MyVector<T>::operator*(const T& vector) const
{
	MyVector<T> product;

	for (size_t i = 0; i < _size; i++)
	{
		product.Add(_array[i] * vector);
	}

	return product;
}

template<class T>
inline MyVector<T>& MyVector<T>::operator=(const MyVector<T>& vector)
{
	delete [] _array;
	_size = 0;
	_maxSize = 2;
	_array = new T[_maxSize];

	for (size_t i = 0; i < vector._size; i++)
	{
		this->Add(vector[i]);
	}
	return *this;
}

template<class T1>
inline std::ostream& operator<<(std::ostream& out, const MyVector<T1>& complex)
{
	for (size_t i = 0; i < complex._size ; i++)
	{
		out << complex._array[i] << " ";
	}
	return out << std::endl;;
}

template<class T1>
inline std::istream& operator>>(std::istream& in, MyVector<T1>& complex)
{
	T1 element;

	do 
	{
		in >> element;
		complex.Add(element);
	} while (in && in.get() != Enter);

	return in;
}

template<class T>
inline T MyVector<T>::DotProduct(const MyVector<T>& vector) const
{
	T product = 0;
	int size = std::min(_size, vector._size);

	if (_size != vector._size)
		std::cout << "Vectors of different lengths. The resulting vector has a minimum size (size = " << size << ")" << std::endl;

	for (size_t i = 0; i < size; i++)
	{
		product += _array[i] * vector[i];
	}

	return product;
}

template<class T>
inline double MyVector<T>::GetMagnitude() const
{
	double result = 0;

	for (size_t i = 0; i < _size; i++)
	{
		result += pow(_array[i], 2);
	}

	return sqrt(result);
}

template<class T>
inline MyVector<T> MyVector<T>::GetNormalized() const
{
	MyVector<T> normalized;
	double magnitude = GetMagnitude();
	for (size_t i = 0; i < _size; i++)
	{
		normalized.Add(_array[i] / magnitude);
	}
	return normalized;
}

template<class T>
inline double MyVector<T>::Angle(const MyVector<T>& vector) const
{
	double cosAngle = this->DotProduct(vector) / (this->GetMagnitude() * vector.GetMagnitude());

	return acos(cosAngle) * 180 / PI;
}