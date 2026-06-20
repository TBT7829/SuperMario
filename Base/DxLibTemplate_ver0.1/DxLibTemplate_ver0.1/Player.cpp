#include "Player.h"
#include "Camera.h"
#include"Const.h"
#include "ImageManager.h"
//#include "SoundManager.h"
#include<DxLib.h>
#include<cmath>

//---------------------------------------------------------------------------------
//	プレイヤーの処理
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------------------------------
Player::Player(int _id) : Object(_id, PLAYER)
{
	pos.x = 100.0f;
	pos.y = 50.0f;
	size.x = size.y = 16.0f;
	movSpeed.x = 0.0f;
	movSpeed.y = 0;
	jumpHoldCounter = 0;
	isRun = false;
	direction = RIGHT;
	currentJumpGravity = PLAYER_GRAVITY;

	// 最初は空中から始まるので「落下中」スタートにする
	// 移動ステートの登録
	moveState.add(GROUND, &Player::initGround, &Player::updateGround, &Player::exitGround);
	moveState.add(RUNNING, &Player::initRunning, &Player::updateRunning, &Player::exitRunning);
	moveState.add(JUMP, &Player::initJump, &Player::updateJump, &Player::exitJump);
	moveState.add(FALL, &Player::initFall, &Player::updateFall, &Player::exitFall);

	moveState.change(FALL);
}

//---------------------------------------------------------------------------------
// デストラクタ
//---------------------------------------------------------------------------------
Player::~Player()
{
}

//---------------------------------------------------------------------------------
// 更新処理
//---------------------------------------------------------------------------------
void Player::update()
{
	

	// シフトキーで走り（左右シフトどちらでも可）
	if(CheckHitKey(KEY_INPUT_LSHIFT) || (CheckHitKey(KEY_INPUT_RSHIFT))) 
	{
		// シフトキーが押されている場合は走り状態を維持する
		isRun = true;
	} 
	else
	{
		// シフトキーが押されていない場合は走り状態を解除する
		isRun = false;
	}

	// 状態の更新
	moveState.update(this);
	formState.update(this);
	effectState.update(this);

	pos.x = max(Camera::getInstance().getOffsetX(), pos.x);
}

//---------------------------------------------------------------------------------
// 描画処理
//---------------------------------------------------------------------------------
void Player::render()
{
	float drawX = Camera::getInstance().worldToScreenX(pos.x);
	DrawBox(drawX, pos.y, drawX + size.x, pos.y + size.y, 0xFF0000, TRUE);


#if 0
	// マネージャーのインスタンスを取得
	ImageManager* pIMGM = ImageManager::getInstance();

	int marioGHandle = pIMGM->IMAGE_PLAYER_IDLE;


	DrawGraph((int)100, (int)110, marioGHandle, TRUE);

	DrawFormatString((int)120, (int)114, GetColor(255, 255, 255), "x %d", m_life);
#endif

}

//---------------------------------------------------------------------------------
// 地面に接地した時の処理
//---------------------------------------------------------------------------------
void Player::onLand(float groundY)
{
	// 位置を床のピッタリ上に合わせる
	pos.y = groundY - size.y;

	// 縦の速度をリセット
	movSpeed.y = 0.0f;

	// ジャンプ保持カウンタをリセット
	jumpHoldCounter = 0;

	// 移動ステートを GROUND に変更
	moveState.change(GROUND);
}

//---------------------------------------------------------------------------------
// 地面に接地している時の初期化処理
//---------------------------------------------------------------------------------
void Player::initGround()
{
}

//---------------------------------------------------------------------------------
// 地面に接地している時の処理
//---------------------------------------------------------------------------------
void Player::updateGround()
{
	// 入力取得
	// 右
	bool right = (CheckHitKey(KEY_INPUT_D) != false);
	// 左
	bool left = (CheckHitKey(KEY_INPUT_A) != false);

	// 現在の入力方向を決める（両方押しは 0 として扱う）
	int inputDir = 0;
	if (right && !left) {
		inputDir = 1;
	}
	else if (left && !right) {
		inputDir = -1;
	}
	else {
		inputDir = 0;
	}

	// 向きの更新(明確に右/左入力があるときだけ行う)
	if (inputDir == 1) direction = RIGHT;
	else if (inputDir == -1) direction = LEFT;

	//最大速度の取得（走り状態なら走り速度、そうでなければ歩き速度）
	float speedMax = isRun ? PLAYER_RUN_SPEED_MAX : PLAYER_WALK_SPEED_MAX;

	// 横方向の加速／減速（滑らかにする）
	if (inputDir == 1) {
		// 右へ加速
		if (movSpeed.x < speedMax) {
			movSpeed.x += PLAYER_ACCEL;
			// 加速しているときに最大速度を超えないようにする
			if (speedMax < movSpeed.x) movSpeed.x = speedMax;
		}
		// もし現在速度が既に目標を超えている場合は減速して目標に合わせる
		else if (speedMax < movSpeed.x) {
			movSpeed.x -= PLAYER_FRICTION;
			if (movSpeed.x < speedMax) movSpeed.x = speedMax;
		}
	}
	else if (inputDir == -1) {
		// 左へ加速
		if (-speedMax < movSpeed.x) {
			movSpeed.x -= PLAYER_ACCEL;
			// 加速しているときに最大速度を超えないようにする
			if (movSpeed.x < -speedMax) movSpeed.x = -speedMax;
		}
		// もし現在速度が既に目標を超えている場合は減速して目標に合わせる
		else if (movSpeed.x < -speedMax) {
			movSpeed.x += PLAYER_FRICTION;
			if (-speedMax < movSpeed.x) movSpeed.x = -speedMax;
		}
	}
	// どちらの方向にも入力がないときは減速する
	else {
		// 入力なし -> 摩擦で減速
		if (movSpeed.x > 0.0f) {
			movSpeed.x -= PLAYER_FRICTION;
			// 減速しているときに0を下回らないようにする
			if (movSpeed.x < 0.0f) movSpeed.x = 0.0f;
		}
		else if (movSpeed.x < 0.0f) {
			movSpeed.x += PLAYER_FRICTION;
			// 減速しているときに0を上回らないようにする
			if (movSpeed.x > 0.0f) movSpeed.x = 0.0f;
		}

		// 小さな値は丸めてゼロにしておく
		if (fabsf(movSpeed.x) < 0.001f) movSpeed.x = 0.0f;
	}

	// 横移動
	//movSpeed.x = 0.0f;
	//if (CheckHitKey(KEY_INPUT_D)) movSpeed.x = 2.0f;
	//if (CheckHitKey(KEY_INPUT_A))  movSpeed.x = -2.0f;

	// x座標の位置更新
	pos.x += movSpeed.x;

	// 着地判定がないので、とりあえず常にFALLへ移行する予備判定を入れる
    // 実際にはCollisionManagerで「床に触れていたらGROUND」にする
    // ここでは「床に触れていないならFALLへ遷移」という仕組みを作る
	moveState.change(FALL);

	
	// ジャンプ
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		moveState.change(JUMP);
	}

}

//---------------------------------------------------------------------------------
// 地面に接地している時の終了処理
//---------------------------------------------------------------------------------
void Player::exitGround()
{

}

//---------------------------------------------------------------------------------
// ダッシュの初期化処理
//---------------------------------------------------------------------------------
void Player::initRunning()
{
	
}

//---------------------------------------------------------------------------------
// ダッシュの更新処理
//---------------------------------------------------------------------------------
void Player::updateRunning()
{
	// 入力取得
	// 右
	bool right = (CheckHitKey(KEY_INPUT_D) != false);
	// 左
	bool left = (CheckHitKey(KEY_INPUT_A) != false);

	// 現在の入力方向を決める（両方押しは 0 として扱う）
	int inputDir = 0;
	if (right && !left) {
		inputDir = 1;
	}
	else if (left && !right) {
		inputDir = -1;
	}
	else {
		inputDir = 0;
	}

	// 向きの更新(明確に右/左入力があるときだけ行う)
	if (inputDir == 1) direction = RIGHT;
	else if (inputDir == -1) direction = LEFT;

	// Shiftが離れたら通常地上状態へ(自然な減速は GROUND 側で行わせる)
	if (!isRun) {
		moveState.change(GROUND);
		return;
	}

	// 走り時は走り最高速度へ向かって加速
	if (inputDir == 1) {
		// 右へ加速
		if (movSpeed.x < PLAYER_RUN_SPEED_MAX) {
			movSpeed.x += PLAYER_ACCEL;
			// 加速しているときに最大速度を超えないようにする
			if (movSpeed.x > PLAYER_RUN_SPEED_MAX) movSpeed.x = PLAYER_RUN_SPEED_MAX;
		}
		// もし現在速度が既に目標を超えている場合は減速して目標に合わせる
		else if (PLAYER_RUN_SPEED_MAX < movSpeed.x) {
			movSpeed.x -= PLAYER_FRICTION;
			if (movSpeed.x < PLAYER_RUN_SPEED_MAX) movSpeed.x = PLAYER_RUN_SPEED_MAX;
		}
	}
	// 左へ加速
	else if (inputDir == -1) {
		if (movSpeed.x > -PLAYER_RUN_SPEED_MAX) {
			movSpeed.x -= PLAYER_ACCEL;
			// 加速しているときに最大速度を超えないようにする
			if (movSpeed.x < -PLAYER_RUN_SPEED_MAX) movSpeed.x = -PLAYER_RUN_SPEED_MAX;
		}
		else if (movSpeed.x < -PLAYER_RUN_SPEED_MAX) {
			movSpeed.x += PLAYER_FRICTION;
			if (-PLAYER_RUN_SPEED_MAX < movSpeed.x) movSpeed.x = -PLAYER_RUN_SPEED_MAX;
		}
	}
	else {
		// 入力なしなら摩擦で減速
		if (movSpeed.x > 0.0f) {
			movSpeed.x -= PLAYER_FRICTION;
			if (movSpeed.x < 0.0f) movSpeed.x = 0.0f;
		}
		else if (movSpeed.x < 0.0f) {
			movSpeed.x += PLAYER_FRICTION;
			if (movSpeed.x > 0.0f) movSpeed.x = 0.0f;
		}
		
		// 小さな値は丸めてゼロにしておく
		if (fabsf(movSpeed.x) < 0.001f) movSpeed.x = 0.0f;
	}

	// 位置更新
	pos.x += movSpeed.x;

	// FALLに遷移(CollisionManager が実際の判定をする)
	moveState.change(FALL);

	// ジャンプ入力
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		moveState.change(JUMP);

	}
}

//---------------------------------------------------------------------------------
// ダッシュの終了処理
//---------------------------------------------------------------------------------
void Player::exitRunning()
{
	// 必要ならここで処理
}

//---------------------------------------------------------------------------------
// ジャンプ中の初期化処理
//---------------------------------------------------------------------------------
void Player::initJump()
{
	// 横速度の絶対値で速度を判定する
	float absSpeed = fabsf(movSpeed.x);

	// デフォルト：低速（立ち/歩き）
	float initMult = JUMP_INIT_MULT_LOW;
	float gravityMult = GRAVITY_MULT_LOW;

	// 中速(歩き)を超えている場合
	if (PLAYER_WALK_SPEED_MAX < absSpeed && absSpeed < PLAYER_RUN_SPEED_MAX) {
		initMult = JUMP_INIT_MULT_MID;
		gravityMult = GRAVITY_MULT_MID;
	}
	// 最高速(ダッシュ相当)
	if (PLAYER_RUN_SPEED_MAX <= absSpeed) {
		initMult = JUMP_INIT_MULT_HIGH;
		gravityMult = GRAVITY_MULT_HIGH;
	}

	// ジャンプ開始時の縦速度を、速度に応じた倍率をかけて設定する
	movSpeed.y = PLAYER_INITIAL_JUMP_SPEED * initMult;

	// このジャンプに適用する重力を保存（updateJump で利用）
	currentJumpGravity = PLAYER_GRAVITY * gravityMult;

	jumpHoldCounter = PLAYER_JUMP_HOLD_FRAME_MAX;
}

//---------------------------------------------------------------------------------
// ジャンプ中の処理
//---------------------------------------------------------------------------------
void Player::updateJump()
{
	// 水平操作
	// 入力取得
	// 右
	bool right = (CheckHitKey(KEY_INPUT_D) != false);
	// 左
	bool left = (CheckHitKey(KEY_INPUT_A) != false);

	// 現在の入力方向を決める（両方押しは 0 として扱う）
	int inputDir = 0;
	if (right && !left) {
		inputDir = 1;
	}
	else if (left && !right) {
		inputDir = -1;
	}
	else {
		inputDir = 0;
	}

	// 右方向の入力があるとき
	if (inputDir == 1) {
		if (movSpeed.x < PLAYER_WALK_SPEED_MAX) {
			movSpeed.x += PLAYER_ACCEL_AIR;
			// 加速しているときに最大速度を超えないようにする
			if (PLAYER_WALK_SPEED_MAX < movSpeed.x) movSpeed.x = PLAYER_WALK_SPEED_MAX;
		}
	}
	// 左方向の入力があるとき
	else if (inputDir == -1) {
		if (-PLAYER_WALK_SPEED_MAX < movSpeed.x) {
			movSpeed.x -= PLAYER_ACCEL_AIR;
			// 加速しているときに最大速度を超えないようにする
			if (movSpeed.x < -PLAYER_WALK_SPEED_MAX) movSpeed.x = -PLAYER_WALK_SPEED_MAX;
		}
	}

	// ジャンプ可変（ボタンを押し続けると上昇を維持する）
	// ジャンプ保持中は JUMP_SUSTAIN を適用して上昇を延ばす
	if (CheckHitKey(KEY_INPUT_SPACE) && 0 < jumpHoldCounter) {
		// 押し続けている間は重力を弱める（上方への速度がすぐ落ちない）
		movSpeed.y += JUMP_SUSTAIN;
		jumpHoldCounter--;
	}
	// ジャンプボタンを離したとき、あるいはジャンプのホールド時間が切れたときは通常重力で落下させる
	else {
		// ジャンプ時に決定した currentJumpGravity を適用
		movSpeed.y += currentJumpGravity;
	}

	// 座標の更新
	pos.y += movSpeed.y;
	pos.x += movSpeed.x;

	// 上昇が終わったら落下状態へ遷移
	if (0.0f <= movSpeed.y ) moveState.change(FALL);
}

//---------------------------------------------------------------------------------
// ジャンプ中の終了処理
//---------------------------------------------------------------------------------
void Player::exitJump()
{

}

//---------------------------------------------------------------------------------
// 落下中の初期化処理
//---------------------------------------------------------------------------------
void Player::initFall()
{

}

//---------------------------------------------------------------------------------
// 落下中の処理
//---------------------------------------------------------------------------------
void Player::updateFall()
{
	// 重力による加速
	movSpeed.y += PLAYER_GRAVITY;
	if (PLAYER_FALL_SPEED_MAX < movSpeed.y) {
		// 落下速度の上限を超えないようにする
		movSpeed.y = PLAYER_FALL_SPEED_MAX;
	}
	// 落下
	pos.y += movSpeed.y;

	// 空中水平操作
	bool right = (CheckHitKey(KEY_INPUT_D) != false);
	bool left = (CheckHitKey(KEY_INPUT_A) != false);

	// 現在の入力方向を決める（両方押しは 0 として扱う）
	int inputDir = 0;
	if (right && !left) {
		inputDir = 1;
	}
	else if (left && !right) {
		inputDir = -1;
	}
	else {
		inputDir = 0;
	}

	// 右方向の入力があるとき
	if (inputDir == 1) {
		// 右へ加速
		if (movSpeed.x < PLAYER_WALK_SPEED_MAX) {
			movSpeed.x += PLAYER_ACCEL_AIR;
			// 加速しているときに最大速度を超えないようにする
			if (PLAYER_WALK_SPEED_MAX < movSpeed.x) movSpeed.x = PLAYER_WALK_SPEED_MAX;
		}
	}
	// 左方向の入力があるとき
	else if (inputDir == -1) {
		// 左へ加速
		if (-PLAYER_WALK_SPEED_MAX < movSpeed.x) {
			movSpeed.x -= PLAYER_ACCEL_AIR;
			// 加速しているときに最大速度を超えないようにする
			if (movSpeed.x < -PLAYER_WALK_SPEED_MAX) movSpeed.x = -PLAYER_WALK_SPEED_MAX;
		}
	}

	pos.x += movSpeed.x;
}

//---------------------------------------------------------------------------------
// 落下中の終了処理
//---------------------------------------------------------------------------------
void Player::exitFall()
{
}

//---------------------------------------------------------------------------------
// 小さい状態での更新処理
//---------------------------------------------------------------------------------
void Player::updateLow()
{
}

//---------------------------------------------------------------------------------
// 大きい状態での更新処理
//---------------------------------------------------------------------------------
void Player::updateTall()
{

}
