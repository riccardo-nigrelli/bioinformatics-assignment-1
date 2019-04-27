#!/usr/bin/python3

def ascii_from_quality(quality):
	return chr(min(quality, 93) + 33)

def reader(quality):

	mapIndexSubstring = {}

	with open('data/ngs-reads.fq', 'r') as file:
		for j, lines in enumerate(file, start = 1):
			if j % 4 == 0:
				character = ascii_from_quality(quality)
				index = [i for i, char in enumerate(lines, start = 0) if char < character or char == character]
				mapIndexSubstring.update({j: index})
			else:
				continue

	return dict(sorted(mapIndexSubstring.items()))

def cleaner(quality, max_length):

	index = reader(quality)
	
	with open('data/ngs-reads.fq', 'r') as file, open('out/clean_read.txt', 'w') as writer:
		for i, lines in enumerate(file, start = 1):
			if i % 4 == 2:
				array = index.get(i + 2)
				count = 0
				for k in range(0, len(array)):
					if count != array[k] and len(lines[count : array[k]]) > max_length:
						writer.write(lines[count : array[k]] + '\n')

					count = array[k] + 1

	file.close()
	writer.close()