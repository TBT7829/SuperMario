#pragma once

//! @brief ゲームカメラを管理するクラス
//! プレイヤーを追いかけ、ワールド座標をスクリーン座標に変換する
class Camera 
{
private:
    //! @brief コンストラクタ
    Camera();

public:

    //! @brief シングルトン
    //! @return 自分自身のただ一つの実体の参照
    inline static Camera& getInstance() {
        static Camera instance;
        return instance;
    }

    //! @brief カメラの更新処理
    //! @param targetPlayerX プレイヤーのX座標
    //! @param screenWidth スクリーンの幅
    //! @param stageWidth ステージの幅
    void update(float targetPlayerX, int screenWidth, int stageWidth);

    //! @brief ワールド座標をスクリーン座標に変換する
    //! @param worldX ワールド座標のX値
    //! @return 変換されたスクリーン座標のX値
    float worldToScreenX(float worldX) const;

    //! @brief カメラのオフセット値を取得する
    //! @return オフセット値
    float getOffsetX() const;

private:
    //! @brief カメラのX方向オフセット値
    float offsetX;
};