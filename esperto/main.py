from collections import deque

def min_operations(N, M):
  if N == M:
    return 0

  queue = deque([(N, 0)])
  visited = set([N])

  while queue:
    current, steps = queue.popleft()
    next_values = [
      current * 2,
      current * 3,
      current // 2,
      current // 3,
      current + 7,
      current - 7
    ]

    for next_val in next_values:
      if 0 <= next_val <= 10000 and next_val not in visited:
        if next_val == M:
          return steps + 1
        visited.add(next_val)
        queue.append((next_val, steps + 1))

  return -1

N, M = map(int, input().split())
print(min_operations(N, M))
