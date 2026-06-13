#pragma once

#include "Enemy.h"
#include "Float2.h"

class Goomba : public Enemy
{
public:
    const float GOOMBA_MOVE_SPEED = 1.0f;


    Goomba(int id, int objectType, Float2 start, Float2 size = { 16.0f, 16.0f });

    virtual ~Goomba();

    void update() override;
    void render() override;

private:
    int anim_frame;
    int anim_counter;
    int anim_delay;
};
