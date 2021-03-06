#include<iostream>
#include"Utils.h"

template<typename T>
class Complex
{
private:
	T _re;
	T _im;

public:
	Complex<T>(T real = 0.0, T imag = 0.0) : _re(real), _im(imag)
	{

	};
	
	Complex<T>(const Complex<T>& c) : _re(c._re), _im(c._im)
	{

	};
	
	inline bool operator ==(const Complex<T>&);
	inline bool operator !=(const Complex<T>&);
	inline bool operator >(const Complex<T>&);
	inline bool operator <(const Complex<T>&);
	inline Complex<T> operator -() const;
	inline Complex<T>& operator +=(const Complex<T>&);
	inline Complex<T>& operator -=(const Complex<T>&);
	inline Complex<T>& operator *=(const Complex<T>&);
	inline Complex<T>& operator /=(const Complex<T>&);
	inline Complex<T> operator +(const Complex<T>&) const;
	inline Complex<T> operator -(const Complex<T>&) const;
	inline Complex<T> operator *(const Complex<T>&) const;
	inline Complex<T> operator /(const Complex<T>&) const;

	inline T Mod()
	{
		return pow(_re, 2) + pow(_im, 2);
	}
	
	template<typename U>
	friend std::ostream& operator <<(std::ostream&, const Complex<U>&);
};

template<typename T>
inline bool Complex<T>::operator==(const Complex<T>& c2)
{
	return Utils::RangeEquality<T>(_re, c2._re) && Utils::RangeEquality<T>(_im, c2._im);
}

template<typename T>
inline bool Complex<T>::operator!=(const Complex<T>& c2)
{
	return !(this->operator==(c2));
}

//Complex number does not have >. I use thie definition to create a sorting
template<typename T>
inline bool Complex<T>::operator>(const Complex<T>& c2)
{
	return pow(_re, 2) + pow(_im, 2) > pow(c2._re, 2) + pow(c2._im, 2);
}

//Complex number does not have <. I use this definition to create a sorting
template<typename T>
inline bool Complex<T>::operator<(const Complex<T>& c2)
{
	return pow(_re, 2) + pow(_im, 2) < pow(c2._re, 2) + pow(c2._im, 2);
}

template<typename T>
inline Complex<T> Complex<T>::operator -() const
{
	return Complex(-_re, -_im);
}

template<typename T>
inline Complex<T>& Complex<T>::operator +=(const Complex<T>& c2)
{
	_re += c2._re;
	_im += c2._im;
	return *this;
}

template<typename T>
inline Complex<T>& Complex<T>::operator -=(const Complex<T>& c2)
{
	return *this += -c2;
}

template<typename T>
inline Complex<T>& Complex<T>::operator *=(const Complex<T>& c2)
{
	T real = _re * c2._re - _im * c2._im;
	T imag = _re * c2._im + _im * c2._re;
	_re = real;
	_im = imag;
	return *this;
}

template<typename T>
inline Complex<T>& Complex<T>::operator /=(const Complex<T>& c2)
{
	Complex<T> nm = Complex<T>(*this) * Complex<T>(c2._re, -c2._im);
	T dn = c2._re * c2._re + c2._im * c2._im;
	_re = nm._re / dn;
	_im = nm._im / dn;
	return *this;
}

template<typename T>
inline Complex<T> Complex<T>::operator +(const Complex<T>& c2) const
{
	return Complex<T>(*this) += c2;
}

template<typename T>
inline Complex<T> Complex<T>::operator -(const Complex<T>& c2) const
{
	return Complex<T>(*this) -= c2;
}

template<typename T>
inline Complex<T> Complex<T>::operator *(const Complex<T>& c2) const
{
	return Complex<T>(*this) *= c2;
}

template<typename T>
inline Complex<T> Complex<T>::operator /(const Complex<T>& c2) const
{
	return Complex<T>(*this) /= c2;
}

template<typename T>
inline std::ostream& operator <<(std::ostream& os, const Complex<T>& c)
{
	os << c._re;
	if (c._im < 0)
		os << c._im << "i";
	else if (c._im > 0)
		os << "+" << c._im << "i";
	return os;
}