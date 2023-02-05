#pragma once

#include "stdafx.h"

struct Vector2 {
	float x, y;

	Vector2() {
		x = y = 0.0f;
	}

	Vector2(float x, float y) {
		this->x = x;
		this->y = y;
	}

	float distance(Vector2 &Vector) {
		return sqrt(distanceEx(Vector));
	}

	float distanceEx(Vector2 &Vector) {
		float _x = this->x - Vector.x, _y = this->y - Vector.y;
		return ((_x * _x) + (_y * _y));
	}
};

struct Vector3 {
	float x, y, z;

	Vector3() {
		x = y = z = 0.0f;
	}

	Vector3(float x, float y, float z) {
		this->x = x; this->y = y; this->z = z;
	}

	bool operator==(Vector3 &Vector) {
		return (this->x == Vector.x && this->y == Vector.y && this->z == Vector.z);
	}

	Vector3& operator+(Vector3 &Vector) {
		return Vector3(this->x + Vector.x, this->y + Vector.y, this->z + Vector.z);
	}

	Vector3& operator-(Vector3 &Vector) {
		return Vector3(this->x - Vector.x, this->y - Vector.y, this->z - Vector.z);
	}

	float distance(Vector3 &Vector) {
		return sqrt(distanceEx(Vector));
	}

	float distanceEx(Vector3 &Vector) {
		float _x = this->x - Vector.x, _y = this->y - Vector.y, _z = this->z - Vector.z;
		return ((_x * _x) + (_y * _y) + (_z * _z));
	}

	float dotProduct(Vector3 &Vector) {
		return (this->x * Vector.x) + (this->y * Vector.y) + (this->z * Vector.z);
	}
};

struct Vector4 {
	float a, b, c, d;

	Vector4() {
		a = b = c = d = 0.0f;
	}

	Vector4(float a, float b, float c, float d) {
		this->a = a;
		this->b = b;
		this->c = c;
		this->d = d;
	}
};