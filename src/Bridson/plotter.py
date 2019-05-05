import numpy as np
import matplotlib.pyplot as plt

with open('points.txt', 'r') as reader:
    # Read and print the entire file line by line
     line = reader.readline()
     while line != '':  # The EOF char is an empty string
         points = line.split(' ')
         plt.scatter(float(points[0]),float(points[1]))
         line = reader.readline()


# while (True):
#     line = input()
#     if(line == ''):
#         break
#     points = line.split(' ')
#     plt.scatter(float(points[0]), float(points[1]))
plt.show()