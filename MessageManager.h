#pragma once

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <memory>

#define ACTION		"action"
#define TYPEID		"typeid"
#define PARENT		"parent"
#define RECEIVERID	"receiverid"
#define DIRECTION	"direction"

/*
struct Message
{
	std::string		m_text = "";
	double			m_time = -1;
	int				m_receiverId = 0;
};
*/

class MessageManager
{
public:
	enum eAction { eActionCreate, eActionKill, eActionMove, eActionShot };

	void startMessage();
	void finishAndSendMessage();

	void addRecord(const std::string & key, const std::string & value);
	void addRecord(const std::string & key, const int & value);
	void addRecord(const std::string & key, const double & value);
	void addRecord(const std::string & key, const size_t & value);

	bool parseMessage(const std::string & message);
	bool getRecordValue(const std::string & key, int & value);
	bool getRecordValue(const std::string & key, std::string & value);
	bool getRecordValue(const std::string & key, size_t & value);

	void sendMessageCreate(size_t typeId, int parentId = 0);
	void sendMessageKill(int id);
	void sendMessageMove(int id, double direction);
	void sendMessageShot(int id);

private:
	rapidjson::Document m_jsonDoc;
};