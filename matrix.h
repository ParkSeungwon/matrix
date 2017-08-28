#pragma once
#include<vector>
#include<string>
#include<exception>
#include<cassert>
#include<numeric>

class MatrixException : public std::exception
{
public:
	MatrixException(std::string s) : err_msg(s) {}
	virtual const char* what() const throw() { return err_msg.c_str(); }

protected:
	std::string err_msg;
};

template <typename T>
class Matrix
{
public:
	Matrix(int w, int h) {
		width = w;
		height = h;
		arr = new T[h * w];
		for(int i=0; i<w * h; i++) arr[i] = 0;
	}
	T* operator[](int x) {
		assert(x > 0);
		return arr + (x -1) * height - 1;
	}
	T* data() {return arr;}
	Matrix(std::vector<std::vector<T>> v) {
		width = v[0].size();
		height = v.size();
		for(int x=0; x<width; x++) for(int y=0; y<height; y++) arr[x][y] = v[y][x];
	}
	template <typename T2> Matrix(Matrix<T2>& r);
	virtual ~Matrix() {delete [] arr;}
	Matrix<T> operator+(const Matrix<T>& r) const {
		if(width != r.width || height != r.height) throw "Matrix size not match";
		Matrix<T> m(width, height);
		for(int i=0; i<width*height; i++) m.arr[i] = arr[i] + r.arr[i];
		return m;
	}
	Matrix<T> operator-(const Matrix<T>& r) const {
		if(width != r.width || height != r.height) throw "Matrix size not match";
		Matrix<T> m(width, height);
		for(int i=0; i<width*height; i++) m.arr[i] = arr[i] - r.arr[i];
		return m;
	}
	std::vector<T> row(int y) const{
		std::vector<T> v;
		T* p = arr + y * width - y;
		for(int i=0; i<height; i++) v.push_back(*arr++);
		return v;
	}
	std::vector<T> column(int x) const{
		std::vector<T> v;
		T* p = arr + x - 1;
		for(int i=0; i<width; i++, arr += height) v.push_back(*arr);
		return v;
	}
	Matrix<T> operator*(const Matrix<T>& r) const {
		Matrix<T> m(r.width, height);
		for(int x = 1; x <= r.width; x++) for(int y = 1; y <= height; y++) 
			m[x][y] = std::inner_product(row(y).begin(), row(y).end(), r.column(x), 0);
		return m;
	}
	Matrix<T>& operator=(const Matrix<T>& r);
	Matrix<T> operator*(const T& r) const {return r * *this;}
	bool operator==(const Matrix<T>& r) const;
	friend Matrix<T> operator*(const T l, const Matrix<T>& r) {
		Matrix<T> m(r.width, r.height);
		for(int y=0; y<r.height; y++) {
			for(int x=0; x<r.width; x++) {
				m.arr[y*r.width+x] = l * r.arr[y*r.width+x];
			}
		}
		return m;
	}
	T& operator()(int x, int y) { return arr[y*width+x]; }
	Matrix<T> inverse() const;
	Matrix<T> E() const;
	Matrix<T> One() const;
	Matrix<T> surround(T wall = 0) const;
	void show();
	
protected:
	T* arr;
	int width, height;

private:
	void alloc();
	void release();
};
