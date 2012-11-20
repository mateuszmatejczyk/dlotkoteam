#pragma once
#include "ifileparser.h"

#include <boost/throw_exception.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;
using namespace boost;

class WikiFileParser :
	public IFileParser
{
public:

	WikiFileParser(void)
	{
	}

	virtual ~WikiFileParser(void)
	{
	}


	boost::shared_ptr< vector< vector<double> > > parse( ifstream& f )
	{
		vector< vector<double> >* ret = new vector< std::vector<double> > ();
		unsigned int maxDimension = 0;
		for( int l=1;!f.eof();++l )
		{
			string line;
			std::getline(f,line);
			istringstream stream(line);
			unsigned int d;
			double v;

			ret->push_back( vector<double>(maxDimension) );
			while( stream >> d >> v )
			{
				if( stream.fail() )
					BOOST_THROW_EXCEPTION( std::runtime_error(string("Bad format, line ")+lexical_cast<string>(l) + ":\n"+line) );

				if( maxDimension<d )
					maxDimension = d;

				if( ret->back().size() >= d )
					ret->back().resize(d);
				ret->back().push_back(v);
			}	
		}

		BOOST_FOREACH(vector<double> v, *ret)
			v.resize(maxDimension);

		return boost::shared_ptr< vector< vector<double> > > ( ret );
	}
};
