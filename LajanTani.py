import sys

def findLajanSize(array):
    
    lajan_height = [0] * len(array)
    for i in range(len(array)):
        
        left_array = array[:i]
        right_array = array[i:]
        lajan_height[i] = min(max(left_array or [0]), max(right_array or [0])) - array[i]

    return lajanMaxArea(lajan_height)

def lajanMaxArea(lajan_height_array): 

    stack = list() 
    max_area = 0
    index = 0

    while index < len(lajan_height_array): 

        if (not stack) or (lajan_height_array[stack[-1]] <= lajan_height_array[index]): 

            stack.append(index) 

            index += 1

        else: 

            top_of_stack = stack.pop() 
            area = (lajan_height_array[top_of_stack] *

                    ((index - stack[-1] - 1) 

                     if stack else index)) 

            max_area = max(max_area, area) 

    while stack: 

        top_of_stack = stack.pop()  

        area = (lajan_height_array[top_of_stack] *

                ((index - stack[-1] - 1) 

                 if stack else index)) 

        max_area = max(max_area, area) 

    return max_area 


n = int(sys.stdin.readline())
array = list(map(int, sys.stdin.readline().split()))
sys.stdout.write(str(findLajanSize(array)))
