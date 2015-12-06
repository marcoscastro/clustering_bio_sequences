#ifndef _SEQUENCE_GENERATOR_H_
#define _SEQUENCE_GENERATOR_H_

#include <vector>
#include <string>
#include <stdlib.h>

class SequenceGenerator
{
public:

	/*
		Generate sequences of the alphabet {A,C,T,G}

		Parameters:
			sequences: vector of sequences
			number_of_sequences: number of sequences
			low: minimum size of the sequence
			high: maximum size of the sequence

	*/
	void generateSequences(std::vector<std::string> & sequences,
						   int number_of_sequences, int low, int high);

	/*
		Generate sequence of the alphabet {A,C,T,G}

		Parameters:
			size_s: length of the sequence

	*/
	std::string generateSequence(int size_s);
};

#endif
