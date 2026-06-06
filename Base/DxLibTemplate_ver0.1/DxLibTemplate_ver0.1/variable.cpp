#include "variable.h"
#include "Object.h"

//------------------------------------------------------------
//  初代マリオ 1-1: 簡易マップデータ初期化
//  - 可読性と変更性を優先し、まずは空(-1)で埋めた後に
//    必要なタイルを個別にセットします。
//  - マップの行/列は Const.h の MAP_ROW / MAP_COL を使用。
//------------------------------------------------------------

int stage1MapData[MAP_ROW][MAP_COL];

void initStage1Map()
{
    // まずはすべて空で初期化
    for (int r = 0; r < MAP_ROW; ++r) {
        for (int c = 0; c < MAP_COL; ++c) {
            stage1MapData[r][c] = -1; // 空セル（何もない）
        }
    }

    // --- 地面: 下2行を全面地面 (値 = 0) ---
    // 初代マリオと同様にマップ下部は地面で埋める
    for (int c = 0; c < MAP_COL; ++c) {
        stage1MapData[MAP_ROW - 1][c] = GROUND_BLOCK;     // 一番下の行
        stage1MapData[MAP_ROW - 2][c] = GROUND_BLOCK;     // その上も地面とする（歩ける床）
    }

    
    stage1MapData[9][16] = QUESTION_BLOCK;   

    stage1MapData[9][20] = BRICK_BLOCK;
    stage1MapData[9][21] = QUESTION_BLOCK;   // ハテナ（中身は MapManager のデフォルト処理に従う）
    stage1MapData[9][22] = BRICK_BLOCK;
    stage1MapData[5][22] = QUESTION_BLOCK;   
    stage1MapData[9][23] = QUESTION_BLOCK;
    stage1MapData[9][24] = BRICK_BLOCK;


    stage1MapData[9][27] = COIN_BLOCK;

    stage1MapData[MAP_ROW - 3][28] = PIPE_BLOCK;

    stage1MapData[MAP_ROW - 3][38] = PIPE_BLOCK;

    stage1MapData[MAP_ROW - 3][46] = PIPE_BLOCK;

    stage1MapData[MAP_ROW - 3][57] = PIPE_BLOCK;

    // 生成をするときのサンプル(皆が見る用)
    
    // --- レンガブロック群（値 = 1） ---
    // 小さなブロック群を作る（平台）
    //stage1MapData[8][36] = 1;
    //stage1MapData[8][37] = 1;
    //stage1MapData[8][38] = 1;

    // --- 高さのあるレンガの山（例） ---
    //stage1MapData[7][60] = 1;
    //stage1MapData[6][60] = 1;
    //stage1MapData[5][60] = 1;

    // --- 敵（クリボー: 値 = 7） 配置例 ---
    // クリボー（敵）のスポーン位置（地面に接するよう row を設定）
    //stage1MapData[MAP_ROW - 3][80] = 7; // クリボー（MapManager が敵生成を行う箇所を有効にしている前提）






    // --- その他メモ ---
    // ・必要ならここに追加で隠しブロック(4)、空ブロック(3)、硬いブロック(6) などを配置する
    // ・土管の幅や高さは MapManager 側の生成ルールに合わせて調整する
    // ・この配列を Stage::init でそのまま MapManager::createStage(stage1MapData, width) に渡す
}