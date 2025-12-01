import bisect

fib = [1, 2]
limit = 10**100

while fib[-1] <= limit:
  fib.append(fib[-1] + fib[-2])

while True:
  a, b = input().split()
  if a == "0" and b == "0":
    break

  a = int(a)
  b = int(b)

  left = bisect.bisect_left(fib, a)
  right = bisect.bisect_right(fib, b)

  print(right - left)
