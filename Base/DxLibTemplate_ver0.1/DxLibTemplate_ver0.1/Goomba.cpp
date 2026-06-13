#include "Goomba.h"
#include "Camera.h"
#include "Float2.h"
#include <DxLib.h>

// クリボーのハンドル 
static int s_kuriboHandle = -1;

Goomba::Goomba(int _id, Float2 _start)
    : Enemy(_id, OBJECT_TYPE::GOOMBA, _start, { 16.0f, 16.0f })
{
    moveSpeed.x = GOOMBA_MOVE_SPEED;
    moveSpeed.y = 0.0f;
}

Goomba::~Goomba()
{
}

void Goomba::update()
{
    // 移動方向へ
    pos.x += moveSpeed.x;


}

void Goomba::render()
{
    // カメラオフセットを適用してワールド座標をスクリーン座標に変換
    float drawX = Camera::getInstance().worldToScreenX(pos.x);
    int drawY = (int)pos.y;
    int x1 = (int)drawX;
    int y1 = drawY;
    int x2 = (int)(drawX + size.x);
    int y2 = drawY + (int)size.y;

    // 最初の描画時に一度だけ画像を読み込む
    if (s_kuriboHandle == -1) {
        s_kuriboHandle = LoadGraph("kuribo_wolk.png");
    }

    /*
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
    */
    //else
    //{
        // 代替: 画像読み込みに失敗した場合は赤い四角を描画
        DrawBox(x1, y1, x2, y2, GetColor(255, 0, 0), TRUE);
    //}

    //printfDx("x:%f, y:%f", x1, y1);
}