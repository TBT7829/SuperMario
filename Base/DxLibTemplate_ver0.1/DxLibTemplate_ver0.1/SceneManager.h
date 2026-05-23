#pragma once

#include "Scene.h"


//! @brief Sceneクラスを継承したものをSceneクラスのポインタ配列で一括管理するマネージャークラス
class SceneManager final
{
//-------------------------
// 定数
//-------------------------
public:
	//! @brief Sceneの数
	//! シーンの種類を列挙
	enum SceneType {
		SCENE_NONE = 0,		//	0：画面なし
		SCENE_TITLE,		//	1：タイトル
		SCENE_GAMESELECT,	//	2：ゲームセレクト
		SCENE_DEMO,			//	3：デモムービー
		SCENE_STAGE,		//	4：ステージ
		SCENE_CLEAR,		//	5：クリア
		SCENE_GAMEOVER,		//	6：ゲームオーバー
		SCENE_CLEAR_TIME,	//	7：クリアタイム
		SCENE_PRACTICE,		//	8：練習
		SCENE_MAX_NUM		//	9：シーンの数
	};

	
//-------------------------
// 静的メンバ関数
//-------------------------
public:
	//! @brief シングルトン
	//! @return 自分自身のただ一つの実体のポインタ
	inline static SceneManager* getInstance()
	{
		static SceneManager s_instance;
		return &s_instance;
	}

//-------------------------
// メンバ関数
//-------------------------
private:
	//! @brief コンストラクタ
	SceneManager();

	// プログラム中に実体が一つしか存在しないという
	// シングルトンパターンを保証するために
	// コピーコンストラクタを削除
	// これをしないと実体が複数作れてしまう
	SceneManager(const SceneManager& obj) = delete;

	// プログラム中に実体が一つしか存在しないという
	// シングルトンパターンを保証するために
	// 代入演算子を削除
	SceneManager& operator = (const SceneManager& obj) = delete;

	//! @brief デストラクタ
	~SceneManager();

public:
	//! @brief シーン切り替え関数
	//! @param nextSceneType 
	void changeScene(int nextSceneType);
	//! @brief 更新処理
	void update();
	//! @brief 描画処理
	void render();

//-------------------------
// メンバ関数
//-------------------------
private:
	//! @brief 今のシーンクラスを保存する変数
	Scene* pScene;
	
public:
	//! @brief 今のシーン
	int currentType;
	//! @brief 次のシーン
	int nextType;
	//! @brief ゲームが終了するかどうかを見る変数
	bool gameFinish;


};

