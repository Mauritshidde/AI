import matplotlib.pyplot as plt
import numpy as np
import random

xpoints = np.array([0, 1, 2, 3, 5, 6])
ypoints = np.array([0, 250, 34, 56 ,67 , 89])

plt.plot(xpoints, ypoints)
plt.show()

values = []
for i in range(12):
    newint = random.randint(0, 100)/100
    values.append(newint)

print(values)