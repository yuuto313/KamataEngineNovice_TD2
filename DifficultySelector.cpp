#include "DifficultySelector.h"
#include <imgui.h>

float EaseInOut(float t) {
	return t < 0.5f ? 2 * t * t : -1 + (4 - 2 * t) * t;
}

void DifficultySelector::Initialize()
{
	counter_ = 1;

	// Easyで使用するテクスチャの情報を初期化
	InitTexData(leftTexData_, "easy.png", 600, 800);

	// Normal使用するテクスチャの情報を初期化
	InitTexData(midTexData_,"normal.png",1200,800);

	// Hardで使用するテクスチャの情報を初期化
	InitTexData(rightTexData_, "hard.png", 1800, 800);

}

void DifficultySelector::Update()
{
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);

	//--------------------------------
	// 選択カウンタの更新
	//--------------------------------

	UpdateDifficultyCounter();

	//--------------------------------
	// 難易度別の更新処理
	//--------------------------------

	switch (difficulty_)
	{
	case Difficulty::None:
		// 何もしない
		break;
	case Difficulty::Easy:

		//--------------------------------
		// Easyでの更新処理
		//--------------------------------

		ResetTexData(rightTexData_);
		ResetTexData(midTexData_);
		UpdateTexData(leftTexData_);

		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
			// Easyで選ばれたことを返す
		}

		break;
	case Difficulty::Normal:

		//--------------------------------
		// Normalでの更新処理
		//--------------------------------

		ResetTexData(leftTexData_);
		ResetTexData(rightTexData_);
		UpdateTexData(midTexData_);
		
		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
			// Normalで選ばれたことを返す
		}

		break;
	case Difficulty::Hard:

		//--------------------------------
		// Hardでの更新処理
		//--------------------------------

		ResetTexData(midTexData_);
		ResetTexData(leftTexData_);
		UpdateTexData(rightTexData_);

		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
			// Hardで選ばれたことを返す
		}

		break;
	default:
		break;
	}

	ImGui::Begin("counter");
	ImGui::Text("%d", counter_);
	ImGui::End();

}

void DifficultySelector::Draw()
{
	// Easyのテクスチャ（左）
	Novice::DrawQuad(leftTexData_.x1, leftTexData_.y1, leftTexData_.x2, leftTexData_.y1,
		leftTexData_.x1, leftTexData_.y2, leftTexData_.x2, leftTexData_.y2,
		0, 0, leftTexData_.width, leftTexData_.height, leftTexData_.texID, 0xFFFFFFFF);
	// Normalのテクスチャ（中央）
	Novice::DrawQuad(midTexData_.x1, midTexData_.y1, midTexData_.x2, midTexData_.y1,
		midTexData_.x1, midTexData_.y2, midTexData_.x2, midTexData_.y2,
		0, 0, midTexData_.width, midTexData_.height, midTexData_.texID, 0xFFFFFFFF);
	// Hardのテクスチャ（右）
	Novice::DrawQuad(rightTexData_.x1, rightTexData_.y1, rightTexData_.x2, rightTexData_.y1,
		rightTexData_.x1, rightTexData_.y2, rightTexData_.x2, rightTexData_.y2,
		0, 0, rightTexData_.width, rightTexData_.height, rightTexData_.texID, 0xFFFFFFFF);

	//--------------------------------
	// 難易度別の描画処理
	//--------------------------------

	switch (difficulty_)
	{
	case Difficulty::None:
		// 何もしない
		break;
	case Difficulty::Easy:

		//--------------------------------
		// Easyでの描画処理
		//--------------------------------

		break;
	case Difficulty::Normal:

		//--------------------------------
		// Normalでの描画処理
		//--------------------------------


		break;
	case Difficulty::Hard:

		//--------------------------------
		// Hardでの描画処理
		//--------------------------------


		break;
	default:
		break;
	}

}

void DifficultySelector::InitTexData(TexData& texData,const char* fileName,int width, int height)
{
	texData.height = 128;
	texData.width = 128;

	texData.scale = 1.0f;

	//--------------------------------
	// 座標を計算
	//--------------------------------

	// ゲーム画面サイズ
	int gameWid = width;
	int gameHeight = height;

	// 中心座標
	int centerX = gameWid / 2;
	int centerY = gameHeight / 2;

	// 4頂点計算
	texData.x1 = centerX - texData.width / 2;
	texData.y1 = centerY - texData.height/ 2;
	texData.x2 = centerX + texData.width / 2;
	texData.y2 = centerY + texData.height / 2;

	texData.prevX1 = texData.x1;
	texData.prevY1 = texData.y1;
	texData.prevX2 = texData.x2;
	texData.prevY2 = texData.y2;

	//--------------------------------
	// textureを読み込む
	//--------------------------------

	texData.texID = Novice::LoadTexture(fileName);
}

void DifficultySelector::UpdateTexData(TexData& texData)
{

	// スケールの進行状況を0から1の範囲で管理
	static float progress = 0.0f;

	// アニメーションの進行状況を更新
	if (scalingUp_) {
		progress += scaleAnimationSpeed_;
		if (progress >= 1.0f) {
			progress = 1.0f;
			scalingUp_ = false;
		}
	} else {
		progress -= scaleAnimationSpeed_;
		if (progress <= 0.0f) {
			progress = 0.0f;
			scalingUp_ = true;
		}
	}

	// イージング関数を使ってスケールを計算
	float easedValue = EaseInOut(progress);
	texData.scale = minScale_ + (maxScale_ - minScale_) * easedValue;

	int width = static_cast<int>(texData.width * texData.scale);
	int height = static_cast<int>(texData.height * texData.scale);

	int centerX = (texData.x1 + texData.x2) / 2;
	int centerY = (texData.y1 + texData.y2) / 2;

	texData.x1 = centerX - width / 2;
	texData.y1 = centerY - height / 2;
	texData.x2 = centerX + width / 2;
	texData.y2 = centerY + height / 2;

}

void DifficultySelector::UpdateDifficultyCounter()
{
	//--------------------------------
	// カウンタを調整
	//--------------------------------

	if (keys[DIK_D] && !preKeys[DIK_D]) {
		counter_ ++;
	}

	if (keys[DIK_A] && !preKeys[DIK_A]) {
		counter_ --;
	}

	if (counter_ < 1) {
		counter_ = 3;
	}

	if (counter_ > 3) {
		counter_ = 1;
	}

	//--------------------------------
	// カウンタの値に応じて難易度を変更する
	//--------------------------------

	switch (counter_) {
	case 1:
		difficulty_ = Difficulty::Easy;
		break;
	case 2:
		difficulty_ = Difficulty::Normal;
		break;
	case 3:
		difficulty_ = Difficulty::Hard;
		break;
	default:
		difficulty_ = Difficulty::None;
		break;
	}

}

void DifficultySelector::ResetTexData(TexData& texData)
{
	texData.scale = 1.0f;
	texData.x1 = texData.prevX1 * static_cast<int>(texData.scale);
	texData.y1 = texData.prevY1 * static_cast<int>(texData.scale);
	texData.x2 = texData.prevX2 * static_cast<int>(texData.scale);
	texData.y2 = texData.prevY2 * static_cast<int>(texData.scale);
}
