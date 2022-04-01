s = input()
d = input()
for i in range(0, len(s)):
  x = ord(s[i]) -  ord('a') - (ord(d[i % len(d)]) - ord('a'))
  x = (x + 26) % 26
  c = chr(x + ord('a'))
  print(c, end = "")
print()
