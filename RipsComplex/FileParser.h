#pragma once

#include <vector>
#include <fstream>
#include <boost/smart_ptr.hpp>

class FileParser
{
public:

	FileParser(void)
	{
	}

	~FileParser(void)
	{
	}

	template< typename PointType, typename ParserType >
	boost::shared_ptr< vector< PointType > > parse( ifstream& f, ParserType parser )
	{
		vector< PointType >* ret = new vector< PointType > ();
		for( int l=1;!f.eof();++l )
		{
			string line;
			std::getline(f,line);
			istringstream stream(line);
			ret->push_back( parser(stream,  l, line ) );
		}
		return boost::shared_ptr< vector< PointType > > ( ret );
	}
};

