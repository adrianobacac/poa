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


#include "PoMsa.h"
#include "HeaviestBundle.h"
#include "SequenceBundler.h"
#include "PercentageMatchSeqRule.h"
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
	SequenceBundler *bundler = new SequenceBundler();
	bundler->addInclusionRule(new PercentageMatchSeqRule(1.0, 1.0));
	
	HeaviestBundle *hb = new HeaviestBundle(poMsa, thread_cnt);

	unsigned long unbunbled_seq_cnt = poMsa->seqs.size();
	while (unbunbled_seq_cnt){
		// pronadi najbolji put
		std::vector<Node *> bestPath;
		bestPath = hb->findTopScoringPath();
		// gotovo nalazenje najboljeg puta

		// stvori novu sekvencu
		Seq *new_consensus = new Seq("name", "> title", bestPath.size(), 0);
		poMsa->cons.push_back(new_consensus);
		poMsa->createSeqOnPath(new_consensus, bestPath);
		poMsa->drawGraph("graph" + to_string(unbunbled_seq_cnt));

		for (Node *node : bestPath) {
			std::cout << node->nucl << " -> ";
		}
		std::cout << std::endl;

		// gotovo stvaranje nove sekvence

		// pronadi slicne sekvence
		std::vector<Seq *> *bundle = new std::vector < Seq * > ;
		int seqs_bundled = bundler->addSequencesToBundle(&poMsa->seqs, new_consensus, bundle);
		unbunbled_seq_cnt -= seqs_bundled;
		if (seqs_bundled > 0){
			std::cout << "pronasao slicne sekvence" << std::endl;

			for (Seq *seq : *bundle){
				seq->rescaleWeight(0);
				std::cout << seq->name << std::endl;
			}
			std::cout << "-----------------" << std::endl;
		}
		else{
			std::cout << "nisam pronasao slicne sekvence" << std::endl;

			break;
		}
		std::getchar();
	}

	return 0;
}
