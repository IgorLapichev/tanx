#include "stdafx.h"

#include <algorithm>

#include "Entity.h"
#include "MessageObserver.h"
#include "Messagemanager.h"
#include "Context.h"

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

void Dispatcher::handleMessage(std::shared_ptr <Message> message)
{
	m_messages.push_back(message);
}

void Dispatcher::processMessages()
{
	Context & context = Context::Instance();

	for (auto & message : m_messages)
	{
		MessageManager manager;
		manager.parseMessage(message);
		
		int action;
		if (!manager.getRecordValue(ACTION, action))
			throw "Bad Message!";

		if (action == MessageManager::eAction::eActionCreate)
		{
			int typeId, parentId;
			if (!manager.getRecordValue(TYPEID, typeId) || !manager.getRecordValue(PARENT, parentId))
				throw "Bad Message!";

			auto entity = context.add(typeId, context.getById(parentId));
			Dispatcher::Instance().subscribe(entity);
		}
		else if (action == MessageManager::eAction::eActionKill)
		{
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
	}

	m_messages.clear();
}

void Dispatcher::createMessage()
{
	;
}