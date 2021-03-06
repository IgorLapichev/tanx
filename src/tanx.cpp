/*
* This file is a server part of tanx game.
*
* (c) Igor Lapichev <lapichev@mail.ru>
*
* For the full copyright and license information, please view the LICENSE
* file that was distributed with this source code.
*/

// tanx.cpp: entry point

#include "stdafx.h"

#include <memory>
#include <algorithm>
#include <thread>
#include<time.h>
#include <iostream>
#include <chrono>

#include "Platform.h"
#include "Entity.h"
#include "UnitEntity.h"
#include "Context.h"
#include "ObjectPool.h"
#include "Logics.h"
#include "MessageManager.h"
#include "MessageObserver.h"
#include "Communicator.h"
#include "ThreadPool.h"

int main()
{
	ThreadPool pool;
	srand((unsigned int)time(NULL));

	std::thread thrdConnector1(Communicator::runService);
	thrdConnector1.detach();

	// testing
	MessageManager manager;
	manager.sendMessageCreate(typeid(UnionEntity).hash_code());

	double time = 0.;
	while (/*time < 1000.*/true)
	{
		Context::Instance().setContextDump();
		Context::Instance().cloneAgents();

		Dispatcher::Instance().processMessages();

		auto objects = Context::Instance().getSecondaryContext();
		for (auto & object : objects)
		{
			// here pass all vehicles that are in union, union moves them by itself
			if (object->getParent() != nullptr)
				continue;

			while (true)
			{
				auto worker = pool.getFreeWorker();
				if (worker != nullptr)
				{
					worker->setObject(object);
					break;
				}
				else
					std::cout << "Null at: " << time << std::endl; 
			}
		}

		// in real  ERROR in ThreadPool. Need to wait while all agents are done!
		// for now just sleep
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		++time;
		std::cout << "Steps at: " << time << std::endl;
	}

    return 0;
}

