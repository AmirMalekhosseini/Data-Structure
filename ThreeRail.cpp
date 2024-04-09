#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

class MyStack {
public:
    int arr[100000];
    int top_index = -1;
    void push(int x) {
        top_index++;
        arr[top_index] = x;
    }
    void pop() {
        if (top_index >= 0) {
            top_index--;
        }
    }
    int top() {
        if (top_index >= 0) {
            return arr[top_index];
        } else {
            return -1;
        }
    }
    bool empty() {
        return top_index == -1;
    }
};

class MyList {
public:
    vector<int> l;
    void push_back(int x) {
        l.push_back(x);
    }
    int back() {
        return l.back();
    }
    void pop_back() {
        l.pop_back();
    }
    bool empty() {
        return l.empty();
    }
};

MyStack rail1, rail2, rail3;
MyList finalWayList;

void moveRail1ToRail2() {
    rail2.push(rail1.top());
    rail1.pop();
    finalWayList.push_back(1);
}

void moveRail1ToRail3() {
    rail3.push(rail1.top());
    rail1.pop();
    finalWayList.push_back(2);
}

void moveRail2ToRail3() {
    rail3.push(rail2.top());
    rail2.pop();
    finalWayList.push_back(3);
}

int main() {
    int n;
    cin >> n;

    int perm[100000];
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        perm[i] = x;
    }

    for (int i = 1; i <= n; i++) {
        rail1.push(i);
    }

    int current = n;

    for (int i = n - 1; i >= 0; i--){

        if(!rail2.empty() && rail2.top( ) == perm[i]){
            moveRail2ToRail3();
        }else if(perm[i]<=current){
            while (current != perm[i])
            {
                moveRail1ToRail2();
                current--;
            }
            moveRail1ToRail3();
            current--;
        }else{
            std::cout << -1 << endl;
            return 0;
        }
    }

    cout << finalWayList.l.size() << endl;
    for (int x : finalWayList.l)
    {
        cout << x << " ";
    }

        

    return 0;
}