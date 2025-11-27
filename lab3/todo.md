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
- initialization (random)
- selection (tournament, roulette, ...)
- variation (crossover, mutation)
- replacement

## Initialization
randomly generate

## Selection (tournament, roulette, ...)
tournament selection, without replacement

## Recombination (k-point crossover, uniform crossover)
k-point crossover

## Mutation (percent per bit)
percent of mutation per bit

## Replacement
x% comes from the selection
(1-x)% is recombined
(steady-state replacement - some of the old become some of the new)

## Hyperparameters
- size of population
- k of k-point crossover
- chance of mutation per bit
- percentage of replaced individuals
- number of people in one tournament match
- ratio of population that comes from selection to recombination
