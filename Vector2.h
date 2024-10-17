#pragma once

/// <summary>
/// 2次元ベクトル
/// </summary>
struct Vector2 final {
	float x;
	float y;

	// 減算オペレーター
	Vector2 operator-(const Vector2& other) const {
		return Vector2(this->x - other.x, this->y - other.y);
	}

	// float との積オペレーター
	Vector2 operator*(float scalar) const {
		return Vector2(this->x * scalar, this->y * scalar);
	}
};
