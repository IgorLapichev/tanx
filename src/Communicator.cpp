#include "stdafx.h"

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>
#include <boost/lexical_cast.hpp>

#include <bitset>

#include <iostream>

#include "Communicator.h"
#include "Context.h"
#include "MessageObserver.h"

void Communicator::runService()
{
	std::string message;

	try
	{
		boost::asio::io_service io_service;
		boost::system::error_code ignored_error;

		while (true)
		{
			boost::asio::ip::tcp::socket socket(io_service);
			boost::asio::ip::tcp::acceptor acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), PORT_NUM));
			acceptor.accept(socket);

//			boost::asio::read(socket,
//				boost::asio::buffer(message),
//				boost::asio::transfer_at_least(1), 
//				ignored_error);
			
			boost::asio::read_until(socket, boost::asio::dynamic_buffer(message), STRING_FINISH, ignored_error);
			size_t position = message.find(STRING_SEPARATOR);
			if (position != std::string::npos)
			{
				message = message.substr(position + strlen(STRING_SEPARATOR), message.length() - 1);
				message = message.substr(0, message.length() - strlen(STRING_FINISH));

				if (message.find(MESSAGE_GET_CONTEXT) != std::string::npos)
					Context::Instance().getContextDump(message);
				else if (message.find(MESSAGE_MOVE) != std::string::npos)
				{
					// manager is needed
					message = message.substr(strlen(MESSAGE_MOVE), message.length() - 1);
					Dispatcher::Instance().handleMessage(message);
				}
				else if (message.find(MESSAGE_SHOT) != std::string::npos)
				{
					// manager is needed
					Dispatcher::Instance().handleMessage(message);
				}
				else
					message = "";
			}

			boost::asio::write(socket,
				boost::asio::buffer(message), 
				ignored_error);
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

/*void Communicator::prepareMessage(std::string & message, const )
{

}*/

/*
void Communicator::test_runService()
{
	static int counter2 = 0;

	while (true)
	{
		std::lock_guard <std::mutex> locker(Context::Instance().m_locker);

		auto obj = Context::Instance().add(typeid(StupidEntity).hash_code());
		if (Context::Instance().getAll().size() > 0)
			Context::Instance().remove(Context::Instance().getAll()[0]);

		std::cout << "Second: " << ++counter2 << std::endl;
	}
}
*/