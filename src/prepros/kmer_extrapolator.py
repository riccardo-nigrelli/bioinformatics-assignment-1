#!/usr/bin/python3

import sys

def extrapolator(k):

  with open("out/clean_read.txt", 'r') as reader, open("out/kmer.txt", 'w') as writer:
    for line in reader:
      for i in range(0, len(line.rstrip()) - k + 1):
	      writer.write(line[i : i + k] + '\n')

  writer.close()
  reader.close()

if __name__ == "__main__":
  extrapolator(int(sys.argv[1]))
