#pragma once

#include <boost/asio.hpp>
#include <mutex>

#define PORT_NUM 1977

class Communicator
{
public:
	static void runService();

private:
};