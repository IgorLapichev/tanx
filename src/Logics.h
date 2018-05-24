/*
* This file is a server part of tanx game.
*
* (c) Igor Lapichev <lapichev@mail.ru>
*
* For the full copyright and license information, please view the LICENSE
* file that was distributed with this source code.
*/

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

