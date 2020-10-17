import re

SPACER = "-" * 50

def make_chance(refs):
  dict = {}
  for ref in refs:
    if ref not in dict:
      dict[ref] = 0
  return dict

def clock(refs, num_pages):
  '''
  Given a list of references, and the number of pages, print the sequence of 
  page replacements using the FIFO algorithm.
  '''
  print("\n" + SPACER)
  print("Clock Algorithm")
  print(SPACER)
  print("Refs: {}".format(refs))
  print(SPACER)

  step = 0
  pages = [None] * num_pages
  hits = 0   
  misses = 0
  clock = 0
  chance = make_chance(refs)

  for i in range(len(refs)):
    step += 1
    ref = refs[i]
    hit = False
    removed = None

    if (ref in pages):
        hit = True
        hits += 1
        chance[ref] = 1

    else:
      misses += 1

      while(pages[clock] is not None and chance[pages[clock]] == 1):
        chance[pages[clock]] = 0
        print("STEP {:02d} [*{}][{}]>> ".format(step, clock, refs[i]), end = '')
        print_pages(pages, num_pages, clock, chance)
        print("* CHECK")
        print(SPACER)
        clock = (clock + 1) % num_pages
        step += 1

      removed = pages[clock]
      pages[clock] = ref
      chance[ref] = 1

    # Print values
    print("STEP {:02d} [*{}][{}]>> ".format(step, clock, refs[i]), end = '')
    print_pages(pages, num_pages, clock, chance)
    chance[ref] = 1

    if (hit):
      print("Hit!")
    else:
      clock = (clock + 1) % num_pages
      if removed:
        print("REPLACE {}".format(removed))
      else:
        print("Miss!")
    print(SPACER)

  print (SPACER)
  print ("Hits: {}".format(hits))
  print ("Misses: {}".format(misses))
  print ("Total: {}".format(len(refs)))
  print (SPACER + "\n")

def print_pages(pages, num_pages, clock, chance):
  rev_pages = pages[:]
  # rev_pages.reverse()
  for i in range(num_pages):
    if i == clock:
      print("* ", end = '')
    if pages[i] is not None:
      print("{}({}) | ".format(rev_pages[i], chance[rev_pages[i]]), end = '')
    else:
      print("{} | ".format("-"), end = '')
    

if __name__ == '__main__':

  # refs = "AFC	008	BC0	AFC	110	008	AEE	AFC	BC0	008"
  # refs = re.split('\s+', refs.strip())
  refs = [1,2,3,4,1,2,5,1,2,3,4,5]
  
  clock(refs, 3)