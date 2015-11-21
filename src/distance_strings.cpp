#include "distance_strings.h"

DistanceStrings::DistanceStrings(std::string& s1, std::string& s2)
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

	This implementation uses bottom-up dynamic programming.

	Reference:
		http://www.levenshtein.net/

	Return:
		score of dissimilarity
*/
int DistanceStrings::levenshteinDistance()
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
	Needleman-Wunsch is a algorithm for global alignment pairwise.
	Needleman-Wunsch is a measure of similarity.
	Uses dynamic programming.

	References:
		https://en.wikipedia.org/wiki/Needleman–Wunsch_algorithm
		http://pt.slideshare.net/mcastrosouza/algoritmo-needlemanwunsch (in portuguese)

	Parameters:
		match
		mistmatch
		gap: score to give an insertion or deletion mutation

	Return:
		score of the alignment
*/
int DistanceStrings::needlemanWunsch(int match, int mismatch, int gap)
{
	std::vector<std::vector<int> > mat(size_s1 + 1,
									   std::vector<int>(size_s2 + 1));

	mat[0][0] = 0;

	for(int i = 1; i <= size_s1; i++)
		mat[i][0] = mat[i - 1][0] + gap;
	for(int i = 1; i <= size_s2; i++)
		mat[0][i] = mat[0][i - 1] + gap;

	for(int i = 1; i <= size_s1; i++)
	{
		for(int j = 1; j <= size_s2; j++)
			mat[i][j] = std::max(std::max(mat[i - 1][j] + gap, mat[i][j - 1] + gap),
								 mat[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? match : mismatch));
	}

	return mat[size_s1][size_s2];
}
