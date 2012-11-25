#pragma once
#include "Distance.h"


class EuclideanSquareDistance :
	public Distance
{
public:

	EuclideanSquareDistance(void)
	{
	}

	virtual ~EuclideanSquareDistance(void)
	{
	}

protected:
	double operator() (double a, double b)
	{
		return (a-b)*(a-b); 
	}
};

