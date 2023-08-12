#include <stdint.h>

// Assumes dev system and target system are both little endian

// Must use this macro for decimals because any reference to float will pull in the soft-float library
// This will be slow on the non FPU arm chips
#define fp32(x) FP32((int32_t)(x*0x10000), true)

class FP32 {
public:
	int32_t Value;
	template<typename T> void fn(T) = delete; // #2
	FP32(int32_t value);
	FP32(int32_t value, bool fromMacro);

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
