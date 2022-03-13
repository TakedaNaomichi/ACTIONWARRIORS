#include "main.h"
#include "resource.h"
#include "player.h"
#include "playerAvoidance.h"
#include "playerStateSelector.h"
#include "status.h"
#include "hitPoint.h"
#include "playerDead.h"
#include "obstancle.h"
#include "collision.h"
#include "scene.h"

PlayerAvoidance::PlayerAvoidance(Player * player, D3DXVECTOR3 vel)
	: m_Velocity(vel)
{
	player->SetAnimation(AnimationTag::Avoidance);
	player->SetInvincible(true);
}

void PlayerAvoidance::Update(Player * player)
{
	// Œ³‚ÌˆÊ’u + ˆÚ“®•ûŒü * ˆê‰ñ‚Ì’l + •‚‚­’l
	float ratio = 1.0f / player->GetAnimeEndFrame();
	D3DXVECTOR3 move = m_Velocity;

	std::vector<Obstancle*> obstancles = player->GetScene()->GetGameObjects<Obstancle>(ObjectType::eObObstancle);
	for (auto obs : obstancles)
	{
		if (Collision::GetInstance()->ObbToObb(player->GetObb(), obs->GetObb()))
		{
			D3DXVECTOR3 nor = player->GetPosition() - obs->GetPosition();
			D3DXVec3Normalize(&nor, &nor);
			move = D3DXVECTOR3(nor.x, 0.0f, nor.z) * 0.02f;
		}
	}

	player->SetTransformTrans(move);

	if (player->GetAnimeFrame() >= player->GetAnimeEndFrame())
	{
		player->SetInvincible(false);
		player->ChangeState(new PlayerStateSelector());
	}
}
