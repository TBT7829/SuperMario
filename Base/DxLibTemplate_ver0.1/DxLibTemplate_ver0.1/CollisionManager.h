#pragma once



//衝突判定を管理するクラス
class CollisionManager final
{
private:
	
    //! @brief コンストラクタ
    CollisionManager() {}
	//! @brief デストラクタ
    ~CollisionManager() {}

public:
    //! @brief インスタンスを取得する
    //! @return CollisionManagerのインスタンス
    inline static CollisionManager* getInstance() 
    {
        static CollisionManager s_instance;
        return &s_instance;
    }

    //! @brief 衝突判定を更新する
    void updateCollision();
};