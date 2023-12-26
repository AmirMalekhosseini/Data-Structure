import io

counted = set()
x = []
y = []
first_x_array = []
first_y_array = []
new_x = []
new_y = []
value = 3141592653585

# use merge sort algorithm:
def merge_sort(x, y):
    length = len(x)
    if length <= 1:
        return

    mid = length // 2
    left_x = x[:mid]
    left_y = y[:mid]
    right_x = x[mid:]
    right_y = y[mid:]

    merge_sort(left_x, left_y)
    merge_sort(right_x, right_y)

    merge(x, y, left_x, right_x, left_y, right_y)

def merge(x, y, left_x, right_x, left_y, right_y):
    i = 0 
    j = 0 
    k = 0
    left_array_length = len(left_x)
    right_array_length = len(right_x)

    while i < left_array_length and j < right_array_length:
        left_array_x = left_x[i]
        right_array_x = right_x[j]
        left_array_y = left_y[i]
        rigth_array_y = right_y[j]

        if left_array_x < right_array_x or (left_array_x == right_array_x and left_array_y <= rigth_array_y):
            x[k] = left_array_x
            y[k] = left_array_y
            i += 1
        else:
            x[k] = right_array_x
            y[k] = rigth_array_y
            j += 1
        k += 1

    while j < right_array_length:
        x[k] = right_x[j]
        y[k] = right_y[j]
        j += 1
        k += 1

    while i < left_array_length:
        x[k] = left_x[i]
        y[k] = left_y[i]
        i += 1
        k += 1

# add points to the screen:
def insert_to_screen(x, y):
    length = len(x)
    if length <= 1:
        return

    mid = length // 2
    left_x = x[:mid]
    left_y = y[:mid]
    right_x = x[mid:]
    right_y = y[mid:]

    insert_to_screen(left_x, left_y)
    insert_to_screen(right_x, right_y)

    point_merge(left_y, right_y, x[mid])

def point_merge(left_y, right_y, array_mid):
    add_points(right_y, array_mid)
    add_points(left_y, array_mid)

def add_points(array, array_mid):
    for y in array:
        current_point = array_mid * value + y
        if current_point not in counted:
            new_x.append(array_mid)
            new_y.append(y)
            counted.add(current_point)

# main program:
def main():
    n = int(input())

    for i in range(n):
        x_input , y_input = map(int, input().split())
        first_x_array.append(x_input)
        first_y_array.append(y_input)

    x = first_x_array.copy()
    y = first_y_array.copy()

    merge_sort(x, y)

    global counted
    global new_x
    global new_y
    counted = set()
    new_x = []
    new_y = []

# count current points:
    for i in range(len(first_x_array)):
        counted.add(first_x_array[i] * value + first_y_array[i])

    insert_to_screen(x, y)

    x = first_x_array.copy()
    y = first_y_array.copy()

    merge_sort(x, y)

    buffered_writer = io.StringIO()

    buffered_writer.write(str(len(new_x)) + "\n")
    buffered_writer.flush()
    for i in range(len(new_x)):
        buffered_writer.write(str(new_x[i]) + " " + str(new_y[i]) + "\n")
    buffered_writer.flush()

    print(buffered_writer.getvalue())

if __name__ == "__main__":
    main()
