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
#include <fstream>

#include "ThreadPool.h"

#include "Graph.h"
#include "HeaviestBundle.h"
#include "SequenceBundler.h"
#include "RuleFactory.h"
#include "OutputFormater.h"
#include "FastaOutputFormater.h"
#include "GraphFactory.h"
#include "Conpoa.h"

using namespace std;

int parse_input(int argc, char *const argv[], string *input, string *conf,
                int *thread_count, int *limit) {
  // default values
  *input = "in.po";
  *conf = "config.txt";
  *thread_count = 1;
  *limit = -1;
  int next_option;
  /* String of short options */
  const char *short_options = "t:i:c:l:";
  /* The array of long options */
  const struct option long_options[] = {
      {"input",   1, NULL, 'i'},
      {"config",  1, NULL, 'c'},
      {"threads", 1, NULL, 't'},
      {"limit",   1, NULL, 'l'}
  };
  do {
    next_option = getopt_long(argc, argv, short_options, long_options, NULL);
    switch (next_option) {
      case 'i':
        *input = optarg;
        break;
      case 'c':
        *conf = optarg;
        break;
      case 't':
        *thread_count = atoi(optarg);
        break;
      case 'l':
        *limit = atoi(optarg);
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
  } while (next_option != -1);

  return (EXIT_SUCCESS);
}


int main(int argc, char *const argv[]) {

  string input;
  string config;
  int thread_cnt;
  int limit;
  if (parse_input(argc, argv, &input, &config, &thread_cnt, &limit)) {
    cout << "Could not parse file" << endl;
    exit(EXIT_FAILURE);
  }
  fprintf(stdout, "INPUT: %s\n", input.c_str());
  fprintf(stdout, "CONFIG: %s\n", config.c_str());
  fprintf(stdout, "THREADS: %d\n", thread_cnt);
  fprintf(stdout, "LIMIT: %d\n", limit);

  GraphFactory graphFactory;
  Graph *poMsa;
  try {
    poMsa = graphFactory.Create(input);
  } catch (std::string message) {
    std::cerr << message << std::endl;
    exit(-1);
  }

  RuleFactory ruleFactory;
  std::list<InclusionRule *> rules;
  try {
    ruleFactory.CreateRules(config, &rules);
  } catch (std::string message) {
    std::cerr << message << std::endl;
    exit(-1);
  }

  ThreadPool pool((size_t) thread_cnt);
  SequenceBundler *bundler = new SequenceBundler(&pool);

  for (InclusionRule *rule : rules) {
    bundler->AddInclusionRule(rule);
  }

  OutputFormater *output = new FastaOutputFormater();

  Conpoa conpoa(poMsa, bundler);
  conpoa.GenerateConsesuses(limit, thread_cnt, output);

  delete bundler;
  delete poMsa;
  for (InclusionRule *rule : rules) {
    delete rule;
  }
  delete output;
  return 0;
}
