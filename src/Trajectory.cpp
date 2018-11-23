/*
* This file is a server part of tanx game.
*
* (c) Igor Lapichev <lapichev@mail.ru>
*
* For the full copyright and license information, please view the LICENSE
* file that was distributed with this source code.
*/

#include "stdafx.h"	


#include "Trajectory.h"

Point::Point(double x, double y) 
{
	this->x = x;
	this->y = y;
}


const std::shared_ptr <Point> Trajectory::getNextPoint()
{
	++m_currentPoint;

	if (m_currentPoint >= m_points.size())
		return nullptr;
	else
		return m_points[m_currentPoint];
}