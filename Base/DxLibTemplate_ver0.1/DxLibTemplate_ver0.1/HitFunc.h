#pragma once

#include "Float2.h"


//=================================================================================
//	２Ｄの当たり判定
//=================================================================================
 
 
//---------------------------------------------------------------------------------
//	座標や四角の大きさに Float2 を渡すバージョン
//---------------------------------------------------------------------------------

//! @brief 円同士の当たり判定（座標に Float2 を渡すバージョン）
//! @param center1 
//! @param radius1 
//! @param center2 
//! @param radius2 
//! @return ヒットしていたらtrue
//! @return ヒットしていなければfalse
bool CheckCircleHit(Float2& center1, float radius1, Float2& center2, float radius2);

//! @brief 点と円の当たり判定（座標に Float2 を渡すバージョン）
//! @param point 
//! @param center 
//! @param radius 
//! @return ヒットしていたらtrue
//! @return ヒットしていなければfalse
bool CheckPointCircleHit(Float2& point, Float2& center, float radius);

//! @brief 四角同士の当たり判定（座標と大きさに Float2 を渡すバージョン）
//! @param box_pos1 
//! @param box_size1 
//! @param box_pos2 
//! @param box_size2 
//! @return ヒットしていたらtrue
//! @return ヒットしていなければfalse
bool CheckBoxHit(Float2& box_pos1, Float2& box_size1, Float2& box_pos2, Float2& box_size2);

//! @brief 点と四角の当たり判定（座標と大きさに Float2 を渡すバージョン）
//! @param point 
//! @param box_pos 
//! @param box_size 
//! @return ヒットしていたらtrue
//! @return ヒットしていなければfalse
bool CheckPointBoxHit(Float2& point, Float2& box_pos, Float2& box_size);

//! @brief 円と四角の当たり判定（座標と大きさに Float2 を渡すバージョン）
//! @param circle 
//! @param radius 
//! @param box_pos 
//! @param box_size 
//! @return ヒットしていたらtrue
//! @return ヒットしていなければfalse
bool CheckCircleBoxHit(Float2& circle, float radius, Float2& box_pos, Float2& box_size);

//! @brief 点と三角形の当たり判定
//! @param point 
//! @param triangle_pos1 
//! @param triangle_pos2 
//! @param triangle_pos3 
//! @return ヒットしていたらtrue
//! @return ヒットしていなければfalse
bool CheckPointTriangleHit(Float2& point, Float2& triangle_pos1, Float2& triangle_pos2, Float2& triangle_pos3);

//! @brief 線分と点の一番近い座標を取得する
//! @param line_start 
//! @param line_goal 
//! @param point 
//! @return Float2型の座標
Float2 GetFloat2LinePointNearPosition(Float2& line_start, Float2& line_goal, Float2& point);

//! @brief 線分と点の一番近い距離を取得する
//! @param line_start 
//! @param line_goal 
//! @param point 
//! @return float型の距離
float GetFloat2LinePointNearDistance(Float2& line_start, Float2& line_goal, Float2& point);

//! @brief 線分と円の当たり判定
//! @param line_start 
//! @param line_goal 
//! @param circle_pos 
//! @param circle_radius 
//! @return ヒットしていたらtrue
//! @return ヒットしていなければfalse
bool CheckLineCircleHit(Float2& line_start, Float2& line_goal, Float2& circle_pos, float circle_radius);

//---------------------------------------------------------------------------------
//	座標や四角の大きさに float を渡すバージョン
//---------------------------------------------------------------------------------

//! @brief ２点の長さを取得する関数
//! @param x1 
//! @param y1 
//! @param x2 
//! @param y2 
//! @return float型の2点間の長さ
float GetDistance(float x1, float y1, float x2, float y2);

//! @brief 円同士の当たり判定
//! @param x1 
//! @param y1 
//! @param r1 
//! @param x2 
//! @param y2 
//! @param r2 
//! @return ヒットしていたらtrue
//! @return ヒットしていなければfalse
bool CheckCircleHit(float x1, float y1, float r1, float x2, float y2, float r2);

//! @brief 点と円の当たり判定
//! @param point_x 
//! @param point_y 
//! @param circle_x 
//! @param circle_y 
//! @param circle_r 
//! @return ヒットしていたらtrue
//! @return ヒットしていなければfalse
bool CheckPointCircleHit(float point_x, float point_y, float circle_x, float circle_y, float circle_r);

//! @brief 四角同士の当たり判定
//! @param x1 
//! @param y1 
//! @param w1 
//! @param h1 
//! @param x2 
//! @param y2 
//! @param w2 
//! @param h2 
//! @return ヒットしていたらtrue
//! @return ヒットしていなければfalse
bool CheckBoxHit(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);

//! @brief 点と四角の当たり判定
//! @param point_x 
//! @param point_y 
//! @param box_x 
//! @param box_y 
//! @param box_w 
//! @param box_h 
//! @return ヒットしていたらtrue
//! @return ヒットしていなければfalse
bool CheckPointBoxHit(float point_x, float point_y, float box_x, float box_y, float box_w, float box_h);

//! @brief 円と四角の当たり判定
//! @param circle_x 
//! @param circle_y 
//! @param circle_r 
//! @param box_x 
//! @param box_y 
//! @param box_w 
//! @param box_h 
//! @return ヒットしていたらtrue
//! @return ヒットしていなければfalse
bool CheckCircleBoxHit(float circle_x, float circle_y, float circle_r, float box_x, float box_y, float box_w, float box_h);