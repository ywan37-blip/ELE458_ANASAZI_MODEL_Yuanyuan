
import csv
import matplotlib.pyplot as plt

# 1. Choose a year to display
year_to_show = 800

# 2. Read household data
house_x = []
house_y = []
field_x = []
field_y = []

with open("outputs/household.csv", "r") as file:
    reader = csv.DictReader(file)

    for row in reader:
        if int(row["year"]) == year_to_show:
            house_x.append(int(row["house_x"]))
            house_y.append(int(row["house_y"]))
            field_x.append(int(row["field_x"]))
            field_y.append(int(row["field_y"]))

# 3. Create the map
plt.figure(figsize=(9, 7))

# Blue circles = households
plt.scatter(
    house_x,
    house_y,
    color="blue",
    marker="o",
    s=35,
    label="Households"
)

# Orange squares = fields
plt.scatter(
    field_x,
    field_y,
    color="orange",
    marker="s",
    s=25,
    label="Fields"
)

# 4. Add labels
plt.title(f"Anasazi Model - Year {year_to_show}")
plt.xlabel("X Coordinate")
plt.ylabel("Y Coordinate")

plt.grid(alpha=0.3)
plt.legend()
plt.axis("equal")

# 5. Save the map
plt.savefig(
    f"outputs/anasazi_map_{year_to_show}.png",
    dpi=300,
    bbox_inches="tight"
)

plt.show()

