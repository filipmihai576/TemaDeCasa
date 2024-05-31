# Traveling Salesman Problem Solver

This repository contains a C program to solve the Traveling Salesman Problem using various algorithms.

## Compilation and Building Instructions

To compile the code and build the application binaries, follow these steps:

1. **Clone the Repository**: Clone this repository to your local machine using Git:

    ```bash
    git clone https://github.com/yourusername/tsp_solver.git
    ```

2. **Navigate to the Directory**: Change your current directory to the repository directory:

    ```bash
    cd tsp_solver
    ```

3. **Compile the Code**: Compile the source code files using a C compiler. For example, using GCC:

    ```bash
    gcc -o tsp_solver tsp_solver.c data_structures.c main.c -lm
    ```

    Make sure you have GCC installed on your system. The `-lm` flag is used to link the math library.

4. **Run the Executable**: Run the generated executable to solve the Traveling Salesman Problem:

    ```bash
    ./tsp_solver
    ```

    This will display the results of solving the problem using DFS, UCS, and A* algorithms.

## Usage

The program automatically generates a small instance of the Traveling Salesman Problem with 4 cities and predefined distances between them. To solve a different instance, modify the `distances` array in the `main.c` file with your desired distances.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
