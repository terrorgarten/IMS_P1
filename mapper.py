import csv
import math as ma
with open("filtered_data.csv", "r") as datafile:
    csv_reader = csv.reader(datafile)

    header = next(csv_reader)
    rows = []
    for row in csv_reader:
        rows.append(row)

y_tiles = 20
x_tiles = 20

x_max = float(max(sublist[0] for sublist in rows))
y_max = float(max(sublist[1] for sublist in rows))
x_min = float(min(sublist[0] for sublist in rows))
y_min = float(min(sublist[1] for sublist in rows))

print(x_min, x_max, y_min, y_max)

x_range = x_max - x_min
y_range = y_max - y_min

x_step = x_range / x_tiles
y_step = y_range / y_tiles

print(x_step, y_step)

out = []
for data in rows:
    x_val = float(data[0])
    y_val = float(data[1])
    data.append(str(ma.floor((x_val - x_min)/x_step)))
    data.append(str(ma.floor((y_val - y_min)/y_step)))
    out.append(data)

print(out)
