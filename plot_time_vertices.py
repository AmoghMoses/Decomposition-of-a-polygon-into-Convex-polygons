import matplotlib.pyplot as plt
import sys


# x axis values
y = []
j = 0
file = open('timing.txt', 'r')
for each in file:
    y.append(float(each))
    j+=1
x = [i for i in range(1,j+1)]

# plotting the points
fig1 = plt.gcf()
plt.plot(x, y, color='green')
# naming the x axis
plt.xlabel('Number Of Vertices(Muliple Of 1000)')
# naming the y axis
plt.ylabel('Time in Milliseconds')
fig1.savefig("./" + sys.argv[1] + "/plot" + ".jpg", dpi = 100)
