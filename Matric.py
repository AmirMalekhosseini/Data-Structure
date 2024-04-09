import sys
from collections import defaultdict

input = sys.stdin.readline


class Node:
    def __init__(self, data):
        self.data = data
        self.next = None


class mylist:
    def __init__(self):
        self.head = None

    def append(self, data):
        if not self.head:
            self.head = Node(data)
        else:
            current = self.head
            while current.next:
                current = current.next
            current.next = Node(data)

    def node(self, index):
        current = self.head
        for _ in range(index):
            if current:
                current = current.next
            else:
                return None
        return current

    def __getitem__(self, index):
        current = self.head
        for _ in range(index):
            if current:
                current = current.next
            else:
                return None
        return current.data

    def __setitem__(self, index, data):
        current = self.head
        for _ in range(index):
            if current:
                current = current.next
            else:
                return None
        if current:
            current.data = data

    def __len__(self):
        length = 0
        current = self.head
        while current:
            length += 1
            current = current.next
        return length


def read_matrices():
    """
    Reads input from the standard input and returns two matrices matrix1 and matrix2.
    """
    n, m = map(int, input().split())
    matrix1 = []
    k = int(input())
    for _ in range(k):
        x, y, w = map(int, input().split())
        matrix1.append(((y, x), w))

    r, s = map(int, input().split())
    matrix2 = []
    l = int(input())
    for _ in range(l):
        x, y, w = map(int, input().split())
        matrix2.append(((x, y), w))

    return matrix1, matrix2


def sort_matrices_ascending(matrix1, matrix2):
    """
    Sorts matrices matrix1 and matrix2 in ascending order.
    """
    matrix1.sort()
    matrix2.sort()


def find_common_rows_between_matrices(matrix1, matrix2, i, j):
    """
    Finds the common rows between matrices matrix1 and matrix2 starting from indices i and j.
    """
    while i < len(matrix1) and j < len(matrix2) and matrix1[i][0][0] != matrix2[j][0][0]:
        while i < len(matrix1) and j < len(matrix2) and matrix1[i][0][0] < matrix2[j][0][0]:
            i += 1
        while i < len(matrix1) and j < len(matrix2) and matrix1[i][0][0] > matrix2[j][0][0]:
            j += 1

    return i, j


def process_common_rows_between_matrices(matrix1, matrix2, i, j, row_counter_1, row_counter_2, result_matrix):
    """
    Processes the common rows between matrices matrix1 and matrix2 starting from indices i and j.
    """
    for p1 in range(row_counter_1):
        for p2 in range(row_counter_2):
            result_matrix.append(((matrix1[i + p1][0][1], matrix2[j + p2][0][1]),
                                  matrix1[i + p1][1] * matrix2[j + p2][1]))


def main():
    matrix1, matrix2 = read_matrices()
    sort_matrices_ascending(matrix1, matrix2)

    result_matrix = []
    i = 0
    j = 0
    while i < len(matrix1) and j < len(matrix2):
        i, j = find_common_rows_between_matrices(matrix1, matrix2, i, j)

        if i >= len(matrix1) or j >= len(matrix2):
            break

        row_counter_1 = 0
        row_counter_2 = 0
        while i + row_counter_1 < len(matrix1) and matrix1[i + row_counter_1][0][0] == matrix2[j][0][0]:
            row_counter_1 += 1

        while j + row_counter_2 < len(matrix2) and matrix1[i][0][0] == matrix2[j + row_counter_2][0][0]:
            row_counter_2 += 1

        process_common_rows_between_matrices(
            matrix1, matrix2, i, j, row_counter_1, row_counter_2, result_matrix)

        j += row_counter_2
        i += row_counter_1

    result_matrix.sort()
    final_result_matrix = []
    for temp in result_matrix:
        if not final_result_matrix or final_result_matrix[-1][0] != temp[0]:
            final_result_matrix.append((temp[0], 0))

        final_result_matrix[-1] = (final_result_matrix[-1]
                                   [0], final_result_matrix[-1][1] + temp[1])

    for temp in final_result_matrix:
        sys.stdout.write(f"{temp[0][0]} {temp[0][1]} {temp[1]}\n")


if __name__ == "__main__":
    main()
