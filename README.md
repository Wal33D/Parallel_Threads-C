# 🧵 PThreads Project

This repository is dedicated to exploring POSIX Threads (PThreads) for parallel and concurrent programming in C. It serves as an educational resource, offering practical examples and detailed insights into using PThreads to enhance computational efficiency through parallel execution. Specifically, this includes a multithreaded program that calculates various statistical values for a list of numbers.

## 📚 Project Structure

The organization of this project is designed to facilitate a comprehensive learning experience:

- **`src/`**: Hosts the source files (`pthreads.c` and `utils.c`) that implement the foundational concepts of PThreads, including the calculation of average, maximum, and minimum values from a series of numbers.
- **`include/`**: Contains the header files (`utils.h`), which provide the necessary function declarations and definitions to support the source implementations.
- **`build/`**: This directory is generated upon compilation and contains all the object files and the final executable binary.
- **`Makefile`**: Specifies the compilation instructions, simplifying the build process through the `make` command.
- **`README.md`**: Offers an overview of the project, including setup instructions and additional information.
- **`.gitignore`**: Ensures certain files are omitted from version control to keep the repository clean.

## 💡 Features

This project demonstrates a practical application of PThreads by creating three separate worker threads to process a series of numbers for:

1. **Thread 1**: Determines the average of the numbers.
2. **Thread 2**: Determines the maximum value.
3. **Thread 3**: Determines the minimum value.

Additionally, it covers a range of topics related to PThreads:

- Basic to advanced techniques for creating, managing, and synchronizing threads.
- Synchronization mechanisms, such as mutexes and condition variables, to ensure thread safety.
- Implementation of parallel algorithms and a comparison of their performance against single-threaded approaches.
- Strategies for avoiding concurrency issues, including deadlocks and race conditions.

## 🚀 Getting Started

### Prerequisites

- GCC or Clang compiler.
- POSIX-compliant operating system (e.g., Linux, macOS).

### Installation

1. **Clone the repository:**
   \```
   git clone https://github.com/your-repository/PThreads.git
   \```

2. **Change to the project directory:**
   \```
   cd PThreads
   \```

3. **Compile the project:**
   \```
   make
   \```
   This will compile the source files and place the executable at `build/pthreads`.

### 🏃 Running the Project

After compiling, you can run the program by navigating to the `build/` directory and executing the binary:

\```
./pthreads
\```

This command runs the main executable, demonstrating the use of PThreads as implemented, including statistical calculations.

## 🔧 Usage

Dive into the `src/` directory to explore and modify the source files. Experimenting with the code will help you grasp the concepts of concurrent programming with PThreads. Each example within the project is designed to highlight specific features or use cases of PThreads.

## 🤝 Contributing

Contributions are welcome to make this project even more educational and practical. If you're interested in contributing, please:

1. Fork the repository.
2. Create your feature branch (`git checkout -b feature/YourFeature`).
3. Commit your changes (`git commit -am 'Add some YourFeature'`).
4. Push to the branch (`git push origin feature/YourFeature`).
5. Open a Pull Request.

## 📜 License

This project is licensed under the MIT License, supporting open-source education and collaboration.
