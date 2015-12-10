# encoding:utf-8

from pylab import *

def show_pie(cluster, labels, fracs, total_sequences):

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

	title('Percentages of sequences of the Cluster ' + str(cluster) + 
				"\nTotal sequences: " + str(total_sequences), 
				bbox={'facecolor':'0.8', 'pad':8})

	show()

if __name__ == "__main__":

	cluster = 1
	total_sequences = 330
	labels = ('EI', 'IE', 'N')
	amount_sequences = [16, 284, 30]
	fracs = []

	for i in amount_sequences:
		fracs.append((i / float(total_sequences)) * 100)

	show_pie(cluster, labels, fracs, total_sequences)