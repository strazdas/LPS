#! coding: utf-8
# n - 10.
# t - permuatation of a set {1, ..., n}.
# v[i, j] - i viršūnės, j vektorio komponentės numeris
# d[j, {1,2}] - j vektorio komponentės numeris; 1 - apatinė riba, 2 - viršutinė riba

from sys import argv
from copy import copy
from itertools import permutations
from datetime import datetime

n = 4
if len(argv) > 1:
    n = int(argv[1])


triangles = []

d_l = [0]*n
d_u = [1]*n
start = datetime.now()
for t in permutations(range(n)):
    vertexes = [copy(d_l)]
    triangles.append(vertexes)  # v[][1, j] = d[j, 1]
    for i in range(n):
        vertexes.append([])
        for j in range(n):
            print triangles
            vertexes[-1].append(vertexes[-2][j])  # v[i+1, j] = v[i, j]
        vertexes[-1][t[i]] = d_u[t[i]]
        # v[i+1, t[i]] = d[t[i], 2]
    break
for triangle in triangles:
    print triangle
end = datetime.now()



# for e in triangles:
#     print e

print 'Result is: %s!=%s triangles' % (n, len(triangles))
print 'Duration: %s' % (end - start,)
