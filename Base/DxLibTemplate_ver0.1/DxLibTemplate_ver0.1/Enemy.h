#pragma once

#include "object.h"
#include "Float2.h"

//! @brief 敵の基底クラス
class Enemy : public Object {
public:
    //! @brief コンストラクタ
    //! @param _id エネミーのID
    //! @param _objectType オブジェクトの種類
    //! @param _start エネミーの初期位置
    //! @param _size エネミーのサイズ
    Enemy(int _id, OBJECT_TYPE _objectType, Float2 _start, Float2 _size = {16.0f, 16.0f}): Object(_id, _objectType)
    {
        pos = _start;
        size.x = _size.x;
        size.y = _size.y;
        isGround = false;
    }
    //! @brief デストラクタ
    virtual ~Enemy() {}

    // Objectの純粋仮想関数を引き継ぐ
    
	//! @brief 更新処理
    virtual void update() override = 0;
    //! @brief 描画処理
    virtual void render() override = 0;

    //! @brief 座標
    Float2 pos;
    //! @brief サイズ
    Float2 size;

    bool isGround;
};