#pragma 

class Goomba : public Enemy
{
public:
	// ’l‚ğ“ü‚ê‚é
	const float GOOMBA_MOVE_SPEED;

	Goomba();
	virtual ~Goomba();

	//! @brief XVˆ—
	void update() override;

	//! @brief •`‰æˆ—
	void render() override;


};

