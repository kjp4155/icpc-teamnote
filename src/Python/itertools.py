import sys
import itertools

arr = [1,2,3,4]

for x in itertools.permutations(arr):
    print(x)

for x in itertools.permutations(arr,2):
    print(x)

for x in itertools.combinations(arr,2):
    print(x)
