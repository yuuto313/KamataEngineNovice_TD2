#include "TitleScene.h"
#include <Novice.h>
#include <algorithm>
#include <cmath>

#define PI 3.14159265f

float easeOutBounce(float t) {
	if (t < 1 / 2.75f) {
		return 7.5625f * t * t;
	} else if (t < 2 / 2.75f) {
		t -= 1.5f / 2.75f;
		return 7.5625f * t * t + 0.75f;
	} else if (t < 2.5 / 2.75) {
		t -= 2.25f / 2.75f;
		return 7.5625f * t * t + 0.9375f;
	} else {
		t -= 2.625f / 2.75f;
		return 7.5625f * t * t + 0.984375f;
	}
}

void TitleScene::Initialize()
{
	//--------------------------------
	// テクスチャ読み込み
	//--------------------------------

	// タイトルバー
	titleBarTexID_ = Novice::LoadTexture("titleBarTex.png");
	InitRectPostion();

	// ui
	uiTexID_ = Novice::LoadTexture("titleUI.png");

	// 矩形の初期サイズを設定
	width_ = originalWidth_;
	height_ = originalHeight_;

	// 色を設定
	red_ = 0xFF;
	green_ = 0xFF;
	blue_ = 0xFF;
	alpha_ = 0xFF;

}

void TitleScene::Update()
{
	UpdateUI();

	UpdateRectPostition();

}

void TitleScene::Draw()
{
	// タイトルバー描画
	Novice::DrawQuad(x1_,y1_,x2_,y1_,x1_,y2_,x2_,y2_,0,0,width_,height_,titleBarTexID_, 0xFFFFFFFF);

	// ui描画
	Novice::DrawSprite(0, 0, uiTexID_, 1.0f, 1.0f, 0.0f, uiColor_);

}

void TitleScene::UpdateUI()
{
	// カウンターをフレームごとに増加させる（60FPSを想定）
	counter_ += 1.0f / 60.0f;

	// 正弦波を使用して、アルファ値を滑らかに変化させる
	// // 0から1の間を変動させる
	float sineValue = (std::sin(counter_ * 2.0f * PI / kDuration) + 1.0f) / 2.0f; 

	// アルファ値を128～255の範囲に
	int minAlpha = 128; // 最小の半透明値
	int maxAlpha = 255; // 最大の不透明値
	alpha_ = static_cast<int>(std::clamp(sineValue * (maxAlpha - minAlpha) + minAlpha, 0.0f, 255.0f));

	// UIの色を更新
	uiColor_ = GetColor(red_, green_, blue_, alpha_);
}

unsigned int TitleScene::GetColor(int red, int green, int blue, int alpha)
{
	return (red << 24) | (green << 16) | (blue << 8) | alpha;
}

void TitleScene::InitRectPostion()
{
	// ゲーム画面サイズ
	int gameWid = 1200;
	int gameHeight = 800;

	// 中心座標
	int centerX = gameWid / 2;
	int centerY = gameHeight / 2;

	// 4頂点計算
	x1_ = centerX -width_ / 2;
	y1_ = centerY -height_ / 2;
	x2_ = centerX + width_ / 2;
	y2_ = centerY + height_ / 2;

	// y座標だけ調整
	int offsetY = 200;
	y1_ = y1_ - offsetY;
	y2_ = y2_ - offsetY;
}

void TitleScene::UpdateRectPostition()
{	
	// 縮小と拡大の段階を設定
	// // 縮小の持続時間
	const float shrinkDuration = 10.0f;  
	// 拡大の持続時間
	const float expandDuration = 6.0f;  

	// カウンターを進行度に変換（0から1の間）
	float totalDuration = shrinkDuration + expandDuration;
	float t = counter_ / totalDuration;

	// アニメーションがループするようにリセット
	if (t >= 1.0f) { 
		// カウンターをリセット
		counter_ = 0.0f; 
		// 進行度もリセット
		t = 0.0f;
	}

	// 縮小と拡大のステージを決定
	float scale;
	if (t < (shrinkDuration / totalDuration)) {
		// 縮小段階 (0からshrinkDurationの間)  
		// 0から1に正規化
		float shrinkT = t / (shrinkDuration / totalDuration); 
		// 1から0に
		scale = 1.0f - easeOutBounce(shrinkT); 
	} else {
		// 拡大段階 (shrinkDurationからtotalDurationの間)
		// 0から1に正規化
		float expandT = (t - (shrinkDuration / totalDuration)) / (expandDuration / totalDuration); 
		// 0から1に 
		scale = easeOutBounce(expandT);  
	}

	// 新しい幅と高さを計算
	int newWidth = static_cast<int>(width_ * scale);
	int newHeight = static_cast<int>(height_ * scale);

	// 矩形の中心を保持するために新しい位置を計算
	int centerX = (x1_ + x2_) / 2;
	int centerY = (y1_ + y2_) / 2;

	// 新しい矩形の座標を計算
	x1_ = centerX - newWidth / 2;
	y1_ = centerY - newHeight / 2;
	x2_ = centerX + newWidth / 2;
	y2_ = centerY + newHeight / 2;

	// カウンターをフレームごとに増加させる（60FPSを想定）
	counter_ += 1.0f / 60.0f;
}

void TitleScene::SetRectPosition()
{
	
}
