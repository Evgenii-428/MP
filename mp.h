#ifndef SPHERE
#define SPHERE

#include "raz.h"
#include "rgb.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <float.h>

const double SELF_AVOID_P = 1e-2;

class Light {
	Vec3 position;
public:
	Light(Vec3 pos = Vec3(0, 0, 0)) :
		position(pos) {}
	Vec3 get_position() {
		return position;
	}
};

class Sphere {
	Vec3 Center;
	double Radius;
	ColorP Color;
public:
	Sphere(Vec3 center, double radius, ColorP color) :
		Center(center), Radius(radius), Color(color) {}
	ColorP get_color() {
		return Color;
	}
	Vec3 get_center() const {
		return Center;
	}
	Vec3 get_normal(const Vec3& p) const {
		return ((p - Center) * (-1 / Radius)).normalize();
	}
	bool intersect(Vec3 O, Vec3 D, double& t) const {
		Vec3 V = O - Center;
		const double b = 2 * V.dot(D);
		const double c = V.dot(V) - Radius * Radius;
		double discr = b * b - 4 * c;
		if (discr < 0) {
			t = FLT_MAX;
			return false;
		}
		const double t1 = (-b - sqrt(discr)) / 2;
		const double t2 = (-b + sqrt(discr)) / 2;
		if (t2 < SELF_AVOID_P) {
			t = FLT_MAX;
			return false;
		}
		t = (t1 >= SELF_AVOID_P) ? t1 : t2;
		return true;
	}
};

class Components {
	vector<Sphere> spheres;
	Light light;
	int N = 0;
public:
	Components() {}
	void add(vector<Sphere>& sph) {
		spheres = sph;
	}
	void setLight(Light l) {
		light = l;
		N = 1;
	}
	ColorP ComputeLighting(Vec3 O, Vec3 D, Sphere& sphere, double t) {
		if (N == 1) {
			Vec3 P = O + D * t;
			Vec3 N = sphere.get_normal(P);
			Vec3 L = (light.get_position() + O - P) * (-1);
			double N_L = N.dot(L);
			double intens = 0.;
			if (N_L > 0) intens = N_L / (N.norm() * (L).norm());
			return (sphere.get_color()).scale_by(intens);
		}
		return ColorP(0, 0, 0);
	}
	ColorP traceray(int x, int y) {
		Vec3 O = Vec3(0, 0, -2000);
		Vec3 D = Vec3(x, y, 2250).normalize();
		double min_t = FLT_MAX;
		double t = FLT_MAX;
		Sphere closest(Vec3(0, 0, 0), 0, ColorP(0, 0, 0));
		int n;
		int len; len = spheres.size();
		for (int i = 0; i < len; i++) {
			if (spheres[i].intersect(O, D, t)) {
				if (min_t > t) {
					closest = spheres[i];
					min_t = t;
					n = 1;
				}
			}
		}
		if (n != 0) return ComputeLighting(O, D, closest, min_t);
		return ColorP(0, 0, 0);
	}
};

#endif
