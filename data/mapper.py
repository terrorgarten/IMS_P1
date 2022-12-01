import csv
import math
import math as ma

with open("filtered_data.csv", "r") as datafile:
    csv_reader = csv.reader(datafile)

    header = next(csv_reader)
    rows = []
    for row in csv_reader:
        rows.append(row)

margin_size = 1.5

y_tiles = 40
x_tiles = 40

# get default bounds
x_max = float(max(sublist[0] for sublist in rows))
y_max = float(max(sublist[1] for sublist in rows))
x_min = float(min(sublist[0] for sublist in rows))
y_min = float(min(sublist[1] for sublist in rows))

# get base range
x_range = x_max - x_min
y_range = y_max - y_min

# to square
x_margin = ((margin_size * x_range) - x_range) / 2
y_margin = ((margin_size * x_range) - y_range) / 2

# update bounds to square
x_max += x_margin
x_min -= x_margin
y_max += y_margin
y_min -= y_margin

# update range to square
x_range = x_max - x_min
y_range = y_max - y_min
# assert square
print(x_range, y_range)
# assert (x_range == y_range)
assert (math.isclose(x_range, y_range))

x_step = x_range / x_tiles
y_step = y_range / y_tiles

out = []
for data in rows:
    x_val = float(data[0])
    y_val = float(data[1])
    data.append(str(ma.floor(x_tiles - (x_val - x_min) / x_step)))
    # revert value for C array sequencing
    data.append(str(ma.floor((y_val - y_min) / y_step)))
    out.append(data)

sorted_out = sorted(out, key=lambda element: (int(element[4]), int(element[5])))
print(sorted_out)

with open('indexes.csv', 'w') as f:
    # using csv.writer method from CSV package
    write = csv.writer(f)

    write.writerow(["X", "Y", "Name", "Emissions", "row", "col"])
    write.writerows(sorted_out)
