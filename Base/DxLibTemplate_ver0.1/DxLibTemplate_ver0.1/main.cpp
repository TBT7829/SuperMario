#include "Const.h"
#include "keyManager.h"
#include "SceneManager.h"
#include "ImageManager.h"
#include "CommonFunc.h"
#include "ObjectManager.h"
#include "soundManager.h"
#include <DxLib.h>


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// シーンマネージャーのシングルトンでインスタンスを取得
	SceneManager* pSceneManager = SceneManager::getInstance();

	ImageManager* pIMGM = ImageManager::getInstance();

	SoundManager* pSM = SoundManager::getInstance();

	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);

	// 内部解像度を初代マリオと同じ（256x240）に設定して自動拡大する
	// ※DxLibではこの関数で内部解像度を固定し、ウインドウサイズに合わせて引き伸ばせます
	// 768 / 256 = 3.0倍
	SetWindowSizeExtendRate(4.0);

	// 拡大時のフィルタリングを「ドットが綺麗に見えるモード」にする
	// ネアレストネイバー（高画質化処理なし）にすることで、ドット絵がクッキリします
	SetDrawValidGraphCreateFlag(FALSE);

	ChangeWindowMode(true);

	if (DxLib_Init() == -1)
	{
		return -1;
	}

	SetMouseDispFlag(TRUE);


	// 描画先画面を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	//---------------------------------------
	// 変数の作成や初期化、その他初期設定
	// ↓ システム初期化 ↓
	initKeyManager();
	// ↑ システム初期化 ↑
	//---------------------------------------
	//　画像の読み込み
	
	// キャラなどのオブジェクト
	pIMGM->setImageInfo(ImageManager::IMAGE_STAGE_BG_11, "world_bgonly_11.png");
	//pIMGM->setImageInfo(ImageManager::IMAGE_STAGE_BG_11, "world_11.png");

	pIMGM->setImageInfo(ImageManager::IMAGE_GROUND_BLOCK_11, "ground_block_11.png");
	pIMGM->setImageInfo(ImageManager::IMAGE_HARD_BLOCK, "hard_block.png");


	pIMGM->loadImageAll();

		
	pSM->loadSoundAll();


	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && pSceneManager->gameFinish == false)
	{
		//---------------------------------------
		// 更新
		// ↓ システム更新 ↓
		updateKeyState();
		UpdateMouseButtonState();
		// ↑ システム更新 ↑
		//---------------------------------------
		// シーンマネージャーの更新関数
		pSceneManager->update();
		
		

		//---------------------------------------
		// 描画
		// ↓ 画面消去 ↓
		clsDx();
		ClearDrawScreen();
		// ↑ 画面消去 ↑
		//---------------------------------------
		// シーンマネージャーの描画関数
		pSceneManager->render();

		

		ScreenFlip();
	}

	// 画像の解除
	pIMGM->clearImageManager();
	// 音源の解除
	pSM->clearSoundManager();

	DxLib_End();

	return 0;
}


