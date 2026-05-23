#include "Color.h"
#include "CommonFunc.h"

//---------------------------------------------------------------------------------
//	Colorクラスの処理
//---------------------------------------------------------------------------------


//---------------------------------------------------------------------------------
//	デフォルトコンストラクタ
//---------------------------------------------------------------------------------
Color::Color()
{
	Color(255, 255, 255, 255);
}


//---------------------------------------------------------------------------------
//	引数ありコンストラクタ
//---------------------------------------------------------------------------------
// 引数に受け取った色を設定
Color::Color(int r, int g, int b, int a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}


//---------------------------------------------------------------------------------
//	演算子オーバーロード
//---------------------------------------------------------------------------------
Color Color::operator + (const Color& otherCol)
{
	int tmpR = fixValue(this->r + otherCol.r, 0, 255);
	int tmpG = fixValue(this->g + otherCol.g, 0, 255);
	int tmpB = fixValue(this->b + otherCol.b, 0, 255);
	int tmpA = fixValue(this->a + otherCol.a, 0, 255);

	Color ret(tmpR, tmpG, tmpB, tmpA);
	return ret;
}

Color Color::operator - (const Color& otherCol)
{
	int tmpR = fixValue(this->r - otherCol.r, 0, 255);
	int tmpG = fixValue(this->g - otherCol.g, 0, 255);
	int tmpB = fixValue(this->b - otherCol.b, 0, 255);
	int tmpA = fixValue(this->a - otherCol.a, 0, 255);

	Color ret(tmpR, tmpG, tmpB, tmpA);
	return ret;
}

Color Color::operator * (float rate)
{
	int tmpR = fixValue((float)this->r * rate, 0, 255);
	int tmpG = fixValue((float)this->g * rate, 0, 255);
	int tmpB = fixValue((float)this->b * rate, 0, 255);
	int tmpA = fixValue((float)this->a * rate, 0, 255);

	Color ret(tmpR, tmpG, tmpB, tmpA);
	return ret;
}

// 引数の無い小括弧をつけると色を取得できるように
int Color::operator () ()
{
	return GetColor(r, g, b) | (a << 24);
}


// 線形補間で色を取る
Color lerpCol(Color& start, Color& end, float rate)
{
	return (end - start) * rate + start;
}