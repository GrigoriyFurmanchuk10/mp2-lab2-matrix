#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 10000));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> exp(10);
	TDynamicVector<int> act(11);
	int  p = 1;
	for (int i = 0; i < exp.size(); i++) {
		exp[i] = p;
		p++;
	}
	act = exp;
	EXPECT_EQ(exp, act);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> exp(10);
	TDynamicVector<int> act(11);
	int  p = 1;
	for (int i = 0; i < exp.size(); i++) {
		exp[i] = p;
		p++;
	}
	act = exp;
	exp = exp.delmem();
	EXPECT_FALSE(act.isempt());
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
  TDynamicVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(4);
	ASSERT_ANY_THROW(v[-9] = 4);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(4);
	ASSERT_ANY_THROW(v[v.size() + 1] = 4);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(2);
	v[0] = 1;
	v[1] = 1;
	ASSERT_NO_THROW(v = v);
	EXPECT_EQ(1, v[0]);
	EXPECT_EQ(1, v[1]);
} 

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v1(2);
	TDynamicVector<int> v2(2);
	v1[0] = 1;
	v1[1] = 2;
	ASSERT_NO_THROW(v2 = v1);
	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	size_t size = 5;
	TDynamicVector<int> v1(size);
	TDynamicVector<int> v2(6);
	v1 = v2;
	EXPECT_NE(size, v1.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(6);
	ASSERT_NO_THROW(v1 = v2);
}


TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(3);
	for (size_t i = 0; i < 3; i++) {
		v1[i] = i;
		v2[i] = i;
	}
	EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v1(3);
	//TDynamicVector<int> v2(3);
	for (size_t i = 0; i < 3; i++) {
		v1[i] = i;
		//v2[i] = i;
	}
	EXPECT_TRUE(v1 == v1);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(4);
	EXPECT_TRUE(v1 != v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(3);
	for (size_t i = 0; i < 3; i++) {
		v1[i] = 1;
		v2[i] = 2;
		//v2[i] = i;
	}
	ASSERT_NO_THROW(v1 = v1 + 1);
	EXPECT_EQ(v2, v1);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(3);
	for (size_t i = 0; i < 3; i++) {
		v1[i] = 2;
		v2[i] = 1;
		//v2[i] = i;
	}
	ASSERT_NO_THROW(v1 = v1 -1);
	EXPECT_EQ(v2, v1);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(3);
	for (size_t i = 0; i < 3; i++) {
		v1[i] = 1;
		v2[i] = 2;
		//v2[i] = i;
	}
	ASSERT_NO_THROW(v1 = v1  * 2);
	EXPECT_EQ(v2, v1);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{	
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(3);
	TDynamicVector<int> v3(3);
	for (size_t i = 0; i < 3; i++) {
		v1[i] = 1;
		v2[i] = 2;
		v3[i] = 3;
	}
	EXPECT_EQ(v3, v1 + v2);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(4);
	for (size_t i = 0; i < 3; i++) {
		v1[i] = 1;
		v2[i] = 2;
	}
	v2[3] = 2;
	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(3);
	TDynamicVector<int> v3(3);
	for (size_t i = 0; i < 3; i++) {
		v1[i] = 3;
		v2[i] = 2;
		v3[i] = 1;
	}
	EXPECT_EQ(v3, v1 - v2);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(4);
	for (size_t i = 0; i < 3; i++) {
		v1[i] = 3;
		v2[i] = 2;
	}
	v2[3] = 2;
	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(3);
	for (size_t i = 0; i < 3; i++) {
		v1[i] = 3;
		v2[i] = 2;
	}
	int exp = 6 * 3;
	EXPECT_EQ(exp, v1 * v2);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(4);
	for (size_t i = 0; i < 3; i++) {
		v1[i] = 3;
		v2[i] = 2;
	}
	v2[3] = 2;
	ASSERT_ANY_THROW(v1 * v2);
}

