#include <stdint.h>

// Assumes dev system and target system are both little endian

class FP32 {
public:
	int32_t Value;
	FP32(int16_t whole_only);
	FP32(int32_t whole_only);
	FP32(float f);
	FP32(double f);
	FP32(int16_t whole, uint16_t fraction);

	int16_t Truncate();
	int16_t Round();

	friend bool operator==(FP32 lhs, const FP32& rhs);

	friend bool operator!=(FP32 lhs, const FP32& rhs);

	friend bool operator>=(FP32 lhs, const FP32& rhs);

	friend bool operator>(FP32 lhs, const FP32& rhs);

	friend bool operator<=(FP32 lhs, const FP32& rhs);

	friend bool operator<(FP32 lhs, const FP32& rhs);

	friend FP32 operator+(FP32 lhs, const FP32& rhs);

	friend FP32 operator-(FP32 lhs, const FP32& rhs);

	friend FP32 operator*(FP32 lhs, const FP32& rhs);
};
