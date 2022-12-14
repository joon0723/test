#pragma once
#include "FPGrowth.h"
#include "BpTree.h"

class Manager
{
private:
	char* cmd;
	FPGrowth* fpgrowth;
	BpTree* bptree;
public:
	Manager(int threshold, int bpOrder)	//constructor
	{
		/* You must fill here */
		this->threshold = threshold;
		this->bpOrder = bpOrder;

		FPGrowth* newfpgrowth = new FPGrowth(fout, threshold);
		BpTree* newbptree = new BpTree(fout, bpOrder);
		fpgrowth = newfpgrowth;
		bptree = newbptree;
	}


	~Manager()//destructor
	{
		/* You must fill here */
	}

	ifstream fin;
	ofstream flog;
	

	void run(const char* command);
	bool LOAD();
	bool BTLOAD();
	
	bool PRINT_ITEMLIST();
	bool PRINT_FPTREE();

	bool PRINT_RANGE(char* item, int start, int end);
	bool PRINT_CONFIDENCE(char* item, double rate);
	bool PRINT_BPTREE(char* item, int min_frequency);


	void printErrorCode(int n);
	void printSuccessCode();

};

