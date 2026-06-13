#pragma once

#include "Enemy.h"
#include "Float2.h"

class Goomba : public Enemy
{
public:
    const float GOOMBA_MOVE_SPEED = 1.0f;

    enum DIRECTION {
        LEFT = 0,		//!< 左向き
        RIGHT,	//!< 右向き
    };

    Goomba(int _id, Float2 _start);

    virtual ~Goomba();

    void update() override;
    void render() override;


    //! @brief クリボーの移動速度
    Float2 moveSpeed;


    //int anim_frame;
    //int anim_counter;
    //int anim_delay =30;
};
