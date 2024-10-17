#include "Particle.h"
#include "math.h"
#include <Novice.h>
#include <time.h>

void Particle::Initialize()
{

	position_ = { 540.0f + static_cast<float>(rand()) / RAND_MAX * (740.0f - 540.0f), // x = 540 ~ 740
	260.0f + static_cast<float>(rand()) / RAND_MAX * (460.0f - 260.0f) };

	red_ = 0xFF;
	green_ = 0xFF;
	blue_ = 0xFF;
	alpha_ = 0xFF;

	radius_ = 5.0f;

	isFinished_ = false;
	counter_ = 0.0f;
}

void Particle::InitializeRandom()
{
	srand(static_cast<unsigned int>(time(0)));
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
