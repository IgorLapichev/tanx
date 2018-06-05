/*
* This file is a server part of tanx game.
*
* (c) Igor Lapichev <lapichev@mail.ru>
*
* For the full copyright and license information, please view the LICENSE
* file that was distributed with this source code.
*/

#include "stdafx.h"

#include "CalcThread.h"
#include "Context.h"
#include "Entity.h"
/*
void CalcThread::loop()
{
	while (true)
	{
		auto entity = Context::Instance().getNextObject();
		if (entity == nullptr)
			continue;

		entity->step(0);
	}
}*/

CalcThread::CalcThread() : m_worker(&CalcThread::loop, this)
{
}

CalcThread::~CalcThread()
{
	m_cv.notify_one();
	m_worker.join();
}
void CalcThread::setObject(std::shared_ptr <BaseEntity> ptr)
{
	std::unique_lock <std::mutex> locker(m_mutex);
	
	m_isBusy = true;
	m_object = ptr;

	m_cv.notify_one();
}

bool CalcThread::isBusy()
{
	std::unique_lock <std::mutex> locker(m_mutex);
	return m_isBusy;
}

void CalcThread::loop()
{
	while (true)
	{
		std::unique_lock <std::mutex> locker(m_mutex);
		
		m_cv.wait(locker, [&]() { return m_isBusy; });

		locker.unlock();
		m_object->step(0);
		locker.lock();

		m_isBusy = false;
	}
}