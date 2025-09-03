# MNIST Classifier in C

This project is a simple **hand-written digit recognizer** implemented in C.  
It uses pre-trained weights for 10 classes (digits 0–9) and runs inference directly from the command line.

## Project Structure

- `src/data.c` - stores weights and bias values for 10 output neurons  
- `src/functions.c` - utility functions (printing images, loading pixels)  
- `src/z2.c` - main program (`mnist_cli`) with multiple modes  

## Build

```bash
make
