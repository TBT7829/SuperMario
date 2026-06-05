#include "Camera.h"

Camera::Camera() 
{
    offsetX = 0.0f;
}

void Camera::update(float targetPlayerX, int screenWidth, int stageWidth) {
#ifdef IS_DEBUG

    // マリオを画面中央(screenWidth / 2)に置くためのオフセット計算
    offsetX = targetPlayerX - (screenWidth / 2.0f);

#endif IS_DEBUG

#ifndef IS_DEBUG

    // プレイヤーがこれまでに到達した最大Xを更新（カメラはこの値基準で右にだけ動く）
    if (maxReachedX < targetPlayerX) {
        maxReachedX = targetPlayerX;
    }
    // カメラのオフセットは「最大到達位置を画面中央に置く」ように計算
    offsetX = maxReachedX - (screenWidth / 2.0f);

#endif IS_DEBUG
    
    // 左端制限
    if (offsetX < 0.0f) offsetX = 0.0f;

    // 右端制限（ステージの終端より先には行かない）
    float maxOffset = (float)(stageWidth - screenWidth);
    if (maxOffset < offsetX) offsetX = maxOffset;
}

// 描画用の座標変換関数
float Camera::worldToScreenX(float worldX) const 
{
    return worldX - offsetX; 
}

float Camera::getOffsetX() const 
{
    return offsetX; 
}

