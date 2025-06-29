#include <iostream>
#include <string>
#include <stack>
#include <windows.h>
#include <limits> 
#include <cstdlib> // For system("cls")
using namespace std;

// Task Class
class Task {
private:
    string description;
    string activity;
    int priority;

public:
	void displayWelcomeMessage() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 11); // Light blue text
    cout << "==============================================\n";
    cout << "     Welcome to the Advanced Task Manager!     \n";
    cout << "==============================================\n";
    cout << " Manage your tasks efficiently with features like:\n";
    cout << " -> High-priority task handling\n";
    cout << " -> General task tracking\n";
    cout << " -> Repeating task management\n";
    cout << " -> Task completion history\n";
    cout << "----------------------------------------------\n";
    cout << "       Your productivity partner awaits!       \n";
    cout << "==============================================\n\n";
    SetConsoleTextAttribute(hConsole, 15); // Reset to white
}

    Task() : description(""), activity(""), priority(-1) {}
    Task(const string& desc, const string& act, int pri)
        : description(desc), activity(act), priority(pri) {}

    string getDescription() const { return description; }
    string getActivity() const { return activity; }
    int getPriority() const { return priority; }

    void inputTask() {
        cout << "Enter Task description: ";
        cin.ignore();
        getline(cin, description);

        // Validate priority input
        while (true) {
            cout << "Enter Task priority (any integer): ";
            if (cin >> priority) { // Check if input is a valid integer
                cin.ignore(); // Clear the buffer
                break; // Valid input, exit loop
            } else {
            	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 12);
                cin.clear(); // Clear error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << "Invalid input. Please enter a valid integer for priority.\n";
                SetConsoleTextAttribute(hConsole, 15);
            }
        }

        cout << "Enter Task activity: ";
        getline(cin, activity);
    }

    void printTask() const {
        cout << "Description: " << description << endl;
        cout << "Activity: " << activity << endl;
        cout << "Priority: " << priority << endl;
    }

    bool operator<(const Task& other) const {
        return priority < other.priority; // Higher priority comes first
    }
};

// Priority Queue for High-Priority Tasks using Doubly Linked List
class PriorityQueue {
private:
    struct Node {
        Task task;
        Node* next;
        Node* prev;
        Node(Task t) : task(t), next(NULL), prev(NULL) {}
    };
    Node* head;

public:
    PriorityQueue() : head(NULL) {}

    void addTask(const Task& task) {
        Node* newNode = new Node(task);

        // Insert in sorted order based on priority
        if (!head) { // If the list is empty
            head = newNode;
        } else if (task.getPriority() > head->task.getPriority()) { // Insert at the head
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        } else { // Insert in the middle or end
            Node* current = head;
            while (current->next && current->next->task.getPriority() >= task.getPriority()) {
                current = current->next;
            }
            newNode->next = current->next;
            newNode->prev = current;
            if (current->next) {
                current->next->prev = newNode;
            }
            current->next = newNode;
        }
    }

    Task getNextTask() {
        if (!head) return Task(); // Return an empty task if the list is empty
        Node* temp = head;
        Task task = temp->task;
        head = head->next;
        if (head) {
            head->prev = NULL;
        }
        delete temp;
        return task;
    }

    bool isEmpty() const {
        return head == NULL;
    }

    void displayTasks() const {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 10); // Green text
        cout << "====================================\n";
        cout << "Priority Queue Tasks:\n";
        cout << "====================================\n";
        if (!head) {
            cout << "There is no high-priority task.\n";
            SetConsoleTextAttribute(hConsole, 15); // Reset to white
            return;
        }
        Node* current = head;
        cout << " Priority               Description\n";
        while (current) {
            cout << "    " << current->task.getPriority() << "     	          " << current->task.getDescription() << "\n";
            current = current->next;
        }
        SetConsoleTextAttribute(hConsole, 15); // Reset to white
    }

    ~PriorityQueue() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};


// Singly Linked List for General Tasks
class SinglyLinkedList {
private:
    struct Node {
        Task task;
        Node* next;
        Node(Task t) : task(t), next(NULL) {}
    };
    Node* head;
    Node* tail;

public:
    SinglyLinkedList() : head(NULL), tail(NULL) {}

    void addTask(const Task& task) {
        Node* newNode = new Node(task);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    Task removeTask() {
        if (!head) return Task();
        Node* temp = head;
        Task task = temp->task;
        head = head->next;
        if (!head) tail = NULL; // If list becomes empty
        delete temp;
        return task;
    }

    bool isEmpty() const {
        return head == NULL;
    }

    void displayTasks() const {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 14); // Yellow text
        cout << "====================================\n";
        cout << "Singly Linked List Tasks:\n";
        cout << "====================================\n";
        Node* temp = head;
        if(temp==NULL){
        	cout<<"There is no General Task."<<endl;
        	return;
		}
        	cout<<  " Priority		"<<"Decription			"<<endl;
        while (temp) {
            cout << "  " << temp->task.getPriority() <<   "  		  	  " << temp->task.getDescription() << "  " << endl;
            temp = temp->next;
          
        }
      //  cout<<"There is no General Task."<<endl;
        SetConsoleTextAttribute(hConsole, 15); // Reset to white
    }
};

// Circular Linked List for Repeating Tasks
class CircularLinkedList {
private:
    struct Node {
        Task task;
        Node* next;
        Node(Task t) : task(t), next(NULL) {}
    };
    Node* head;
    Node* tail;

public:
    CircularLinkedList() : head(NULL), tail(NULL) {}

    void addTask(const Task& task) {
        Node* newNode = new Node(task);
        if (!head) {
            head = tail = newNode;
            tail->next = head; // Circular connection
        } else {
            tail->next = newNode;
            tail = newNode;
            tail->next = head;
        }
    }

    Task getTask() {
        if (!head) return Task();
        return head->task; // Just retrieve the task
    }

    void moveToNext() {
        if (head) head = head->next; // Move to next task
    }

    bool isEmpty() const {
        return head == NULL;
    }

    void displayTasks() const {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 9); // Blue text
        cout << "====================================\n";
        cout << "Circular Linked List Tasks:\n";
        cout << "====================================\n";
        	
        if (!head){
        	cout<<"There is no Repeating task yet."<<endl;
	return;	} 
        	cout<<  " Priority "<<"   	        Decription		"<<endl;
        Node* temp = head;
        do {
            cout << "  " << temp->task.getPriority() << "                       " << temp->task.getDescription()<<endl;
            temp = temp->next;
        } while (temp != head);
        SetConsoleTextAttribute(hConsole, 15); // Reset to white
    }
};

// Stack for Completed Tasks
class Stack {
private:
    stack<Task> tasks;

public:
    void push(const Task& task) {
        tasks.push(task);
    }

    void displayTasks() const {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 12); // Red text
        cout << "====================================\n";
        cout << "Completed Tasks Stack:\n";
        cout << "====================================\n";
        stack<Task> temp = tasks;
        if(temp.empty()){
        	cout<<"Still there is no complteted Task."<<endl;
        	return;
		}
			cout<<  " Priority "<<"   	        Decription		"<<endl;
        while (!temp.empty()) {
        		
                cout << "  " << temp.top().getPriority() << "                      " << temp.top().getDescription()<< endl;
            temp.pop();
        }
        SetConsoleTextAttribute(hConsole, 15); // Reset to white
    }
};

// Main Program
int main() {
    SinglyLinkedList generalTasks;
    PriorityQueue highPriorityTasks;
    CircularLinkedList repeatingTasks;
    Stack completedTasks;

    int choice;
	Task task;
	task.displayWelcomeMessage();
    while (true) {
        cout << "\n1. Add Task\n2. Add Repeating Task\n3. Complete Task\n4. Display All Tasks\n5. Exit\nEnter your choice: ";

        // Input validation
        if (!(cin >> choice)) { // Check if input is invalid
            cin.clear(); // Clear error state
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 12);
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a valid number.\n";
            SetConsoleTextAttribute(hConsole, 15);
            continue; // Re-prompt the user
        }

        switch (choice) {
            case 1: { // Add task
                Task task;
                task.inputTask();
                if (task.getPriority() > 8) {
                    highPriorityTasks.addTask(task);
                } else {
                    generalTasks.addTask(task);
                }
                cout <<"\nTask Added!" << endl;
                break;
            }
            case 2: { // Add repeating task
                Task task;
                task.inputTask();
                repeatingTasks.addTask(task);
                cout << "Repeating Task Added!" << endl;
                break;
            }
            case 3: { // Complete a task
                if (!highPriorityTasks.isEmpty()) {
                    Task task = highPriorityTasks.getNextTask();
                    cout << "Completing High-Priority Task:\n";
                    task.printTask();
                    completedTasks.push(task);
                } else if (!generalTasks.isEmpty()) {
                    Task task = generalTasks.removeTask();
                    cout << "Completing General Task (FIFO):\n";
                    task.printTask();
                    completedTasks.push(task);
                } else if (!repeatingTasks.isEmpty()) {
                    Task task = repeatingTasks.getTask();
                    cout << "Completing Repeating Task:\n";
                    task.printTask();
                    completedTasks.push(task);
                    repeatingTasks.moveToNext();
                } else {
                    cout << "No tasks to complete.\n";
                }
                break;
            }
            case 4: { // Display tasks
                system("cls"); // Clear the console screen
                cout << "\nDisplaying All Tasks...\n";
                highPriorityTasks.displayTasks();
                generalTasks.displayTasks();
                repeatingTasks.displayTasks();
                completedTasks.displayTasks();
                break;
            }
            case 5: {
                cout << "\nExiting program.\n Best of Luck!";
                return 0;
            }
            default: {
            	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 12);
                cout << "Invalid choice. Please select a valid option (1-5).\n";
                SetConsoleTextAttribute(hConsole, 15);
            }
        }
    }
}

