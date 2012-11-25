#include <iostream>
#include <boost/foreach.hpp>
#include <fstream>

#include <cmath>
#include <vector>

#include <boost/graph/graphviz.hpp>
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>


namespace po = boost::program_options;


#include "DefaultPointParser.h"
#include "WikiPointParser.h"
#include "BruteForceNeighborhoodGraph.h"
#include "EuclideanSquareDistance.h"
#include "InductiveVRComplexBuilder.h" 
#include "PointsDimensionTest.h"

using namespace std;

#define M_PI       3.14159265358979323846
typedef pair<double,double> Point;




// A helper function to simplify the main part.
template<class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
	copy(v.begin(), v.end(), ostream_iterator<T>(os, " ")); 
	return os;
}


#include <list>

int main(int ac, char* av[])
{

	try {
		int format;
		double epsylon;
		int k;
		string config_file;
	
		// Declare a group of options that will be 
		// allowed only on command line
		po::options_description generic("Generic options");
		generic.add_options()
			("version,v", "print version string")
			("help", "produce help message")
			("config,c", po::value<string>(&config_file)->default_value("config.cfg"),
				  "name of a file of a configuration.")
			;
	
		// Declare a group of options that will be 
		// allowed both on command line and in
		// config file
		po::options_description config("Configuration");
		config.add_options()
			("format,f", po::value<int>(&format)->default_value(0), 
				  "0 - default format\n1 - wiki format")
			("epsylon,e", po::value<double>(&epsylon), 
				  "neighbourhood graph epsylon")
			("kskeleton,k", po::value<int>(&k), 
				  "k skeleton")

			;

		// Hidden options, will be allowed both on command line and
		// in config file, but will not be shown to the user.
		po::options_description hidden("Hidden options");
		hidden.add_options()
			("input-file", po::value< vector<string> >(), "input file")
			;

		
		po::options_description cmdline_options;
		cmdline_options.add(generic).add(config).add(hidden);

		po::options_description config_file_options;
		config_file_options.add(config).add(hidden);

		po::options_description visible("Allowed options");
		visible.add(generic).add(config);
		
		po::positional_options_description p;
		p.add("input-file", -1);
		
		po::variables_map vm;
		store(po::command_line_parser(ac, av).
			  options(cmdline_options).positional(p).run(), vm);
		notify(vm);
		
		ifstream ifs(config_file.c_str());
		if (!ifs)
		{
			cout << "can not open config file: " << config_file << "\n";
			return 0;
		}
		else
		{
			store(parse_config_file(ifs, config_file_options), vm);
			notify(vm);
		}
	
		if (vm.count("help")) {
			cout << visible << "\n";
			return 0;
		}

		if (vm.count("version")) {
			cout << "Persistent Homology, version 1.0\n";
			return 0;
		}


		if (vm.count("input-file"))
		{
			cout << "Input files are: " 
				 << vm["input-file"].as< vector<string> >() << "\n";
		}
		else
		{
			cout << "No input-files" << endl;
			return 0;
		}

		
		boost::shared_ptr<AdjacencyList> aList;
		string filename = vm["input-file"].as< vector<string> >().front() ;

		ifstream file( filename );
		if( file.good() )
		{
			cout << "Parsing file..." << endl;
			BruteForceNeighborhoodGraph graphBuilder;
			switch( format )
			{
			case 0:
				aList = graphBuilder(file, DefaultPointParser(), epsylon*epsylon, EuclideanSquareDistance() );
				break;
			case 1:
				aList = graphBuilder(file, WikiPointParser(), epsylon*epsylon, EuclideanSquareDistance() );
				break;
			default:
				BOOST_THROW_EXCEPTION( std::logic_error("Bad format" ) );
			}
		}
		else
		{
			BOOST_THROW_EXCEPTION( runtime_error("Can't open file") );
		}


		boost::shared_ptr< IVRComplexBuilder > VRComplexBuilder(new InductiveVRComplexBuilder());

		boost::shared_ptr< VRComplexGraph > g = (*VRComplexBuilder)(*aList, k);


		property_map<VRComplexGraph, double Simplex::*>::type filtration =  get(&Simplex::filtration, *g);


		{
			size_t i = filename.rfind('.');
			if (i != std::string::npos)
				filename.erase(filename.begin() + i, filename.end());
		}

		string graphvizOutfile = filename+ "-vr_complex.dot";
		
		std::cout << "Writing GraphViz output to " << graphvizOutfile << "... ";
		std::cout.flush();

		typedef std::map<VRComplexGraph::vertex_descriptor, size_t>IndexMap;
		IndexMap mapIndex;
		boost::associative_property_map<IndexMap> propmapIndex(mapIndex);

		typedef std::map<VRComplexGraph::vertex_descriptor, string> LabelMap;
		LabelMap mapLabel;
		boost::associative_property_map<LabelMap> propmapLabel(mapLabel);

		//indexing the vertices
		int j=0;
		BGL_FORALL_VERTICES(v, *g, VRComplexGraph)
		{
			put(propmapIndex, v, j++);
			string s;
			BOOST_FOREACH( int u, (*g)[v].V )
				s+= lexical_cast<string>(u);
			s+= string(" (") + lexical_cast<string>((*g)[v].filtration) + ")";
			
			put(propmapLabel, v, s);
		}


		boost::dynamic_properties dp;
		//dp.property("label", get(&Simplex::filtration, *g));
		dp.property("node_id", propmapIndex);
		dp.property("label", propmapLabel);


		write_graphviz_dp(ofstream(graphvizOutfile), *g, dp);
		cout << " Done!" << endl;


		string metisOutfile = filename + "-vr_complex.graph";
		cout << "Writing METIS output to " << metisOutfile << "... ";
		ofstream of(metisOutfile);
		
		of << num_vertices(*g) << " " << num_edges(*g) << " 10 2" << endl;
		BGL_FORALL_VERTICES(v, *g, VRComplexGraph)
		{
			of << (*g)[v].V.size() << " " << (*g)[v].filtration;
			VRComplexGraph::out_edge_iterator it,end;
			tuples::tie(it,end) = out_edges(v, *g);
			for( ;it!=end;++it )
				of << " " << get(propmapIndex, target( *it, *g) );
			of << endl;
		}

		of.flush();
		of.close();
		
		cout << "Done!" << endl;

	}
	catch(std::exception& e)
	{
		cout << "ERROR: " << e.what() << "\n";
		return 1;
	}    
	return 0;
}

