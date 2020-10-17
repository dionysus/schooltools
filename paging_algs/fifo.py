import re

SPACER = "-" * 50

def fifo(refs, num_pages):
  '''
  Given a list of references, and the number of pages, print the sequence of 
  page replacements using the FIFO algorithm.
  '''
  print("\n" + SPACER)
  print("First In First Out (FIFO) Algorithm")
  print(SPACER)
  print("Refs: {}".format(refs))
  print(SPACER)

  pages = []
  hits = 0   
  misses = 0

  for i in range(len(refs)):
    ref = refs[i]
    hit = False
    removed = None
    if (ref in pages):
        hit = True
        hits += 1
    else:
      misses += 1
      if len(pages) < num_pages:
        pages.append(ref)
      else:
        removed = pages.pop(0)
        pages.append(ref)

    # Print values
    print("STEP {:02d} [{}]>> ".format(i + 1, refs[i]), end = '')
    print_pages(pages, num_pages)

    if (hit):
      print("Hit!")
    else:
      if removed:
        print("Miss! Replaced {}".format(removed))
      else:
        print("Miss!")
    
    print(SPACER)

  print (SPACER)
  print ("Hits: {}".format(hits))
  print ("Misses: {}".format(misses))
  print ("Total: {}".format(len(refs)))
  print (SPACER + "\n")

def print_pages(pages, num_pages):
  rev_pages = pages[:]
  rev_pages.reverse()
  for i in range(num_pages):
    if i < len(pages):
      print("{} | ".format(rev_pages[i]), end = '')
    else:
      print("{} | ".format("-"), end = '')

if __name__ == '__main__':
  # refs= [0, 1, 2, 3, 0, 1, 5, 4, 0, 1, 2, 3]
  refs = "AFC	008	BC0	AFC	110	008	AEE	AFC	BC0	008"
  refs = re.split('\s+', refs.strip())
  
  fifo(refs, 4)