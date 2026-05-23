#pragma once


//---------------------------------------------------------------------------------
//	Float2 クラス
//---------------------------------------------------------------------------------
class Float2
{
	//-------------------------
	// メンバ関数
	//-------------------------
public:
	//! @brief デフォルトコンストラクタ
	Float2();					
	//! @brief 引数ありコンストラクタ
	Float2(float x, float y);					

	//!@brief xとyを0にする
	void Clear();								
	
	//! @brief xとyの値を設定する
	//! @param x 
	//! @param y 
	void Set(float x, float y);

	//! @brief 他の Float2 の値を設定する
	//! @param f2 設定する Float2
	void Set(Float2& f2);

	//	長さ取得
	float GetLength();							
	//	正規化
	void Normalize();							
	//	長さ設定
	void SetLength(float length);				

	Float2& operator = (const Float2& f2);		//	= 演算子のオーバーロード
	Float2& operator += (const Float2& f2);		//	+= 演算子のオーバーロード
	Float2& operator -= (const Float2& f2);		//	-= 演算子のオーバーロード
	Float2& operator *= (const float f);		//	*= 演算子のオーバーロード
	Float2& operator /= (const float f);		//	/= 演算子のオーバーロード

	//-------------------------
	// メンバ変数
	//-------------------------
public:
	float x;
	float y;

};

//	+ 演算子のオーバーロード
Float2 operator + (const Float2& f2_1, const Float2& f2_2);
//	- 演算子のオーバーロード
Float2 operator - (const Float2& f2_1, const Float2& f2_2);
//	* 演算子のオーバーロード
Float2 operator * (const Float2& f2, const float f);
//	/ 演算子のオーバーロード
Float2 operator / (const Float2& f2, const float f);

//	マウス座標を Float2 で取得
Float2 GetMouseFloat2();
//	２つの Float2 の距離を求める
float GetFloat2Distance(Float2& pos1, Float2& pos2);
//	２つの Float2 の内積を求める
float GetFloat2Dot(Float2& v1, Float2& v2);
//	２つの Float2 の外積を求める
float GetFloat2Cross(Float2& v1, Float2& v2);