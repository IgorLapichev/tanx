/*
* This file is a server part of tanx game.
*
* (c) Igor Lapichev <lapichev@mail.ru>
*
* For the full copyright and license information, please view the LICENSE
* file that was distributed with this source code.
*/

#include "stdafx.h"

#include "MessageManager.h"
#include "MessageObserver.h"

void MessageManager::startMessage()
{
	m_jsonDoc.SetObject();
}

void MessageManager::finishAndSendMessage()
{
	rapidjson::StringBuffer strBuf;
	rapidjson::Writer <rapidjson::StringBuffer> writer(strBuf);
	m_jsonDoc.Accept(writer);
	
	std::string message = strBuf.GetString();
	Dispatcher::Instance().handleMessage(message);
}

void MessageManager::addRecord(const std::string & key, const std::string & value)
{
	auto & allocator = m_jsonDoc.GetAllocator();
	m_jsonDoc.AddMember(rapidjson::Value(key.c_str(), allocator).Move(), rapidjson::Value(value.c_str(), allocator).Move(), allocator);
}

void MessageManager::addRecord(const std::string & key, const int & value)
{
	auto & allocator = m_jsonDoc.GetAllocator();
	m_jsonDoc.AddMember(rapidjson::Value(key.c_str(), allocator).Move(), rapidjson::Value().SetInt(value), allocator);
}

void MessageManager::addRecord(const std::string & key, const double & value)
{
	auto & allocator = m_jsonDoc.GetAllocator();
	m_jsonDoc.AddMember(rapidjson::Value(key.c_str(), allocator).Move(), rapidjson::Value().SetDouble(value), allocator);
}

void MessageManager::addRecord(const std::string & key, const size_t & value)
{
	auto & allocator = m_jsonDoc.GetAllocator();
	m_jsonDoc.AddMember(rapidjson::Value(key.c_str(), allocator).Move(), rapidjson::Value().SetUint64(value), allocator);
}

void MessageManager::sendMessageCreate(size_t typeId, int parentId)
{
	startMessage();
	addRecord(ACTION, eActionCreate);
	addRecord(TYPEID, typeId);
	addRecord(PARENT, parentId);
	finishAndSendMessage();
}

void MessageManager::sendMessageKill(int id)
{
	startMessage();
	addRecord(ACTION, eActionKill);
	addRecord(RECEIVERID, id);
	finishAndSendMessage();
}

void MessageManager::sendMessageMove(int id, double direction)
{
	startMessage();
	addRecord(ACTION, eActionMove);
	addRecord(RECEIVERID, id);
	addRecord(DIRECTION, direction);
	finishAndSendMessage();
}

void MessageManager::sendMessageShot(int id)
{
	startMessage();
	addRecord(ACTION, eActionShot);
	addRecord(RECEIVERID, id);
	finishAndSendMessage();
}

bool MessageManager::parseMessage(const std::string & message)
{
	m_jsonDoc.Parse(message.c_str());
	if (m_jsonDoc.HasParseError())
		return false;
	return true;
}

bool MessageManager::getRecordValue(const std::string & key, int & value)
{
	if (m_jsonDoc.HasMember(key.c_str()) && m_jsonDoc[key.c_str()].IsInt())
	{
		value = m_jsonDoc[key.c_str()].GetInt();
		return true;
	}
	else
		return false;
}

bool MessageManager::getRecordValue(const std::string & key, size_t & value)
{
	if (m_jsonDoc.HasMember(key.c_str()) && m_jsonDoc[key.c_str()].IsUint64())
	{
		value = m_jsonDoc[key.c_str()].GetUint64();
		return true;
	}
	else
		return false;
}

bool MessageManager::getRecordValue(const std::string & key, std::string & value)
{
	if (m_jsonDoc.HasMember(key.c_str()) && m_jsonDoc[key.c_str()].IsString())
	{
		value = m_jsonDoc[key.c_str()].GetString();
		return true;
	}
	else
		return false;
}

bool MessageManager::getRecordValue(const std::string & key, double & value)
{
	if (m_jsonDoc.HasMember(key.c_str()) && m_jsonDoc[key.c_str()].IsDouble())
	{
		value = m_jsonDoc[key.c_str()].GetDouble();
		return true;
	}
	else
		return false;
}