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
#include <vector>

struct Point
{
	Point(double x, double y);

	double x = -1.;
	double y = -1.;
};

class Trajectory
{
public:
	void addPoint(std::shared_ptr <Point> point) { m_points.push_back(point); }
	const std::shared_ptr <Point> getNextPoint();

private:
	int m_currentPoint = -1;
	std::vector <std::shared_ptr <Point>> m_points;
};