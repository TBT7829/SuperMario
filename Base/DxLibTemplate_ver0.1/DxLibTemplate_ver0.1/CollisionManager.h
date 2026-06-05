#pragma once

#include "Float2.h"

//衝突判定を管理するクラス
class CollisionManager final
{
private:
    //! @brief コンストラクタ
    CollisionManager() {}
	//! @brief デストラクタ
    ~CollisionManager() {}

public:
    //! @brief 衝突方向
    enum CollisionSide {
        NONE = 0,
        TOP,		// 上から当たった（AがBの上側）
        BOTTOM,		// 下から当たった（AがBの下側）
        LEFT,		// 左から当たった（AがBの左側）
        RIGHT,		// 右から当たった（AがBの右側）
        MULTIPLE	// 複数方向の重なり(拡張性を持たせるため)
    };

    //! @brief 衝突に関する詳細情報
    struct CollisionInfo {
        CollisionInfo()
        {
            isHit = false;
            side = NONE;
            penetration.Set(0.0f, 0.0f);
        }
        bool isHit;				// 当たっているか
        CollisionSide side;		// 主な衝突方向（方向）
        Float2 penetration;		// 最小分離ベクトル（押し戻す量、座標系に依存）
        
    };

    //! @brief インスタンスを取得する
    //! @return CollisionManagerのインスタンス
    inline static CollisionManager* getInstance() 
    {
        static CollisionManager s_instance;
        return &s_instance;
    }

    //! @brief 衝突判定を更新する
    void updateCollision();

    //! @brief 2つの衝突を検出する
    //! @param pos1 A の左上座標
    //! @param size1 A の幅・高さ
    //! @param pos2 B の左上座標
    //! @param size2 B の幅・高さ
    //! @return 衝突の有無・方向・押し戻し量を含む CollisionInfo
    CollisionInfo detectCollision(const Float2& pos1, const Float2& size1, const Float2& pos2, const Float2& size2) const;
};