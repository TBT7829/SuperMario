#include "Title.h"
#include "ObjectManager.h"
#include "ImageManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "MapManager.h"

#include "Camera.h"
#include "PlayerManager.h"
#include "Player.h"

#include "CollisionManager.h"

#include <DxLib.h>


//=================================================================================
//	タイトルシーンの処理
//=================================================================================


//---------------------------------------------------------------------------------
//	コンストラクタ
//---------------------------------------------------------------------------------
Title::Title()
{
	init();
}
//---------------------------------------------------------------------------------
//	デストラクタ
//---------------------------------------------------------------------------------
Title::~Title()
{
	exit();
}
//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void Title::init()
{
	ObjectManager* pOM = ObjectManager::getInstance();
	PlayerManager::getInstance()->playerGenerate();

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


	MapManager::getInstance()->createStage(mapBuffer, MAP_COL);

	// 背景画像
	imageBG = ImageManager::IMAGE_STAGE_BG_11;

	// 次のシーンは未設定(-1)にしておく
	nextScene = -1;


}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void Title::update()
{
	ObjectManager* pOM = ObjectManager::getInstance();

	// シーンマネージャーのインスタンスを取得
	SceneManager* pSceneManager = SceneManager::getInstance();

	SoundManager* pSoundManager = SoundManager::getInstance();
	//PlaySoundMem(pSoundManager->getSoundHandle(SoundManager::SOUND_TITLE), DX_PLAYTYPE_LOOP, FALSE);

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

}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void Title::render()
{
	ObjectManager* pOM = ObjectManager::getInstance();

	int imgHandle = ImageManager::getInstance()->getImageHandle(imageBG);

	// 背景の世界でのX座標は「0」
	float bgWorldX = 0.0f;

	// カメラを通して、画面上のどこに描画すべきかを計算する
	float drawX = Camera::getInstance().worldToScreenX(bgWorldX);
	DrawGraph(drawX, 0, imgHandle, TRUE);

	pOM->renderAll();

	MapManager::getInstance()->drawDebugMap();

}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void Title::exit()
{

}
