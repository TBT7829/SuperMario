#include "Stage.h"
#include "ImageManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "Camera.h"
#include "PlayerManager.h"
#include"Player.h"
#include "ObjectManager.h"
#include "MapManager.h"
#include "CollisionManager.h"
#include "mapdata.h"
#include <DxLib.h>


//=================================================================================
//	ステージシーンの処理
//=================================================================================


//---------------------------------------------------------------------------------
//	コンストラクタ
//---------------------------------------------------------------------------------
Stage::Stage()
{
	init();
}
//---------------------------------------------------------------------------------
//	デストラクタ
//---------------------------------------------------------------------------------
Stage::~Stage()
{
	exit();
}
//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void Stage::init()
{
	ObjectManager* pOM = ObjectManager::getInstance();
	PlayerManager::getInstance()->playerGenerate();

	/*
	int mapBuffer[MAP_ROW][MAP_COL];
	for (int row = 0; row < MAP_ROW; row++) {
		for (int col = 0; col < MAP_COL; col++) {
			// 一番下なら地面
			if (MAP_ROW - 2 <= row) {
				mapBuffer[row][col] = 0;
			}
			else {
				mapBuffer[row][col] = 1;
			}

		}
	}
	*/

	initStage1Map();

	MapManager::getInstance()->createStage(stage1MapData, MAP_COL);


	// 背景画像
	imageBG = ImageManager::IMAGE_STAGE_BG_11;

	// 次のシーンは未設定(-1)にしておく
	nextScene = -1;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void Stage::update()
{
	ObjectManager* pOM = ObjectManager::getInstance();

	// シーンマネージャーのインスタンスを取得
	SceneManager* pSceneManager = SceneManager::getInstance();

	SoundManager* pSoundManager = SoundManager::getInstance();

	

	PlayerManager* pPM = PlayerManager::getInstance();

	pOM->updateAll();

	CollisionManager::getInstance()->updateCollision();

	// プレイヤーの取得
	Player* pPlayer = pPM->get();

	Camera::getInstance().update(pPlayer->pos.x, WINDOW_WIDTH, STAGE_1_LENGTH);

	if (0 < nextScene) {
		// ゲームセレクトへ
		pSceneManager->changeScene(nextScene);
	}

	// サウンドの取得
	int bgmHandle = pSoundManager->getSoundHandle(SoundManager::SOUND_STAGE);

	// サウンドの再生（毎フレーム再生コールしないようにチェックしてから再生する）
	if (bgmHandle != -1)
	{
		// DxLib の CheckSoundMem を使って現在再生中か確認する
		// 再生中でなければループ再生を開始する
		if (CheckSoundMem(bgmHandle) == 0)
		{
			(bgmHandle, DX_PLAYTYPE_LOOP);
		}
	}

}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void Stage::render()
{
	ObjectManager* pOM = ObjectManager::getInstance();

	int imgHandle = ImageManager::getInstance()->getImageHandle(imageBG);

	// 背景の世界でのX座標は「0」
	float bgWorldX = 0.0f;

	// カメラを通して、画面上のどこに描画すべきかを計算する
	float drawX = Camera::getInstance().worldToScreenX(bgWorldX);
	DrawGraph(drawX, 0, imgHandle, TRUE);

	pOM->renderAll();

#ifdef IS_DEBUG
	MapManager::getInstance()->drawDebugMap();
#endif

}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void Stage::exit()
{

}
