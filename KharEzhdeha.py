import sys


def heapSort(array):
    counter = 0
    n = len(array)
    for i in range(n // 2 - 1, -1, -1):
        counter += maxHeapify(array, n, i)
    for i in range(n - 1, 0, -1):
        array[0], array[i] = array[i], array[0]
        maxHeapify(array, i, 0)
    return counter


def maxHeapify(array, n, i):
    counter = 0
    largest = i
    left = 2 * i + 1
    right = 2 * i + 2
    if left < n and array[left] > array[largest]:
        largest = left
    if right < n and array[right] > array[largest]:
        largest = right
    if largest != i:
        counter += 1
        array[i], array[largest] = array[largest], array[i]
        counter += maxHeapify(array, n, largest)
    return counter


n = int(sys.stdin.readline())
array = list(map(int, sys.stdin.readline().split()))
counter = heapSort(array)
sys.stdout.write(str(counter))
