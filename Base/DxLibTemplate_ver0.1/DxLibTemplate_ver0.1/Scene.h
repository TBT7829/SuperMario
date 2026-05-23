#pragma once



//	抽象クラスなので実体(インスタンス)を作ることができない。
//	また基底クラスから派生したクラスは、
//	絶対に純粋仮想関数と同じ名前の関数を持つ必要がある。

//! @brief それぞれのシーンに継承させる基底クラス
class Scene 
{
//-------------------------
// メンバ関数
//-------------------------
public:
	//	= 0がついてるので純粋仮想関数となり
	//	Sceneクラスは抽象クラスとなる

	//! @brief 初期化処理
	virtual void init() = 0;

	//! @brief 更新処理
	virtual void update() = 0;

	//! @brief 描画処理
	virtual void render() = 0;

	//! @brief 終了処理
	virtual void exit() = 0;

};
