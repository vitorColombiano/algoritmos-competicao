import sys
sys.setrecursionlimit(10**6)

def dfs(i, j):
  stack = [(i, j)]
  while stack:
    x, y = stack.pop()
    if visited[x][y]:
      continue
    visited[x][y] = True
    for dx, dy in [(1,0), (-1,0), (0,1), (0,-1)]:
      nx, ny = x + dx, y + dy
      if 0 <= nx < N and 0 <= ny < M:
        if not visited[nx][ny] and grid[nx][ny] == '.':
          stack.append((nx, ny))

N, M = map(int, sys.stdin.readline().split())
grid = [list(sys.stdin.readline().strip()) for _ in range(N)]

visited = [[False] * M for _ in range(N)]
clicks = 0

for i in range(N):
  for j in range(M):
    if grid[i][j] == '.' and not visited[i][j]:
      dfs(i, j)
      clicks += 1

print(clicks)
