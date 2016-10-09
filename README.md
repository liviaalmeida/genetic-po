# Genetic Algorithm to solve simple Linear Programming Problem

How to use:

Parameters through command line

First argument are the parameters of Linear Programming Problem
- Vars = number of variables of the problem
- Objective = "max" or "min" and coefficients
- Rest = to identify any restriction. Instead of symbols to less than, equal, etc, use: eql (equal to), les (less than), leq (less than or equal to), gre (greater than), geq (greater than or equal to), dif (different of)

Second argument is the configuration of the Genetic Algorith
- Only parameter to be implemented is diversity

Run using: ./solver (arg1) (arg2)
