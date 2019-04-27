#!/usr/bin/python3

def counter(k):

  list_kmer = []
  freq = {}

  reader = open("out/clean_read_1.txt", 'r')

  while True:
    line = reader.readline().rstrip()

    if not line:
      break

    for i in range(0, len(line) - k + 1):
      kmer = line[i : i + k]

      if kmer in freq:
        freq[kmer] += 1
      else:
        freq[kmer] = 1
  
  reader.close()

  freq = {key:val for key, val in freq.items() if val != 1}

  writer = open("out/kmer.txt", 'w')

  for key in freq.keys():
    writer.write(key + '\n')

  writer.close()