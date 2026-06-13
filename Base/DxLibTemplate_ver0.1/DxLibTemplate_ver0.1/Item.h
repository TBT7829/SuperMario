#pragma once

#include "Object.h"
#include "Float2.h"

//! @brief アイテムの基底クラス
//! @brief Objectを継承し、マリオ内のアイテム全般を管理する
//! @brief コイン、マッシュルーム、ファイアフラワーなど拡張可能
class Item : public Object
{
public:
	//! @brief コンストラクタ
	//! @param _id オブジェクトID
	//! @param _itemType アイテムの種類
	//! @param _pos アイテムの生成位置
	Item(int _id, OBJECT_TYPE _itemType, Float2 _pos);

	//! @brief デストラクタ
	virtual ~Item();

	//! @brief 更新処理（抽象メソッド）
	virtual void update() override = 0;

	//! @brief 描画処理（抽象メソッド）
	virtual void render() override = 0;

	//! @brief プレイヤーに拾われた時の処理
	//! @note CollisionManagerから呼び出される
	virtual void onCollectByPlayer() = 0;

	//! @brief 座標
	Float2 pos;

	//! @brief サイズ
	Float2 size;

	//! @brief 速度
	Float2 velocity;

	//! @brief 画面外チェック用フラグ
	bool isOffScreen;

protected:
	//! @brief 初期化処理
	virtual void activateProc() override;

	//! @brief 終了処理
	virtual void deactiveProc() override;
};
