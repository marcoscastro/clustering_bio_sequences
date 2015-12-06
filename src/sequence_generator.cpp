#include "sequence_generator.h"

void SequenceGenerator::generateSequences(std::vector<std::string> & sequences,
		int number_of_sequences, int low, int high)
{
	int size_s;

	for(int i = 0; i < number_of_sequences; i++)
	{
		size_s = rand() % (high - low + 1) + low;
		sequences.push_back(generateSequence(size_s));
	}
}

/*
	Generate sequence of the alphabet {A,C,T,G}

	Parameters:
		size_s: length of the sequence

*/
std::string SequenceGenerator::generateSequence(int size_s)
{
	std::string s, alfabeth("ACTG");

	for(int i = 0; i < size_s; i++)
		s.push_back(alfabeth[rand() % 4]);
	return s;
}
