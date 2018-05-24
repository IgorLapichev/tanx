#pragma once

#include <memory>

struct StupidEntity;
struct MediumEntity;
struct SmartEntity;

struct BulletEntity;

class Logics
{
public:
	enum eMoveStatus { idle = 0, ready, moving };
	enum eDirection { right = 0, up, left, down };

	void recalculate(const std::shared_ptr <StupidEntity> & pEntity);
	void recalculate(const std::shared_ptr <MediumEntity> & pEntity);
	void recalculate(const std::shared_ptr <SmartEntity> & pEntity);

	void recalculate(const std::shared_ptr <BulletEntity> & pEntity);
};

