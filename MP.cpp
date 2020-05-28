#include <iostream>
#include <fstream>
#include "mp.h"
using namespace std;

void render(Components c) {
	int x = 500;
	int y = 500;
	ColorP pix_col;
	ofstream my_Img("h.ppm");
	if (my_Img.is_open()) {
		my_Img << "P3\n" << y << " " << x << " 255\n";
		for (int i = 0; i < x; i++) {
			for (int j = 0; j < y; j++) {
				pix_col = c.traceray(i, j);
				my_Img << (int)pix_col.get_r() << ' ' << (int)pix_col.get_g() << ' ' << (int)pix_col.get_b() << "\n";
			}
		}
		my_Img.close();
	}
	else cout << "Could not open the file";
}

int main() {
	Components components;
	Light light;
	vector<Sphere> sphere;
	Sphere sph1(Vec3(225, 130, 200), 100, ColorP(400, 100, 120));
	Sphere sph2(Vec3(225, 360, 320), 150, ColorP(300, 100, 300));
	sphere.push_back(sph1);
	sphere.push_back(sph2);
	components.add(sphere);
	components.setLight(light);
	render(components);
	return 0;
}
