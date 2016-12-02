# Shitty late at night code to get this challenge started
def main():
    input_file = open ('input1.txt', 'r')
    path = input_file.readline()
    directions = path.split(', ')
    x_coord = 0
    y_coord = 0
    facing = 'N'
    # print directions
    for direction in directions:
        distance = int(direction[1:])
        if direction[0] == 'R':
            if facing == 'N':
                facing = 'E'
            elif facing == 'E':
                facing = 'S'
            elif facing == 'S':
                facing = 'W'
            elif facing == 'W':
                facing = 'N'
        elif direction[0] == 'L':
            if facing == 'N':
                facing = 'W'
            elif facing == 'W':
                facing = 'S'
            elif facing == 'S':
                facing = 'E'
            elif facing == 'E':
                facing = 'N'
        if facing == 'N':
            y_coord += distance
        elif facing == 'W':
            x_coord -= distance
        elif facing == 'S':
            y_coord -= distance
        elif facing == 'E':
            x_coord += distance

    print "The total distance is:", abs(x_coord) + abs(y_coord)

if __name__ == "__main__":
    main()