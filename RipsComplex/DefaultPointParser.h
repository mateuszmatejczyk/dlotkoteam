#pragma once

#include <boost/throw_exception.hpp>
#include <boost/lexical_cast.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>


using namespace std;
using namespace boost;


/*
* Different instance of parser should be used for different set point
* Parser also checks dimension consistency
*/

class DefaultPointParser 
{
	unsigned int dimension;


public:
	DefaultPointParser(void)
		: dimension(-1)
	{
	}

	~DefaultPointParser(void)
	{
	}


	typedef vector<double> Point;

	Point operator()(istringstream& stream, int l, const string& line)
	{
		double d;
		int dim=0;
		vector<double> ret;
		while( stream >> d )
		{
			++dim;
			ret.push_back(d);
		}

		if( dimension == -1 )
			dimension=dim;
		if( dim == 0 || dimension!=dim )
			BOOST_THROW_EXCEPTION( std::runtime_error(string("Inconsistent Dimension, line ")+lexical_cast<string>(l) + ":\n"+line) );

		return ret;
	}

};

