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
#include <memory>
#include <mutex>
#include <map>
#include <functional>

#include "Messagemanager.h"

struct BaseEntity;
struct Message;

class Dispatcher
{
	Dispatcher();
	Dispatcher(const Dispatcher& root) = delete;
	Dispatcher & operator = (const Dispatcher&) = delete;

public:
	static Dispatcher & Instance()
	{
		static Dispatcher theSingleInstance;
		return theSingleInstance;
	}

	bool subscribe(std::shared_ptr <BaseEntity> ptr);
	bool unsubscribe(std::shared_ptr <BaseEntity> ptr);

	void handleMessage(std::string & message);
	void processMessages();

	void processCreate(MessageManager & manager);
	void processKill(MessageManager & manager);
	void processMove(MessageManager & manager);
	void processShot(MessageManager & manager);

private:
	std::mutex																	m_locker;
	std::vector <std::shared_ptr <BaseEntity>>									m_subscribers;
	std::vector <std::string>													m_messages;

	//typedef void (Dispatcher::*Processor)(MessageManager &);
	//std::map <int, Processor>													m_processors;
	std::map <int, std::function <void(Dispatcher*, MessageManager & manager)>>	m_processors;

};