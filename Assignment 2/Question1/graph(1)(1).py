import matplotlib.pyplot as plt

with open("Readings(1)(1).txt") as file:
    time_readings = []

    for line in file:
        for i in line.split():
            time_readings.append(float(i))

file.close()

time_readings_for_OTHER = time_readings[0:10]
time_readings_for_RR = time_readings[10:20]
time_readings_for_FIFO = time_readings[20:30]

x_coordinates_for_OTHER = []
x_coordinates_for_RR = []
x_coordinates_for_FIFO = []

for i in range(10):
    x_coordinates_for_OTHER.append(4*i + 1)
    x_coordinates_for_RR.append(4*i + 2)
    x_coordinates_for_FIFO.append(4*i + 3)

x_values = [0, 5, 5, 2, 10, 10, 4, 15, 15, 6, 20, 20, 8, 25, 25, 10, 30, 30, 12, 35, 35, 14, 40, 40, 16, 45, 45, 18, 50, 50]

x_coordinates = []
for i in range(10):
    x_coordinates.append(x_coordinates_for_OTHER[i])
    x_coordinates.append(x_coordinates_for_RR[i])
    x_coordinates.append(x_coordinates_for_FIFO[i])


plt.bar(x_coordinates_for_OTHER, time_readings_for_OTHER, color='red', label='OTHER')
plt.bar(x_coordinates_for_RR, time_readings_for_RR, color='blue', label='RR')
plt.bar(x_coordinates_for_FIFO, time_readings_for_FIFO, color='green', label='FIFO')

plt.xticks(x_coordinates, x_values)

plt.xlabel("Priority")
plt.ylabel("Time (sec)")
plt.title("Sequential Threads Running on two cores")
plt.legend()
plt.show()


    