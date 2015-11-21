#include "distance.h"

Distance::Distance(std::string& s1, std::string& s2)
{
	this->s1 = s1;
	this->s2 = s2;
	this->size_s1 = s1.size();
	this->size_s2 = s2.size();
}

/*
	Levenshtein distance: string metric for
	measuring the difference between two sequences
	Levenshtein is a measure of dissimilarity

	This implementation uses bottom-up dynamic programming

	reference: http://www.levenshtein.net/

	Return
		score of dissimilarity
*/
int Distance::levenshteinDistance()
{
	std::vector<std::vector<unsigned int> > mat(size_s1 + 1,
			std::vector<unsigned int>(size_s2 + 1));

	mat[0][0] = 0;

	for(int i = 1; i <= size_s1; i++)
		mat[i][0] = i;
	for(int i = 1; i <= size_s2; i++)
		mat[0][i] = i;

	for(int i = 1; i <= size_s1; i++)
		for(int j = 1; j <= size_s2; j++)
			mat[i][j] = std::min(std::min(mat[i - 1][j] + 1, mat[i][j - 1] + 1),
								 mat[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1));

	return mat[size_s1][size_s2];
}

/*
	Needleman-Wunsch algorithm
	An algorithm to align sequences.

	reference: https://en.wikipedia.org/wiki/Needleman–Wunsch_algorithm

	Parameters
		match
		mistmatch
		gap

	Return
		score of the alignment
*/
int Distance::needlemanWunsch(int match, int mismatch, int gap)
{
	return 0;
}
