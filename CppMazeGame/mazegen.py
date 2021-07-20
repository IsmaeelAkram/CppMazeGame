import random

# Clear obstacles file
f = open("obstacles.txt", "w")
f.close()

f = open("obstacles.txt", "a")
grid_width = 40
grid_height = 10

for h in range(grid_height):
    for w in range(grid_width):
        isObstacle = random.random() > .75
        if isObstacle:
            f.write(f"{w},{h}\n")

f.close()
