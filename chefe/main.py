import sys
from collections import deque

def process_case():
  while True:
    line = sys.stdin.readline()
    if not line:
      break

    N, M, I = map(int, line.split())
    ages = list(map(int, sys.stdin.readline().split()))
    graph = [[] for _ in range(N + 1)]
    rev = [[] for _ in range(N + 1)]

    # Relações de gerência
    for _ in range(M):
      X, Y = map(int, sys.stdin.readline().split())
      graph[X].append(Y)
      rev[Y].append(X)

    for _ in range(I):
      parts = sys.stdin.readline().split()
      cmd = parts[0]

      if cmd == 'T':
        A, B = map(int, parts[1:])

        # Troca as posições de A e B no grafo
        graph[A], graph[B] = graph[B], graph[A]
        rev[A], rev[B] = rev[B], rev[A]

        # Corrigir referências
        for i in range(1, N + 1):
          # Corrige quem é gerenciado
          graph[i] = [B if x == A else A if x == B else x for x in graph[i]]
          rev[i] = [B if x == A else A if x == B else x for x in rev[i]]

      elif cmd == 'P':
        E = int(parts[1])
        visited = [False] * (N + 1)
        queue = deque(rev[E])
        youngest = float('inf')
        found = False

        while queue:
          u = queue.popleft()
          if visited[u]:
              continue
          visited[u] = True
          found = True
          youngest = min(youngest, ages[u - 1])
          for manager in rev[u]:
              if not visited[manager]:
                  queue.append(manager)

        if found:
          print(youngest)
        else:
          print('*')

if __name__ == "__main__":
  process_case()
