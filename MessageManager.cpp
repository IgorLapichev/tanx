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
	
	std::shared_ptr <Message> message = std::make_shared <Message>();
	message->m_text = strBuf.GetString();

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

void MessageManager::parseMessage(const std::shared_ptr <Message> & message)
{
//	m_jsonDoc.Clear();
	m_jsonDoc.Parse(message->m_text.c_str());
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

std::string MessageManager::packContext()
{
	rapidjson::Document jsonDoc;
	jsonDoc.SetObject();
	auto & allocator = jsonDoc.GetAllocator();

//	rapidjson::Value o(rapidjson::kObjectType);
//	{
		rapidjson::Value contacts(rapidjson::kArrayType);

		rapidjson::Value v1(rapidjson::kObjectType);
		v1.AddMember(rapidjson::Value("111", allocator).Move(), rapidjson::Value("121", allocator).Move(), allocator);
		v1.AddMember(rapidjson::Value("112", allocator).Move(), rapidjson::Value("122", allocator).Move(), allocator);

		contacts.PushBack(v1.Move(), allocator);

		rapidjson::Value v2(rapidjson::kObjectType);
		v2.AddMember(rapidjson::Value("211", allocator).Move(), rapidjson::Value("221", allocator).Move(), allocator);
		v2.AddMember(rapidjson::Value("212", allocator).Move(), rapidjson::Value("222", allocator).Move(), allocator);

		contacts.PushBack(v2.Move(), allocator);

//		o.AddMember("contacts", contacts, allocator);
//	}

	jsonDoc.AddMember(rapidjson::Value("contacts", allocator).Move(), contacts.Move(), allocator);

	rapidjson::StringBuffer strBuf;
	rapidjson::Writer <rapidjson::StringBuffer> writer(strBuf);
	jsonDoc.Accept(writer);

	std::shared_ptr <Message> message = std::make_shared <Message>();
	message->m_text = strBuf.GetString();

	return "";
}