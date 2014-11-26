#include "xshare.h"

void div();

inline unsigned int float2uint(const float f) {
	int tmp = 0;
	std::memcpy(&tmp, &f, sizeof(float));
	if (tmp >= 0) return (unsigned int)f;
	unsigned int u;
	// use memcpy instead of assignment to avoid undesired optimizations by C++-compiler.
	std::memcpy(&u, &f, sizeof(float));
	return ((u) << 1) >> 1; // set sign bit to 0.
}

inline float uint2float(const unsigned int u) {
	if (u<(1U << 19)) return (float)u;  // Consider safe storage of unsigned int as floats until 19bits (i.e 524287).
	float f;
	const unsigned int v = u | (1U << (8 * sizeof(unsigned int)-1)); // set sign bit to 1.
	// use memcpy instead of simple assignment to avoid undesired optimizations by C++-compiler.
	std::memcpy(&f, &v, sizeof(float));
	return f;
}

#define TEST_X(f) { \
	float fvar = (f); unsigned int uval = float2uint(f); printf("%f => %lu\n", fvar, uval); \
	float fres = uint2float(uval); printf("%lu => %f\n", uval, fres); \
} 

#ifdef FUNK_TANGO

int main()
{
	TEST_X(12341.678432f);	// BAD
	TEST_X(123.1232f);	// BAD
	TEST_X(1.23323123132f);	// BAD
	TEST_X(-2.0432f);	// GOOD

	div();
	getchar();

	return 0;
}

#endif

void div()
{
	int a = 1;
	int b = 123;

	const int MAX = 1000;
	int x = 0, m = 0;

	for (int i = 0; i < MAX; i++)
	{
		for (int n = 0; n < a; n++)
		{
			if (a < b)
			{
				if (x == 0)
				{
					printf("0.");
					x++;
				}

				a = a * 10;
			}

			if (b * n > a)
			{
				printf("%d", n - 1);
				a = a - b * (n - 1);
			}

			m++;
		}
	}

}