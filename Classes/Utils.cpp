#include "Utils.h"
#include <math.h>

void GetUnitVec(const _In_ FLOAT x, const _In_ FLOAT y, _Out_ FLOAT* unitX, _Out_ FLOAT* unitY)
{
	// 둘다 0일 경우.
	if (!x && !y)
	{
		*unitX = 0;
		*unitY = 0;
		return;
	}
	else if (x == 0)
	{
		*unitX = 0;
		*unitY = 1;
		return;
	}
	else if (y == 0)
	{
		*unitX = 1;
		*unitY = 0;
		return;
	}

	FLOAT length = fabs(sqrtf(x * x + y * y));
	*unitX = x / length;
	*unitY = y / length;

	return;
}