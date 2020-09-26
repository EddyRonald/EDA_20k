#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const double maxpoints = 100;

template<class T>
struct Point3D {
	T x,y,z;
	Point3D(T x,T y,T z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Point3D() {this->x = this->y = this->z = (T)0;}
};

template<class T>
class Octree
{
public:
	Point3D<T> A; 
	Point3D<T> B; 
	T ancho;
	vector<Point3D<T> > Points;
	Octree<T>* zero,* one,* two,* thre,* four,* five,* six,* seven;
	Octree();
	Octree(Point3D<T> A, Point3D<T> B, T ancho);
	void Insertar(Point3D<T> P);
	bool Delimitador(Point3D<T>);
};


template<class T>
Octree<T>::Octree() {
	A = new Point3D<T>();
	B = new Point3D<T>();
	this->zero = this->one = this->two = this->thre = this->four = this->five = this->six = this->seven = NULL;
	this->ancho = 0;
}

template<class T>
Octree<T>::Octree(Point3D<T> A, Point3D<T> B, T ancho) {
	this->zero = this->one = this->two = this->thre = this->four = this->five = this->six = this->seven = NULL;
	this->A = A;
	this->B = B;
	this->ancho = ancho;
}

template<class T>
bool Octree<T>::Delimitador(Point3D<T> P) {
	return (P.x >= A.x && P.x <= B.x && P.y >= A.y && P.y <= B.y && P.z <= A.z && P.z >= B.z);
}

template<class T>
void Octree<T>::Insertar(Point3D<T> P) {
	if (!Delimitador(P)) { return; }
	if (Points.size() < maxpoints && zero == NULL && one == NULL && two == NULL && thre == NULL &&
		four == NULL && five == NULL && six == NULL && seven == NULL) {
		Points.push_back(P);
		return;
	}
	else {
		if (Points.size() == 0 && zero != NULL && one != NULL && two != NULL && thre != NULL &&
			four != NULL && five != NULL && six != NULL && seven != NULL) {
			zero->Insertar(P);
			one->Insertar(P);
			two->Insertar(P);
			thre->Insertar(P);
			four->Insertar(P);
			five->Insertar(P);
			six->Insertar(P);
			seven->Insertar(P);
		}
		else {
			vector<Point3D<T> > tempoints;
			tempoints.push_back(P);
			for (int i = 0; i < Points.size(); i++)
			{
				tempoints.push_back(Points[i]);
			}

			T p = ancho / 2;
			five = new Octree(Point3D<T>(A.x + p, A.y + p, A.z), Point3D<T>(A.x + 2 * p, A.y + 2 * p, A.z - p), ancho / 2);
			seven = new Octree(Point3D<T>((B.x + A.x) / 2, (B.y + A.y) / 2, (B.z + A.z) / 2), Point3D<T>(B.x, B.y, B.z), ancho / 2);
			thre = new Octree(Point3D<T>(A.x + p, A.y, A.z), Point3D<T>(A.x + 2 * p, A.y + p, A.z - p), ancho / 2);
			one = new Octree(Point3D<T>(A.x + p, A.y, A.z - p), Point3D<T>(A.x + 2 * p, A.y + p, A.z - 2 * p), ancho / 2);
			four = new Octree(Point3D<T>(A.x, A.y + p, A.z), Point3D<T>(A.x + p, A.y + 2 * p, A.z - p), ancho / 2);
			six = new Octree(Point3D<T>(A.x, A.y + p, A.z - p), Point3D<T>(A.x + p, A.y + 2 * p, A.z - 2 * p), ancho / 2);
			zero = new Octree(Point3D<T>(A.x, A.y, A.z), Point3D<T>((B.x + A.x) / 2, (B.y + A.y) / 2, (B.z + A.z) / 2), ancho / 2);
			two = new Octree(Point3D<T>(A.x, A.y, A.z - p), Point3D<T>(A.x + p, A.y + p, A.z - 2 * p), ancho / 2);


			for (int i = 0; i < tempoints.size(); ++i)
			{
				if (tempoints[i].x >= (A.x + B.x) / 2) 
				{
					if (tempoints[i].y >= (A.y + B.y) / 2) 
					{
						if (tempoints[i].z >= (A.z + B.z) / 2) 
						{
							five->Insertar(tempoints[i]);
						}
						else 
						{
							seven->Insertar(tempoints[i]);
						}
					}
					else 
					{
						if (tempoints[i].z >= (A.z + B.z) / 2) 
						{
							one->Insertar(tempoints[i]);
						}
						else 
						{
							thre->Insertar(tempoints[i]);
						}
					}
				}
				else 
				{
					if (tempoints[i].y >= (A.y + B.y) / 2) 
					{
						if (tempoints[i].z >= (A.z + B.z) / 2) 
						{
							four->Insertar(tempoints[i]);
						}
						else 
						{
							six->Insertar(tempoints[i]);
						}
					}
					else 
					{
						if (tempoints[i].z >= (A.z + B.z) / 2) 
						{
							zero->Insertar(tempoints[i]);
						}
						else 
						{
							two->Insertar(tempoints[i]);
						}
					}
				}
			}

			Points.clear();
		}
	}
}


