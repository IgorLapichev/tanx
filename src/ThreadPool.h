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

#include "CalcThread.h"

#define NUM_THREADS 5

class ThreadPool
{
public:
	ThreadPool();
	~ThreadPool();

	std::shared_ptr <CalcThread> getFreeWorker();

private:
	std::vector<std::shared_ptr<CalcThread>> m_workers;

};