#pragma once
#include <vector>

#include "DefaultPointParser.h"
#include "WikiPointParser.h"

using namespace std;

class Distance
{
public:

	Distance(void)
	{
	}

	virtual ~Distance(void)
	{
	}

	double operator() (const DefaultPointParser::Point& p1, const DefaultPointParser::Point& p2 )
	{
		typedef DefaultPointParser::Point::const_iterator it;
		double sum=0;
		for( it i1 = p1.begin(), i2 = p2.begin(); i1 != p1.end(); ++i1,++i2 )
			sum+= (*this)(*i1,*i2);
		return sum;
	}

	double operator() ( const WikiPointParser::Point& p1, const WikiPointParser::Point& p2 )
	{
		typedef WikiPointParser::Point::const_iterator it;
		double sum=0;
		it i1 = p1.begin(), i2 = p2.begin();

		while( i1!=p1.end() && i2!=p2.end() )
		{
			if( i1->dim==i2->dim )
				sum += (*this)((i1++)->val,(i2++)->val);
			else if( i1->dim<i2->dim )
				sum += (*this)( (i1++)->val,0);
			else
				sum += (*this)( (i2++)->val,0);
		}

		for( ; i1 != p1.end(); ++i1)
			sum += (*this)(i1->val,0);
		for( ; i2 != p2.end(); ++i2)
			sum += (*this)(i2->val,0);

		return sum;
	}


protected:
	virtual double operator() (double a, double b)=0;
};

