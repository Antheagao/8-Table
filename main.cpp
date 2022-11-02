/*
    Name:   Anthony Mendez
    Date:   11/1/22

    Description: This is a program which solves an 8-Table puzzle using
                 the general search algorithm that performs different
                 searches depending on the heuristic
                
*/
#include "problem.cpp"  // For problem class, 
#include <queue>        // For priority queue to hold puzzle states
#include <set>          // To hold states visited, avoiding repeated states
#include <utility>      // For swap function
#include <algorithm>    // For max function
#include <cmath>        // For absolute value
using namespace std;

// Function prototypes
// Let //* = TESTED (function has been tested and proven correct)
vector<vector<int>> general_search(Problem &problem, string queueing_function);
// * Uniform cost search                * Solved and tested up to depth 16
// * Misplaced Tile Heuristic           * Solved and tested up to depth 12
// * Manhattan Distance Heuristic       * Solved and tested up to depth 16
queue<vector<vector<int>>> expand(vector<vector<int>> node,
                                  vector<string> operators); //*
void push_helper(queue<vector<vector<int>>> &nodes,
                 queue<vector<vector<int>>> children,
                 set<vector<vector<int>>> visitedStates,
                 string queueing_function); //*
void calc_lowest_hn(queue<vector<vector<int>>> &nodes,
                    queue<vector<vector<int>>> notRepeat, queue<int> hnList);
void calc_misplaced_hn(queue<vector<vector<int>>>notRepeat,
                       queue<int> &hnList);
void calc_manhattan_hn(queue<vector<vector<int>>>notRepeat,
                       queue<int> &hnList);
bool valid_index(string op, vector<vector<int>> node); //*
vector<vector<int>> create_child(string op, vector<vector<int>> node); //*
void printTable(vector<vector<int>> &nxnTable); //*
void createTable(Problem &problem); //*
void displayOptions(); //*
void verifyInput(int lower, int upper, int &userInput); //*
void inputAction(Problem &problem, int userInput); //*
vector<vector<int>> searchAlgorithmChoice(Problem &problem); //*

int main(int argc, char **argv)
{
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));

    // Declare variables
    Problem problem;
    int userInput;
    vector<vector<int>> result;
    vector<vector<int>> failure = { {0, 0, 0},
                                    {0, 0, 0},
                                    {0, 0, 0} };

    // Display game options and get user input
    displayOptions();
    cin >> userInput;
    verifyInput(1, 4, userInput);
    cout << "You chose option " << userInput << endl << endl;
    
    // Choose initial state for puzzle based on user input
    inputAction(problem, userInput);

    // Display the puzzle that the user chose
    cout << endl << "The initial state of your puzzle is: " << endl;
    problem.print_initial_state();
    cout << endl;

    // Get user input for search algorithm and perform it
    result = searchAlgorithmChoice(problem);

    // Display final message to user
    if (result == problem.get_goal_state())
    {
        cout << "The solved nxn table is: " << endl;
        printTable(result);
    }
    else 
    {
        cout << "The nxn table with no solution is: " << endl;
        printTable(result);
    }

    return 0;
}

// Function for General (Generic) Search Algorithm
vector<vector<int>> general_search(Problem &problem, string queueing_function)
{
    // Declare variables
    queue<vector<vector<int>>> nodes;       // Priority queue of puzzle states
    queue<vector<vector<int>>> children;    // pushed into back of nodes
    vector<vector<int>> node;               // The current head puzzle state
    set<vector<vector<int>>> visitedStates; // Holds visited states, no repeat
    int num_nodes_expanded = 0;             // Number of nodes expanded
    int max_queue_size = 0;                 // largest size of the queue
    int queue_size = 0;                     // Current size of queue
    int solution_depth = -1;                // The depth of the solution

    // Push initial state into the queue
    nodes.push(problem.get_initial_state());

    // Loop until the queue is empty, or solution is found in loop
    while (nodes.empty() == false)
    {
        // Update the max size of queue
        queue_size = nodes.size();
        max_queue_size = max(queue_size, max_queue_size);

        // Store front node, mark it as visited, and remove it
        node = nodes.front();
        visitedStates.insert(node);
        nodes.pop();

        // Update solution depth
        solution_depth++;

        // If the node is at goal state return it, otherwise expand it
        if (problem.goal_test(node) == true)
        {
            cout << "Solution found!!!" << endl;
            cout << "Solution depth was: " << int(solution_depth / log2(2.13)) + 1 << endl;
            cout << "Number of nodes expanded: " << num_nodes_expanded << endl;
            cout << "Max queue size: " << max_queue_size << endl;
            return node;
        }
        else 
        {cout << "Number of nodes expanded: " << num_nodes_expanded << endl;
            // Expand the node and receive all of its children
            children = expand(node, problem.get_operators());
            num_nodes_expanded++;

            // Put children into queue if they are not a repeated state
            push_helper(nodes, children, visitedStates, queueing_function);
        }
    }

    // There is no solution, return initial state
    cout << "Failure, no solution found" << endl;
    return problem.get_initial_state();
}

// Function to expand the children of a node
// TESTED
queue<vector<vector<int>>> expand(vector<vector<int>> node,
                                  vector<string> operators)
{
    // Declare variables
    queue<vector<vector<int>>> children;
    int size = operators.size();
    
    // Create all children for the given node
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

// Helper function to push temp queue into nodes queue
// TESTED
void push_helper(queue<vector<vector<int>>> &nodes,
                 queue<vector<vector<int>>> children,
                 set<vector<vector<int>>> visitedStates,
                 string queueing_function)
{
    // Declare variables
    queue<vector<vector<int>>> notRepeat;
    queue<int> hnList;

    // Loop until children queue is empty to filter out repeat states
    while(children.empty() == false)
    {
        // If the child state is not a repeated state, push it into the queue
        if (visitedStates.find(children.front()) == visitedStates.end())
        {
            notRepeat.push(children.front());
            children.pop();
        }
        else 
        {
            children.pop();
        }
    }

    // Decide which queueing function is being used
    if (queueing_function == "Uniform Cost")
    {
        while (notRepeat.empty() == false)
        {
            nodes.push(notRepeat.front());
            notRepeat.pop();
        }
    }
    else if (queueing_function == "Misplaced Tiles")
    {
        // Calculate an h(n) value for each child
        calc_misplaced_hn(notRepeat, hnList);

        // Decide which child has min h(n), store it and print it
        calc_lowest_hn(nodes, notRepeat, hnList);
    }
    else if (queueing_function == "Manhattan Distance")
    {
        // Calculate the h(n) value for each child
        calc_manhattan_hn(notRepeat, hnList);
        
        // Decide which child has min h(n), store it and print it
        calc_lowest_hn(nodes, notRepeat, hnList);
    }
}

// Function to calculate the min h(n) for a list of h(n)
void calc_lowest_hn(queue<vector<vector<int>>> &nodes,
                    queue<vector<vector<int>>> notRepeat, queue<int> hnList)
{
    // Declare variables
    int minHn = hnList.front();
    vector<vector<int>> bestHn = notRepeat.front();
    
    hnList.pop();
    notRepeat.pop();

    // Calculate the min h(n) of queue
    while (notRepeat.empty() == false)
    {
        if (min(hnList.front(), minHn) == hnList.front())
        {
            minHn = hnList.front();
            bestHn = notRepeat.front();
            hnList.pop();
            notRepeat.pop();
        }
        else 
        {
            hnList.pop();
            notRepeat.pop();
        }
    }
    
    // Display the lowest h(n) and push it into the queue
    cout << "The best state to expand with a g(n) = 1 and h(n) = " << minHn << " is..." << endl;
    printTable(bestHn);
    nodes.push(bestHn);
}

// Function to calculate value of misplaced tile heuristic
void calc_misplaced_hn(queue<vector<vector<int>>>notRepeat, 
                       queue<int> &hnList)
{
    // Declare variables
    Problem problem;
    vector<vector<int>> goal = problem.get_goal_state();
    vector<vector<int>> grid;
    int size = goal.size();
    int hn;

    // Calculate the number of tiles out of place and store them in the queue
    while (notRepeat.empty() == false)
    {
        hn = 0;
        grid = notRepeat.front();
        for (int row = 0; row < size; row++)
        {
            for (int col = 0; col < size; col++)
            {
                if (grid.at(row).at(col) != goal.at(row).at(col)
                    && grid.at(row).at(col) != 0)
                {
                    hn++;
                }
            }
        }
        notRepeat.pop();
        hnList.push(hn);
    }
}

// Function to calculate value of manhattan heuristic
void calc_manhattan_hn(queue<vector<vector<int>>>notRepeat,
                       queue<int> &hnList)
{
    // Declare variables
    Problem problem;
    vector<vector<int>> goal = problem.get_goal_state();
    vector<vector<int>> grid;
    int size = goal.size();
    int hn;

    // Calculate the distance to tile's goal state and store the total
    while (notRepeat.empty() == false)
    {
        hn = 0;
        grid = notRepeat.front();
        for (int row = 0; row < size; row++)
        {
            for (int col = 0; col < size; col++)
            {
                if (grid.at(row).at(col) != goal.at(row).at(col) &&
                    grid.at(row).at(col) != 0)
                {
                    for (int i = 0; i < size; i++)
                    {
                        for (int j = 0; j < size; j++)
                        {
                            if (grid.at(row).at(col) == goal.at(i).at(j))
                            {
                                hn += (abs(row - i) + abs(col - j));
                            }
                        }
                    }
                }
            }
        }

        // Remove front state from queue and store its h(n) value
        notRepeat.pop();
        hnList.push(hn);
    }
}

// Function to check if blank can be moved in desired direction
// TESTED
bool valid_index(string op, vector<vector<int>> node)
{
    // Declare variables
    int size = node.size();

    // Check the operator that is being performed
    if (op == "MBL")
    {
        // If blank is at leftmost column, it cannot be moved further left
        for (int row = 0; row < size; row++)
        {
            if (node.at(row).at(0) == 0)
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
            if (node.at(row).at(size - 1) == 0)
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
            if (node.at(0).at(col) == 0)
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
            if (node.at(size - 1).at(col) == 0)
            {
                return false;
            }
        }
    }

    // Blank can be moved in desired direction, return true
    return true;
}

// Function to create a child by shifting blank
// TESTED
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

    /*
        This wont be reached, the node is guranteed to be swapped since
        valid_index() verified the node can be swapped before this function call
        The node is returned in the if statements to prevent double swapping
    */
    return node;
}

// Function to print an nxn table
// TESTED
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

// Function to let user create a custom table with nxn size
// TESTED
void createTable(Problem &problem)
{
    // Declare variables
    int size;
    int temp;
    int count = 0;
    vector<vector<int>> tempVector;
    vector<vector<int>> tempGoalVector;

    // Get input for size of nxn table
    cout << "Enter an integer n between 2-4 for the nxn table: ";
    cin >> size;

    // Verify the input fot the table
    while (size < 2 || size > 4)
    {
        cout << "Invalid input, enter integer n"
             << "between 2-4 for nxn table: ";
        cin >> size;
    }

    // Loop and get input for the rows and columns of the table
    cout << "Enter rows and columns for your " << size << "x"
         << size << " table:" << endl;
    for (int row = 0; row < size; row++)
    {
        vector<int> rowVector;
        for (int col = 0; col < size; col++)
        {
            cin >> temp;
            rowVector.push_back(temp);
        }
        tempVector.push_back(rowVector);
    }

    // Set the initial state of the table using mutator function
    problem.set_initial_state(tempVector);    

    // Update the goal state nxn
    tempGoalVector = tempVector;
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            if (row == size - 1 && col == size - 1)
            {
                tempGoalVector[row][col] = 0;
            }
            else 
            {
                count++;
                tempGoalVector[row][col] = count;
            }
        }
    }
    problem.set_goal_state(tempGoalVector);
}

// Function to display options
// TESTED
void displayOptions()
{
    // Display the choices to the user
    cout << "This is an AI puzzle table solver, "
         << "below are a list of options." << endl << endl;
    cout << "1: Use a 3x3 default puzzle" << endl;
    cout << "2: Enter your own 3x3 puzzle" << endl;
    cout << "3: Use a randomly generated 3x3 puzzle" << endl;
    cout << "4: Create your own nxn puzzle" << endl << endl;
    cout << "Enter your choice from 1-4: ";
}

// Function to verify any user input with 2 bounds
// TESTED
void verifyInput(int lower, int upper, int &userInput)
{
    // Loop and ask for input if the user input is invalid
    while (userInput < lower || userInput > upper)
    {
        cout << "Invalid input, Enter a number from " << lower
             << "-" << upper << ": " << endl;
        cin >> userInput;
    }
}

// Perform one of the options chosen by the user
// TESTED
void inputAction(Problem &problem, int userInput)
{
    // create an initial state based on user input
    if (userInput == 1)
    {
        problem.select_initial_state();
    }
    else if (userInput == 2)
    {
        problem.change_initial_state();
    }
    else if (userInput == 3)
    {
        problem.random_initial_state();
    }
    else if (userInput == 4)
    {
        createTable(problem);
    }
}

// Function to select a search algorithm based on user input
// TESTED
vector<vector<int>> searchAlgorithmChoice(Problem &problem)
{
    // Declare and initialize variables
    int userInput;
    vector<vector<int>> result;
    string algorithm1 = "UniformCostSearch";
    string algorithm2 = "Misplaced Tile Heuristic";
    string algorithm3 = "Manhattan Distance Heuristic";


    // Display choices to user
    cout << "The search algorithm choices are: " << endl;
    cout << "1: " << algorithm1 << endl;
    cout << "2: " << algorithm2 << endl;
    cout << "3: " << algorithm3 << endl;
    cout << endl << "Enter your choice from 1-3: ";

    // Get the user input and verify it
    cin >> userInput;
    verifyInput(1, 3, userInput);

    // Call the search algorithm that was chosen
    if (userInput == 1)
    {
        cout << "You chose " << algorithm1 << endl << endl;
        result = general_search(problem, "Uniform Cost");
    }
    else if (userInput == 2)
    {
        cout << "You chose " << algorithm2 << endl << endl;
        result = general_search(problem, "Misplaced Tiles");
    }
    else if (userInput == 3)
    {
        cout << "You chose " << algorithm3 << endl << endl;
        result = general_search(problem, "Manhattan Distance");
    }

    // Return the result vector to main
    return result;
}