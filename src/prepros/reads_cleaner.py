#!/usr/bin/python3

import os
import sys

def ascii_from_quality(quality):
  return chr(min(quality, 93) + 33)

def reader(quality, reads_file):

  mapIndexSubstring = {}

  with open(reads_file, 'r') as file:
    for j, lines in enumerate(file, start = 1):
      if j % 4 == 0:
        character = ascii_from_quality(quality)
        index = [i for i, char in enumerate(lines, start = 0) if char < character]
        mapIndexSubstring.update({j: index})

  return dict(sorted(mapIndexSubstring.items()))

def cleaner(quality, max_length, reads_file):
	
  extension = os.path.splitext(reads_file)[1]
  if extension != '.fq' and extension != '.fasta':
    print('Invalid format file')
  
  index = reader(quality, reads_file)

  with open(reads_file, 'r') as file, open('out/clean_read.txt', 'w') as writer:
    for i, lines in enumerate(file, start = 1):
      if i % 4 == 2:
        array = index.get(i + 2)
        count = 0
        
        if array[0] == len(lines):
          writer.write(lines + '\n')
        else:
          string = ""
          for k in range(0, len(array)):
            if count != array[k] and len(lines[count : array[k]]) > max_length:
              if len(string) <= len(lines[count : array[k]]):
                string = lines[count : array[k]]
                
            count = array[k] + 1
          
          if string == "":
            print("Characters are all less than input quality\n");
          else: 
            writer.write(string + '\n')

  file.close()
  writer.close()

if __name__ == "__main__":
  cleaner(int(sys.argv[1]), int(sys.argv[2]), sys.argv[3])