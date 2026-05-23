#include "SceneManager.h"

#include "Title.h"
#include "Stage.h"

#include<DxLib.h>

//---------------------------------------------------------------------------------
//	シーン全体の管理処理
//---------------------------------------------------------------------------------

//	Sceneクラスを継承した必要なシーンのクラスの実体を生成して、
//	SceneManagerがSceneポインタ型で一括管理する

//---------------------------------------------------------------------------------
//	コンストラクタ
//---------------------------------------------------------------------------------
SceneManager::SceneManager()
{
	// 初期化
	currentType = SCENE_NONE;
	nextType = SCENE_NONE;

	// タイトルから始める
	changeScene(SCENE_TITLE);
}

//---------------------------------------------------------------------------------
//	デストラクタ
//---------------------------------------------------------------------------------
SceneManager::~SceneManager()
{
	if (pScene != nullptr) {
		// pSceneをdeleteする
		delete pScene;
		pScene = nullptr;
	}
}

//---------------------------------------------------------------------------------
//	シーンの切り替え関数
//---------------------------------------------------------------------------------
void SceneManager::changeScene(int nextSceneType)
{
	// シーンを渡された次のシーンに変更する
	nextType = nextSceneType;
}

//---------------------------------------------------------------------------------
//	更新関数
//---------------------------------------------------------------------------------
void SceneManager::update()
{
	if (nextType != SCENE_NONE) {
		if (currentType != nextType)
		{
			if (pScene != nullptr) {
				// 今のシーンの終了処理を呼ぶ
				pScene->exit();
				// pSceneをdeleteして
				// 今のシーンを終了
				delete pScene;
				pScene = nullptr;
			}

			// 引数に渡されたシーンタイプのシーンクラスを
			// pSceneにnewしてやる
			switch (nextType) {
				// タイトル
			case SceneType::SCENE_TITLE:
				pScene = new Title;
				break;
				// ゲームセレクト
			case SceneType::SCENE_GAMESELECT:
				//pScene = new GameSelect;
				break;
				// デモ
			case SceneType::SCENE_DEMO:
				//pScene = new Demo;
				break;
				// ステージ
			case SCENE_STAGE:
				pScene = new Stage;
				break;
				// クリア
			case SCENE_CLEAR:
				//pScene = new Clear;
				break;
				// ゲームオーバー
			case SCENE_GAMEOVER:
				//pScene = new GameOver;
				break;
				// クリアタイム
			case SCENE_CLEAR_TIME:
				//pScene = new ClearTime;
				break;
				// 渡されたシーンがおかしい場合
				// 予期せぬ挙動を防ぎ、このswitchでバグが起こっているのがわかるように
				// abort関数を動かす
			default:
				abort();
				break;
			}

			// 変更し終えたら今のシーンを保存
			currentType = nextType;
		}

		nextType = SCENE_NONE;
	}


	if (pScene != nullptr) {
		// 今のシーンの更新関数を呼ぶ
		pScene->update();
	}
	


}

//---------------------------------------------------------------------------------
//	描画関数
//---------------------------------------------------------------------------------
void SceneManager::render()
{
	if (pScene != nullptr) {
		// 今のシーンの描画関数を呼ぶ
		pScene->render();
	}
	
	SetFontSize(16);

	
}