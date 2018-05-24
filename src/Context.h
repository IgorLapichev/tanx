/*
* This file is a server part of tanx game.
*
* (c) Igor Lapichev <lapichev@mail.ru>
*
* For the full copyright and license information, please view the LICENSE
* file that was distributed with this source code.
*/

#pragma once

#include <vector>
#include <map>
#include <memory>
#include <mutex>

#include "ObjectPool.h"

struct BaseEntity;

class Context
{
	Context() {};
	Context(const Context& root) = delete;
	Context & operator = (const Context&) = delete;

public:
	enum eEntityType {Column, Brick, Tank, Bullet};
	
	static Context & Instance()
	{
		static Context theSingleInstance;
		return theSingleInstance;
	}

	const std::vector <std::shared_ptr <BaseEntity>> getAll() const { return m_currentContext; }
	const std::shared_ptr <BaseEntity> getById(const int & id);

	const std::shared_ptr <BaseEntity> add(size_t typeId, const std::shared_ptr <BaseEntity> &  pParent = nullptr);
	template <typename T> auto add(const std::shared_ptr <BaseEntity> &  pParent = nullptr)
	{
		auto ptr = m_pool.createEntity <T>();
		if (ptr != nullptr)
		{
			ptr->setParent(pParent);
			ptr->init();

			ptr->m_id = (0 << 8) + ++m_counter;

			m_currentContext.push_back(ptr);
		}

		return ptr;
	}
	
	void remove(const std::shared_ptr <BaseEntity> & ptr);

	void setContextDump();
	void getContextDump(std::string & message);

	void swap();

	//////////// move to ContextManager
//	bool isCellBusy(std::tuple <int, int> position);
//	bool isCellOutOfRange(std::tuple <int, int> position);

	std::mutex									m_locker;

private:
	int											m_counter = 0;

	std::string									m_dump;
	ObjectPool									m_pool;
	std::vector <std::shared_ptr <BaseEntity>>	m_context[2];
	std::vector <std::shared_ptr <BaseEntity>>	m_currentContext = m_context[0];

};