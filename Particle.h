#pragma once
#include "Vector2.h"
#include <random>

// パーティクル
class Particle
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	unsigned int GetColor(int red, int green, int blue, int alpha) {

		//ビットの調節
		red <<= 24;//11111111 00000000 00000000 00000000 
		green <<= 16;//00000000 11111111 00000000 00000000
		blue <<= 8;//00000000 00000000 11111111 00000000

		int color = red + green + blue + alpha;

		return color;

	}

	/// <summary>
	/// フラグゲッター
	/// </summary>
	/// <returns></returns>
	bool IsFinished()const { return isFinished_; }

private:
	// メンバ変数

	// パーティクルの位置
	Vector2 position_ = {};
	int color_ = {};

	int red_;
	int green_;
	int blue_;
	int alpha_;

	float radius_ = {};


	// 終了フラグ
	bool isFinished_ = false;
	// 存続時間<秒>
	static inline const float kDuration = 2.0f;
	// 経過時間カウンタ
	float counter_ = 0.0f;

};


