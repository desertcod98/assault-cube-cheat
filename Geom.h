#pragma once

struct Vec3 {
	float x, y, z;

	Vec3 operator-(const Vec3& other) const {
		Vec3 result;
		result.x = x - other.x;
		result.y = y - other.y;
		result.z = z - other.z;
		return result;
	}
};

struct view_matrix_t {
	float* operator[ ](int index) {
		return matrix[index];
	}

	float matrix[4][4];
};

Vec3 WorldToScreen(const Vec3 pos, view_matrix_t matrix);
void setRect();
void DrawLine(float StartX, float StartY, float EndX, float EndY);
void DrawBorderBox(int x, int y, int w, int h, int thickness);
void DrawFilledRect(int x, int y, int w, int h);
float Vec3SquareDistance(Vec3 v, Vec3 w);