def merge(arr, temp, left, mid, right):
    i = left
    j = mid + 1
    k = left
    count = 0

    while i <= mid and j <= right:
        if arr[i] > arr[j] * 19:
            count += mid - i + 1
            j += 1
        else:
            i += 1

    i = left
    j = mid + 1

    while i <= mid and j <= right:
        if arr[i] <= arr[j]:
            temp[k] = arr[i]
            i += 1
        else:
            temp[k] = arr[j]
            j += 1
        k += 1

    while i <= mid:
        temp[k] = arr[i]
        i += 1
        k += 1

    while j <= right:
        temp[k] = arr[j]
        j += 1
        k += 1

    for i in range(left, right + 1):
        arr[i] = temp[i]

    return count

def mergeSort(arr, temp, left, right):
    count = 0

    if left < right:
        mid = (left + right) // 2

        count += mergeSort(arr, temp, left, mid)
        count += mergeSort(arr, temp, mid + 1, right)
        count += merge(arr, temp, left, mid, right)

    return count

def countSituations(arr):
    n = len(arr)
    temp = [0] * n

    return mergeSort(arr, temp, 0, n - 1)

# Input n
n = int(input())

# Input array members
arr = list(map(int, input().split()))

count = countSituations(arr)
print(count)