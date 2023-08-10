#include <stdint.h>

// Assumes dev system and target system are both little endian

class Fixed16_16 {
public:
	int32_t Value;
	Fixed16_16(int16_t whole_only);
	Fixed16_16(int32_t whole_only);
	Fixed16_16(float f);
	Fixed16_16(double f);
	Fixed16_16(int16_t whole, uint16_t fraction);

	int16_t Truncate();
	int16_t Round();

	friend Fixed16_16 operator+(Fixed16_16 lhs, const Fixed16_16& rhs);

	friend Fixed16_16 operator-(Fixed16_16 lhs, const Fixed16_16& rhs);

	friend Fixed16_16 operator*(Fixed16_16 lhs, const Fixed16_16& rhs);
};
