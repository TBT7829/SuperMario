#include "MapManager.h"
#include "ObjectManager.h"
#include "EnemyManager.h"
#include "BlockManager.h"
#include "Camera.h"

#include "GroundBlock.h"

#include"Const.h"
#include<DxLib.h>

//---------------------------------------------------------------------------------
//	MapManagerの処理
//---------------------------------------------------------------------------------
MapManager::MapManager()
{
	// ステージの幅は0から
    currentStageWidth = 0;
    // 最初は全部空で初期化
    for (int y = 0; y < MAP_ROW; y++) {
        for (int x = 0; x < MAP_COL; x++) {
            mapArray[y][x] = 0;
        }
    }

}

//---------------------------------------------------------------------------------
//	デストラクタ
//---------------------------------------------------------------------------------
MapManager::~MapManager()
{
    currentStageWidth = 0;
    
    for (int y = 0; y < MAP_ROW; y++) {
        for (int x = 0; x < MAP_COL; x++) {
            mapArray[y][x] = 0;
        }
    }

}

//---------------------------------------------------------------------------------
//	ステージ番号に応じたマップを配列にセットする
//---------------------------------------------------------------------------------
void MapManager::createStage(int mapData[MAP_ROW][MAP_COL], int stageWidth)
{
	// マネージャーのインスタンスを取得
    ObjectManager* pOM = ObjectManager::getInstance();
    EnemyManager* pEM = EnemyManager::getInstance();
    BlockManager* pBM = BlockManager::getInstance();

    // 中身を初期化
    pEM->exit();
    pBM->exit();

    // ステージの幅を設定
    currentStageWidth = stageWidth;

    for (int row = 0; row < MAP_ROW; row++) {
        for (int col = 0; col < MAP_COL; col++) {
			// 現在のマスの番号を取得
            int curMassData = mapData[row][col];

            // マス目の左上のドット座標を計算する
            Float2 pixel;
            pixel.x = (float)(col * BLOCK_SIZE);
            pixel.y = (float)(row * BLOCK_SIZE);

			// 何もない(-1以下)なら描画する必要がないのでスキップ
            switch (curMassData) {
            case 0: // 地面
            {
                mapArray[row][col] = 0;

                
                // オブジェクトを作って各マネージャーに登録する
                GroundBlock* pGround = new GroundBlock(pOM->generateId(), pixel);
				// もし登録できなかったら、作ったオブジェクトを削除して中断する
                if (pBM->Add(pGround) == false) {
                    delete pGround;
                    abort();
                }
				// もし登録できなかったら、作ったオブジェクトを削除して中断する
                if (pOM->add(pGround) == false) {
                    delete pGround;
                    abort();
                }
            }
            break;
            case 1: // レンガブロック
            {
                mapArray[row][col] = 1;

            }
            break;
            case 2: // ハテナブロック
            {
                mapArray[row][col] = 2;

            }
            break;
            case 3: // 空ブロック
            {
                mapArray[row][col] = 3;

            }
            break;
            case 7: // クリボー
            {
                mapArray[row][col] = 7;

            }
            break;
            default:
                abort();
                break;
            }

        }
    }

}

//---------------------------------------------------------------------------------
//	デバッグ用マップ描画処理
//---------------------------------------------------------------------------------
void MapManager::drawDebugMap()
{
    // DxLibの色データを作成 (R, G, B)
    int white = GetColor(255, 255, 255); // 地面用（白）
    int brown = GetColor(150, 75, 0); // レンガ用（茶色）
    int yellow = GetColor(255, 255, 0); // ハテナ用（黄色）

    // 縦と横のマス目をすべてループでチェックする
    for (int y = 0; y < MAP_ROW; y++) {
        for (int x = 0; x < currentStageWidth; x++) {

            // 現在のマスの番号を取得
            int curMassData = mapArray[y][x];

            // 何もない(-1以下)なら描画する必要がないのでスキップ
            if (curMassData < 0) {
                continue;
            }

            // マス目の左上と右下のドット座標を計算する
            float worldX = x * BLOCK_SIZE;
            float screenX = Camera::getInstance().worldToScreenX(worldX);
            
            int x1 = (int)screenX;
            int y1 = y * BLOCK_SIZE;
            int x2 = x1 + BLOCK_SIZE;
            int y2 = y1 + BLOCK_SIZE;

            // 画面外のブロックは描画をスキップして軽くする処理
            if (x2 < 0 || x1 > 256) {
                continue;
            }

            // チップの種類に合わせて色を変えて、四角の枠線を描画
            switch (curMassData) {
            case 0:
                DrawLineBox(x1, y1, x2, y2, white);
                break;

            case 1:
                DrawLineBox(x1, y1, x2, y2, brown);
                break;

            case 2:
                DrawLineBox(x1, y1, x2, y2, yellow);
                break;

            default:
                break;
            }
        }
    }
}
