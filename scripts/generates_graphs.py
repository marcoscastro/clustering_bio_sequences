# encoding:utf-8

from pylab import *

def show_pie(cluster, labels, fracs, title_graph):

	labels, fracs, explode = labels, fracs, ()
	max_idx = fracs.index(max(fracs))
	colors = ['yellowgreen', 'gold', 'lightskyblue', 'lightcoral']
	selected_colors = colors[0:len(labels)]

	for i in range(len(labels)):
		if(i != max_idx):
			explode += (0,)
		else:
			explode += (0.05,)

	my_pie = pie(fracs, explode=explode, labels=labels, colors=selected_colors,
					autopct='%1.1f%%', shadow=True, startangle=120)

	for i in range(len(labels)):
		my_pie[1][i].set_fontsize(15)

	title(title_graph, bbox={'facecolor':'0.8', 'pad':8})

	show()

if __name__ == "__main__":

	cluster = 1
	total_sequences = 57
	labels = ('Promoter (+)', 'No Promoter (-)')
	amount_sequences = [7, 50]
	fracs = []

	title_graph = 'Percentages of sequences of the Cluster ' + str(cluster) + \
					'\nTotal sequences: ' + str(total_sequences)

	for i in amount_sequences:
		fracs.append((i / float(total_sequences)) * 100)

	show_pie(cluster, labels, fracs, title_graph)