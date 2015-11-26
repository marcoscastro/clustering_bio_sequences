#ifndef _DISTANCE_STRINGS_H_
#define _DISTANCE_STRINGS_H_

#include <algorithm>
#include <vector>
#include <string>
#include <math.h>
#include "common.h"

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
int levenshteinDistance(std::string & s1, std::string & s2)
{
	int size_s1 = s1.size(), size_s2 = s2.size();
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
double needlemanWunsch(std::string & s1, std::string & s2, double match = 1,
					   double mismatch = 0, double gap = 0)
{
	int size_s1 = s1.size(), size_s2 = s2.size();
	std::vector<std::vector<double> > mat(size_s1 + 1,
										  std::vector<double>(size_s2 + 1));

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

/*
	White Similarity
	reference: http://www.catalysoft.com/articles/StrikeAMatch.html
*/

double whiteSimilarity(std::string & s1, std::string & s2)
{
	if(s1 == s2)
		return 1;

	int size_s1 = s1.size(), size_s2 = s2.size();

	if(size_s1 < 2 || size_s2 < 2)
		return 0;

	double hits = 0;
	int i = 0, j = 0;
	std::string pair_s1, pair_s2;

	size_s1--;
	size_s2--;

	while(i < size_s1 && j < size_s2)
	{
		pair_s1 = s1.substr(i, 2);
		pair_s2 = s2.substr(j, 2);

		if(pair_s1 == pair_s2)
			hits += 2;

		i++;
		j++;
	}

	return ((hits / (size_s1 + size_s2)) * 100);
}


#endif
