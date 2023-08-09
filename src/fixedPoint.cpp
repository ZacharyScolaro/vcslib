#include "./doctest/doctest.hpp"

#include <stdint.h>
	
// Assumes dev system and target system are both little endian

class Fixed16_16 {
public:
	int32_t Value;
	Fixed16_16(int16_t whole_only)
	{
		Value = whole_only << 16;
	}
	Fixed16_16(int32_t whole_only)
	{
		Value = whole_only << 16;
	}
	Fixed16_16(float f)
	{
		Value = (int32_t)(f * 0x10000);
	}
	Fixed16_16(double f)
	{
		Value = (int32_t)(f * 0x10000);
	}
	Fixed16_16(int16_t whole, uint16_t fraction)
	{
		Value = whole << 16 | fraction;
	}

	int16_t Truncate() {
		return Value / 0x10000;
	}

	int16_t Round() {
		int32_t temp = Value + ((Value & 0x80000000) ? 0xffff8000 : 0x8000);
		return temp / 0x10000;
	}

	friend Fixed16_16 operator+(Fixed16_16 lhs,const Fixed16_16& rhs)
	{
		lhs.Value += rhs.Value;
		return lhs;
	}

	friend Fixed16_16 operator-(Fixed16_16 lhs,const Fixed16_16& rhs)
	{
		lhs.Value -= rhs.Value;
		return lhs;
	}

	friend Fixed16_16 operator*(Fixed16_16 lhs, const Fixed16_16& rhs)
	{
		lhs.Value = (int32_t)((int64_t)lhs.Value * (int64_t)rhs.Value >> 16);
		return lhs;
	}
};

TEST_CASE("Fixed16_16"){
	// CTORS
	CHECK(Fixed16_16(1).Value == 0x00010000);
	CHECK(Fixed16_16(5, 0x8000).Value == 0x00058000);
	CHECK(Fixed16_16(9.25f).Value == 0x00094000);
	CHECK(Fixed16_16(9.25).Value == 0x00094000);
	CHECK(Fixed16_16(-3.5).Value == (int32_t)0xfffc8000);

	// Addition
	CHECK((Fixed16_16(3) + Fixed16_16(5)).Value == 0x00080000);

	// Subtraction
	CHECK((Fixed16_16(11) - Fixed16_16(7)).Value == 0x00040000);
	CHECK((Fixed16_16(7) - Fixed16_16(11)).Value == 0xfffc0000);

	// Multiplication
	CHECK((Fixed16_16(13) * Fixed16_16(3)).Value == 0x00270000);
	CHECK((Fixed16_16(1.5) * Fixed16_16(1.5)).Value == 0x00024000);
	CHECK((Fixed16_16(32767) * Fixed16_16(0.5)).Value == 0x3fff8000);
	CHECK((Fixed16_16(-0.5) * Fixed16_16(10)).Round() == (int32_t)-5);
	
	// Truncate
	CHECK(Fixed16_16(75.36).Truncate() == (int16_t)75);
	CHECK(Fixed16_16(7.5).Truncate() == (int16_t)7);
	CHECK(Fixed16_16(-9.5).Truncate() == (int16_t)-9);
	CHECK(Fixed16_16(-5.2).Truncate() == (int16_t)-5);
	
	// Round
	CHECK(Fixed16_16(75.36).Round() == (int16_t)75);
	CHECK(Fixed16_16(123).Round() == (int16_t)123);
	CHECK(Fixed16_16(56.5).Round() == (int16_t)57);
	CHECK(Fixed16_16(99.4999).Round() == (int16_t)99);
	CHECK(Fixed16_16(88.999).Round() == (int16_t)89);
	CHECK(Fixed16_16(-75.36).Round() == (int16_t)-75);
	CHECK(Fixed16_16(-123).Round() == (int16_t)-123);
	CHECK(Fixed16_16(-56.5).Round() == (int16_t)-57);
	CHECK(Fixed16_16(-99.4999).Round() == (int16_t)-99);
	CHECK(Fixed16_16(-88.999).Round() == (int16_t)-89);
	CHECK(Fixed16_16(-0.5).Round() == (int16_t)-1);
}
