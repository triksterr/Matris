// file: test_figure_move_rotate.cpp

#include <gtest/gtest.h>

#include "round.h"
#include "figure.h"
#include "layers.h"
#include "rules.h"

#include <vector>

namespace
{
	bool samePositions(const std::vector<Cube> &a, const std::vector<Cube> &b)
	{
		if(a.size() != b.size())
			return false;

		for(std::size_t i = 0; i < a.size(); ++i)
			if(a[i].getX() != b[i].getX() || a[i].getY() != b[i].getY())
				return false;

		return true;
	}

	bool inBounds(const Cube &cube, int w, int h)
	{
		return cube.getX() >= 0 && cube.getX() < w && cube.getY() >= 0 && cube.getY() < h;
	}
}

TEST(FigureMoveRotate, MoveAndRotateKeepFigureInsideGlass)
{
	Round &round = Round::getInstance();
	Layers &layers = Layers::getInstance();

	round.reset();
	round.setGlass(10, 15);
	layers.Init();

	for(int i = 0; i < 200; ++i)
	{
		Figure fig;
		const int beforeNum = fig.getNum();
		const int beforeCount = static_cast<int>(fig.getCubes().size());

		fig.rotateR();
		fig.rotateL();
		fig.moveL(1);
		fig.moveR(1);
		fig.moveU(1);
		fig.moveD(1);

		const std::vector<Cube> cubes = fig.getCubes();
		for(const Cube &cube : cubes)
			EXPECT_TRUE(inBounds(cube, round.getGlassW(), round.getGlassH()));

		EXPECT_EQ(fig.getNum(), beforeNum);
		EXPECT_EQ(static_cast<int>(cubes.size()), beforeCount);
	}
}

TEST(FigureMoveRotate, MoveBlockedByLayersCollision)
{
	Round &round = Round::getInstance();
	Layers &layers = Layers::getInstance();

	round.reset();
	round.setGlass(10, 15);
	layers.Init();

	Figure fig;
	const std::vector<Cube> before = fig.getCubes();

	if(before.empty())
	{
		SUCCEED();
		return;
	}

	const Cube &base = before.front();
	int dx = (base.getX() + 1 < round.getGlassW()) ? 1 : -1;
	const int ox = base.getX() + dx;
	const int oy = base.getY();

	for(const Cube &cube : before)
		if(cube.getX() == ox && cube.getY() == oy)
		{
			SUCCEED();
			return;
		}

	Cube obstacle(ox, oy, 7, RGBcolor(255, 255, 255));
	ASSERT_TRUE(layers.writeCube(&obstacle));

	if(dx > 0)
		fig.moveR(1);
	else
		fig.moveL(1);

	const std::vector<Cube> after = fig.getCubes();
	EXPECT_TRUE(samePositions(before, after));
}

TEST(FigureMoveRotate, RotateBlockedByLayersCollision)
{
	Round &round = Round::getInstance();
	Layers &layers = Layers::getInstance();

	round.reset();
	round.setGlass(10, 15);
	layers.Init();

	bool prepared = false;
	for(int attempt = 0; attempt < 200 && !prepared; ++attempt)
	{
		Figure fig;
		const std::vector<Cube> before = fig.getCubes();
		if(before.size() < 2)
			continue;

		const int cx = fig.getX();
		const int cy = fig.getY();

		for(const Cube &cube : before)
		{
			const Point offset{cube.getX() - cx, cube.getY() - cy};
			if(offset.x == 0 && offset.y == 0)
				continue;

			const Point targetOffset = rotateP(offset, 90);
			const int tx = cx + targetOffset.x;
			const int ty = cy + targetOffset.y;

			if(tx < 0 || tx >= round.getGlassW() || ty < 0 || ty >= round.getGlassH())
				continue;

			bool occupiedNow = false;
			for(const Cube &c : before)
				if(c.getX() == tx && c.getY() == ty)
				{
					occupiedNow = true;
					break;
				}
			if(occupiedNow)
				continue;

			Cube obstacle(tx, ty, 5, RGBcolor(255, 255, 255));
			if(!layers.writeCube(&obstacle))
				continue;

			fig.rotateR();
			const std::vector<Cube> after = fig.getCubes();
			EXPECT_TRUE(samePositions(before, after));
			prepared = true;
			break;
		}

		layers.Init();
	}

	if(!prepared)
		SUCCEED();
}
