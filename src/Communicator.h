/*
* This file is a server part of tanx game.
*
* (c) Igor Lapichev <lapichev@mail.ru>
*
* For the full copyright and license information, please view the LICENSE
* file that was distributed with this source code.
*/

#pragma once

#include <boost/asio.hpp>
#include <mutex>

#define PORT_NUM 1977

#define MESSAGE_GET_CONTEXT "GetContext"
#define MESSAGE_MOVE "Move"
#define MESSAGE_SHOT "Shot"

#define STRING_SEPARATOR "  "
#define STRING_FINISH "\r\n"

class Communicator
{
public:
	static void runService();

	void prepareMessage(std::string & message);
private:
};