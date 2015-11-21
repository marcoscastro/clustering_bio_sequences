#ifndef _SEQUENCE_GENERATOR_H_
#define _SEQUENCE_GENERATOR_H_

class SequenceGenerator
{
public:
	std::string generateSequence(int size_s)
	{
		std::string s, alfabeth("ACTG");

		for(int i = 0; i < size_s; i++)
			s.push_back(alfabeth[rand() % 3]);
		return s;
	}
};

#endif
