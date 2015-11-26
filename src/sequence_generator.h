#ifndef _SEQUENCE_GENERATOR_H_
#define _SEQUENCE_GENERATOR_H_

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
						   int number_of_sequences, int low, int high)
	{
		int size_s;

		for(int i = 0; i < number_of_sequences; i++)
		{
			size_s = rand() % (high - low + 1) + low;
			sequences.push_back(generateSequence(size_s));
		}
	}

	std::string generateSequence(int size_s)
	{
		std::string s, alfabeth("ACTG");

		for(int i = 0; i < size_s; i++)
			s.push_back(alfabeth[rand() % 4]);
		return s;
	}
};

#endif
