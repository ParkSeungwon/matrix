#include<iostream>
#include"matrix.h"
using namespace std;

template <typename T>
Matrix<T>::Matrix(int w, int h)
{
	width = w;
	height = h;
	alloc();
	for(int y=0; y<height; y++) {
		for(int x=0; x<width; x++) {
			arr[y][x] = 0;
		}
	}
}

template <typename T>
Matrix<T>::Matrix(vector<vector<T>> v)
{
	height = v.size();
	width = v[0].size();
	alloc();
	for(int y=0; y<height; y++) {
		for(int x=0; x<width; x++) {
			arr[y][x] = v[y][x];
		}
	}
}

template <typename T>
void Matrix<T>::alloc()
{
	arr = new T*[height];
	for(int i=0; i<height; i++) arr[i] = new T[width];
}

template <typename T>
void Matrix<T>::release() 
{
	for(int i=0; i<height; i++) delete [] arr[i];
	delete arr;
}

template <typename T>
Matrix<T>::~Matrix() {
	release();
}

template <typename T>
bool Matrix<T>::operator==(const Matrix<T>& r) const
{
	if(width != r.width || height != r.height) return false;
	for(int y=0; y<height; y++) {
		for(int x=0; x<width; x++) {
			if(arr[y][x] != r.arr[y][x]) return false;
		}
	}
	return true;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& r) const
{
	if(width != r.width || height != r.height) throw MatrixException("w, h does not match");
	Matrix<T> m(width, height);
	for(int y=0; y<height; y++) {
		for(int x=0; x<width; x++) {
			m.arr[y][x] = arr[y][x] + r.arr[y][x];
		}
	}
	return m;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& r) const
{
	if(width != r.width || height != r.height) throw MatrixException("w, h does not match");
	Matrix<T> m(width, height);
	for(int y=0; y<height; y++) {
		for(int x=0; x<width; x++) {
			m.arr[y][x] = arr[y][x] - r.arr[y][x];
		}
	}
	return m;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& r) const
{
	if(width != r.height) throw MatrixException("w, h does not match");
	Matrix<T> m(r.width, height);
	for(int y=0; y<height; y++) {
		for(int x=0; x<r.width; x++) {
			for(int i=0; i<width; i++) m.arr[y][x] = m.arr[y][x] + arr[y][i] * r.arr[i][x];
		}
	}
	return m;
}

template <typename T>
void Matrix<T>::show()
{
	for(int y=0; y<height; y++) {
		for(int x=0; x<width; x++) {
			cout << arr[y][x] << ' ';
		}
		cout << endl;
	}
}
	
template <typename T>
Matrix<T> Matrix<T>::surround(T wall) const
{
	Matrix<T> m(width+2, height+2);
	for(int x=0; x<width+2; x++) {
		m.arr[0][x] = wall;
		m.arr[height+1][x] = wall;
	}
	for(int y=1; y<height+1; y++) {
		m.arr[y][0] = wall;
		m.arr[y][width+1] = wall;
	}
	for(int y=0; y<height; y++) {
		for(int x=0; x<width; x++) {
			m.arr[y+1][x+1] = arr[y][x];
		}
	}
	return m;
}

template <typename T>
Matrix<T> Matrix<T>::inverse() const
{
	if(!((width == 3 && height == 3) || (width == 2 && height == 2)))
		throw MatrixException("only 2X2 3X3 Matrix is supported!");
	Matrix<T> m(width, height);
	if(width == 2) {
		T a = arr[0][0];
		T b = arr[0][1];
		T c = arr[1][0];
		T d = arr[1][1];
		if(a*d - b*c == 0) throw MatrixException("No inverse ");
		T e = 1/(a*d-b*c);
		m.arr[0][0] = d*e;
		m.arr[1][1] = a*e;
		m.arr[0][1] = -b*e;
		m.arr[1][0] = -c*e;
	} else {
		T a = arr[0][0];
		T b = arr[0][1];
		T c = arr[0][2];
		T d = arr[1][0];
		T e = arr[1][1];
		T f = arr[1][2];
		T g = arr[2][0];
		T h = arr[2][1];
		T i = arr[2][2];
		T j = a*e*i - a*f*h - b*d*i + b*f*g + c*d*h - c*e*g;
		if(j == 0) throw MatrixException("No inverse ");
		j = 1 / j;
		m.arr[0][0] = e*i - f*h;
		m.arr[0][1] = c*h - b*i;
		m.arr[0][2] = b*f - c*e;
		m.arr[1][0] = f*g - d*i;
		m.arr[1][1] = a*i - c*g;
		m.arr[1][2] = c*d - a*f;
		m.arr[2][0] = d*h - e*g;
		m.arr[2][1] = b*g - a*h;
		m.arr[2][2] = a*e - b*d;
		for(int y=0; y<3; y++) for(int x=0; x<3; x++) m.arr[y][x] *= j;
	}
	return m;
}

template <typename T>
Matrix<T> Matrix<T>::E() const
{
	if(width != height) throw MatrixException("w, h does not match");
	Matrix<T> m(width, height);
	for(int y=0; y<height; y++) {
		for(int x=0; x<width; x++) {
			if(x == y) m.arr[y][x] = 1;
			else m.arr[y][x] = 0;
		}
	}
	return m;
}

template <typename T>
Matrix<T> Matrix<T>::One() const
{
	Matrix<T> m(width, height);
	for(int y=0; y<height; y++) {
		for(int x=0; x<width; x++) {
			m.arr[y][x] = 1;
		}
	}
	return m;
}

