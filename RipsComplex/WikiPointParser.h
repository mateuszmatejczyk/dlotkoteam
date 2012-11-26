#pragma once

#include <boost/throw_exception.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;
using namespace boost;


typedef unsigned int uint;

struct DimVal
{
	uint dim;
	double val;
	DimVal(uint dim, double val)
		: dim(dim), val(val)
	{}
};


class WikiPointParser
{
public:

	WikiPointParser(void)
	{
	}

	virtual ~WikiPointParser(void)
	{
	}

	typedef vector<DimVal> Point;

	Point operator()(istringstream& stream, int l, const string& line)
	{
		Point ret;
		uint d;
		double v;
		while( stream >> d >> v )
		{
			if( stream.fail() )
				BOOST_THROW_EXCEPTION( std::runtime_error(string("Bad format, line ")+lexical_cast<string>(l) + ":\n"+line) );
			ret.push_back(DimVal(d,v));
		}	

		return ret;
	
	}
};
