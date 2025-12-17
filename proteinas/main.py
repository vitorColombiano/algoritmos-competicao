import sys
sys.setrecursionlimit(10**7)
input = sys.stdin.readline

class SAM:
  def __init__(self, n):
    self.next = [{}]          # transições
    self.link = [-1]          # sufix link
    self.len = [0]            # tamanho do maior sufixo
    self.endcnt = [0]         # contagem real de ocorrências
    self.last = 0             # estado atual
    self.size = 1
    self.cap = n*2 + 5

  def extend(self, c):
    p = self.last
    curr = self.size
    self.size += 1

    self.len.append(self.len[p] + 1)
    self.next.append({})
    self.link.append(0)
    self.endcnt.append(1)

    # move transições
    while p != -1 and c not in self.next[p]:
      self.next[p][c] = curr
      p = self.link[p]

    if p == -1:
      self.link[curr] = 0
    else:
      q = self.next[p][c]
      if self.len[p] + 1 == self.len[q]:
        self.link[curr] = q
      else:
        clone = self.size
        self.size += 1

        self.next.append(self.next[q].copy())
        self.len.append(self.len[p] + 1)
        self.link.append(self.link[q])
        self.endcnt.append(0)

        while p != -1 and self.next[p].get(c) == q:
          self.next[p][c] = clone
          p = self.link[p]

        self.link[q] = clone
        self.link[curr] = clone

    self.last = curr

  def finalize_counts(self):
    """Propaga endcnt usando ordem decrescente de len"""
    order = sorted(range(self.size), key=lambda x: self.len[x], reverse=True)
    for v in order:
      if self.link[v] != -1:
        self.endcnt[self.link[v]] += self.endcnt[v]


def main():
  N, M = map(int, input().split())
  DNA = input().strip()
  PROT = input().strip()

  sam = SAM(N)
  for c in DNA:
    sam.extend(c)

  sam.finalize_counts()

  Q = int(input())
  out = []

  for _ in range(Q):
    A, B = map(int, input().split())
    A -= 1
    B -= 1

    state = 0
    ok = True

    for ch in PROT[A:B+1]:
      if ch not in sam.next[state]:
        ok = False
        break
      state = sam.next[state][ch]

    if ok:
      out.append(str(sam.endcnt[state]))
    else:
      out.append("0")

  print("\n".join(out))


if __name__ == "__main__":
  main()
