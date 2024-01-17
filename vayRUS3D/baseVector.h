#pragma once
namespace UreTechEngine {
	struct vector4 {
		double x = 0;
		double y = 0;
		double z = 0;
		double w = 0;
		vector4(double _x = 0.0, double _y = 0.0, double _z = 0.0, double _w = 0.0) {
			x = _x;
			y = _y;
			z = _z;
			w = _w;
		}
		float fx() {
			return float(x);
		}
		float fy() {
			return float(y);
		}
		float fz() {
			return float(z);
		}
		float fw() {
			return float(w);
		}
	};
	struct vector3 {
		double x = 0;
		double y = 0;
		double z = 0;
		vector3(double _x=0.0, double _y = 0.0, double _z = 0.0) {
			x = _x;
			y = _y;
			z = _z;
		}
		void addX(double _x) {
			x += _x;
		}
		void addY(double _y) {
			y += _y;
		}
		void addZ(double _z) {
			z += _z;
		}
		float fx() {
			return float(x);
		}
		float fy() {
			return float(y);
		}
		float fz() {
			return float(z);
		}
	};
	struct vector2 {
		double x = 0;
		double y = 0;
	};
	struct vector {
		double x = 0;
	};
}