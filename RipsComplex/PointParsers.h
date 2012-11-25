#pragma once

#include <vector>
#include <boost/throw_exception.hpp>

using namespace std;

template <typename P>
class IPointParser
{
public:

	IPointParser(void)
	{
	}

	virtual ~IPointParser(void)
	{
	}

	P parsePoint(string line)
	{
		BOOST_THROW_EXCEPTION( std::runtime_error(string("Inconsistent Dimension, line ")+lexical_cast<string>(l) + ":\n"+line) );
	}
};

