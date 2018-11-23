/*
* This file is a server part of tanx game.
*
* (c) Igor Lapichev <lapichev@mail.ru>
*
* For the full copyright and license information, please view the LICENSE
* file that was distributed with this source code.
*/

#pragma once

#include "defs.h"

#include "Entity.h"

#include <memory>
#include <algorithm>
#include <vector>
#include <map>

#define MAX_COLUMN_ENTITIES NUM_X * NUM_Y
#define MAX_BRICK_ENTITIES 50
#define MAX_TANK_ENTITIES 10
#define MAX_BULLET_ENTITIES 100
#define MAX_UNION_ENTITIES 50
#define MAX_UNIT_ENTITIES 100

class ObjectPool
{
	struct Record
	{
		std::shared_ptr <BaseEntity> instance;
		bool						 in_use = false;
	};

public:
	ObjectPool();
	~ObjectPool();

	template <typename T> void initEntity()
	{
		Record record;
		record.instance = std::make_shared <T>();

		m_pool[typeid(T).hash_code()].push_back(record);
	}

	template <typename T> std::shared_ptr <BaseEntity> createEntity()
	{
		for (auto &entity : m_pool[typeid(T).hash_code()])
			if (!entity.in_use)
			{
				entity.in_use = true;
				return entity.instance;
			}

		return nullptr;
	}

	std::shared_ptr <BaseEntity> createEntity(size_t typeId)
	{
		for (auto &entity : m_pool[typeId])
			if (!entity.in_use)
			{
				entity.in_use = true;
				return entity.instance;
			}

		return nullptr;
	}

	void removeEntity(std::shared_ptr <BaseEntity> ptr)
	{
		auto it = std::find_if(m_pool[ptr->getTypeId()].begin(), m_pool[ptr->getTypeId()].end(), [&ptr](const auto & entity) {return entity.instance == ptr;});
		if (it != m_pool[ptr->getTypeId()].end())
			(*it).in_use = false;
	}

private:
	std::map <size_t, std::vector <Record>> m_pool;
};