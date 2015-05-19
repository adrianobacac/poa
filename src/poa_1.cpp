//============================================================================
// Name        : poa_1.cpp
// Author      : Adriano Bacac
// Version     :
// Copyright   : Your copyright notice
// Description : Consensus generator from partial order sequence alignment
//============================================================================

#include <iostream>
#include <getopt.h>
#include <string.h>


#include <vector>
#include <chrono>

#include "ThreadPool.h"

#include "PoMsa.h"
#include "HeaviestBundle.h"
#include "SequenceBundler.h"
#include "RuleFactory.h"
#include "OutputFormater.h"
#include "FastaOutputFormater.h"

using namespace std;

int parse_input(int argc, char * const argv[], string *input, string *conf, int *thread_count) {
	// default values
	*input = "in.po";
	*conf = "config.txt";
	*thread_count = 1;

	int next_option;
	/* String of short options */
	const char *short_options = "t:i:c:";
	/* The array of long options */
	const struct option long_options[] = {
			{ "input",  1, NULL, 'i' },
			{ "config", 1, NULL, 'c' },
			{ "threads", 1, NULL, 't'}
	};

	do {
		next_option = getopt_long(argc, argv, short_options, long_options, NULL);
		switch (next_option) {
			case 'i':
				/* User requested help */
				*input = optarg;
				break;
			case 'c':
				*conf = optarg;
				break;
			case 't':
				*thread_count =  atoi(optarg);
				break;
			case '?':
				/* The user specified an invalid option */
				fprintf(stdout, "Requested arg does not exist!\n");
				exit(EXIT_FAILURE);
			case -1:
				/* Done with options */
				break;

			default:
				/* Unexpected things */
				fprintf(stdout, "I can't handle this arg!\n");
				exit(EXIT_FAILURE);
		}
	} while(next_option != -1);

	return (EXIT_SUCCESS);
}

int parse_config(std::string filePath, std::list<InclusionRule *> *rules){
	std::ifstream fin;
	fin.open(filePath);

	if (!fin.good()) {
		throw "File " + std::string(filePath) + " can't be opened";
	}
	std::string line;
	while(std::getline(fin, line)){

		InclusionRule *rule = RuleFactory::createRule(line);
		if (rule){
			rules->push_back(rule);
		}
	}
	return EXIT_SUCCESS;
}
int main(int argc, char * const argv[]) {

	string input;
	string config;
	int thread_cnt;
	if(parse_input(argc, argv, &input, &config, &thread_cnt)){
		cout << "Could not parse file" << endl;
		exit(EXIT_FAILURE);
	}
	fprintf(stdout, "INPUT: %s\n", input.c_str());
	fprintf(stdout, "CONFIG: %s\n", config.c_str());
	fprintf(stdout, "THREADS: %d\n", thread_cnt);

	PoMsa *poMsa;
	try {
		poMsa = new PoMsa(input);
	}catch (std::string message){
		std::cerr << message << std::endl;
		exit(-1);
	}
	poMsa->drawGraph("graph_start");
	std::list<InclusionRule *> *rules = new std::list<InclusionRule *>;

	try {
		parse_config(config, rules);
	}catch (std::string message){
		std::cerr << message << std::endl;
		exit(-1);
	}

	ThreadPool pool((size_t)thread_cnt);
	SequenceBundler *bundler = new SequenceBundler(&pool);

	for(InclusionRule *rule : *rules){
		bundler->addInclusionRule(rule);
	}

	HeaviestBundle *hb = new HeaviestBundle(poMsa, thread_cnt);

	unsigned long unbunbled_seq_cnt = poMsa->seqs.size();
	while (unbunbled_seq_cnt){
		// pronadi najbolji put
		std::vector<Node *> bestPath;
		bestPath = hb->findTopScoringPath();
		// gotovo nalazenje najboljeg puta

		// stvori novu sekvencu
		Seq *new_consensus = new Seq("consensus", "", bestPath.size(), 0);
		poMsa->cons.push_back(new_consensus);
		poMsa->createSeqOnPath(new_consensus, bestPath);
		new_consensus->setStartNode(bestPath[0]);
		poMsa->drawGraph("graph" + to_string(unbunbled_seq_cnt));

		for (Node *node : bestPath) {
			std::cout << node->nucl;
		}
		std::cout << std::endl;

		// gotovo stvaranje nove sekvence

		// pronadi slicne sekvence


		std::vector<Seq *> *bundle = new std::vector < Seq * > ;
		int seqs_bundled = bundler->addSequencesToBundle(&poMsa->seqs, new_consensus, bundle);
		unbunbled_seq_cnt -= seqs_bundled;
		new_consensus->title = to_string(seqs_bundled);
		if (seqs_bundled > 0){
			std::cout << "pronasao slicnih sekvenci: " << seqs_bundled << std::endl;

			for (Seq *seq : *bundle){
				seq->rescaleWeight(0);
				// std::cout << seq->name << std::endl;
			}
			// std::cout << "-----------------" << std::endl;
		}
		else{
			std::cout << "nisam pronasao slicne sekvence" << std::endl;

			break;
		}
		//std::getchar();
	}
	OutputFormater *output = new FastaOutputFormater();
	output->format("out.fa", poMsa);
	return 0;
}
