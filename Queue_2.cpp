#include <iostream>

using namespace std;

class Student {
public:
    int id;
    Student* mentor;
    Student* mentees[10000];
    int chainLength;
    int menteesCount;

    Student() : id(0), mentor(nullptr), chainLength(0), menteesCount(0) {}

    Student(int studentId) : id(studentId), mentor(nullptr), chainLength(0), menteesCount(0) {}
};

void calculateChainLength(Student* student) {
    int maxChainLength = 0;

    for (int i = 0; i < student->menteesCount; i++) {
        calculateChainLength(student->mentees[i]);
        maxChainLength = max(maxChainLength, student->mentees[i]->chainLength);
    }

    student->chainLength = maxChainLength + 1;
}

int main() {
    int n;
    cin >> n;

    Student* students = new Student[n + 1];

    for (int i = 1; i <= n; i++) {
        students[i] = Student(i);
    }

    for (int i = 1; i <= n; i++) {
        int mentorId;
        cin >> mentorId;

        if (mentorId != -1) {
            students[i].mentor = &students[mentorId];
            students[mentorId].mentees[students[mentorId].menteesCount++] = &students[i];
        }
    }

    for (int i = 1; i <= n; i++) {
        calculateChainLength(&students[i]);
    }

    int maxChainLength = 0;
    for (int i = 1; i <= n; i++) {
        int chainLength = students[i].chainLength;
        maxChainLength = max(maxChainLength, chainLength);
    }

    cout << maxChainLength << endl;

    // Clean up memory
    delete[] students;

    return 0;
}