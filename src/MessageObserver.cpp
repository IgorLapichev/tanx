/*
* This file is a server part of tanx game.
*
* (c) Igor Lapichev <lapichev@mail.ru>
*
* For the full copyright and license information, please view the LICENSE
* file that was distributed with this source code.
*/

#include "stdafx.h"

#include <algorithm>
#include <mutex>

#include "Entity.h"
#include "MessageObserver.h"
#include "Context.h"

Dispatcher::Dispatcher()
{
	m_processors[MessageManager::eAction::eActionCreate]	= &Dispatcher::processCreate;
	m_processors[MessageManager::eAction::eActionKill]		= &Dispatcher::processKill;
	m_processors[MessageManager::eAction::eActionMove]		= &Dispatcher::processMove;
	m_processors[MessageManager::eAction::eActionShot]		= &Dispatcher::processShot;
}

bool Dispatcher::subscribe(const std::shared_ptr <BaseEntity> ptr)
{
	auto result = std::find(m_subscribers.begin(), m_subscribers.end(), ptr);
	if (result == m_subscribers.end())
	{
		m_subscribers.push_back(ptr);
		return true;
	}
	else
		return false;
}
bool Dispatcher::unsubscribe(const std::shared_ptr <BaseEntity> ptr)
{
	m_subscribers.erase(
		std::remove_if(m_subscribers.begin(),
			m_subscribers.end(),
		[ptr](const auto & entity) {return entity == ptr; }),
		m_subscribers.end()
	);
	return true;
}

void Dispatcher::handleMessage(std::string & message)
{
	std::lock_guard <std::mutex> locker(m_locker);
	m_messages.push_back(message);
}

void Dispatcher::processMessages()
{
	Context & context = Context::Instance();

	std::lock_guard <std::mutex> locker(m_locker);
	for (auto & message : m_messages)
	{
		MessageManager manager;
		if (!manager.parseMessage(message))
			continue;//throw "Bad Message!";
		
		int action;
		if (!manager.getRecordValue(ACTION, action))
			continue;//throw "Bad Message!";
		try
		{
			//(this->*m_processors[action])(manager);
			m_processors[action](this, manager);
		}
		catch (std::string)
		{
			continue;
		}
	}

	m_messages.clear();
}

void Dispatcher::processCreate(MessageManager & manager)
{
	Context & context = Context::Instance();
	size_t typeId;
	int parentId;

	if (!manager.getRecordValue(TYPEID, typeId) || !manager.getRecordValue(PARENT, parentId))
		throw "Bad Message!";

	auto entity = context.add(typeId, context.getById(parentId));
	Dispatcher::Instance().subscribe(entity);
}

void Dispatcher::processKill(MessageManager & manager)
{
	Context & context = Context::Instance();
	int receiverId;
	if (!manager.getRecordValue(RECEIVERID, receiverId))
		throw "Bad Message!";

	auto it = std::find_if(m_subscribers.begin(), m_subscribers.end(), [&receiverId](auto & entity)
	{
		if (entity != nullptr)
			return entity->m_id == receiverId;
		else
			return false;
	});

	if (it != m_subscribers.end())
	{
		context.remove(*it);
		unsubscribe(*it);
	}
}

void Dispatcher::processMove(MessageManager & manager)
{
	int r = 0;
}

void Dispatcher::processShot(MessageManager & manager)
{
	int r = 0;
}

