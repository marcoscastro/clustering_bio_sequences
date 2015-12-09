'''
	Script to transform the splice.data.txt for the fasta file format
	Author: Marcos Castro

	Works in Python 2.x and 3.x
	The script generates  a fasta file with the name splice.data.fasta

	splice.data.txt is a dataset with primate splice-junction gene sequences (DNA)

	Link for download of the original dataset:
		https://archive.ics.uci.edu/ml/datasets/Molecular+Biology+(Splice-junction+Gene+Sequences)
'''

import sys

if __name__ == "__main__":

	if(len(sys.argv) != 2):
		print('\nError: insufficient arguments.\n')
		print('Command:\n\n\tpromoters_data_to_fasta.py <path_promoters_data>')
		print('\tExample: promoters_data_to_fasta.py promoters.data.txt')
	else:
		content = ''
		lines = tuple(open(sys.argv[1], 'r'))

		for line in lines:

			content_sequence = '>'
			line = line.replace('\n', '')
			attributes_sequence = line.split(',')
			class_sequence =  attributes_sequence[0]
			sequence = attributes_sequence[2].replace(' ', '')
			content_sequence += class_sequence + '\n'
			content_sequence += sequence.replace('\t', '').upper() + '\n'
			content += content_sequence

		f = open('promoters.data.fasta', 'w')
		f.write(content)
		f.close()

		print('\nThe \"promoters.data.fasta\" file was generated.\n')
