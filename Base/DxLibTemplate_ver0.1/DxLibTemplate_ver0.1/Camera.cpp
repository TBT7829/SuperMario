#include "Camera.h"

Camera::Camera() 
{
    offsetX = 0.0f;
}

void Camera::update(float targetPlayerX, int screenWidth, int stageWidth) {
    // マリオを画面中央(screenWidth / 2)に置くためのオフセット計算
    offsetX = targetPlayerX - (screenWidth / 2.0f);

    // 左端制限
    if (offsetX < 0.0f) offsetX = 0.0f;

    // 右端制限（ステージの終端より先には行かない）
    float maxOffset = (float)(stageWidth - screenWidth);
    if (offsetX > maxOffset) offsetX = maxOffset;
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

