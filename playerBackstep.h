#pragma once

#include "playerState.h"

class PlayerBackstep : public PlayerState
{
public:
	PlayerBackstep(Player* player);
	~PlayerBackstep() {}

	void Update(Player* player) override;
};