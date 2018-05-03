#pragma once

#include <vector>
#include <memory>

struct BaseEntity;
struct Message;

class Dispatcher
{
	Dispatcher() {};
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

	void handleMessage(std::shared_ptr <Message> message);
	void processMessages();

	void createMessage();

private:
	std::vector <std::shared_ptr <BaseEntity>> m_subscribers;
	std::vector <std::shared_ptr <Message>> m_messages;
};