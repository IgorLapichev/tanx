#include"stdafx.h"

#include "ObjectPool.h"

ObjectPool::ObjectPool()
{
	for (int i = 0; i < MAX_COLUMN_ENTITIES; ++i)
		initEntity <ColumnEntity>();

	for (int i = 0; i < MAX_BRICK_ENTITIES; ++i)
		initEntity <WallEntity>();

	for (int i = 0; i < MAX_TANK_ENTITIES; ++i)
	{
		initEntity <StupidEntity>();
		initEntity <MediumEntity>();
		initEntity <SmartEntity>();
	}

	for (int i = 0; i < MAX_BULLET_ENTITIES; ++i)
		initEntity <BulletEntity>();
}

ObjectPool::~ObjectPool()
{

}

/*ObjectPool & ObjectPool::Instance()
{
	return this;
}*/