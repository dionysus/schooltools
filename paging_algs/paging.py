import clock
import fifo
import lru
import re

alg = None
num = None

while(alg != 'c' and alg != 'f' and alg != 'l'):
  print('>> Which paging alg? [c]lock, [f]ifo, or [l]ru:')
  alg = input()

while(not isinstance(num, int)):
  print('>> Number of Pages in memory (int):')
  num = input()
  try:
    num = int(num)
  except ValueError:
    print('Try an integer!')
    num = None


print('>> References (space separated - "A B A C B"):')
refs = input()
refs = re.split('\s+', refs.strip())

if alg == 'c':
  clock.clock(refs, num)
elif alg == 'f':
  fifo.fifo(refs, num)
elif alg == 'l':
  lru.lru(refs, num)
