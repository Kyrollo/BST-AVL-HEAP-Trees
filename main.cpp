#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

fstream myfile;
vector<int> IdList;

class BST
{
private:
    class Node
    {
    public:
        int id;
        string name;
        float gpa;
        string depart;
        Node *left;
        Node *right;
        Node(int Id, string Name, float Gpa, string Dep)
        {
            id = Id;
            name = Name;
            gpa = Gpa;
            depart = Dep;
            left = right = nullptr;
        }
    };

    Node *root;
    int cs = 0, it = 0, ds = 0, is = 0;
    Node *Insert(Node *root, int id, string name, float gpa, string depart)
    {
        if (root == nullptr)
        {
            return new Node(id, name, gpa, depart);
        }
        if (id < root->id)
        {
            root->left = Insert(root->left, id, name, gpa, depart);
        }
        else if (id > root->id)
        {
            root->right = Insert(root->right, id, name, gpa, depart);
        }
        return root;
    }

    Node *FindMin(Node *node)
    {
        Node *current = node;
        while (current && current->left != nullptr)
        {
            current = current->left;
        }
        return current;
    }
    Node *RemoveBst(Node *root, int id)
    {

        if (root == nullptr)
        {
            return root;
        }
        if (id < root->id)
        {
            root->left = RemoveBst(root->left, id);
        }
        else if (id > root->id)
        {
            root->right = RemoveBst(root->right, id);
        }
        else
        {
            if (root->left == nullptr)
            {
                Node *temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr)
            {
                Node *temp = root->left;
                delete root;
                return temp;
            }
            Node *temp = FindMin(root->right);
            root->id = temp->id;
            root->name = temp->name;
            root->gpa = temp->gpa;
            root->depart = temp->depart;
            root->right = RemoveBst(root->right, temp->id);
        }
        return root;
    }
    Node *SearchBst(Node *root, int id)
    {
        if (root == nullptr || root->id == id)
        {
            return root;
        }
        if (id < root->id)
        {
            return SearchBst(root->left, id);
        }

        return SearchBst(root->right, id);
    }

    void print(Node *root)
    {

        if (root == nullptr)
        {

            return;
        }
        print(root->left);
        cout << "ID : " << root->id << endl;
        cout << "Name : " << root->name << endl;
        cout << "GPA : " << root->gpa << endl;
        cout << "Department : " << root->depart << endl;
        if (root->depart == "CS")
        {
            cs++;
        }
        else if (root->depart == "IT")
        {
            it++;
        }
        else if (root->depart == "DS")
        {
            ds++;
        }
        else if (root->depart == "IS")
        {
            is++;
        }
        cout << "------------------------------------" << endl;
        print(root->right);
    }

public:
    BST()
    {
        root = nullptr;
    }
    void AddStudent(int id, string name, float gpa, string depart)
    {
        root = Insert(root, id, name, gpa, depart);
    }
    bool SearchStu(int id)
    {
        Node *result = SearchBst(root, id);
        if (result == nullptr)
        {
            cout << "Student not found" << endl;
            cout << endl;
            return false;
        }
        else
        {
            cout << "Student is found" << endl;
            cout << "ID: " << result->id << endl;
            cout << "Name : " << result->name << endl;
            cout << "GPA : " << result->gpa << endl;
            cout << "Department : " << result->depart << endl;
            cout << endl;

            return true;
        }
    }
    void RemoveStu(int id)
    {
        if (SearchStu(id) == true)
        {
            root = RemoveBst(root, id);
            cout << "Student is deleted " << endl;
            cout << endl;
        }
    }
    void PrintAll()
    {
        cs = 0, it = 0, ds = 0, is = 0;
        print(root);
        cout << "Students per Departments: " << endl;
        cout << "CS " << cs << " Students" << endl;
        cout << "IT " << it << " Students" << endl;
        cout << "DS " << ds << " Students" << endl;
        cout << "IS " << is << " Students" << endl;
        cout << endl;
    }
};

struct Student
{
    int id;
    string name;
    double gpa;
    string department;
};

class AVL
{
private:
    struct Node
    {
        Student student;
        int height;
        int key;
        Node *left;
        Node *right;
        Node(const Student &stud) : student(stud), height(1), key(1), left(nullptr), right(nullptr) {}
    };
    Node *root;
    int cs = 0, it = 0, ds = 0, is = 0;

    int getHeight(Node *N)
    {
        if (N == NULL)
            return 0;
        return N->height;
    }

    int getKey(Node *node)
    {
        if (node == nullptr)
            return 0;
        return node->key;
    }

    int balanceFactor(Node *node)
    {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    void updateHeight(Node *node)
    {
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    Node *rotateLeft(Node *node)
    {
        Node *pivot = node->right;
        node->right = pivot->left;
        pivot->left = node;
        updateHeight(node);
        updateHeight(pivot);
        return pivot;
    }

    Node *rotateRight(Node *node)
    {
        Node *pivot = node->left;
        node->left = pivot->right;
        pivot->right = node;
        updateHeight(node);
        updateHeight(pivot);
        return pivot;
    }

    Node *insertHelper(Node *node, const Student &stud)
    {
        if (node == nullptr)
        {
            return new Node(stud);
        }

        if (stud.id < node->student.id)
        {
            node->left = insertHelper(node->left, stud);
        }
        else if (stud.id > node->student.id)
        {
            node->right = insertHelper(node->right, stud);
        }
        else
        {
            // Duplicate IDs are not allowed in AVL, so we can return without any modifications.
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        node->key = 1 + getKey(node->left) + getKey(node->right);

        int balance = balanceFactor(node);

        if (balance > 1 && stud.id < node->left->student.id)
        {
            return rotateRight(node);
        }

        if (balance < -1 && stud.id > node->right->student.id)
        {
            return rotateLeft(node);
        }

        if (balance > 1 && stud.id > node->left->student.id)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && stud.id < node->right->student.id)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    Node *findMin(Node *node)
    {
        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }

    Node *deleteHelper(Node *node, int id)
    {
        if (node == nullptr)
        {
            return node;
        }

        if (id < node->student.id)
        {
            node->left = deleteHelper(node->left, id);
        }
        else if (id > node->student.id)
        {
            node->right = deleteHelper(node->right, id);
        }
        else
        {
            // Found the node to be deleted
            if (node->left == nullptr && node->right == nullptr)
            {
                // Node has no children
                delete node;
                node = nullptr;
            }
            else if (node->left == nullptr)
            {
                // Node has only right child
                Node *temp = node;
                node = node->right;
                delete temp;
            }
            else if (node->right == nullptr)
            {
                // Node has only left child
                Node *temp = node;
                node = node->left;
                delete temp;
            }
            else
            {
                // Node has both left and right children
                Node *successor = findMin(node->right);
                node->student = successor->student;
                node->right = deleteHelper(node->right, successor->student.id);
            }
        }

        if (node == nullptr)
        {
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        node->key = 1 + getKey(node->left) + getKey(node->right);

        int balance = balanceFactor(node);

        if (balance > 1 && balanceFactor(node->left) >= 0)
        {
            return rotateRight(node);
        }

        if (balance > 1 && balanceFactor(node->left) < 0)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && balanceFactor(node->right) <= 0)
        {
            return rotateLeft(node);
        }

        if (balance < -1 && balanceFactor(node->right) > 0)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node *searchHelper(Node *node, int id)
    {
        if (node == nullptr || node->student.id == id)
        {
            return node;
        }

        if (id < node->student.id)
        {
            return searchHelper(node->left, id);
        }
        else
        {
            return searchHelper(node->right, id);
        }
    }

    void printHelper(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }
        printHelper(node->left);
        cout << "ID : " << node->student.id << "\n";
        cout << "Name : " << node->student.name << "\n";
        cout << "GPA : " << node->student.gpa << "\n";
        cout << "Department : " << node->student.department << "\n";
        if (node->student.department == "CS" || node->student.department == "cs")
        {
            cs++;
        }
        else if (node->student.department == "IT" || node->student.department == "it")
        {
            it++;
        }
        else if (node->student.department == "DS" || node->student.department == "ds")
        {
            ds++;
        }
        else if (node->student.department == "IS" || node->student.department == "is")
        {
            is++;
        }
        cout << "------------------------------------"
             << "\n";
        printHelper(node->right);
    }

public:
    AVL() : root(nullptr) {}

    void insertStudent(const Student &stud)
    {
        root = insertHelper(root, stud);
    }

    void removeStudent(int id)
    {
        root = deleteHelper(root, id);
    }

    bool searchStudent(int id)
    {
        Node *node = searchHelper(root, id);
        if (node != nullptr)
        {
            cout << "\nStudent found:\n";
            cout << "ID: " << node->student.id << "\n";
            cout << "Name: " << node->student.name << "\n";
            cout << "GPA: " << node->student.gpa << "\n";
            cout << "Department: " << node->student.department << "\n";
        }
        else
        {
            cout << "\nStudent not found.\n";
        }
    }

    void printAll()
    {
        if (root == nullptr)
        {
            cout << "No students found.\n";
            return;
        }
        cout << "\nAll Students:\n";
        printHelper(root);
        cout << "Students per Departments:\n";
        cout << "CS: " << cs << " Students\n";
        cout << "IT: " << it << " Students\n";
        cout << "DS: " << ds << " Students\n";
        cout << "IS: " << is << " Students\n";
        cs = it = ds = is = 0;
    }
};

class MinHeap{
	private:
		vector<Student> arr = {};

	public:

		bool findId(int id){

			bool found = false;

			for(int i = 0 ; i < arr.size() ; i++){

				if(arr[i].id == id){
					found = true;
					break;
				}

			}

			return found;
		}
		void heapify(int n, int i)
		{
		    int smallest = i;
		    int l = 2 * i + 1;
		    int r = 2 * i + 2;

		    if (l < n && arr[l].gpa < arr[smallest].gpa)
		        smallest = l;

		    if (r < n && arr[r].gpa < arr[smallest].gpa)
		        smallest = r;

		    if (smallest != i) {
		        swap(arr[i], arr[smallest]);

		        heapify(n, smallest);
		    }
		}

		void heapSort()
		{
		 	int n = arr.size();
		    for (int i = n / 2 - 1; i >= 0; i--)
		        heapify( n, i);

		    for (int i = n - 1; i >= 0; i--) {
		        swap(arr[0], arr[i]);

		        heapify( i, 0);
		    }
		}

		void printAll()
		{
		    for (int i =  arr.size()-1; i > -1; --i)
		        cout << arr[i].name << "-" << arr[i].gpa << "\n";
		}

		void add_student(Student new_s){
			arr.push_back(new_s);
			heapSort();
		}
};

struct Node
{
    int id;
    string name;
    float gpa;
    string department;

    Node(int _id, const string &_name, float _gpa, const string &_department)
    {
        id = _id;
        name = _name;
        gpa = _gpa;
        department = _department;
    }
};

class MaxHeap
{
private:
    vector<Node> heap;

    void heapify(int n, int i)
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && heap[left].gpa > heap[largest].gpa)
            largest = left;

        if (right < n && heap[right].gpa > heap[largest].gpa)
            largest = right;

        if (largest != i)
        {
            swap(heap[i], heap[largest]);
            heapify(n, largest);
        }
    }

    void heapSort()
    {
        int n = heap.size();

        // Build a max heap
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(n, i);

        // Extract elements from the heap one by one
        for (int i = n - 1; i > 0; i--)
        {
            // Move the current root (maximum element) to the end
            swap(heap[0], heap[i]);

            // Call heapify on the reduced heap
            heapify(i, 0);
        }
    }

public:
    void insert(Node node)
    {
        heap.push_back(node);
        IdList.push_back(node.id);
        heapSort();
    }

    void printHeap()
    {
        for (int i = heap.size() - 1; i >= 0; i--)
        {
            cout << "ID: " << heap[i].id << endl
                 << "Name: " << heap[i].name << endl
                 << "GPA: " << heap[i].gpa << endl
                 << "Department: " << heap[i].department << endl
                 << "----------------------------------\n";
        }
    }
};

bool validateGPA(float gpa)
{
    if (gpa > 4.0 || gpa < 0)
    {
        cout << "Invalid GPA: " << gpa << endl;
        return false;
    }
    else
        return true;
}

bool validateDept(string &dept)
{
    if (dept == "IS" || dept == "IT" || dept == "DS" || dept == "CS" || dept == "is" || dept == "it" || dept == "ds" || dept == "cs")
    {
        return true;
    }
    else
        cout << "Invalid Department: " << dept << endl;
        return false;
}

bool validateID(int id)
{
    for (int i = 0; i < IdList.size(); i++)
    {
        if (id == IdList[i])
        {
            cout << "Duplicate ID: " << id << endl;
            return false;
            break;
        }
        else
            return true;
    }
}


void maxheapmenu()
{
    MaxHeap tree;
    int id;
    string name, d;
    float gpa;
    fstream myfile;
    myfile.open("input.txt", ios::in);
    if (myfile.is_open())
    {
        string line0, line1, line2, line3, line4;
        getline(myfile, line0);
        while (getline(myfile, line1) && getline(myfile, line2) && getline(myfile, line3) && getline(myfile, line4))
        {
            int StoreId;
            string StoreName;
            float StoreGpa;
            string StoreDep;

            istringstream iss1(line1);
            if (!(iss1 >> StoreId))
            {
                cerr << "Error parsing line: " << line1 << '\n';
                continue;
            }

            istringstream iss3(line3);
            if (!(iss3 >> StoreGpa))
            {
                cerr << "Error parsing line: " << line3 << '\n';
                continue;
            }

            StoreName = line2;
            StoreDep = line4;
            Node node(StoreId, StoreName, StoreGpa, StoreDep);
            tree.insert(node);
        }
    }
    myfile.close();
    int option;
    cout << "1. Add student" << endl;
    cout << "2. Print All (sorted by GPA)" << endl;
    cout << "3.close" << endl;

    cin >> option;
    while (option == 1 || option == 2 || option == 3)
    {
        if (option == 1)
        {
            cout << "Enter the new student" << endl;
            cout << "id : ";
            cin >> id;
            cout << "Name : ";
            cin.ignore(1, '\n');
            getline(cin, name);
            cout << "GPA : ";
            cin >> gpa;
            cout << "Department : ";
            cin >> d;
            if (validateDept(d) && validateGPA(gpa) && validateID(id))
            {
                Node node(id, name, gpa, d);
                tree.insert(node);
                cout << "Student is added Successfully " << endl;
                cout << endl;
            }
            else
                cout << "try again with valid data !\n";
        }
        else if (option == 2)
        {
            myfile.open("input.txt");
            string line0;
            if (getline(myfile, line0))
            {
                cout << line0 << endl;
            }
            tree.printHeap();
            myfile.close();
        }
        else
        {
            cout << "closed ";
            break;
        }
        cout << "1. Add student" << endl;
        cout << "2. Print All (sorted by GPA)" << endl;
        cout << "3.close" << endl;
        cin >> option;
    }
}

void storeData(BST &tree)
{
    fstream myfile;
    myfile.open("input.txt", ios::in);
    if (myfile.is_open())
    {
        string line0, line1, line2, line3, line4;
        getline(myfile, line0);
        while (getline(myfile, line1) && getline(myfile, line2) && getline(myfile, line3) && getline(myfile, line4))
        {
            int StoreId;
            string StoreName;
            float StoreGpa;
            string StoreDep;

            istringstream iss1(line1);
            if (!(iss1 >> StoreId))
            {
                cerr << "Error parsing line: " << line1 << '\n';
                continue;
            }

            istringstream iss3(line3);
            if (!(iss3 >> StoreGpa))
            {
                cerr << "Error parsing line: " << line3 << '\n';
                continue;
            }

            StoreName = line2;
            StoreDep = line4;
            tree.AddStudent(StoreId, StoreName, StoreGpa, StoreDep);
        }
    }
    myfile.close();
}

void storeData(AVL &avl)
{
    Student newStudent;
    fstream myfile;
    myfile.open("input.txt", ios::in);
    if (myfile.is_open())
    {
        string line0, line1, line2, line3, line4;
        getline(myfile, line0);
        while (getline(myfile, line1) && getline(myfile, line2) && getline(myfile, line3) && getline(myfile, line4))
        {
            int StoreId;
            string StoreName;
            float StoreGpa;
            string StoreDep;

            istringstream iss1(line1);
            if (!(iss1 >> StoreId))
            {
                cerr << "Error parsing line: " << line1 << '\n';
                continue;
            }

            istringstream iss3(line3);
            if (!(iss3 >> StoreGpa))
            {
                cerr << "Error parsing line: " << line3 << '\n';
                continue;
            }
            StoreName = line2;
            StoreDep = line4;
            newStudent.id = StoreId;
            newStudent.name = StoreName;
            newStudent.gpa = StoreGpa;
            newStudent.department = StoreDep;
            avl.insertStudent(newStudent);
        }
    }
    myfile.close();
}

void storeData(MinHeap &students)
{
    fstream myfile;
    myfile.open("input.txt", ios::in);
    if (myfile.is_open())
    {
        string line0, line1, line2, line3, line4;
        getline(myfile, line0);
        while (getline(myfile, line1) && getline(myfile, line2) && getline(myfile, line3) && getline(myfile, line4))
        {
            int StoreId;
            string StoreName;
            float StoreGpa;
            string StoreDep;

            istringstream iss1(line1);
            if (!(iss1 >> StoreId))
            {
                cerr << "Error parsing line: " << line1 << '\n';
                continue;
            }

            istringstream iss3(line3);
            if (!(iss3 >> StoreGpa))
            {
                cerr << "Error parsing line: " << line3 << '\n';
                continue;
            }

            StoreName = line2;
            StoreDep = line4;
            Student new_s = {StoreId, StoreName, StoreGpa, StoreDep};
            students.add_student(new_s);
        }
    }
    myfile.close();
}

int main()
{
    BST tree;
    storeData(tree);
    AVL avl;
    storeData(avl);
    MinHeap min_heap;
    storeData(min_heap);
    int dataChoice;
    cout << "1. BST"
         << "\n";
    cout << "2. AVL"
         << "\n";
    cout << "3. Min Heap"
         << "\n";
    cout << "4. Max Heap"
         << "\n";
    cout << "5. Exit Program"
         << "\n";
    cout << "Enter your choice: ";
    cin >> dataChoice;

    while (dataChoice != 5)
    {
        switch (dataChoice)
        {
        case 1:
        {
            int id;
            string name, d;
            float gpa;
            int option;
            cout << "1. Add student\n";
            cout << "2. Remove student\n";
            cout << "3. Search student\n";
            cout << "4. Print All (sorted by id)\n";
            cout << "5. Return to main menu\n";
            cout << "Enter your choice: ";
            cin >> option;
            while (option == 1 || option == 2 || option == 3 || option == 4)
            {
                if (option == 1)
                {

                    cout << "Enter the new student" << endl;
                    cout << "id : ";
                    cin >> id;

                    cout << "Name : ";
                    cin.ignore(1, '\n');
                    getline(cin, name);
                    cout << "GPA : ";
                    cin >> gpa;
                    cout << "Department : ";
                    cin >> d;

                    if(validateGPA(gpa)&&validateDept(d))
                    {
                        tree.AddStudent(id, name, gpa, d);
                        cout << "Student is added Successfully " << endl;
                        cout << endl;
                    }
                    else
                    cout << "try again with valid data !\n";
                    cout << endl;
                }
                else if (option == 2)
                {
                    int RemoveID;
                    cout << "ID : ";
                    cin >> RemoveID;
                    tree.RemoveStu(RemoveID);
                }
                else if (option == 3)
                {
                    int SearchId;
                    cout << "ID : ";
                    cin >> SearchId;
                    tree.SearchStu(SearchId);
                }

                else if (option == 4)
                {
                    myfile.open("input.txt");
                    string line0;
                    if (getline(myfile, line0))
                    {
                        cout << line0 << endl;
                    }
                    tree.PrintAll();
                    myfile.close();
                }

                else if (option == 5)
                {
                    cout << "\nReturning to the main menu.\n";
                    break;
                }

                cout << "1. Add student" << endl;
                cout << "2. Remove student" << endl;
                cout << "3. Search student" << endl;
                cout << "4. Print All (sorted by id)" << endl;
                cin >> option;
            }
            break;
        }
        case 2:
        {
            Student newStudent;
            int choice;
            while (choice != 5)
            {

                cout << "\nChoose one of the following options:"
                     << "\n";
                cout << "1. Add student"
                     << "\n";
                cout << "2. Remove student"
                     << "\n";
                cout << "3. Search student"
                     << "\n";
                cout << "4. Print All (sorted by id)"
                     << "\n";
                cout << "5. Return to main menu"
                     << "\n";
                cout << "Enter your choice: ";
                cin >> choice;
                switch (choice)
                {
                case 1:
                {
                    Student newStudent;
                    cout << "\nEnter student ID: ";
                    cin >> newStudent.id;
                    while (validateID(newStudent.id))
                    {
                        cout << "\nEnter an unique student ID: ";
                        cin >> newStudent.id;
                    }
                    cout << "\nEnter student name: ";
                    cin.ignore();
                    getline(cin, newStudent.name);
                    cout << "\nEnter student GPA: ";
                    cin >> newStudent.gpa;
                    while (!validateGPA(newStudent.gpa))
                    {
                        cout << "\nEnter student GPA: ";
                        cin >> newStudent.gpa;
                    }
                    cout << "\nEnter student department: ";
                    cin.ignore();
                    getline(cin, newStudent.department);
                    while (!validateDept(newStudent.department))
                    {
                        cout << "\nEnter a valid student department: ";
                        cin.ignore();
                        getline(cin, newStudent.department);
                    }
                    avl.insertStudent(newStudent);
                    cout << "Student added successfully!"
                         << "\n";
                    break;
                }
                case 2:
                {
                    int id;
                    cout << "\nEnter student ID to remove: ";
                    cin >> id;
                    avl.removeStudent(id);
                    cout << "Student removed successfully!"
                         << "\n";
                    break;
                }
                case 3:
                {
                    int id;
                    cout << "\nEnter student ID to search: ";
                    cin >> id;
                    avl.searchStudent(id);
                    break;
                }
                case 4:
                {
                    cout << "\n";
                    avl.printAll();
                    break;
                }
                case 5:
                {
                    cout << "\nReturning to the main menu.\n";
                    break;
                }
                default:
                {
                    cout << "Invalid choice . Please enter a valid choice.\n";
                    break;
                }
                }
            }
            break;
        }
        case 3: {
                 Student newStudent;
                int choice;
                while (choice != 3)
                {

                    cout << "\nChoose one of the following options:" << "\n";
                    cout << "1. Add student" << "\n";
                    cout << "2. Print All (sorted by gpa)" << "\n";
                    cout << "3. Return to main menu" << "\n";
                    cout << "Enter your choice: ";
                    cin >> choice;
                    switch (choice) {
                        case 1: {
                            Student newStudent;
                            cout << "\nEnter student ID: ";
                            cin >> newStudent.id;
                            while(min_heap.findId(newStudent.id)){
                            	    cout << "Id Already exists ,  Enter id Again: ";

                            	 cin >> newStudent.id;
							}
                            cout << "Enter student name: ";
                            cin.ignore();
                            getline(cin, newStudent.name);
                            cout << "Enter student GPA: ";
                            cin >> newStudent.gpa;
                             while(newStudent.gpa < 0 || newStudent.gpa > 4){
                            	    cout << "Gpa not valid ,  Enter gpa Again: ";

                            	 cin >> newStudent.gpa;
							}
                            cout << "Enter student department: ";
                            cin.ignore();
                            getline(cin, newStudent.department);
                            min_heap.add_student(newStudent);
                            cout << "Student added successfully!" << "\n";
                            break;
                        }

                        case 2: {
                            cout << "\n";
                            min_heap.printAll();
                            break;
                        }
                        case 3: {
                            cout << "\nReturning to the main menu.\n";
                            break;
                        }
                        default:{
                            cout << "Invalid choice . Please enter a valid choice.\n";
                        break;
                        }
                    }
                }

                break;
            }
        case 4:
        {
            maxheapmenu();
            break;
        }
        case 5:
        {
            cout << "Exiting the program."
                 << "\n";
            break;
        }
        default:
        {
            cout << "Invalid choice. Please enter a valid choice."
                 << "\n";
            break;
        }
        }
        cout << "\n\n1. BST"
             << "\n";
        cout << "2. AVL"
             << "\n";
        cout << "3. Min Heap"
             << "\n";
        cout << "4. Max Heap"
             << "\n";
        cout << "5. Exit Program"
             << "\n";
        cout << "Enter your choice: ";
        cin >> dataChoice;
    }
}


