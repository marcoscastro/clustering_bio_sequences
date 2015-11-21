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

	This implementation uses bottom-up dynamic programming.

	Refernece:
		http://www.levenshtein.net/

	Return:
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
int Distance::needlemanWunsch(int match, int mismatch, int gap)
{
	std::vector<std::vector<int> > mat(size_s1 + 1,
									   std::vector<int>(size_s2 + 1));
	std::map<std::pair<int, int>, std::pair<int, int> > traceback;
	int score = 0;

	mat[0][0] = 0;

	for(int i = 1; i <= size_s1; i++)
	{
		mat[i][0] = mat[i - 1][0] + gap;
		traceback[std::make_pair(i, 0)] = std::make_pair(i - 1, 0);

	}
	for(int i = 1; i <= size_s2; i++)
	{
		mat[0][i] = mat[0][i - 1] + gap;
		traceback[std::make_pair(0, i)] = std::make_pair(0, i - 1);
	}

	int diagonal, top, left;

	for(int i = 1; i <= size_s1; i++)
	{
		for(int j = 1; j <= size_s2; j++)
		{
			diagonal = mat[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? match : mismatch);
			top = mat[i - 1][j] + gap;
			left = mat[i][j - 1] + gap;
			mat[i][j] = std::max(std::max(diagonal, top), left);

			if(diagonal == mat[i][j])
				traceback[std::make_pair(i, j)] = std::make_pair(i - 1, j - 1);
			else if(top == mat[i][j])
				traceback[std::make_pair(i, j)] = std::make_pair(i - 1, j);
			else
				traceback[std::make_pair(i, j)] = std::make_pair(i, j - 1);
		}
	}

	int i = size_s1, j = size_s2, i_next, j_next;
	std::pair<int, int> my_pair;

	// get the score by traceback
	while(i > 0 && j > 0)
	{
		score += mat[i][j];
		i_next = traceback[std::make_pair(i, j)].first;
		j_next = traceback[std::make_pair(i, j)].second;
		i = i_next;
		j = j_next;
	}

	return score;
}
