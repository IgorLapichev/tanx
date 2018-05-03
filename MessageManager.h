#pragma once

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <memory>

#define ACTION		"action"
#define TYPEID		"typeid"
#define PARENT		"parent"
#define RECEIVERID	"receiverid"

struct Message
{
	std::string		m_text = "";
	double			m_time = -1;
	int				m_receiverId = 0;
};

class MessageManager
{
public:
	enum eAction { eActionCreate, eActionKill };

	void startMessage();
	void finishAndSendMessage();

	void addRecord(const std::string & key, const std::string & value);
	void addRecord(const std::string & key, const int & value);

	void parseMessage(const std::shared_ptr <Message> & message);
	bool getRecordValue(const std::string & key, int & value);
	bool getRecordValue(const std::string & key, std::string & value);

	void sendMessageCreate(size_t typeId, int parentId = 0);
	void sendMessageKill(int id);

	std::string packContext();

private:
	rapidjson::Document m_jsonDoc;
};