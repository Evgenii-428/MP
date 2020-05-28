#ifndef COLOR
#define COLOR

class ColorP {
	int r, g, b;
public:
	ColorP(int red = 0, int green = 0, int blue = 0) : r(red), g(green), b(blue) {}
	int get_r() {
		return r;
	}
	int get_g() {
		return g;
	}
	int get_b() {
		return b;
	}
	ColorP scale_by(double scalar) {
		return (scalar > 0) ? Color_trunc(scalar * r, scalar * g, scalar * b) : ColorP(0, 0, 0);
	}
	static int trunc(int val) {
		return (val > 255) ? 255 : val;
	}
	static ColorP Color_trunc(int red, int green, int blue) {
		return ColorP(trunc(red), trunc(green), trunc(blue));
	}
};

#endif