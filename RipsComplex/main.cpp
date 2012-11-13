#include <iostream>
#include <boost/foreach.hpp>
#include <fstream>

#include <cmath>
#include <vector>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

using namespace std;

// A helper function to simplify the main part.
template<class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
	copy(v.begin(), v.end(), ostream_iterator<T>(os, " ")); 
	return os;
}


int main(int ac, char* av[])
{
	try {
		int format;
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
				  "0 - default format/n1 - wiki format")
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

		cout << "Format is " << format << "\n";                
	}
	catch(exception& e)
	{
		cout << e.what() << "\n";
		return 1;
	}    
	return 0;
}

