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

#include <tuple>
#include <typeinfo>
#include <memory>
#include <string>

#define GETTYPEID(x) (typeid(x).hash_code())

struct BaseEntity : public std::enable_shared_from_this <BaseEntity>
{
	virtual void init() = 0;
	virtual void step(const double & time) = 0;

	virtual bool isOnCell(std::tuple <int, int> position) = 0;

	const size_t & getTypeId() const { return m_typeId; }
	const std::string & getEntityName() const { return m_entityName; }

	void setParent(const std::shared_ptr <BaseEntity> &  pParent) { m_parent = pParent; }

	virtual const std::tuple <int, int> & getPosition() = 0;
	virtual const double & getDirection() = 0;

	virtual const void setPosition(std::tuple <int, int> position) = 0;
	virtual const void setDirection(double direction) = 0;

	int										m_id = 0;
	std::shared_ptr <BaseEntity>			m_parent = nullptr;

protected:
	size_t									m_typeId = 0;
	std::string								m_entityName;
};

struct SpatialEntity : BaseEntity
{
	// Refactoring is needed
	std::tuple <int, int> m_position = std::make_tuple(-1, -1);
	std::tuple <int, int> m_nextposition = std::make_tuple(-1, -1);

	double m_direction = 0;
	int m_speed = 0;
	int m_movingTime = -1;
	int m_moveStatus = Logics::eMoveStatus::idle;

public:
	virtual void init() override;
	virtual void step(const double & time) override;

	virtual const std::tuple <int, int> & getPosition() final { return m_position; }
	virtual const double & getDirection() final { return m_direction; }

	virtual const void setPosition(std::tuple <int, int> position) final { m_position = position; }
	virtual const void setDirection(double direction) final { m_direction = direction; }

	virtual bool isOnCell(std::tuple <int, int> position) final;

protected:
};

struct TankEntity : SpatialEntity
{
	int m_numBullets = -1;
	double m_lastReloaded = 0;
	double m_reloadTime = 10;

	virtual void step(const double & time) override {;}

protected:
	void shot(const double & time);
};

struct StupidEntity : TankEntity
{
	StupidEntity()
	{
		m_typeId = GETTYPEID(StupidEntity);
		m_entityName = "StupidEntity";
	}

	virtual void init() final;
	virtual void step(const double & time) final;
};

struct MediumEntity : TankEntity
{
	MediumEntity()
	{
		m_typeId = GETTYPEID(MediumEntity);
		m_entityName = "MediumEntity";
	}

	virtual void init() final;
	virtual void step(const double & time) final;
};

struct SmartEntity : TankEntity
{
	SmartEntity()
	{
		m_typeId = GETTYPEID(SmartEntity);
		m_entityName = "SmartEntity";
	}

	virtual void init() final;
	virtual void step(const double & time) final;
};

struct WallEntity : SpatialEntity
{
	WallEntity()
	{
		m_typeId = GETTYPEID(WallEntity);
		m_entityName = "WallEntity";
	}

	virtual void init() final;
	virtual void step(const double & time) final;
};

struct ColumnEntity : SpatialEntity
{

};

struct BulletEntity : SpatialEntity
{
	BulletEntity()
	{
		m_typeId = GETTYPEID(BulletEntity);
		m_entityName = "BulletEntity";
	}

	virtual void init() final;
	virtual void step(const double & time) final;
};