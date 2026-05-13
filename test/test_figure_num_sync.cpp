#include "gtest/gtest.h"

#include "round.h"
#include "figure.h"

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
