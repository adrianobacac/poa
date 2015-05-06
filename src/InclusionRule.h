#pragma once
#include "Node.h"

class InclusionRule{
public:
	InclusionRule();
	virtual ~InclusionRule()=0;
	virtual void process(Node *node)=0;
};

