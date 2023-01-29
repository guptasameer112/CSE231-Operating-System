import matplotlib.pyplot as plt

with open("Readings(1)(2).txt") as file:
    time_readings = []

    for line in file:
        for i in line.split():
            time_readings.append(float(i))

file.close()

time_readings_for_FIFO = time_readings[2]
time_readings_for_OTHER = time_readings[1]
time_readings_for_RR = time_readings[0]

x_coordinates_for_OTHER = [0]
x_coordinates_for_RR = [20]
x_coordinates_for_FIFO = [40]


x_values = [0, 20, 40]

x_coordinates = [0, 20, 40]


plt.bar(x_coordinates_for_OTHER, time_readings_for_OTHER, color='red', label='OTHER')
plt.bar(x_coordinates_for_RR, time_readings_for_RR, color='blue', label='RR')
plt.bar(x_coordinates_for_FIFO, time_readings_for_FIFO, color='green', label='FIFO')

plt.xticks(x_coordinates, x_values)

plt.xlabel("Priority")
plt.ylabel("Time (min)")
plt.title("Parallel Threads Running on two cores")
plt.legend()
plt.show()


    