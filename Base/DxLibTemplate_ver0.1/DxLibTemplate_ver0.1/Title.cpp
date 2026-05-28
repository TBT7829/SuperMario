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
	
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void Title::exit()
{

}
