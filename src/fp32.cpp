#include "./doctest/doctest.hpp"
#include "fp32.hpp"

FP32::FP32(int32_t value)
{
	Value = (int32_t)(value * 0x10000);
}

FP32::FP32(int32_t value, bool fromMacro)
{
	Value = fromMacro ? value : (int32_t)(value * 0x10000);
}

FP32::operator int const()
{
	return this->Round();
}

int16_t FP32::Truncate() const {
	return Value / 0x10000;
}

int16_t FP32::Round() const {
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

// fp32++
FP32 FP32::operator++(int)
{
	FP32 old = 0;
	old.Value = this->Value;
	this->Value = (*this + 1).Value;
	return old;
}

FP32 FP32::operator+=(const FP32& rhs)
{
	*this = *this + rhs;
	return *this;
}

FP32 operator-(FP32 lhs, const FP32& rhs)
{
	lhs.Value -= rhs.Value;
	return lhs;
}

// fp32--
FP32 FP32::operator--(int)
{
	FP32 old = 0;
	old.Value = this->Value;
	this->Value = (*this - 1).Value;
	return old;
}

FP32 FP32::operator-=(const FP32& rhs)
{
	*this = *this - rhs;
	return *this;
}

FP32 operator*(FP32 lhs, const FP32& rhs)
{
	lhs.Value = (int32_t)(((int64_t)lhs.Value * (int64_t)rhs.Value) / 0x10000);
	return lhs;
}

FP32 operator/(FP32 lhs, const FP32& rhs)
{
	if (rhs.Value != 0)
	{
		if (lhs.Value < 0)
		{
			lhs.Value = ((lhs.Value / rhs.Value) * 0x10000) + (((lhs.Value % rhs.Value) * 0x10000) / rhs.Value);
		}
		else
		{
			lhs.Value = ((lhs.Value / rhs.Value) * 0x10000) - (((lhs.Value % rhs.Value) * 0x10000) / rhs.Value);
		}
	}
	else
	{
		lhs.Value = (lhs.Value < 0) ? 0x80000000 : 0x7fffffff;
	}
	return lhs;
}

FP32 operator%(FP32 lhs, const FP32& rhs)
{
	if (rhs.Value != 0)
	{
		lhs.Value = (lhs.Value % rhs.Value);
	}
	else
	{
		// TODO crash screen?
	}
	return lhs;
}


// Skip tests in bare metal ARM builds
#ifndef __ARM_EABI__

extern int ARMOFF;

TEST_CASE("FP32 implicit constructor") {
	FP32 a = 5;
	CHECK(a.Value == 0x00050000);
}

TEST_CASE("FP32") {
	// CTORS
	CHECK(FP32(1).Value == 0x00010000);
	CHECK(fp32(9.25f).Value == 0x00094000);
	CHECK(fp32(9.25).Value == 0x00094000);
	CHECK(fp32(-3.5).Value == (int32_t)0xfffc8000);

	// == Comparisons
	CHECK((fp32(3) == fp32(5)) == false);
	CHECK((fp32(7) == fp32(7)) == true);
	CHECK((fp32(11.19) == fp32(11.19)) == true);
	CHECK((fp32(-11.19) == fp32(11.19)) == false);

	// == Comparisons
	CHECK((fp32(3) != fp32(5)) == true);
	CHECK((fp32(7) != fp32(7)) == false);
	CHECK((fp32(11.19) != fp32(11.19)) == false);
	CHECK((fp32(-11.19) != fp32(11.19)) == true);

	// >= Comparisons
	CHECK((fp32(3) >= fp32(5)) == false);
	CHECK((fp32(7) >= fp32(7)) == true);
	CHECK((fp32(9) >= fp32(7)) == true);
	CHECK((fp32(11.18) >= fp32(11.19)) == false);
	CHECK((fp32(11.19) >= fp32(11.19)) == true);
	CHECK((fp32(11.191) >= fp32(11.19)) == true);
	CHECK((fp32(-11.19) >= fp32(11.19)) == false);

	// > Comparisons
	CHECK((fp32(3) > fp32(5)) == false);
	CHECK((fp32(7) > fp32(7)) == false);
	CHECK((fp32(9) > fp32(7)) == true);
	CHECK((fp32(11.18) > fp32(11.19)) == false);
	CHECK((fp32(11.19) > fp32(11.19)) == false);
	CHECK((fp32(11.191) > fp32(11.19)) == true);
	CHECK((fp32(-11.19) > fp32(11.19)) == false);
	CHECK((fp32(1.7) > fp32(-1.7)) == true);

	// <= Comparisons
	CHECK((fp32(3) <= fp32(5)) == true);
	CHECK((fp32(7) <= fp32(7)) == true);
	CHECK((fp32(9) <= fp32(7)) == false);
	CHECK((fp32(11.18) <= fp32(11.19)) == true);
	CHECK((fp32(11.19) <= fp32(11.19)) == true);
	CHECK((fp32(11.191) <= fp32(11.19)) == false);
	CHECK((fp32(-11.19) <= fp32(11.19)) == true);
	CHECK((fp32(1.7) <= fp32(-1.7)) == false);

	// < Comparisons
	CHECK((fp32(3) < fp32(5)) == true);
	CHECK((fp32(7) < fp32(7)) == false);
	CHECK((fp32(9) < fp32(7)) == false);
	CHECK((fp32(11.18) < fp32(11.19)) == true);
	CHECK((fp32(11.19) < fp32(11.19)) == false);
	CHECK((fp32(11.191) < fp32(11.19)) == false);
	CHECK((fp32(-11.19) < fp32(11.19)) == true);
	CHECK((fp32(1.7) < fp32(-1.7)) == false);

	// Addition
	CHECK((fp32(3) + fp32(5)).Value == 0x00080000);
	FP32 a = fp32(7.25);
	a++;
	CHECK(a.Value == fp32(8.25).Value);
	a+= fp32(2.75);
	CHECK(a.Value == fp32(11).Value);
	a+= 5;
	CHECK(a.Value == fp32(16).Value);

	// Subtraction
	CHECK((fp32(11) - fp32(7)).Value == 0x00040000);
	CHECK((fp32(7) - fp32(11)).Value == 0xfffc0000);
	a = fp32(7.25);
	a--;
	CHECK(a.Value == fp32(6.25).Value);
	a -= fp32(2.75);
	CHECK(a.Value == fp32(3.5).Value);
	a -= 2;
	CHECK(a.Value == fp32(1.5).Value);

	// Multiplication
	CHECK((fp32(13) * fp32(3)).Value == 0x00270000);
	CHECK((fp32(1.5) * fp32(1.5)).Value == 0x00024000);
	CHECK((fp32(32767) * fp32(0.5)).Value == 0x3fff8000);
	CHECK((fp32(-0.5) * fp32(10)).Round() == (int32_t)-5);

	// Division
	CHECK((fp32(12.0) / 3).Value == 0x00040000);
	CHECK((fp32(-12.0) / 3).Value == fp32(-4).Value);
	CHECK((fp32(1.5) / fp32(1.5)).Value == 0x00010000);
	CHECK((fp32(-1.5) / fp32(-1.5)).Value == 0x00010000);
	CHECK((fp32(7) / fp32(0.5)) == 14);
	CHECK((fp32(-7) / fp32(0.5)) == -14);
	CHECK((fp32(7) / fp32(-0.5)) == -14);
	CHECK((fp32(0.5) / fp32(10)).Value == fp32(0.05).Value);
	CHECK((fp32(-0.5) / fp32(10)).Value == fp32(-0.05).Value);
	CHECK((fp32(0.5) / fp32(-10)).Value == fp32(-0.05).Value);
	CHECK((fp32(-0.5) / fp32(-10)).Value == fp32(0.05).Value);
	////// Division by 0 returns int.max or int.min depending on numerator sign
	CHECK((fp32(7) / fp32(0)).Value == 0x7fffffff);
	CHECK((fp32(-7) / fp32(0)).Value == 0x80000000);
	
	//Modulus
	CHECK((fp32(12.0) % 3).Value == 0);
	CHECK((fp32(-12.0) % 3).Value == 0);
	CHECK((fp32(-12.0) % -3).Value == 0);
	CHECK((fp32(4.5) % fp32(1.5)).Value == 0);
	CHECK((fp32(4.7) % fp32(1.5)) == fp32(0.2));

	// Truncate
	CHECK(fp32(0).Truncate() == (int16_t)0);
	CHECK(fp32(75.36).Truncate() == (int16_t)75);
	CHECK(fp32(7.5).Truncate() == (int16_t)7);
	CHECK(fp32(-9.5).Truncate() == (int16_t)-9);
	CHECK(fp32(-5.2).Truncate() == (int16_t)-5);

	// Round
	CHECK(fp32(0).Round() == (int16_t)0);
	CHECK(fp32(75.36).Round() == (int16_t)75);
	CHECK(fp32(123).Round() == (int16_t)123);
	CHECK(fp32(56.5).Round() == (int16_t)57);
	CHECK(fp32(99.4999).Round() == (int16_t)99);
	CHECK(fp32(88.999).Round() == (int16_t)89);
	CHECK(fp32(-75.36).Round() == (int16_t)-75);
	CHECK(fp32(-123).Round() == (int16_t)-123);
	CHECK(fp32(-56.5).Round() == (int16_t)-57);
	CHECK(fp32(-99.4999).Round() == (int16_t)-99);
	CHECK(fp32(-88.999).Round() == (int16_t)-89);
	CHECK(fp32(-0.5).Round() == (int16_t)-1);

	// Rounding when cast to int
	CHECK((int)fp32(0) == (int16_t)0);
	CHECK((int)fp32(75.36) == 75);
	CHECK((int)fp32(123) == (int16_t)123);
	CHECK((int)fp32(56.5) == (int16_t)57);
	CHECK((int)fp32(99.4999) == (int16_t)99);
	CHECK((int)fp32(88.999) == (int16_t)89);
	CHECK((int)fp32(-75.36) == (int16_t)-75);
	CHECK((int)fp32(-123) == (int16_t)-123);
	CHECK((int)fp32(-56.5) == (int16_t)-57);
	CHECK((int)fp32(-99.4999) == (int16_t)-99);
	CHECK((int)fp32(-88.999) == (int16_t)-89);
	CHECK((int)fp32(-0.5) == (int16_t)-1);

}
#endif