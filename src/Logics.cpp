#include "stdafx.h"

#include "defs.h"
#include "Logics.h"
#include "Entity.h"

void Logics::recalculate(const std::shared_ptr <StupidEntity> & pEntity)
{
	if (pEntity->m_moveStatus == eMoveStatus::moving)
		return;

	bool toMove = rand() * 2 / RAND_MAX;
	if (toMove)
	{
		pEntity->m_moveStatus = eMoveStatus::ready;
	}
	else
	{
		//eDirection direction = (eDirection)(rand() * 4 / RAND_MAX);
		//pEntity->m_direction = direction * PI / 180.;

		pEntity->m_direction = 270. * PI / 180.;
	}
}

void Logics::recalculate(const std::shared_ptr <MediumEntity> & pEntity)
{
	int r = 0;
}

void Logics::recalculate(const std::shared_ptr <SmartEntity> & pEntity)
{
	int r = 0;
}

void Logics::recalculate(const std::shared_ptr <BulletEntity> & pEntity)
{
	pEntity->m_moveStatus = eMoveStatus::moving;
}
