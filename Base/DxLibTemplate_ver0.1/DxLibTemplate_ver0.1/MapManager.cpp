#include "MapManager.h"
#include "ObjectManager.h"
#include "EnemyManager.h"
#include "BlockManager.h"
#include "Camera.h"

#include "GroundBlock.h"
#include "BrickBlock.h"
#include "QuestionBlock.h"
#include "EmptyBlock.h"
#include "HiddenBlock.h"
#include "CoinBlock.h"
#include "HardBlock.h"
#include "Pipe.h"

#include"Const.h"
#include "CommonFunc.h"
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

    // 入力 mapData を直接変更しないようローカルにコピーする
    int tempMap[MAP_ROW][MAP_COL];
    for (int r = 0; r < MAP_ROW; ++r) {
        for (int c = 0; c < MAP_COL; ++c) {
            tempMap[r][c] = mapData[r][c];
        }
    }

    // pipe の識別用カウンタ（pipeId に使用）
    int pipeCounter = 0;

    for (int row = 0; row < MAP_ROW; row++) {
        for (int col = 0; col < MAP_COL; col++) {
			// 現在のマスの番号を取得
            int curMassData = tempMap[row][col];

            // マス目の左上のドット座標を計算する
            Float2 pixel;
            pixel.x = (float)(col * BLOCK_SIZE);
            pixel.y = (float)(row * BLOCK_SIZE);

            // 何もない(-1以下)なら描画する必要がないのでスキップ
            if (curMassData < 0) {
                mapArray[row][col] = -1;
                continue;
            }

			mapArray[row][col] = curMassData;

			// 何もない(-1以下)なら描画する必要がないのでスキップ
            switch (curMassData) {
            case GROUND_BLOCK: // 地面
            {
                // オブジェクトを作って各マネージャーに登録する
                GroundBlock* pGround = new GroundBlock(pOM->generateId(), pixel);
				// もし登録できなかったら、作ったオブジェクトを削除して中断する
                if (pBM->Add(pGround) == false) {
                    delete pGround;
                    MY_ABORT();
                }
				// もし登録できなかったら、作ったオブジェクトを削除して中断する
                if (pOM->add(pGround) == false) {
                    delete pGround;
                    MY_ABORT();
                }
            }
            break;
            case BRICK_BLOCK: // レンガブロック
            {
                
                BrickBlock* pBrick = new BrickBlock(pOM->generateId(), pixel);
                if (pBM->Add(pBrick) == false) 
                {
                    delete pBrick; 
                    MY_ABORT(); 
                }
                if (pOM->add(pBrick) == false) 
                {
                    delete pBrick; 
                    MY_ABORT(); 
                }
                
            }
            break;
            case QUESTION_BLOCK: // ハテナブロック
            {
                // 仮: デフォルトでコインを内包（必要ならマップデータに種類を持たせる）
                QuestionBlock* pQB = new QuestionBlock(pOM->generateId(), pixel, QuestionBlock::ITEM_COIN);
                if (pBM->Add(pQB) == false) 
                {
                    delete pQB;
                    MY_ABORT(); 
                }
                if (pOM->add(pQB) == false)
                {
                    delete pQB; 
                    MY_ABORT(); 
                }
            

            }
            break;
            case EMPTY_BLOCK: // 空ブロック
            {
                /*
                EmptyBlock* pEmpty = new EmptyBlock(pOM->generateId(), pixel);
                if (pBM->Add(pEmpty) == false) 
                {
                    delete pEmpty; 
                    MY_ABORT();
                }
                if (pOM->add(pEmpty) == false) 
                {
                    delete pEmpty; 
                    MY_ABORT();
                }
                */
            }
            break;
            case HIDDEN_BLOCK: // 隠しブロック
            {
                /*
                HiddenBlock* pHidden = new HiddenBlock(pOM->generateId(), pixel);
                if (pBM->Add(pHidden) == false)
                {
                    delete pHidden; 
                    MY_ABORT(); 
                }
                if (pOM->add(pHidden) == false)
                { 
                    delete pHidden;
                    MY_ABORT(); 
                }
                */
            }
            break;
            case COIN_BLOCK: // コインブロック
            {
                // デフォルト8コイン（マップに値を拡張して変えられる）
                CoinBlock* pCoinBlock = new CoinBlock(pOM->generateId(), pixel, 8);
                if (pBM->Add(pCoinBlock) == false) 
                {
                    delete pCoinBlock; 
                    MY_ABORT();
                }
                if (pOM->add(pCoinBlock) == false) 
                {
                    delete pCoinBlock;
                    MY_ABORT();
                }
            }
            break;
            case HARD_BLOCK: // 硬いブロック
            {
                /*
                HardBlock* pHard = new HardBlock(pOM->generateId(), pixel);
                if (pBM->Add(pHard) == false) 
                {
                    delete pHard; 
                    abort(); 
                }
                if (pOM->add(pHard) == false) 
                {
                    delete pHard;
                    MY_ABORT(); 
                }
                */
            }
            break;
            case PIPE_BLOCK: // 土管
            {
                // ローカル tempMap 上でまだ未処理の PIPE_BLOCK のみ処理する
                if (tempMap[row][col] != PIPE_BLOCK) {
                    break;
                }

                // 単一セル扱いで Pipe を作成（幅2, 高さ3）
                Float2 pipeSize = { (float)BLOCK_SIZE * 2, (float)BLOCK_SIZE * 2 };

                // 基準セル(pixel)の「下端」を土管の底に合わせる
                int pipePosX = (int)pixel.x;
                int pipeBottomY = (int)pixel.y + BLOCK_SIZE;             // このセルの下端が底になる
                int pipePosY = pipeBottomY - pipeSize.y;               // 上端を決定
                if (pipePosY < 0) { pipePosY = 0; }

                Float2 pipePos = { (float)pipePosX, (float)pipePosY };
                Float2 exitPos = { pixel.x, pixel.y }; // 必要なら別途データで拡張
                Pipe* pPipe = new Pipe(pOM->generateId(), pipePos, pipeSize, exitPos, pipeCounter++, true);

                // 登録
                if (pBM->Add(pPipe) == false) { delete pPipe; MY_ABORT(); }
                if (pOM->add(pPipe) == false) { delete pPipe; MY_ABORT(); }

                // ローカルコピーにフラグを立てて重複生成を防止
                tempMap[row][col] = -1;
                mapArray[row][col] = PIPE_BLOCK;
            }
            break;
            case GOOMBA: // クリボー
            {

            }
            break;
            default:
                MY_ABORT();
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
    int brown = GetColor(150, 75, 0);   // レンガ用（茶色）
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

            // 種類に合わせて色を変えて、四角の枠線を描画
            switch (curMassData) {
            case -1:
                DrawLineBox(x1, y1, x2, y2, white);
                break;

            case 1:
                DrawLineBox(x1, y1, x2, y2, brown);
                break;

            case 2:
                //DrawLineBox(x1, y1, x2, y2, yellow);
                break;

            default:
                DrawLineBox(x1, y1, x2, y2, white);
                break;
            }
        }
    }
}
