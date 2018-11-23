/*
* This file is a server part of tanx game.
*
* (c) Igor Lapichev <lapichev@mail.ru>
*
* For the full copyright and license information, please view the LICENSE
* file that was distributed with this source code.
*/

#pragma once

#include "Logics.h"
#include "Entity.h"
#include "Trajectory.h"

#include <list>

struct UnionEntity : public SpatialEntity
{
	UnionEntity()
	{
		m_typeId = GETTYPEID(UnionEntity);
		m_entityName = "UnionEntity";
	}

	virtual void init() final;
	virtual void step(const double & time) final;

	const std::list <std::shared_ptr <BaseEntity>> getUnits() { return m_units; }

private:
	enum eStates {eStateCreate = 0, eStateCollect, eStateDismiss, eStateStep};

	void CreateUnits();
	void CollectUnits();
	void StepUnits(const double & time);
	void DismissUnits();

	int m_state = eStateCreate;
	std::list <std::shared_ptr <BaseEntity>> m_units;
	Trajectory m_trajectory;
};







struct UnitEntity : public SpatialEntity
{
	UnitEntity()
	{
		m_typeId = GETTYPEID(UnitEntity);
		m_entityName = "UnitEntity";
	}

	virtual void init() final;
	virtual void step(const double & time) final;

private:
	enum eStates { eStateIdle = 0, eStateMoveLine, eStateMoveFront };

	int m_orderIndex;
};