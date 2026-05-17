// file: test_figure_num_sync.cpp

#include <gtest/gtest.h>
//#include <gmock/gmock.h>

#include "round.h"
#include "figure.h"
#include "cube.h"

////__________________________________________________________________________________

TEST(FigureNumSync, MatchesCubeVectorSizeAfterConstruction)
{
	Round &round = Round::getInstance();

	round.reset();
	round.setGlass(10, 15);

	for(int i = 0; i < 100; ++i)
	{
		Figure fig;
		const int realCount = static_cast<int>(fig.getCubes().size());
		EXPECT_EQ(fig.getNum(), realCount);
	}
}

////__________________________________________________________________________________