#pragma once

#include "object.h"
#include "Float2.h"

//! @brief ブロックの基底クラス
class Block : public Object {
public:
    //! @brief コンストラクタ
    //! @param _id ブロックのID
    //! @param _objectType オブジェクトの種類
    //! @param _start ブロックの初期位置
    //! @param _size ブロックのサイズ
    Block(int _id, int _objectType, Float2 _start, Float2 _size = {16.0f, 16.0f} ): Object(_id, _objectType)
    {
        pos.x = _start.x;
        pos.y = _start.y;
        size.x = _size.x;
        size.y = _size.y;
        isSolid = true;
    }

    //! @brief デストラクタ
    virtual ~Block() 
    {

    }

    //! @brief 更新処理
    virtual void update() override = 0;
    //! @brief 描画処理
    virtual void render() override = 0;

    //! @brief 座標
    Float2 pos;
	//! @brief サイズ
    Float2 size;

    //! @brief 当たり判定用
    //! @brief 通り抜けられない固いブロックかどうかのフラグ
    bool isSolid;
};