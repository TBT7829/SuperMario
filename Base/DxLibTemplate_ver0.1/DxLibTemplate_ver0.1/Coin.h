#pragma once

#include "Item.h"

//! @brief コインクラス
//! @brief Item クラスを継承
//! @brief ハテナブロックやコインブロックから生成される
//! @brief プレイヤーが接触するとスコア加算
class Coin : public Item
{
public:
	//! @brief コンストラクタ
	//! @param _id オブジェクトID
	//! @param _pos コイン出現位置
	Coin(int _id, Float2 _pos);

	//! @brief デストラクタ
	virtual ~Coin();

	//! @brief 更新処理
	//! @note 浮き上がる物理演算を実装
	void update() override;

	//! @brief 描画処理
	void render() override;

	//! @brief プレイヤーに拾われた時の処理
	//! @note スコア加算、サウンド再生などをCollisionManager経由で実行
	void onCollectByPlayer() override;

private:
	//! @brief 出現フレーム
	int spawnFrame;

	//! @brief ライフタイム（表示フレーム数）
	int lifetimeFrames;

	//! @brief 垂直速度（重力の影響で変化）
	float verticalVelocity;


	//! @brief 回転角度（描画時の視覚効果用）
	float rotationAngle;
};