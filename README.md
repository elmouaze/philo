# Philosophers: "I Never Thought Philosophy Would Be So Deadly"

This repository contains my implementation of the **Philosophers** project, where philosophers sit at a round table and alternately eat, think, and sleep, with a key challenge being to avoid starvation. The project was designed to teach threading, process synchronization, and the use of mutexes in C. 

## Table of Contents

- [Project Overview](#project-overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Compilation](#compilation)
- [Logs and Output](#logs-and-output)
- [Contributing](#contributing)
- [License](#license)

---

## Project Overview

In this project, philosophers are represented by threads that must share forks to eat. The goal is to ensure that each philosopher gets a chance to eat without causing starvation or race conditions, by managing the allocation of shared resources (the forks) using mutexes.

The project involves creating a simulation of philosophers who:
- Think
- Eat (using two forks)
- Sleep
- Try to avoid dying of starvation

Philosophers must not run into data races or deadlocks, and must respect the time constraints on eating, sleeping, and dying.

---

## Features

- **Multithreading**: Each philosopher is represented as a separate thread.
- **Mutexes**: Forks are protected by mutexes to ensure only one philosopher can use them at a time.
- **Simulation Rules**: Philosophers must alternate between thinking, eating, and sleeping, and cannot starve.
- **Logging**: Detailed logging for each philosopher's actions and status changes.

---

## Installation

To get started with the project, clone this repository to your local machine:

```bash
git clone https://github.com/yourusername/philosophers.git
cd philosophers
```

Ensure you have a C compiler (e.g., `gcc`) and `make` installed.

---

## Usage

### Run the Simulation

To compile and run the simulation, simply use the provided Makefile:

1. **Compile the project**:

```bash
make
```

2. **Run the simulation** with the required arguments:

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers`: Total number of philosophers (and forks).
- `time_to_die`: Time in milliseconds a philosopher can go without eating before dying.
- `time_to_eat`: Time in milliseconds it takes for a philosopher to eat.
- `time_to_sleep`: Time in milliseconds a philosopher will sleep.
- `number_of_times_each_philosopher_must_eat` (optional): If provided, the simulation stops when all philosophers have eaten this many times.

Example:

```bash
./philo 5 800 200 200 3
```

This will simulate 5 philosophers, with a 800ms death timeout, 200ms for eating and sleeping, and each philosopher must eat 3 times.

---

## Project Structure

```
philosophers/
│
├── Makefile               # Makefile to compile the project
├── philo.c                # Main C file containing the program logic
├── philo.h                # Header file containing declarations
└── README.md              # Project documentation
```

---

## Compilation

To compile the project:

1. **Makefile**: Use the provided Makefile, which includes rules for `make all`, `make clean`, `make fclean`, and `make re`.
2. **Libraries**: This project does not use external libraries except for the standard C library (`pthread` for multithreading).

---

## Logs and Output

The program will log the actions of each philosopher in the following format:

```
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```

- `timestamp_in_ms`: The current time in milliseconds.
- `X`: The philosopher number.

**Example Output**:

```
1001 1 has taken a fork
1002 1 is eating
1003 1 is sleeping
1004 1 is thinking
1005 2 has taken a fork
1006 2 is eating
...
```

A philosopher's death (if they starve) is logged similarly:

```
2001 1 died
```

---

## Contributing

If you'd like to contribute to this project, feel free to fork the repository, make changes, and submit a pull request. For any issues or feature requests, open an issue.

---

## License

This project is licensed under the MIT License.

---

Feel free to modify the sections as needed!
