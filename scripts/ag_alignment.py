'''
	Alignment using Genetic Algorithm

	Reference (in portuguese):
		http://www.bdtd.ufscar.br/htdocs/tedeSimplificado//tde_busca/arquivo.php?codArquivo=555

	Author: Marcos Castro
'''

import random

s1 = 'ACTGGTACTA'
s2 = 'ATCGCTG'
pop = []
len_pop = 10

# function that returns the fitness of chromosome
def get_fitness(chr_first_half, chr_second_half):
	
	hits, len_chr = 0, len(chr_first_half)

	for i in range(len_chr):
		if(chr_first_half[i] == 1 and chr_first_half[i] == chr_second_half[i]):
			hits += 1
	return hits


def show_pop():

	for p in pop:

		print(p[0])
		print(p[1])

		idx_s1, idx_s2 = 0, 0
		align_s1, align_s2 = '', ''

		for i in range(len(p[0])):
			if(p[0][i] == 0):
				align_s1 += '-'
			else:
				align_s1 += s1[idx_s1]
				idx_s1 += 1

		for i in range(len(p[1])):
			if(p[1][i] == 0):
				align_s2 += '-'
			else:
				align_s2 += s2[idx_s2]
				idx_s2 += 1

		print(align_s1)
		print(align_s2)

		print('Score: %d\n' % p[2])


def align_with_ag():

	len_s1, len_s2 = len(s1), len(s2)

	# chromosome size
	len_chr = len_s1 + len_s2

	# initializing the population
	for i in range(len_pop):

		chr_first_half = [0] * len_chr
		chr_second_half = [0] * len_chr
		
		while(True):
			pos = random.randint(0, len_chr - 1)
			chr_first_half[pos] = 1
			if(sum(chr_first_half) == len_s1):
				break

		while(True):
			pos = random.randint(0, len_chr - 1)
			chr_second_half[pos] = 1
			if(sum(chr_second_half) == len_s2):
				break

		fitness = get_fitness(chr_first_half, chr_second_half)
		pop.append((chr_first_half, chr_second_half, fitness))

	show_pop()


align_with_ag()