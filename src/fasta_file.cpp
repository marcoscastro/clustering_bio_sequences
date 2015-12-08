#include "fasta_file.h"

void FastaFile::readFasta(std::string file_path)
{
	std::ifstream input(file_path.c_str());

	if(!input.good())
	{
		std::cerr << "\nError opening FASTA file.\n";
		exit(1);
	}

	bool flag_insert = false;
	std::string line, name, content;

	while(std::getline(input, line))
	{
		if(!line.empty())
		{
			if(line[0] == '>')
			{
				if(flag_insert)
				{
					sequences.push_back(std::make_pair(name, content));
					content.clear();
					flag_insert = false;
				}
				name = line.substr(1);
			}
			else
			{
				content += line;
				flag_insert = true;
			}
		}
	}

	if(!content.empty())
		sequences.push_back(std::make_pair(name, content));
}


FastaFile::FastaFile(std::string file_path)
{
	readFasta(file_path);
}

void FastaFile::showSequences()
{
	std::cout << "\nShowing sequences of the FASTA file:\n\n";

	std::vector<std::pair<std::string, std::string> >::iterator it;

	for(it = sequences.begin(); it != sequences.end(); it++)
		std::cout << (*it).first << "\n" << (*it).second << "\n\n";
}

// return the sequences
const std::vector<std::pair<std::string, std::string> > & FastaFile::getSequences()
{
	return sequences;
}
