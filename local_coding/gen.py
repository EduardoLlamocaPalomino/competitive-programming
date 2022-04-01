from random import randint, choices
from os import system
import sys

def clear(files):
  statement = "rm"
  for file in files:
    statement = statement + " " + file
  system(statement)

iterations = 200

system("make randin")
system("make brute")
system("make main")

for _ in range(iterations):
  print("Test Case {}: ".format(_ + 1), end="")
  system("./randin > in")
  system("./main < in > wa_out")
  system("./brute < in > ac_out")
  wa_out = open("wa_out", "r").read().strip()
  ac_out = open("ac_out", "r").read().strip()
  if wa_out != ac_out:
    print("Wrong Answer")
    clear(["main", "brute", "randin"])
    exit(0)
  print("Correct")

print("Accepted")
#clear(["main", "brute", "wa_out", "ac_out", "randin"])
