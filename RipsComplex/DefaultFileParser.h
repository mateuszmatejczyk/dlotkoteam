#pragma once
#include "ifileparser.h"
#include <boost/throw_exception.hpp>
#include <boost/lexical_cast.hpp>
#include <string>
#include <sstream>
#include <iostream>


using namespace std;
using namespace boost;

class DefaultFileParser :
	public IFileParser
{
public:

	DefaultFileParser(void)
	{
	}

	~DefaultFileParser(void)
	{
	}

	boost::shared_ptr< vector< vector<double> > > parse( ifstream& f )
	{
		vector< vector<double> >* ret = new vector< std::vector<double> > ();
		int lastDimension = -1;
		for( int l=1;!f.eof();++l )
		{
			string line;
			std::getline(f,line);
			istringstream stream(line);
			double d;
			ret->push_back( vector<double>() );
			int dimension=0;
			while( stream >> d )
			{
				++dimension;
				ret->back().push_back(d);
			}

			if( lastDimension == -1 )
				lastDimension = dimension;
			if( dimension == 0 || dimension!=lastDimension )
				BOOST_THROW_EXCEPTION( std::runtime_error(string("Inconsistent Dimension, line ")+lexical_cast<string>(l) + ":\n"+line) );
		}
		return boost::shared_ptr< vector< vector<double> > > ( ret );
	}
};

