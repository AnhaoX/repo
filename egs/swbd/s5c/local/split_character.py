#!/usr/bin/env python
# Author: Xiaotian Zhang
#
# This tool takes an input file with id and words, and an output filename
# It outputs the id and segmented characters

import sys

def Usage():
  print "Usage: %s input_filename output_filename" % (sys.argv[0],)
  sys.exit(-1)
    
if __name__ == '__main__':
  if len(sys.argv) != 3:
    Usage()

  fout = open(sys.argv[2], 'w')
  for line in open(sys.argv[1], 'r'):
    sound_id = line.decode('utf-8').split()[0]
    word = ''.join(line.decode('utf-8')[len(sound_id):].strip(' \r\n').split())
    
    n = len(word)   
    write_str = sound_id
    for i in range(n):
      write_str += ' ' + word[i]
      print (word[i].encode('utf-8'))
    write_str += '\n'
    
    fout.write(write_str.encode('utf-8'))
