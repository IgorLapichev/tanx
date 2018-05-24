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

int main()
{
	srand((unsigned int)time(NULL));

	std::thread thrdConnector1(Communicator::runService);
	thrdConnector1.detach();

	// testing
	MessageManager manager;
	manager.sendMessageCreate(typeid(StupidEntity).hash_code());
	manager.sendMessageCreate(typeid(StupidEntity).hash_code());

	double time = 0.;
	while (/*time < 1000.*/true)
	{
		Dispatcher::Instance().processMessages();

		auto objects = Context::Instance().getAll();
		std::for_each(objects.begin(), objects.end(), [time](const auto & entity)
		{
			entity->step(time);
		});

		Context::Instance().setContextDump();

		++time;
		std::cout << "Steps" << std::endl;
	}

    return 0;
}

