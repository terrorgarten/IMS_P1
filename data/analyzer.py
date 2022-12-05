import matplotlib.pyplot as plt
import numpy as np

file_name1 = "../exp1a.txt"
file_name2 = "../exp1b.txt"
data1 = np.loadtxt(file_name1, delimiter=' ', unpack=True)
data2 = np.loadtxt(file_name2, delimiter=' ', unpack=True)

x = data1[0]
y1 = data1[1] # the first graph
y2 = data2[1] # the second graph

plt.plot(x,y1, label='Radotín pracuje')
plt.plot(x,y2, label='Radotín nepracuje')
plt.xlabel('Tick')
plt.ylabel('Emissions [kg]')
plt.title('Graf Experimentu 1.')
plt.legend()
plt.show()