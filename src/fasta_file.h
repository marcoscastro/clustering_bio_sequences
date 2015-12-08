// read FASTA file format

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>

class FastaFile
{

private:
	std::vector<std::pair<std::string, std::string> > sequences;

private:
	
	// read the fasta file
	void readFasta(std::string file_path);

public:

	// constructor
	FastaFile(std::string file_path);

	// shows the sequences
	void showSequences();
	
	// return the sequences
	const std::vector<std::pair<std::string, std::string> > & getSequences();
	
	// generate file
	void generateFile(std::string & filename, std::string & content);
};
