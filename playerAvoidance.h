#pragma once

#include "playerState.h"

class PlayerAvoidance : public PlayerState
{
public:
	PlayerAvoidance(Player* player, D3DXVECTOR3 vel);
	~PlayerAvoidance() override {}

	void Update(Player* player) override;

private:
	D3DXVECTOR3 m_Velocity;
};