# Algorithms
- Simulated Annealing
- GA

# Simulated Annealing
## Hyperparameters
- n -> random n-th bit neighbours for each step (should be small)
- T0 -> initial temperature
- cs -> cooling schedule (maybe a function pointer)
- me -> max_evals

## TODO
- evaluate()
    - update temperature (if not first iteration / separate first from others
    with different function calls) (based on cooling schedule)
    - check if it should terminate (too many evaluations)
- getNeighbors()
    - get the first (and only) node
    - generate a random n-bit distant neighbor from that node
- chooseNodes()
    - randomly (according to formula) dictate if node is chosen or not, if not 
    the last one is chosen again. If fitness is bigger, then choose new node

# Genetic Algorithm
## Hyperparameters
