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

    // --- パイプ(例) ---
    // 短い土管（幅2タイル）を設置: マップの左寄り（列12-13）
    // 値 7 を土管コードとして使う（MapManager に対応スロットを追加済みである前提）
    int pipeCol = 12;
    stage1MapData[MAP_ROW - 3][pipeCol]     = PIPE_BLOCK; // 土管上部
   

    // もう一つ異なる高さの土管（幅2、少し右側）
    int pipeCol2 = 48;
    stage1MapData[MAP_ROW - 3][pipeCol2]     = PIPE_BLOCK; // 高めの土管（上部）


    // --- ハテナブロックとコインブロックの配置（例） ---
    // ハテナブロック（値 = 2）: 空中に1つ
    stage1MapData[8][20] = QUESTION_BLOCK;   // ハテナ（中身は MapManager のデフォルト処理に従う）
    // コインブロック（値 = 5）
    stage1MapData[8][22] = COIN_BLOCK;


    // 生成をするときのサンプル
    
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