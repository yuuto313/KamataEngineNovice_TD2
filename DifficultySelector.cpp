#include "DifficultySelector.h"
#include <imgui.h>

void DifficultySelector::Initialize()
{
	counter_ = 1;

	// 中央のテクスチャデータ
	midTexdata_.texID = Novice::LoadTexture("select_easy.png");

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

		break;
	case Difficulty::Normal:

		//--------------------------------
		// Normalでの更新処理
		//--------------------------------

		break;
	case Difficulty::Hard:

		//--------------------------------
		// Hardでの更新処理
		//--------------------------------

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

	// Normalのテクスチャ（中央）
	Novice::DrawQuad();

	// Hardのテクスチャ（右）


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

void DifficultySelector::InitMidTexturePosition()
{

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
