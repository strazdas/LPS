#! coding: utf-8
from sys import argv
from copy import copy
from itertools import permutations
from datetime import datetime
from math import factorial


n = 10
if len(argv) > 1:
    n = int(argv[1])

# triangles = []

d_l = [0]*n
d_u = [1]*n

start = datetime.now()

for k in range(factorial(n)):
    """Generates permutation for each k"""
    teta = []
    for j in range(0, n):
        teta.append(j)

    c = 1
    for j in range(2, n+1):
        c *= j - 1
        i = j - 1 - (k/c) % j
        tmp = teta[j-1]
        teta[j-1] = teta[i]
        teta[i] = tmp

    """Finds the simplex for this vertex"""
    vertexes = [copy(d_l)]
    # triangles.append(vertexes)  # v[][1, j] = d[j, 1]

    for i in range(n):
        vertexes.append([])
        for j in range(n):
            vertexes[-1].append(vertexes[-2][j])  # v[i+1, j] = v[i, j]
        vertexes[-1][teta[i]] = d_u[teta[i]]

end = datetime.now()
# for triangle in triangles:
#     print triangle

print 'Trukmė', end - start
