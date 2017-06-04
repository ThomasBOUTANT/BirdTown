#include "gtest/gtest.h"
#include "../BirdTown_Bibliotheque/monMain.h"

TEST(Exemple1, Factorielle)
{
	EXPECT_EQ(1, factorielle(-1));
	EXPECT_EQ(1, factorielle(0));
	EXPECT_EQ(6, factorielle(3));
}

TEST(Exemple1, CarreParfait)
{
	EXPECT_FALSE(estUnCarreParfait(-2));
	EXPECT_TRUE(estUnCarreParfait(0));
	EXPECT_TRUE(estUnCarreParfait(4));
	EXPECT_FALSE(estUnCarreParfait(8));
}