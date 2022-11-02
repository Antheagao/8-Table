#include "problem.cpp"  // For problem class, 
#include <queue>        // For priority queue to hold puzzle states
#include <set>          // To hold states visited, avoiding repeated states
#include <cmath>
using namespace std;

bool valid_index(string op, vector<vector<int>> child);
void push_helper(queue<vector<vector<int>>> &nodes,
                 queue<vector<vector<int>>> children,
                 set<vector<vector<int>>> visitedStates);
vector<vector<int>> create_child(string op, vector<vector<int>> node);
queue<vector<vector<int>>> expand(vector<vector<int>> node,
                                  vector<string> operators);
void printTable(vector<vector<int>> &nxnTable);
void test_valid_index();
void test_push_helper();
void test_create_child();
void test_expand();

int main()
{
    //test_valid_index();
    //test_push_helper();
    //test_create_child();
    //test_expand();

    double num = 13/7;
    //cout << log2(4) / log2(1.1);
    cout << log2(46) / log2(2.13);
    return 0;
}

void test_valid_index()
{
    vector<string> ops = {"MBL", "MBR", "MBU", "MBD"};
    vector<vector<int>> test1 = { {1, 2, 3},
                                 {4, 5, 6},
                                 {7, 8, 0} };
    vector<vector<int>> test2 = { {1, 2, 3},
                                 {4, 5, 6},
                                 {7, 0, 8} };

    vector<vector<int>> test3 = { {1, 2, 3},
                                 {4, 5, 6},
                                 {0, 8, 7} };
    vector<vector<int>> test4 = { {1, 2, 3},
                                 {4, 5, 0},
                                 {7, 8, 6} };
    vector<vector<int>> test5 = { {1, 2, 3},
                                 {4, 0, 6},
                                 {7, 8, 5} };

    vector<vector<int>> test6 = { {1, 2, 3},
                                 {0, 5, 6},
                                 {7, 8, 4} };
    vector<vector<int>> test7 = { {1, 2, 0},
                                 {4, 5, 6},
                                 {7, 8, 3} };
    vector<vector<int>> test8 = { {1, 0, 3},
                                 {4, 5, 6},
                                 {7, 8, 2} };

    vector<vector<int>> test9 = { {0, 2, 3},
                                 {4, 5, 6},
                                 {7, 8, 1} };
    queue<vector<vector<int>>> list;

    list.push(test1); list.push(test2); list.push(test3);
    list.push(test4); list.push(test5); list.push(test6);
    list.push(test7); list.push(test8); list.push(test9);

    queue<vector<vector<int>>> superList = list;

    for (int index = 0; index < ops.size(); index++)
    {
        list = superList;
        while (list.empty() == false)
        {
            if (valid_index(ops[index], list.front()))
            {
                cout << "This table can perform " << ops[index] << endl;
                for (int row = 0; row < list.front().size(); row++)
                {
                    for (int col = 0; col < list.front().size(); col++)
                    {
                        cout << list.front()[row][col] << " ";
                    }
                    cout << endl;
                }
                cout << endl;
            }
            else 
            {
                cout << "This table cannot perform " << ops[index] << endl;
                for (int row = 0; row < list.front().size(); row++)
                {
                    for (int col = 0; col < list.front().size(); col++)
                    {
                        cout << list.front()[row][col] << " ";
                    }
                    cout << endl;
                }
                cout << endl;
            }
            list.pop();
        }
    }
}

// Function to check if blank can be moved in desired direction
bool valid_index(string op, vector<vector<int>> child)
{
    // Declare variables
    int size = child.size();

    // Check the operator that is being performed
    if (op == "MBL")
    {
        // If blank is at leftmost column, it cannot be moved further left
        for (int row = 0; row < size; row++)
        {
            if (child.at(row).at(0) == 0)
            {
                return false;
            }
        }
    }
    else if (op == "MBR")
    {
        // If blank is at rightmost column, it cannot be moved further right
        for (int row = 0; row < size; row++)
        {
            if (child.at(row).at(size - 1) == 0)
            {
                return false;
            }
        }
    }
    else if (op == "MBU")
    {
        // If blank is at topmost row, it cannot be moved further up
        for (int col = 0; col < size; col++)
        {
            if (child.at(0).at(col) == 0)
            {
                return false;
            }
        }
    }
    else if (op == "MBD")
    {
        // If blank is at bottommost row, it cannot be moved further down
        for (int col = 0; col < size; col++)
        {
            if (child.at(size - 1).at(col) == 0)
            {
                return false;
            }
        }
    }

    // Blank can be moved in desired direction, return true
    return true;
}

// Helper function to push temp queue into nodes queue
void push_helper(queue<vector<vector<int>>> &nodes,
                 queue<vector<vector<int>>> children,
                 set<vector<vector<int>>> visitedStates)
{
    // Loop until children queue is empty
    while(children.empty() == false)
    {
        // If the child state is not a repeated state, push it into the queue
        if (visitedStates.find(children.front()) == visitedStates.end())
        {
            nodes.push(children.front());
            children.pop();
        }
        else 
        {
            children.pop();
        }
    }
}

void test_push_helper()
{
    // Declare test variables
    queue<vector<vector<int>>> nodes;
    queue<vector<vector<int>>> children;
    set<vector<vector<int>>> visitedStates;

    vector<vector<int>> test1 = { {1, 2, 3},
                                 {4, 5, 6},
                                 {7, 8, 0} };
    vector<vector<int>> test2 = { {1, 2, 3},
                                 {4, 5, 6},
                                 {7, 0, 8} };

    vector<vector<int>> test3 = { {1, 2, 3},
                                 {4, 5, 6},
                                 {0, 8, 7} };
    vector<vector<int>> test4 = { {1, 2, 3},
                                 {4, 5, 0},
                                 {7, 8, 6} };
    vector<vector<int>> test5 = { {1, 2, 3},
                                 {4, 0, 6},
                                 {7, 8, 5} };

    vector<vector<int>> test6 = { {1, 2, 3},
                                 {0, 5, 6},
                                 {7, 8, 4} };
    vector<vector<int>> test7 = { {1, 2, 0},
                                 {4, 5, 6},
                                 {7, 8, 3} };
    vector<vector<int>> test8 = { {1, 0, 3},
                                 {4, 5, 6},
                                 {7, 8, 2} };

    vector<vector<int>> test9 = { {0, 2, 3},
                                 {4, 5, 6},
                                 {7, 8, 1} };

    children.push(test1); children.push(test2); children.push(test3);
    children.push(test4); children.push(test5); children.push(test6);
    children.push(test7); children.push(test8); children.push(test9);
    
    visitedStates.insert(test1);
    visitedStates.insert(test2);
    visitedStates.insert(test3);

    push_helper(nodes, children, visitedStates);

    cout << "These nodes made it to the list, duplicates omitted " << endl;
    while (nodes.empty() == false)
    {
        for (int row = 0; row < nodes.front().size(); row++)
                {
                    for (int col = 0; col < nodes.front().size(); col++)
                    {
                        cout << nodes.front()[row][col] << " ";
                    }
                    cout << endl;
                }
                cout << endl;
        nodes.pop();
    }
}

// Function to create a child by shifting blank
vector<vector<int>> create_child(string op, vector<vector<int>> node)
{
    // Declare variables
    int size = node.size();

    // Find blank and swap it in direction based on operator
    if (op == "MBL")
    {
        // Swap blank with the value to its left
        for (int row = 0; row < size; row++)
        {
            for (int col = 1; col < size; col++)
            {
                if (node.at(row).at(col) == 0)
                {
                    swap(node.at(row).at(col), node.at(row).at(col - 1));
                    return node;
                }
            }
        }
    }
    else if (op == "MBR")
    {
        // Swap blank with the value to its right
        for (int row = 0; row < size; row++)
        {
            for (int col = 0; col < size - 1; col++)
            {
                if (node.at(row).at(col) == 0)
                {
                    swap(node.at(row).at(col), node.at(row).at(col + 1));
                    return node;
                }
            }
        }
    }
    else if (op == "MBU")
    {
        // Swap blank with the value above it
        for (int row = 1; row < size; row++)
        {
            for (int col = 0; col < size; col++)
            {
                if (node.at(row).at(col) == 0)
                {
                    swap(node.at(row).at(col), node.at(row - 1).at(col));
                    return node;
                }
            }
        }
    }
    else if (op == "MBD")
    {
        // Swap blank with the value below it
        for (int row = 0; row < size - 1; row++)
        {
            for (int col = 0; col < size; col++)
            {
                if (node.at(row).at(col) == 0)
                {
                    swap(node.at(row).at(col), node.at(row + 1).at(col));
                    return node;
                }
            }
        }
    }

    return node;
}

void test_create_child()
{
    vector<vector<int>> test1 = { {1, 2, 3},
                                 {4, 5, 6},
                                 {7, 8, 0} };
    vector<vector<int>> test2 = { {1, 2, 3},
                                 {4, 5, 6},
                                 {7, 0, 8} };

    vector<vector<int>> test3 = { {1, 2, 3},
                                 {4, 5, 6},
                                 {0, 8, 7} };
    vector<vector<int>> test4 = { {1, 2, 3},
                                 {4, 5, 0},
                                 {7, 8, 6} };
    vector<vector<int>> test5 = { {1, 2, 3},
                                 {4, 0, 6},
                                 {7, 8, 5} };

    vector<vector<int>> test6 = { {1, 2, 3},
                                 {0, 5, 6},
                                 {7, 8, 4} };
    vector<vector<int>> test7 = { {1, 2, 0},
                                 {4, 5, 6},
                                 {7, 8, 3} };
    vector<vector<int>> test8 = { {1, 0, 3},
                                 {4, 5, 6},
                                 {7, 8, 2} };

    vector<vector<int>> test9 = { {0, 2, 3},
                                 {4, 5, 6},
                                 {7, 8, 1} };

    queue<vector<vector<int>>> list;
    queue<vector<vector<int>>> superList;
    vector<vector<int>> child;
    vector<string> ops = {"MBL", "MBR", "MBU", "MBD"};

    list.push(test1); list.push(test2); list.push(test3);
    list.push(test4); list.push(test5); list.push(test6);
    list.push(test7); list.push(test8); list.push(test9);

    superList = list;
    for (int index = 0; index < ops.size(); index++)
    {
        list = superList;
        while (list.empty() == false)
        {   if (valid_index(ops[index], list.front()) == true)
            {
                cout << "The table for " << ops[index] << " : " << endl;
                printTable(list.front());
                cout << endl;
                cout << "Created the child" << endl;
                child = create_child(ops[index], list.front());
                printTable(child);
                cout << endl;
                list.pop();
            }
            else 
            {
                list.pop();
            }
        }
    }
    
}

void printTable(vector<vector<int>> &nxnTable)
{
    // Declare variables
    int size = nxnTable.size();

    // Loop through table and display it
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            cout << nxnTable[row][col] << " ";
        }
        cout << endl;
    }
}

// Function to expand the children of a node
queue<vector<vector<int>>> expand(vector<vector<int>> node,
                                  vector<string> operators)
{
    // Declare variables
    queue<vector<vector<int>>> children;
    int size = operators.size();
    
    for (int index = 0; index < size; index++)
    {
        if (operators[index] == "MBL" && valid_index(operators[index], node))
        {
            children.push(create_child(operators[index], node));
        }
        else if (operators[index] == "MBR" &&
                 valid_index(operators[index], node))
        {
            children.push(create_child(operators[index], node));
        }
        else if (operators[index] == "MBU" &&
                 valid_index(operators[index], node))
        {
            children.push(create_child(operators[index], node));
        }
        else if (operators[index] == "MBD" && 
                 valid_index(operators[index], node))
        {
            children.push(create_child(operators[index], node));
        }
    }

    return children;
}

void test_expand()
{
    queue<vector<vector<int>>> children;
    vector<string> ops = {"MBL", "MBR", "MBU", "MBD"};
    vector<vector<int>> test1 = { {1, 2, 3},
                                 {4, 5, 6},
                                 {7, 8, 0} };
    vector<vector<int>> test2 = { {1, 2, 3},
                                 {4, 5, 6},
                                 {7, 0, 8} };

    vector<vector<int>> test3 = { {1, 2, 3},
                                 {4, 5, 6},
                                 {0, 8, 7} };
    vector<vector<int>> test4 = { {1, 2, 3},
                                 {4, 5, 0},
                                 {7, 8, 6} };
    vector<vector<int>> test5 = { {1, 2, 3},
                                 {4, 0, 6},
                                 {7, 8, 5} };

    vector<vector<int>> test6 = { {1, 2, 3},
                                 {0, 5, 6},
                                 {7, 8, 4} };
    vector<vector<int>> test7 = { {1, 2, 0},
                                 {4, 5, 6},
                                 {7, 8, 3} };
    vector<vector<int>> test8 = { {1, 0, 3},
                                 {4, 5, 6},
                                 {7, 8, 2} };

    vector<vector<int>> test9 = { {0, 2, 3},
                                 {4, 5, 6},
                                 {7, 8, 1} };

    cout << "The parent node: " << endl;
    children = expand(test2, ops);
    printTable(test2);
    cout << endl;
    while (children.empty() == false)
    {   
        cout << "One of the children: " << endl;
        printTable(children.front());
        cout << endl;
        children.pop();
    }
}