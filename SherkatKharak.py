
import sys


class PriorityQueue:
    def __init__(self):
        self.heap = []

    def parent(self, i):
        return (i - 1) // 2

    def left_child(self, i):
        return 2 * i + 1

    def right_child(self, i):
        return 2 * i + 2

    def swap(self, i, j):
        self.heap[i], self.heap[j] = self.heap[j], self.heap[i]

    def insert_max(self, item):
        self.heap.append(item)
        self.heapify_up_max(len(self.heap) - 1)

    def insert_min(self, item):
        self.heap.append(item)
        self.heapify_up_min(len(self.heap) - 1)

    def extract_max(self):
        if len(self.heap) == 0:
            return None

        max_element = self.heap[0]
        self.swap(0, len(self.heap) - 1)
        self.heap.pop()
        self.heapify_down_max(0)

        return max_element

    def extract_min(self):
        if len(self.heap) == 0:
            return None

        min_element = self.heap[0]
        self.swap(0, len(self.heap) - 1)
        self.heap.pop()
        self.heapify_down_min(0)

        return min_element

    def heapify_up_max(self, i):
        while i > 0 and self.heap[i] > self.heap[self.parent(i)]:
            self.swap(i, self.parent(i))
            i = self.parent(i)

    def heapify_down_max(self, i):
        largest = i
        left = self.left_child(i)
        right = self.right_child(i)

        if left < len(self.heap) and self.heap[left] > self.heap[largest]:
            largest = left

        if right < len(self.heap) and self.heap[right] > self.heap[largest]:
            largest = right

        if largest != i:
            self.swap(i, largest)
            self.heapify_down_max(largest)

    def heapify_up_min(self, i):
        while i > 0 and self.heap[i] < self.heap[self.parent(i)]:
            self.swap(i, self.parent(i))
            i = self.parent(i)

    def heapify_down_min(self, i):
        smallest = i
        left = self.left_child(i)
        right = self.right_child(i)

        if left < len(self.heap) and self.heap[left] < self.heap[smallest]:
            smallest = left

        if right < len(self.heap) and self.heap[right] < self.heap[smallest]:
            smallest = right

        if smallest != i:
            self.swap(i, smallest)
            self.heapify_down_min(smallest)


def find_max(queue, n):

    counter = 0

    for _ in range(n):

        max_element = queue.extract_max()
        if max_element is not None:
            counter += max_element
            max_element -= 1
            queue.insert_max(max_element)

    return counter


def find_min(queue, n):

    counter = 0

    for _ in range(n):

        min_element = queue.extract_min()
        if min_element is not None:
            counter += min_element
            min_element -= 1
            if min_element > 0:
                queue.insert_min(min_element)

    return counter


def main():

    max_queue = PriorityQueue()
    min_queue = PriorityQueue()

    n, m = map(int, input().split())

    for _ in range(m):
        item = int(sys.stdin.readline().strip())

        if (item == 0):
            continue

        max_queue.insert_max(item)
        min_queue.insert_min(item)

    max_result = find_max(max_queue, n)
    min_result = find_min(min_queue, n)

    print(min_result, max_result)


if __name__ == "__main__":
    main()
