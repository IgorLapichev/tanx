/*
* This file is a server part of tanx game.
*
* (c) Igor Lapichev <lapichev@mail.ru>
*
* For the full copyright and license information, please view the LICENSE
* file that was distributed with this source code.
*/

#include "stdafx.h"

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <algorithm>

#include "Context.h"
#include "Entity.h"

void Context::remove(const std::shared_ptr <BaseEntity> & ptr)
{
	m_primaryContext.erase(
		std::remove_if(m_primaryContext.begin(),
			m_primaryContext.end(),
		[ptr](const auto & entity) {return entity == ptr;}), 
		m_primaryContext.end()
	);

	m_pool.removeEntity(ptr);
}

const std::shared_ptr <BaseEntity> Context::add(size_t typeId, const std::shared_ptr <BaseEntity> &  pParent)
{
	const std::shared_ptr <BaseEntity> ptr = m_pool.createEntity(typeId);
	if (ptr != nullptr)
	{
		ptr->setParent(pParent);
		ptr->init();
		ptr->m_id = (0 << 16) + ++m_counter;

		m_primaryContext.push_back(ptr);
	}

	return ptr;
}

void Context::clone(const std::shared_ptr <BaseEntity> & original)
{
	const std::shared_ptr <BaseEntity> ptr = m_pool.createEntity(original->getTypeId());
	if (ptr != nullptr)
	{
		// need to make virtual clone() in entity
		ptr->setParent(original->m_parent);
		
		ptr->setPosition(original->getPosition());
		ptr->setDirection(original->getDirection());

		ptr->m_id = original->m_id;

		m_secondaryContext.push_back(ptr);
	}
}

const std::shared_ptr <BaseEntity> Context::getById(const int & id)
{
	if (id <= 0)
		return nullptr;

	auto entity = std::find_if(m_primaryContext.begin(),
		m_primaryContext.end(),
		[id](const auto & entity)
	{
		return entity->m_id == id;
	});
	if (entity == m_primaryContext.end())
		return nullptr;

	return *entity;
}

void Context::swap()
{
	//m_currentContext == *m_context ? m_currentContext = *m_context : m_currentContext = *(m_context + 1);
}

void Context::setContextDump()
{
	rapidjson::Document jsonDoc;
	jsonDoc.SetObject();
	auto & allocator = jsonDoc.GetAllocator();
	rapidjson::Value jsonObjects(rapidjson::kArrayType);

	for (auto & object : m_primaryContext)
	{
		rapidjson::Value jsonObject(rapidjson::kObjectType);

		jsonObject.AddMember(rapidjson::Value("Entity", allocator).Move(), rapidjson::Value(object->getEntityName().c_str(), allocator), allocator);
		jsonObject.AddMember(rapidjson::Value("x", allocator).Move(), rapidjson::Value().SetInt(std::get<0>(object->getPosition())), allocator);
		jsonObject.AddMember(rapidjson::Value("y", allocator).Move(), rapidjson::Value().SetInt(std::get<1>(object->getPosition())), allocator);
		jsonObject.AddMember(rapidjson::Value("Direction", allocator).Move(), rapidjson::Value().SetDouble(object->getDirection()), allocator);

		jsonObjects.PushBack(jsonObject.Move(), allocator);
	}
	jsonDoc.AddMember(rapidjson::Value("Objects", allocator).Move(), jsonObjects.Move(), allocator);

	rapidjson::StringBuffer strBuf;
	rapidjson::Writer <rapidjson::StringBuffer> writer(strBuf);
	jsonDoc.Accept(writer);

	std::lock_guard <std::mutex> locker(m_locker);
	m_dump = strBuf.GetString();
}

void Context::getContextDump(std::string & message)
{
	std::lock_guard <std::mutex> locker(m_locker);
	message = m_dump;
}

void Context::cloneAgents()
{
	for (auto & object : m_secondaryContext)
		remove(object);
	m_secondaryContext.clear();

	for (auto & object : m_primaryContext)
		clone(object);
}

const std::vector <std::shared_ptr <BaseEntity>> & Context::getSecondaryContext() const
{
	return m_secondaryContext;
}


/*
bool Context::isCellBusy(std::tuple <int, int> position)
{
	for (auto entity : m_currentContext)
	{
		auto entityPosition = entity->getPosition();
		if (std::get<0>(entityPosition) == std::get<0>(position) && std::get<1>(entityPosition) == std::get<1>(position))
			return true;
	}

	return false;
}

bool Context::isCellOutOfRange(std::tuple <int, int> position)
{
	return std::get<0>(position) >= 0 || std::get<0>(position) <= NUM_X_CELLS || std::get<1>(position) >= 0 || std::get<1>(position) <= NUM_Y_CELLS;
}
*/