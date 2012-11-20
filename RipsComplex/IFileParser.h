#pragma once

#include <vector>
#include <fstream>
#include <boost/smart_ptr.hpp>

class IFileParser
{
public:

	IFileParser(void)
	{
	}

	~IFileParser(void)
	{
	}

	virtual boost::shared_ptr< std::vector< std::vector<double> > > parse( std::ifstream& f )=0;
};

