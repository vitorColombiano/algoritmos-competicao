import sys
import heapq
from collections import deque

for line in sys.stdin:
  if not line.strip():
    continue
  n = int(line)
  
  stack = []
  queue = deque()
  pqueue = []
  
  is_stack = True
  is_queue = True
  is_pqueue = True
  
  for _ in range(n):
    op, *rest = map(int, sys.stdin.readline().split())
    
    if op == 1:
      x = rest[0]
      stack.append(x)
      queue.append(x)
      heapq.heappush(pqueue, -x)
    else:
      x = rest[0]
      
      if stack:
        val = stack.pop()
        if val != x:
          is_stack = False
      else:
        is_stack = False
      
      if queue:
        val = queue.popleft()
        if val != x:
          is_queue = False
      else:
        is_queue = False
      
      if pqueue:
        val = -heapq.heappop(pqueue)
        if val != x:
          is_pqueue = False
      else:
        is_pqueue = False
  
  total = is_stack + is_queue + is_pqueue
  if total == 0:
    print("impossible")
  elif total > 1:
    print("not sure")
  else:
    if is_stack:
      print("stack")
    elif is_queue:
      print("queue")
    else:
      print("priority queue")
