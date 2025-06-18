# anyad

A simple tool that searches for the minimum of a [Rosenbrock function](https://en.wikipedia.org/wiki/Rosenbrock_function) using
[forward mode automatic differentiation](https://en.wikipedia.org/wiki/Automatic_differentiation#Forward_accumulation).


## Setup

To build this project a C++ compiler that supports the C++17 standard (or above), and CMake are required.
Once those are available to your system:

```bash
# Remove existing build directory if it exists
rm -rf build

# Create and enter build directory
mkdir build && cd build

# Configure and build the project
cmake ..
make

# Run the program
./ad ../config.toml
```


## Run configuration

The `config.toml` file contains the parameters to configure the Rosenbrock function, and to configure the
search parameters. With the former, the `a` and `b` parameters of the Rosenbrock function can be tweaked to
shift the minimum, and to make its "valley" less steep. With the latter set of parameters the resources spent for the
search can be set.

### [rosenbrock]

- `a` - defines the minimum of the function (if b > 0), i.e., xmin = a, ymin = a^2.
- `b` - defines the steepness of the valley.

### [search]

- `alpha` - scale for the step in the direction of the steepest descent.
- `epochs` - the number of gradient-descent steps to take.
- `multi_trial_count` - the number of random of starting points to try (the total amount of steps is epochs * multi\_trial\_count).


## Beyond Rosenbrock

...Implementation of custom functions...
