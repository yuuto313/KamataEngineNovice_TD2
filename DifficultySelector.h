#pragma once
#include <cmath>
#include <Novice.h>
#include "Vector2.h"

enum class Difficulty : uint32_t{
	None,
	Easy,
	Normal,
	Hard,
};

struct TexData
{
	int x1;
	int y1;
	int x2;
	int y2;

	// 以前の座標を保存するための変数
	int prevX1;
	int prevY1;
	int prevX2;
	int prevY2;

	int width;
	int height;
	
	float scale;

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

	// left = Easy
	TexData leftTexData_;

	// mid = Normal
	TexData midTexData_;

	// right = Hard
	TexData rightTexData_;


	// スケーリングの可不可
	bool scalingUp_ = true; 
	// スケーリングするスピード
	float scaleAnimationSpeed_ = 0.01f; 
	// Speed of scaling animation
	// スケール最小
	const float minScale_ = 0.8f;    
	// スケール最大
	const float maxScale_ = 1.2f;       
private:
	// メンバ関数

	/// <summary>
	/// テクスチャ情報を初期化
	/// </summary>
	void InitTexData(TexData& texData,const char* fileName,int width,int height);

	/// <summary>
	/// テクスチャ情報を更新
	/// </summary>
	void UpdateTexData(TexData& texData);

	/// <summary>
	/// カウンタを調整
	/// </summary>
	void UpdateDifficultyCounter();

	/// <summary>
	/// テクスチャ情報をリセット
	/// </summary>
	void ResetTexData(TexData& texData);
};

