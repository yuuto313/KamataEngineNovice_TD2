#include "Particle.h"
#include "math.h"
#include <Novice.h>
#include <time.h>

void Particle::Initialize()
{
	// 描画する横幅
	float minWid = 540.0f;
	float maxWid = 740.0f;
	
	// 縦幅
	float minHigh = 260.0f;
	float maxhigh = 460.0f;

	position_ = { minWid + static_cast<float>(rand()) / RAND_MAX * (maxWid - minWid), // x = 540 ~ 740
	minHigh + static_cast<float>(rand()) / RAND_MAX * (maxhigh - minHigh) };// y = 260 ~ 460

	// 色を設定
	red_ = 0xFF;
	green_ = 0xFF;
	blue_ = 0xFF;
	alpha_ = 0xFF;

	// パーティクルの情報
	radius_ = 5.0f;
	isFinished_ = false;
	counter_ = 0.0f;
}

void Particle::Update()
{
	if (isFinished_) {
		return;
	}

	counter_ += 1.0f / 60.0f;

	// 3秒経ったら消える
	if (counter_ >= kDuration) {
		counter_ = kDuration;
		// 終了する
		isFinished_ = true;
	}

	//--------------------------------
	// 画面の中心引き寄せられる
	//--------------------------------

	// 画面の中心
	Vector2 center = { 640.0f,360.0f };

	// 位置の差分を計算
	Vector2 direction = center - position_;

	// 移動速度を設定
	float speed = 100.0f * (1.0f / 60.0f);

	float length = sqrtf(direction.x * direction.x + direction.y * direction.y);

	if (length > 0.001f) {
		direction.x /= length;
		direction.y /= length;
	}

	position_.x += direction.x * speed;
	position_.y += direction.y * speed;

	//--------------------------------
	// 色を徐々に透明に
	//--------------------------------

	//color_.w = std::clamp((kDuration - counter_) / kDuration, 0.0f, 1.0f);

	alpha_--;
	if (alpha_ < 0) {
		alpha_ = 0;
	}

	color_ = GetColor(red_, green_, blue_, alpha_);

	//--------------------------------
	// 半径を小さくする
	//--------------------------------

	radius_ -= 0.1f;

}

void Particle::Draw()
{
	if (isFinished_) {
		return;
	}

	Novice::DrawEllipse((int)position_.x, (int)position_.y, (int)radius_, (int)radius_, 0.0f, color_, kFillModeSolid);
}
