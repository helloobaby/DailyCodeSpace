from itertools import chain
a=[[1],[2],[3],[4]]
for num in chain.from_iterable(a):
    print(num)

for nums in a:
    for num in nums:
        print(num)
