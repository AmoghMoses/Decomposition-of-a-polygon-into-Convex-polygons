import matplotlib.pyplot as plt
import sys

n = int(sys.argv[1])
file = open('output_before.txt', 'r')
vertices = []
edges = []
i = 0
for each in file:
    vertices.append(tuple(float(item) for item in each.split(' ')))
    edges.append((i, i+1))
    i += 1

vertices.append(vertices[0])

fig, ax = plt.subplots()

# Plot the polygon vertices

 # Display the plot

# Plot the polygon edges

for edge in edges:
    start = vertices[edge[0]]
    end = vertices[edge[1]]
    ax.plot([start[0], end[0]], [start[1], end[1]], 'c-')

for vertex in vertices:
    ax.plot(vertex[0], vertex[1])
# plt.show()
fig.savefig("./" + sys.argv[2] + "/polygon_before_" + str(n) + ".jpg" , dpi = 100)


