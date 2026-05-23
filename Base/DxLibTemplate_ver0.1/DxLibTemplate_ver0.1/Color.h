#pragma once

#include<DxLib.h>


//! @brief 色(赤、緑、青)と透明度を持つクラス
class Color
{
//-------------------------
// メンバ関数
//-------------------------
public:
	//! @brief デフォルトコンストラクタ
	//! @brief 引数を渡さなかった場合はこちらのコンストラクタで色が全て255に指定されたコンストラクタが呼ばれる
	Color();

	//! @brief 引数ありコンストラクタ
	//! @brief 引数に受け取った色を設定
	//! @param r 
	//! @param g 
	//! @param b 
	//! @param a 
	Color(int r, int g, int b, int a);
	

	//-----------------
	// 演算子オーバーロード 
	//-----------------
	// 今の自分の持っている色情報に、別にもらってきた色情報を足し合わせ、
	// 新しい色情報を返す関数
	Color operator + (const Color& otherCol);
	
	// 今の自分の持っている色情報に、別にもらってきた色情報を引き、
	// 新しい色情報を返す関数
	Color operator - (const Color& otherCol);
	
	// 今の自分の持っている色情報に、指定された割合を掛け合わせ、
	// 新しい色情報を返す関数
	Color operator * (float rate);

	// 引数の無い小括弧をつけると色を取得できるように
	int operator () ();
	
//-------------------------
// メンバ変数
//-------------------------
public:
	//! @brief 赤色保存用変数
	int r;
	//! @brief 緑色保存用変数
	int g;
	//! @brief 青色保存用変数
	int b;
	//! @brief アルファ値(透明度)保存用変数
	int a;

};


// 値Aと値Bの間のどこかの値を取得
//  引数1: 開始点(値A)
//  引数2: 終了点(値B)
//  引数3: 中間地点(0.0～1.0)
//		   0.0:	   0％
//		   1.0:	 100％
//  戻り値: 指定された地点での値

//! @brief 開始点と終点の間のどこかの値を取得
//! @param start (開始点)
//! @param end (終点)
//! @param rate ( 中間地点(0.0～1.0) )
//! @return 指定された地点での値
Color lerpCol(Color& start, Color& end, float rate);

