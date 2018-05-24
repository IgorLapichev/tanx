#include "stdafx.h"	

#include "defs.h"
#include "Entity.h"
#include "Context.h"
#include "Messagemanager.h"

void SpatialEntity::init()
{
	if (m_parent == nullptr)
	{
		//m_position = std::make_tuple((rand() * NUM_X * 2 / RAND_MAX + 1), 0);
		//m_nextposition = std::make_tuple(std::get<0>(m_position), std::get<1>(m_position));

		static int zzz = 0;
		if (zzz == 0)
		{
			m_position = std::make_tuple(1, 0);
		}
		else if (zzz == 1)
		{
			m_position = std::make_tuple(1, 3);
		}

		++zzz;
	}
	else
	{
		m_position = m_parent->getPosition();
		m_direction = m_parent->getDirection();
	}
}

void SpatialEntity::step(const double & time)
{
	switch (m_moveStatus)
	{
		case Logics::eMoveStatus::ready:
			{
				int next_x = std::get<0>(m_position) + int(cos(m_direction)); // ошибки!!!
				int next_y = std::get<1>(m_position) + int(sin(m_direction));

				if (next_x < 0 || next_x > NUM_X_CELLS || next_y < 0 || next_y > NUM_Y_CELLS)
				{
					m_moveStatus = Logics::eMoveStatus::idle;
					return;
				}
				
				for (auto & entity : Context::Instance().getAll())
				{
					if (entity->m_id != m_id)
						if (isOnCell(std::make_tuple(next_x, next_y)))
						{
							m_moveStatus = Logics::eMoveStatus::idle;
							return;
						}
				}

				m_nextposition = std::make_tuple(next_x, next_y);

				m_movingTime = 0;
				m_moveStatus = Logics::eMoveStatus::moving;
				return;
			}
			break;

		case Logics::eMoveStatus::moving:
			{
				int distance = m_speed * ++m_movingTime;
				/*
								m_map_position = std::make_tuple(std::get<0>(m_position) * CELL_SIZE + int(cos(m_direction) * distance),
																 std::get<1>(m_position) * CELL_SIZE + int(sin(m_direction) * distance));

								if (m_map_position == m_nextposition)
									m_moveStatus = Logics::eMoveStatus::idle;
								else
									++m_movingTime;
							}
							break;
				*/

				size_t bulletTypeId = typeid(BulletEntity).hash_code();
				if (m_typeId != bulletTypeId)
				{
					if (distance >= CELL_SIZE)
						m_moveStatus = Logics::eMoveStatus::idle;
				}
				else
				{
					if (distance >= CELL_SIZE)
					{
						int next_x = std::get<0>(m_position) + int(cos(m_direction)); // ошибки!!!
						int next_y = std::get<1>(m_position) + int(sin(m_direction));

						if (next_x < 0 || next_x > NUM_X_CELLS || next_y < 0 || next_y > NUM_Y_CELLS)
						{
							// kill bullet;
							//Dispatcher::Instance().handleMessage();
						}

						m_position = std::make_tuple(next_x, next_y);
					}
				}
			}
		default:
			break;
	}
}

bool SpatialEntity::isOnCell(std::tuple <int, int> position)
{
	return !(m_position == position && m_nextposition == position);
}

void TankEntity::shot(const double & time)
{
	if (time - m_lastReloaded < m_reloadTime)
		return;

	MessageManager manager;
	manager.sendMessageCreate(typeid(BulletEntity).hash_code(), m_id);

	m_lastReloaded = time;
}

void StupidEntity::init()
{
	m_speed = 1;
	m_numBullets = 1000;

	SpatialEntity::init();
}

void StupidEntity::step(const double & time)
{
	Logics logics;
	auto thisEntity = std::dynamic_pointer_cast <StupidEntity> (shared_from_this());
	logics.recalculate(thisEntity);

	SpatialEntity::step(time);
	shot(time);
}

void MediumEntity::init()
{
	int r = 0;
}

void MediumEntity::step(const double & time)
{
	int r = 0;
}

void SmartEntity::init()
{
	int r = 0;
}

void SmartEntity::step(const double & time)
{
	int r = 0;
}

void WallEntity::init()
{
	int r = 0;
}

void WallEntity::step(const double & time)
{
	int r = 0;
}

void BulletEntity::init()
{
	m_speed = 5;

	SpatialEntity::init();
}

void BulletEntity::step(const double & time)
{
	MessageManager manager;
	Logics logics;
	auto thisEntity = std::dynamic_pointer_cast <BulletEntity> (shared_from_this());
	logics.recalculate(thisEntity);

	int distance = m_speed * ++m_movingTime;
	if (distance >= CELL_SIZE)
	{
		int next_x = std::get<0>(m_position) + int(cos(m_direction));
		int next_y = std::get<1>(m_position) + int(sin(m_direction));

		// check bullet, shot other entity
		auto entities = Context::Instance().getAll();
		auto & position = m_position;
		auto & id = m_id;
		auto parentId = (m_parent == nullptr) ? 0 : m_parent->m_id;

		auto entity = std::find_if(entities.begin(),
			entities.end(),
			[&position, id, parentId](const auto & entity)
			{
				bool isMeOrParent = entity->m_id == id || entity->m_id == parentId;
				return entity->getPosition() == position && !isMeOrParent;
			});

		if (entity != entities.end())
		{
			manager.sendMessageKill((*entity)->m_id);
			manager.sendMessageKill(m_id);
			return;
		}

		// check bullet, out of range;
		if (next_x < 0 || next_x > NUM_X_CELLS || next_y < 0 || next_y > NUM_Y_CELLS)
		{
			manager.sendMessageKill(m_id);
			return;
		}

		m_position = std::make_tuple(next_x, next_y);
	}
}
