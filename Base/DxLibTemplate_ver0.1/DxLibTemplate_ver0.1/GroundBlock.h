#pragma once

#include "block.h"

//! @brief 地面ブロッククラス
//! Block クラスを継承し、衝突判定のある地面ブロックを表現する
class GroundBlock : public Block {
public:
    //! @brief コンストラクタ
    //! @param _id オブジェクトID
    //! @param _start ブロックの開始位置
    //! @note 型（objectType）には GROUND_BLOCK を指定しており、
    //!       座標やサイズ、isSolid の初期化は親クラス（Block）で行われる
    GroundBlock(int _id, Float2 _start);

    //! @brief デストラクタ
    virtual ~GroundBlock();

    //! @brief 更新処理
    //! @note Block クラス（Object クラス）から継承した純粋仮想関数をオーバーライド
    void update() override; 

    //! @brief 描画処理
    //! @note Block クラス（Object クラス）から継承した純粋仮想関数をオーバーライド
    void render() override;


    //! @brief 画像を保存する変数
    int image;
};