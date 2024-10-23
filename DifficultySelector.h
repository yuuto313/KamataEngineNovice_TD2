#pragma once
#include <cmath>
#include <Novice.h>

enum class Difficulty : uint32_t{
	None,
	Easy,
	Normal,
	Hard,
};

struct MidTexData
{
	int x1;
	int y1;
	int x2;
	int y2;

	uint32_t texID;
};

/// <summary>
/// 難易度選択クラス
/// </summary>
class DifficultySelector
{
public:

	void Initialize();

	void Update();

	void Draw();

private:
	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// 入力を受け取るカウンタ
	uint32_t counter_ = 1;

	//　難易度（初期はイージー）
	Difficulty difficulty_ = Difficulty::Easy;

	MidTexData midTexdata_;

private:
	// メンバ関数

	/// <summary>
	/// 中央のテクスチャの位置を設定
	/// </summary>
	void InitMidTexturePosition();

	/// <summary>
	/// カウンタを調整
	/// </summary>
	void UpdateDifficultyCounter();
};

