import matplotlib.pyplot as plt
import sys

data = input()
data = list(map(int, data.split()))

time = input()
time = list(map(int, time.split()))

plt.plot(data, time)
plt.xlabel("File Size")
plt.ylabel("Time")
plt.title("Lab 01 - Step Size: 100")
plt.show()

