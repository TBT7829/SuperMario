#include "Goomba.h"
#include <DxLib.h>

// クリボーのハンドル 
static int s_kuriboHandle = -1;

Goomba::Goomba(int id, int objectType, Float2 start, Float2 size)
    : Enemy(id, objectType, start, size)
{
    anim_frame = 0;
    anim_counter = 0;
    anim_delay = 30;
}

Goomba::~Goomba()
{
}

void Goomba::update()
{
    // 左向きのクリボーなので左へ移動する
    pos.x += GOOMBA_MOVE_SPEED;

    // アニメーションの切り替えを遅くする
    anim_counter++;
    if (anim_counter >= anim_delay) {
        anim_frame = (anim_frame + 1) % 2; // アニメーションフレームを切り替える
        anim_counter = 0;
    }

}

void Goomba::render()
{
    // 最初の描画時に一度だけ画像を読み込む
    if (s_kuriboHandle == -1) {
        s_kuriboHandle = LoadGraph("kuribo_wolk.png");
    }

    if (s_kuriboHandle != -1) {
        if (anim_frame == 0)
        {
            DrawRectGraph((int)pos.x, (int)pos.y, 0, 0, 16, 16, s_kuriboHandle, TRUE);
        }
        else if (anim_frame == 1)
        {
            DrawRectGraph((int)pos.x, (int)pos.y, 16, 0, 32, 32, s_kuriboHandle, TRUE);
        }
    }
    else
    {
        // 代替: 画像読み込みに失敗した場合は赤い四角を描画
        DrawBox((int)pos.x, (int)pos.y, (int)(pos.x + size.x), (int)(pos.y + size.y), GetColor(255, 0, 0), TRUE);
    }
}