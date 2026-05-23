#include "Timer.h"


void Timer::start(int max)
{
	// 値を0にする
	myTimerCount = 0;
	// どこまで数えるかを決める
	timerCountMax = max;
	// 終了していない状態にする
	isFinish = false;

	state = ACTIVE;
}

void Timer::setMaxTimeStop(int max)
{
	// 値を0にする
	myTimerCount = 0;
	// どこまで数えるかを決める
	timerCountMax = max;
	// 終了していない状態にする
	isFinish = false;

	state = STOP;
}

void Timer::update() 
{
	// タイマーを動かす必要がなければ
	if (state == STOP || isFinish == true || timerCountMax <= 0)
	{
		// ここで弾く
		return;
	}

	// 値を増やす
	myTimerCount++;

	// 今の値が決められた時間にたっつぃたら
	if (timerCountMax <= myTimerCount)
	{
		// 終了状態に
		isFinish = true;
		state = STOP;
	}
}