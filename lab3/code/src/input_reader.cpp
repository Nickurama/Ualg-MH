#include "input_reader.hpp"
#include "algorithms/simulated_annealing.hpp"
#include "algorithms/tournament_ga.hpp"
#include <algorithm>

std::unique_ptr<Algorithm<BitArray>> getAlgorithm(int argc, char *argv[])
{
	if (argc - 1 < 2)
	{
		std::cerr << "Usage: maxsat <input_file> <algorithm> <algorithm_args>\n";
		std::cerr << "Missing algorithm!\n";
		std::exit(1);
	}
	std::string algorithm_str = argv[2];

	if (algorithm_str == "naive")
	{
		return std::make_unique<NaiveAlgorithm<BitArray>>();
	}
	else if (algorithm_str == "nahillclimb")
	{
		uint32_t hamming_distance = 1;
		uint64_t multistart = 0;
		uint64_t max_evals = 0;

		if (argc - 1 < 5)
		{
			std::cout << "Usage: nahillclimb <hamming_distance> <multistart> <max_evals>\n";
			std::cout << "Missing arguments!\n";
			std::exit(1);
		}

		try
		{
			hamming_distance = std::stoi(argv[3]);
			multistart = std::stol(argv[4]);
			max_evals = std::stol(argv[5]);
		}
		catch (std::exception&)
		{
			std::cout << "Usage: nahillclimb <hamming_distance> <multistart> <max_evals>\n";
			std::cout << "Of types: <int> <long> <long>\n";
			std::exit(1);
		}

		return std::make_unique<NAHillclimb<BitArray>>(hamming_distance, multistart, max_evals);
	}
	else if (algorithm_str == "vnahillclimb")
	{
		uint32_t hamming_distance = 1;
		uint64_t multistart = 0;
		uint64_t max_evals = 0;

		if (argc - 1 < 5)
		{
			std::cout << "Usage: vnahillclimb <max_hamming_distance> <multistart> <max_evals>\n";
			std::cout << "Missing arguments!\n";
			std::exit(1);
		}

		try
		{
			hamming_distance = std::stoi(argv[3]);
			multistart = std::stol(argv[4]);
			max_evals = std::stol(argv[5]);
		}
		catch (std::exception&)
		{
			std::cout << "Usage: vnahillclimb <hamming_distance> <multistart> <max_evals>\n";
			std::cout << "Of types: <int> <long> <long>\n";
			std::exit(1);
		}

		return std::make_unique<VNAHillclimb<BitArray>>(hamming_distance, multistart, max_evals);
	}
	else if (algorithm_str == "simannealing")
	{
		uint32_t hamming_distance = 1;
		double init_temp = 0.0;
		uint64_t max_evals = 0;

		if (argc - 1 < 5)
		{
			std::cout << "Usage: simannealing <hamming_distance> <init_temp> <max_evals>\n";
			std::cout << "Missing arguments!\n";
			std::exit(1);
		}

		try
		{
			hamming_distance = std::stoi(argv[3]);
			init_temp = std::stod(argv[4]);
			max_evals = std::stol(argv[5]);
		}
		catch (std::exception&)
		{
			std::cout << "Usage: simannealing <hamming_distance> <init_temp> <max_evals>\n";
			std::cout << "Of types: <int> <double> <long>\n";
			std::exit(1);
		}

		std::function<double(double)> cooling_schedule = [](double t) {
			// return std::max(t - 0.001, 0.0); // linear
			return t * 0.999;
		};

		return std::make_unique<SimulatedAnnealing<BitArray>>(hamming_distance, init_temp, cooling_schedule, max_evals);
	}
	else if (algorithm_str == "tournamentga")
	{
		uint64_t pop_size = 10;
		uint64_t num_crossover_points = 1;
		double mutation_chance = 0.0001;
		uint64_t match_individual_number = 2;
		uint64_t max_evals = 0;

		if (argc - 1 < 7)
		{
			std::cout << "Usage: tournamentga <pop_size> <num_crossover_points> <mutation_chance> <match_individual_number> <max_evals>\n";
			std::cout << "Missing arguments!\n";
			std::exit(1);
		}

		try
		{
			pop_size = std::stoul(argv[3]);
			num_crossover_points = std::stoul(argv[4]);
			mutation_chance = std::stod(argv[5]);
			match_individual_number = std::stoul(argv[6]);
			max_evals = std::stoul(argv[7]);
		}
		catch (std::exception&)
		{
			std::cout << "Usage: tournamentga <pop_size> <num_crossover_points> <mutation_chance> <match_individual_number> <max_evals>\n";
			std::cout << "Of types: <ulong> <ulong> <double> <ulong> <ulong>\n";
			std::exit(1);
		}

		return std::make_unique<TournamentGA<BitArray>>(pop_size, num_crossover_points, mutation_chance, match_individual_number, max_evals);
	}
	else
	{
		std::cerr << "Usage: maxsat <input_file> <algorithm> <algorithm_args>\n";
		std::cerr << "Unknown algorithm \"" << argv[2] << "\".\n";
		std::cerr << "Possible options: naive, nahillclimb, vnahillclimb, simannealing, tournamentga\n";
		std::exit(1);
	}
}

std::string getInputFilename(int argc, char *argv[])
{
	if (argc - 1 < 1)
	{
		std::cerr << "Usage: maxsat <input_file> <algorithm> <algorithm_args>\n";
		std::cerr << "Missing input file!\n";
		std::exit(1);
	}
	return argv[1];
}
