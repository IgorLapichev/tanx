/*
* This file is a server part of tanx game.
*
* (c) Igor Lapichev <lapichev@mail.ru>
*
* For the full copyright and license information, please view the LICENSE
* file that was distributed with this source code.
*/

#pragma once
/*
class CalcThread
{
public:

	static void loop();
};
*/

#include <thread>
#include <condition_variable>

struct BaseEntity;

class CalcThread
{
public:

	CalcThread();
	~CalcThread();

	void setObject(std::shared_ptr <BaseEntity> ptr);
	bool isBusy();

private:

	bool							m_isBusy = false;
	std::condition_variable			m_cv;
	std::mutex						m_mutex;
	std::thread						m_worker;

	std::shared_ptr <BaseEntity>	m_object;

	void loop();

	//	void thread_fn();
};
