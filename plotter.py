# import numpy as np
# import pandas as pd
# import matplotlib.pyplot as plt
import json
from pyproj import Transformer
import csv
import pandas as pd
from shapely.geometry import Point
import geopandas as gpd
from geopandas import GeoDataFrame

#
# data = pd.read_json("dataset.json")
#
# df = pd.Dataframe(data["feature");


DATAFILE = "dataset.json"

with open(DATAFILE) as f:
    json_data = json.load(f)

transformer = Transformer.from_crs("epsg:5514", "epsg:4326")

list = []

for record in json_data["features"]:
    x_cord = record["properties"]["X"]
    y_cord = record["properties"]["Y"]
    name = record["properties"]["PROVOZ"]
    emissions = record["properties"]["CO2EKV"]
    x_cord, y_cord = transformer.transform(x_cord, y_cord)
    factory_tuple = (x_cord, y_cord, name, emissions)
    list.append(factory_tuple)

list.sort(key=lambda a: a[3])
fin_list = list[-15:]

with open('filtered_data.csv', 'w') as f:
    # using csv.writer method from CSV package
    write = csv.writer(f)

    write.writerow(["X", "Y", "Name", "Emissions"])
    write.writerows(fin_list)

df = pd.read_csv("filtered_data.csv", delimiter=',', skiprows=0, low_memory=False)

crs={'init':'epsg:4326'}

geometry = [Point(xy) for xy in zip(df['X'], df['Y'])]
gdf = GeoDataFrame(df, crs=crs, geometry=geometry)
print(type(gdf))


# this is a simple map that goes with geopandas
prague_shapefile = gpd.read_file(r'shapefiles/PRAHA_P.shp')
# world = gpd.read_file(gpd.datasets.get_path('naturalearth_lowres'))
gdf.plot(ax=prague_shapefile.plot(figsize=(10, 6)), marker='o', color='red', markersize=15)
gdf.to_file("tmp.png")




