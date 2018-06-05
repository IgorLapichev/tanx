/*
* This file is a server part of tanx game.
*
* (c) Igor Lapichev <lapichev@mail.ru>
*
* For the full copyright and license information, please view the LICENSE
* file that was distributed with this source code.
*/

#include "stdafx.h"

#include "ThreadPool.h"

ThreadPool::ThreadPool()
{
	for (size_t i = 0; i < NUM_THREADS; ++i)
	{
		auto pWorker = std::make_shared <CalcThread> ();
		m_workers.push_back(pWorker);
	}
}

ThreadPool::~ThreadPool() {}

std::shared_ptr <CalcThread> ThreadPool::getFreeWorker()
{
	std::shared_ptr <CalcThread> pWorker = nullptr;

	for (auto & it : m_workers)
	{
		if (it->isBusy())
			continue;

		pWorker = it;
		break;
	}

	return pWorker;
}