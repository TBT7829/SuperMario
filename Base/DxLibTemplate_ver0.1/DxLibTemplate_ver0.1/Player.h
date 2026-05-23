#pragma once

#include "Object.h"
#include "Float2.h"
#include "StateMachine.h"

//! @brief プレイヤーキャラクターを表すクラス
//! 移動状態、形態（フォーム）、エフェクト状態をステートマシンで管理
class Player : public Object
{
public:
	//! @brief プレイヤーの移動状態
	enum MOVE_STATE {
		GROUND = 0,	//!< 地面に接地している状態
		JUMP,		//!< ジャンプ中の状態
		FALL		//!< 落下中の状態
	};

	//! @brief プレイヤーのフォーム（形態）
	enum FORM_STATE {
		LOW = 0,	//!< 小さい状態
		TALL,		//!< 大きい状態
		FIRE		//!< ファイア状態
	};

	//! @brief プレイヤーのエフェクト状態
	enum EFFECT_STATE {
		NORMAL = 0,	//!< 通常状態
		STAR		//!< スター状態
	};


	//! @brief コンストラクタ
	//! @param _id オブジェクトID
	Player(int _id);
	//! @brief デストラクタ
	virtual ~Player();

	//! @brief 更新処理
	void update();
	//! @brief 描画処理
	void render();

	//! @brief 地面に接地した時の処理
	//! @param groundY 地面の高さ（Y座標）
	void onLand(float groundY);

	//! @brief プレイヤーの位置座標
	Float2 pos;
	//! @brief プレイヤーのサイズ
	Float2 size;
	//! @brief プレイヤーの移動速度
	Float2 movSpeed;

	//! @brief 移動状態を管理するステートマシン
	StateMachine<Player> moveState;
	//! @brief フォーム状態を管理するステートマシン
	StateMachine<Player> formState;
	//! @brief エフェクト状態を管理するステートマシン
	StateMachine<Player> effectState;
	
	
private:
	//! @brief 地面に接地している時の初期化処理
	void initGround();
	//! @brief 地面に接地している時の更新処理
	void updateGround();
	//! @brief 地面に接地している時の終了処理
	void exitGround();

	//! @brief ジャンプ中の初期化処理
	void initJump();
	//! @brief ジャンプ中の更新処理
	void updateJump();
	//! @brief ジャンプ中の終了処理
	void exitJump();

	//! @brief 落下中の初期化処理
	void initFall();
	//! @brief 落下中の更新処理
	void updateFall();
	//! @brief 落下中の終了処理
	void exitFall();


	//! @brief 小さい状態での更新処理
	void updateLow();
	//! @brief 大きい状態での更新処理
	void updateTall();
};