/*
* This file is a server part of tanx game.
*
* (c) Igor Lapichev <lapichev@mail.ru>
*
* For the full copyright and license information, please view the LICENSE
* file that was distributed with this source code.
*/

#include "stdafx.h"	


#include "UnitEntity.h"
#include "MessageManager.h"
#include "Context.h"

void UnionEntity::init()
{
	m_trajectory.addPoint(std::make_shared <Point> (10., 50.));
	m_trajectory.addPoint(std::make_shared <Point> (70., 90.));
	m_trajectory.addPoint(std::make_shared <Point> (60., 10.));
}

void UnionEntity::step(const double & time)
{
	switch (m_state)
	{
	case eStates::eStateCreate:
		CreateUnits();
		break;
	case eStates::eStateCollect:
		CollectUnits();
		break;
	case eStates::eStateDismiss:
		DismissUnits();
		break;
	case eStates::eStateStep:
		StepUnits(time);
		break;
	default:
		break;
	}
}

void UnionEntity::CreateUnits()
{
	MessageManager manager;
	manager.sendMessageCreate(typeid(UnitEntity).hash_code(), m_id);
	manager.sendMessageCreate(typeid(UnitEntity).hash_code(), m_id);
	manager.sendMessageCreate(typeid(UnitEntity).hash_code(), m_id);

	m_state = eStateCollect;
}

void UnionEntity::CollectUnits()
{
	int i = 0;
	auto objects = Context::Instance().getSecondaryContext();
	for (auto it = objects.begin(); it != objects.end(); ++it)
	{
		if ((*it)->getParent() != nullptr && (*it)->getParent()->m_id == m_id)
			m_units.push_back(*it);
	}

	if (m_units.size() > 0)
		m_state = eStateStep;
}

void UnionEntity::StepUnits(const double & time)
{
	for (auto & object : m_units)
		object->step(time);
}

void UnionEntity::DismissUnits()
{
	for (auto & object : m_units)
		object->setParent(nullptr);

	m_units.clear();
}







void UnitEntity::init()
{
	int r = 0;
}

void UnitEntity::step(const double & time)
{
	int r = 0;
}