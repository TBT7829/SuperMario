#pragma once

//#define IS_DEBUG

//---------------------------------------------------------------------------------
//	定数:
//	 画面サイズ、プレイヤー、プレイヤーの弾、ビット、ビットマーカー,マーカーマネージャー関連
//   エネミー、エネミーの弾、その他(単一でいいもの等)
//---------------------------------------------------------------------------------


//-----------------------------------------
//	画面サイズ
//-----------------------------------------

//! @brief 画面の幅
const int WINDOW_WIDTH = 256;
//! @brief 画面の高さ
const int WINDOW_HEIGHT = 240;

//! @brief 画面の半分の幅
const int WINDOW_WIDTH_HALF = WINDOW_WIDTH / 2;
//! @brief 画面の半分の高さ
const int WINDOW_HEIGHT_HALF = WINDOW_HEIGHT / 2;

//-----------------------------------------
//	マップ
//-----------------------------------------

//! @brief マップの列(幅)
const int MAP_COL = 211;
//! @brief マップの行(高さ)
const int MAP_ROW = 15;
//! @brief マップデータの最大数
const int MAP_DATA_NUM = 1;

//! @brief ステージ1の長さ
const int STAGE_1_LENGTH = 3376;

//-----------------------------------------
//	プレイヤー
//-----------------------------------------
//! @brief プレイヤーの加速度
const float PLAYER_ACCEL = 0.25f;
//! @brief プレイヤーの空中加速度
const float PLAYER_ACCEL_AIR = 0.12f;
//! @brief プレイヤーの減速度(摩擦)
const float PLAYER_FRICTION = 0.18f;
//! @brief プレイヤーの歩き最高速度
const float PLAYER_WALK_SPEED_MAX = 2.0f;
//! @brief プレイヤーの走り最高速度
const float PLAYER_RUN_SPEED_MAX = 4.0f;
//! @brief プレイヤーの重力
const float PLAYER_GRAVITY = 0.5f;
//! @brief プレイヤーの最高落下速度
const float PLAYER_FALL_SPEED_MAX = 8.0f;
//! @brief プレイヤーのジャンプ初速
const float PLAYER_INITIAL_JUMP_SPEED = -5.0f;
//! @brief ジャンプ保持フレーム上限数
const int   PLAYER_JUMP_HOLD_FRAME_MAX = 20.0f;
//! @brief ジャンプ保持中の重力軽減値(ジャンプを長くするために、ジャンプボタンを押し続けている間は重力を弱める)
//! @brief SUSTAIN: 持続
const float JUMP_SUSTAIN = 0.12f;

// ジャンプ段階用の倍率（内部実装、ここで調整可能）
static const float JUMP_INIT_MULT_LOW = 1.00f; // 立ち/歩き
static const float JUMP_INIT_MULT_MID = 1.08f; // 中速
static const float JUMP_INIT_MULT_HIGH = 1.12f; // Bダッシュ（最高速）

static const float GRAVITY_MULT_LOW = 1.20f; // 低速時は重力強め（早く落ちる）
static const float GRAVITY_MULT_MID = 1.00f; // 中速は基準
static const float GRAVITY_MULT_HIGH = 1.05f; // 高速時は重力弱め（高く長く飛べる）


//-----------------------------------------
//	ブロック
//-----------------------------------------

constexpr int BLOCK_SIZE = 16;

//! @brief ブロックの上限数
constexpr int BLOCK_MAX = 4000;

//-----------------------------------------
//	エネミー
//-----------------------------------------

//! @brief エネミーの上限数
constexpr int ENEMY_MAX = 120;

//-----------------------------------------
//	その他(単一でいいもの等)
//-----------------------------------------

//! @brief オブジェクトの上限数
const int OBJECT_MAX = 8000;

//! @brief 保存できる音源の数
const int SOUND_INFO_LENGTH = 20;

//! @brief 保存できる画像の数
const int IMAGE_INFO_LENGTH = 128;
//! @brief 画像の拡大率
const int IMAGE_RATE = 1.0f;

