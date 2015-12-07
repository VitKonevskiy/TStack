
#include "../Stack (m)/Stack.h"
#include "../Stack (m)/TParser.h"
#include "../gtests/gtest.h"

TEST(Stack, can_create_matrix_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> S(5));
}
TEST(Stack, can_create_matrix_with_positive_length2)
{
	ASSERT_ANY_THROW(TStack<int> S(5));
}


int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}