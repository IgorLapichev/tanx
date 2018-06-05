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

#include "Platform.h"
#include "Entity.h"
#include "Context.h"
#include "ObjectPool.h"
#include "Logics.h"
#include "MessageManager.h"
#include "MessageObserver.h"
#include "Communicator.h"
#include "ThreadPool.h"

int main()
{
	srand((unsigned int)time(NULL));

	std::thread thrdConnector1(Communicator::runService);
	thrdConnector1.detach();

//	std::thread thrdLoop1(CalcThread::loop);
//	thrdLoop1.detach();

	//CalcThread thread;
	//thread.appendFn();

	ThreadPool pool;
//	CalcThread thr;

	// testing
	MessageManager manager;
	manager.sendMessageCreate(typeid(StupidEntity).hash_code());
	manager.sendMessageCreate(typeid(StupidEntity).hash_code());

	double time = 0.;
	while (/*time < 1000.*/true)
	{
		Context::Instance().setContextDump();
		Context::Instance().cloneAgents();

		Dispatcher::Instance().processMessages();

		auto objects = Context::Instance().getSecondaryContext();
		for (auto & object : objects)
		{
			auto worker = pool.getFreeWorker();
			if (worker != nullptr)
				worker->setObject(object);
			else
				std::cout << "Null at: " << time << std::endl; // <<<<< ERROR in ThreadPool. Need to wait while all agents are done!
		}

		++time;
		std::cout << "Steps at: " << time << std::endl;
	}

    return 0;
}

