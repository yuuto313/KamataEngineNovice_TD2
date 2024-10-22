#pragma once
#include <cstdint>


class TitleScene {
public:

	void Initialize();

	void Update();

	void Draw();

private:
	// メンバ変数

	// タイトルバーのテクスチャハンドル
	uint32_t titleBarTexID_ = 0;

	int originalWidth_ = 600;
	int originalHeight_ = 250;

	int width_;
	int height_;

	int x1_;
	int x2_;
	int y1_;
	int y2_;

	// UIのテクスチャハンドル
	uint32_t uiTexID_ = 0;

	// 
	static inline const float kDuration = 3.0f;

	// 経過時間カウント
	float counter_ = 0.0f;

	// 増加フラグ
	bool isIncreasing_ = true;

	// uiテクスチャの色
	int uiColor_ = {};

	int red_;
	int green_;
	int blue_;
	int alpha_;

	// メンバ関数

	// UIの点滅処理
	void UpdateUI();

	// 色を設定
	unsigned int GetColor(int red, int green, int blue, int alpha);

	/// <summary>
	/// 四角形の座標を設定
	/// </summary>
	void InitRectPostion();

	void UpdateRectPostition();

	void SetRectPosition();

};