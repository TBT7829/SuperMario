#pragma once

#include "Scene.h"


//! @brief Sceneを継承したタイトルクラス
class Title : public Scene
{
	//-------------------------
	// メンバ関数
	//-------------------------
private:
	//! @brief デストラクタ
	virtual ~Title();

public:
	//! @brief コンストラクタ
	Title();
	//! @brief 初期化処理
	void init();
	//! @brief 更新処理
	void update();
	//! @brief 描画処理
	void render();
	//! @brief 終了処理
	void exit();

	//-------------------------
	// メンバ変数
	//-------------------------
private:
	//! @brief 背景を保存する変数
	int imageBG;

public:
	//! @brief 一時停止(ポーズ)しているかを判断する変数
	bool poseFlag;
	//! @brief 次のシーン
	int nextScene;

};
