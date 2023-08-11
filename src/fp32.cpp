#include "./doctest/doctest.hpp"
#include "fp32.hpp"

FP32::FP32(int16_t whole_only)
{
	Value = whole_only << 16;
}

FP32::FP32(int32_t whole_only)
{
	Value = whole_only << 16;
}

FP32::FP32(float f)
{
	Value = (int32_t)(f * 0x10000);
}

FP32::FP32(double f)
{
	Value = (int32_t)(f * 0x10000);
}

FP32::FP32(int16_t whole, uint16_t fraction)
{
	Value = whole << 16 | fraction;
}

int16_t FP32::Truncate() {
	return Value / 0x10000;
}

int16_t FP32::Round() {
	int32_t temp = Value + ((Value & 0x80000000) ? 0xffff8000 : 0x8000);
	return temp / 0x10000;
}

bool operator==(FP32 lhs, const FP32& rhs)
{
	return lhs.Value == rhs.Value;
}

bool operator!=(FP32 lhs, const FP32& rhs)
{
	return lhs.Value != rhs.Value;
}

bool operator>=(FP32 lhs, const FP32& rhs)
{
	return lhs.Value >= rhs.Value;
}

bool operator>(FP32 lhs, const FP32& rhs)
{
	return lhs.Value > rhs.Value;
}

bool operator<=(FP32 lhs, const FP32& rhs)
{
	return lhs.Value <= rhs.Value;
}

bool operator<(FP32 lhs, const FP32& rhs)
{
	return lhs.Value < rhs.Value;
}

FP32 operator+(FP32 lhs, const FP32& rhs)
{
	lhs.Value += rhs.Value;
	return lhs;
}

FP32 operator-(FP32 lhs, const FP32& rhs)
{
	lhs.Value -= rhs.Value;
	return lhs;
}

FP32 operator*(FP32 lhs, const FP32& rhs)
{
	lhs.Value = (int32_t)((int64_t)lhs.Value * (int64_t)rhs.Value >> 16);
	return lhs;
}


TEST_CASE("FP32") {
	// CTORS
	CHECK(FP32(1).Value == 0x00010000);
	CHECK(FP32(5, 0x8000).Value == 0x00058000);
	CHECK(FP32(9.25f).Value == 0x00094000);
	CHECK(FP32(9.25).Value == 0x00094000);
	CHECK(FP32(-3.5).Value == (int32_t)0xfffc8000);

	// == Comparisons
	CHECK((FP32(3) == FP32(5)) == false);
	CHECK((FP32(7) == FP32(7)) == true);
	CHECK((FP32(11.19) == FP32(11.19)) == true);
	CHECK((FP32(-11.19) == FP32(11.19)) == false);

	// == Comparisons
	CHECK((FP32(3) != FP32(5)) == true);
	CHECK((FP32(7) != FP32(7)) == false);
	CHECK((FP32(11.19) != FP32(11.19)) == false);
	CHECK((FP32(-11.19) != FP32(11.19)) == true);

	// >= Comparisons
	CHECK((FP32(3) >= FP32(5)) == false);
	CHECK((FP32(7) >= FP32(7)) == true);
	CHECK((FP32(9) >= FP32(7)) == true);
	CHECK((FP32(11.18) >= FP32(11.19)) == false);
	CHECK((FP32(11.19) >= FP32(11.19)) == true);
	CHECK((FP32(11.191) >= FP32(11.19)) == true);
	CHECK((FP32(-11.19) >= FP32(11.19)) == false);

	// > Comparisons
	CHECK((FP32(3) > FP32(5)) == false);
	CHECK((FP32(7) > FP32(7)) == false);
	CHECK((FP32(9) > FP32(7)) == true);
	CHECK((FP32(11.18) > FP32(11.19)) == false);
	CHECK((FP32(11.19) > FP32(11.19)) == false);
	CHECK((FP32(11.191) > FP32(11.19)) == true);
	CHECK((FP32(-11.19) > FP32(11.19)) == false);
	CHECK((FP32(1.7) > FP32(-1.7)) == true);

	// <= Comparisons
	CHECK((FP32(3) <= FP32(5)) == true);
	CHECK((FP32(7) <= FP32(7)) == true);
	CHECK((FP32(9) <= FP32(7)) == false);
	CHECK((FP32(11.18) <= FP32(11.19)) == true);
	CHECK((FP32(11.19) <= FP32(11.19)) == true);
	CHECK((FP32(11.191) <= FP32(11.19)) == false);
	CHECK((FP32(-11.19) <= FP32(11.19)) == true);
	CHECK((FP32(1.7) <= FP32(-1.7)) == false);

	// < Comparisons
	CHECK((FP32(3) < FP32(5)) == true);
	CHECK((FP32(7) < FP32(7)) == false);
	CHECK((FP32(9) < FP32(7)) == false);
	CHECK((FP32(11.18) < FP32(11.19)) == true);
	CHECK((FP32(11.19) < FP32(11.19)) == false);
	CHECK((FP32(11.191) < FP32(11.19)) == false);
	CHECK((FP32(-11.19) < FP32(11.19)) == true);
	CHECK((FP32(1.7) < FP32(-1.7)) == false);

	// Addition
	CHECK((FP32(3) + FP32(5)).Value == 0x00080000);

	// Subtraction
	CHECK((FP32(11) - FP32(7)).Value == 0x00040000);
	CHECK((FP32(7) - FP32(11)).Value == 0xfffc0000);

	// Multiplication
	CHECK((FP32(13) * FP32(3)).Value == 0x00270000);
	CHECK((FP32(1.5) * FP32(1.5)).Value == 0x00024000);
	CHECK((FP32(32767) * FP32(0.5)).Value == 0x3fff8000);
	CHECK((FP32(-0.5) * FP32(10)).Round() == (int32_t)-5);

	// Truncate
	CHECK(FP32(75.36).Truncate() == (int16_t)75);
	CHECK(FP32(7.5).Truncate() == (int16_t)7);
	CHECK(FP32(-9.5).Truncate() == (int16_t)-9);
	CHECK(FP32(-5.2).Truncate() == (int16_t)-5);

	// Round
	CHECK(FP32(75.36).Round() == (int16_t)75);
	CHECK(FP32(123).Round() == (int16_t)123);
	CHECK(FP32(56.5).Round() == (int16_t)57);
	CHECK(FP32(99.4999).Round() == (int16_t)99);
	CHECK(FP32(88.999).Round() == (int16_t)89);
	CHECK(FP32(-75.36).Round() == (int16_t)-75);
	CHECK(FP32(-123).Round() == (int16_t)-123);
	CHECK(FP32(-56.5).Round() == (int16_t)-57);
	CHECK(FP32(-99.4999).Round() == (int16_t)-99);
	CHECK(FP32(-88.999).Round() == (int16_t)-89);
	CHECK(FP32(-0.5).Round() == (int16_t)-1);
}
