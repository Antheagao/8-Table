#ifndef PROBLEM_HPP
#define PROBLEM_HPP
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>  // Random function library
#include <ctime>    // Time library

// Problem class to represent the nxn table puzzle
class Problem 
{
    private:
        std::vector<std::vector<int>> initial_state;   // nxn vector
        std::vector<std::string> operators;            // vector for operators
        std::vector<std::vector<int>> goal_state;      // nxn vector for goal
    public:
        // Constructor to initialize the puzzle operators and goal state
        Problem();

        // Destructor to clear the vectors
        ~Problem();

        // Function to test if the goal state has been reached
        bool goal_test(std::vector<std::vector<int>> &state);

        // Functions for initial state
        void change_initial_state();
        void select_initial_state();
        void random_initial_state();
        bool random_helper(std::vector<int> tempList, int temp);

        // Functions for printing tables and operators
        void print_initial_state();
        void print_operators();
        void print_goal_state();

        // Mutator functions
        void set_initial_state(std::vector<std::vector<int>> temp);
        void set_operators(std::vector<std::string> temp);
        void set_goal_state(std::vector<std::vector<int>> temp);

        // Accessor functions
        std::vector<std::vector<int>> get_initial_state() const;
        std::vector<std::string> get_operators() const;
        std::vector<std::vector<int>> get_goal_state() const;
};

#endif 