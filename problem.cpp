#include "problem.hpp"

// Constructor to initialize the puzzle operators and goal state
// TESTED
Problem::Problem()
{
    /*
        Default Operators for puzzle are:
            Move Blank Left     -> MBL
            Move Blank Right    -> MBR
            Move Blank Up       -> MBU
            Move Blank Down     -> MBD
    */
    operators = {"MBL", "MBR", "MBU", "MBD"};

    // Default goal state for 8 table project
    goal_state = { {1, 2, 3},
                   {4, 5, 6},
                   {7, 8, 0} };
    
    // Default initial state
    initial_state = { {0, 0, 0},
                      {0, 0, 0},
                      {0, 0, 0} };
}

// Destructor to clear the vectors
// TESTED
Problem::~Problem()
{
    initial_state.clear();
    operators.clear();
    goal_state.clear();
}

// Function to test if the goal state has been reached
// TESTED
bool Problem::goal_test(std::vector<std::vector<int>> &state)
{
    if (goal_state == state)
    {
        return true;
    }
    else 
    {
        return false;
    }
}

// Functions for initial state
// Function to let user input initial state
// TESTED
void Problem::change_initial_state()
{
    // Declare variables
    int size = initial_state.size();

    // Loop through 2D table to get user input
    std::cout << "Enter your own 3x3 table, use each number once, "
         << "use 0 as blank:" << std::endl;
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            std::cin >> initial_state[row][col];
        }
    }
}

// Function that lets user select a default initial state
// TESTED
void Problem::select_initial_state()
{
    // Declare variables
    int userInput;
    std::vector<std::vector<int>> diff1 = { {1, 2, 3},
                                            {4, 5, 6},
                                            {7, 8, 0} };

    std::vector<std::vector<int>> diff2 = { {1, 2, 3},
                                            {4, 5, 6},
                                            {0, 7, 8} };

    std::vector<std::vector<int>> diff3 = { {1, 2, 3},
                                            {5, 0, 6},
                                            {4, 7, 8} };

    std::vector<std::vector<int>> diff4 = { {1, 3, 6},
                                            {5, 0, 2},
                                            {4, 7, 8} };

    std::vector<std::vector<int>> diff5 = { {1, 3, 6},
                                            {5, 0, 7},
                                            {4, 8, 2} };

    std::vector<std::vector<int>> diff6 = { {1, 6, 7},
                                            {5, 0, 3},
                                            {4, 8, 2} };
    
    // Get user input for a default table
    std::cout << "Enter a number 1-6 for the difficulty of your puzzle: ";
    std::cin >> userInput;

    // Verify user input
    while (userInput < 1 || userInput > 6)
    {
        std::cout << "Invalid input, enter a number 1-6: ";
        std::cin >> userInput;
    }

    // Mutate the initial state by changing it to a new table difficulty
    if (userInput == 1)
    {
        std::cout << "You chose difficulty " << userInput << std::endl;
        set_initial_state(diff1);
    }
    else if (userInput == 2)
    {
        std::cout << "You chose difficulty " << userInput << std::endl;
        set_initial_state(diff2);
    }
    else if (userInput == 3)
    {
        std::cout << "You chose difficulty " << userInput << std::endl;
        set_initial_state(diff3);
    }
    else if (userInput == 4)
    {
        std::cout << "You chose difficulty " << userInput << std::endl;
        set_initial_state(diff4);
    }
    else if (userInput == 5)
    {
        std::cout << "You chose difficulty " << userInput << std::endl;
        set_initial_state(diff5);
    }
    else if (userInput == 6)
    {
        std::cout << "You chose difficulty " << userInput << std::endl;
        set_initial_state(diff6);
    }
}

// Function that generates a random initial state
// TESTED
void Problem::random_initial_state()
{
    // Declare variables
    std::vector<std::vector<int>> random_puzzle = get_initial_state();
    std::vector<int> tempList;
    int size = initial_state.size();
    int tableSize = initial_state.size() * initial_state.size();
    int temp;

    // Create a random nxn table
    std::cout << "Generating your random 3x3 table..." << std::endl;
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            if (row == 0 && col == 0)
            {
                temp = rand() % tableSize;
                tempList.push_back(temp);
                random_puzzle[row][col] = temp;
            }
            else 
            {
                temp = rand() % tableSize;
                while (random_helper(tempList, temp) == false)
                {
                    temp = rand() % tableSize;
                }
                tempList.push_back(temp);
                random_puzzle[row][col] = temp;
            }
        }
    }

    // Set the initial state to the random table
    set_initial_state(random_puzzle);
}

// Helper function to check if rand number is already part of table
// TESTED
bool Problem::random_helper(std::vector<int> tempList, int temp)
{
    // Declare variables
    int size = tempList.size();

    // Check if the random number is within the list
    for (int index = 0; index < size; index++)
    {
        if (tempList[index] == temp)
        {
            return false;
        }
    }

    return true;
}

// Function to print initial state of table
// TESTED
void Problem::print_initial_state()
{
    // Declare variables
    int size = initial_state.size();

    // Loop through table and display it
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            std::cout << initial_state[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

// Function to print operators of table
// TESTED
void Problem::print_operators()
{
    // Declare variables
    int size = operators.size();

    // Loop and display operators
    for (int index = 0; index < size; index++)
    {
        std::cout << operators[index] << " ";
    }
    std::cout << std::endl;
}

// Function to print goal state of table
// TESTED
void Problem::print_goal_state()
{
    // Declare variables
    int size = goal_state.size();

    // Loop through table and display it
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            std::cout << goal_state[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

// Mutator functions
// TESTED
void Problem::set_initial_state(std::vector<std::vector<int>> temp)
{
    initial_state = temp;
}

void Problem::set_operators(std::vector<std::string> temp)
{
    operators = temp;
}

void Problem::set_goal_state(std::vector<std::vector<int>> temp)
{
    goal_state = temp;
}

// Accessor functions
// TESTED
std::vector<std::vector<int>> Problem::get_initial_state() const
{
    return initial_state;
}

std::vector<std::string> Problem::get_operators() const
{
    return operators;
}

std::vector<std::vector<int>> Problem::get_goal_state() const
{
    return goal_state;
}