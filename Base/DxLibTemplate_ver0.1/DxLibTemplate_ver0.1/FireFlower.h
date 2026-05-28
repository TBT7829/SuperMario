#pragma once

#include "Item.h"

//! @brief ファイアフラワークラス
//! @brief Item クラスを継承
//! @brief ハテナブロックから生成される（Yボタン所持時のマリオ用）
//! @brief プレイヤーが接触するとファイア状態に変更される
class FireFlower : public Item
{
public:
	//! @brief コンストラクタ
	//! @param _id オブジェクトID
	//! @param _pos ファイアフラワー出現位置
	FireFlower(int _id, Float2 _pos);

	//! @brief デストラクタ
	virtual ~FireFlower();

	//! @brief 更新処理
	//! @note マッシュルームと同じ物理演算で移動
	void update() override;

	//! @brief 描画処理
	void render() override;

	//! @brief プレイヤーに拾われた時の処理
	//! @note プレイヤーのフォーム変更（FIRE状態へ）
	void onCollectByPlayer() override;

private:
	//! @brief 移動方向（-1=左, 1=右）
	int moveDirection;

	//! @brief 移動速度
	float moveSpeed;

	//! @brief 回転角度（視覚効果用）
	float rotationAngle;
};
