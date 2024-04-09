import sys


class Node:
    def __init__(self, data):
        
        self.data = data
        self.next = None


class MyList:
    def __init__(self):
        
        self.head = None
        self.length = 0
        self.tail = None

    def append(self, data):

        # Append the given data to the end of the list and increment the length in O(1).

        new_node = Node(data)

        if not self.head:
            self.head = new_node
            self.tail = new_node
        else:
            self.tail.next = new_node
            self.tail = new_node
        self.length += 1

    def pop(self, index):

        if not self.head:
            return None
        if index == 0:
            data = self.head.data
            self.head = self.head.next
            if not self.head:
                self.tail = None
            self.length -= 1
            return data
        current = self.head
        for _ in range(index - 1):
            if not current.next:
                return None
            current = current.next
        data = current.next.data
        current.next = current.next.next
        if not current.next:
            self.tail = current
        self.length -= 1
        return data

    def __getitem__(self, index):

        current = self.head
        for _ in range(index):
            if not current:
                return None
            current = current.next
        return current.data if current else None

    def __len__(self):

        # Return the length of the list in O(1).
        return self.length


def process_data(max_machines, num_tasks, num_batches, cost_per_batch, processing_times, machines):

    # Calculate the total cost of processing the tasks on the machines.

    total_cost = 0
    current_batch = 1
    for _ in range(num_batches):
        current_batch = 1 if current_batch > max_machines else current_batch
        current_task, current_cost = 0, cost_per_batch

        while current_task < len(machines[current_batch - 1]) and current_cost > 0:
            workpiece = machines[current_batch - 1].pop(0)
            if current_cost - workpiece >= 0:
                current_cost -= workpiece
                current_task = 0
            else:
                machines[current_batch - 1].append(workpiece)
                current_task += 1

        total_cost += cost_per_batch * \
            processing_times[current_batch - 1] - \
            current_cost * processing_times[current_batch - 1]
        current_batch += 1

    return total_cost


def populate_machines(max_machines, num_tasks, machines):

    # Populate the machines list with the input data.

    for _ in range(num_tasks):
        task_type, workpiece_weight = map(int, input().split())
        machines[task_type - 1].append(workpiece_weight)


max_machines, num_tasks, num_batches, cost_per_batch = map(
    int, input().split())
processing_times = list(map(int, input().split()))

machines = [MyList() for _ in range(max_machines + 1)]

populate_machines(max_machines, num_tasks, machines)

total_cost = process_data(max_machines, num_tasks,
                          num_batches, cost_per_batch, processing_times, machines)
print(total_cost)
