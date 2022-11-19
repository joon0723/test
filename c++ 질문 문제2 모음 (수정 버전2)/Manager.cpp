#include "Manager.h"
#include <string>

void Manager::run(const char* command)
{
	fin.open(command);
	flog.open("log.txt", ios::app); //log.txt open
	if(!fin)
	{
		flog << "File Open Error" << endl;
		return;
	}
	while (!fin.eof())
	{
		/* You must fill here */
		fin.getline(cmd, 64);
		char* tmp;
		tmp = strtok(cmd, " "); //string truncation

		///////////////////LOAD/////////////////////
		if (strcmp(tmp, "LOAD") == 0)
		{
			flog << "========" << cmd << "========" << endl;
			cout << "========" << cmd << "========" << endl;
			if (LOAD()) {
				printSuccessCode();
			}
			else {
				printErrorCode(100);
			}
		}

		///////////////////BTLOAD/////////////////////
		else if (strcmp(tmp, "BTLOAD") == 0)
		{
			flog << "========" << cmd << "========" << endl;
			cout << "========" << cmd << "========" << endl;
			if (BTLOAD()) {
				printSuccessCode();
			}
			else {
				printErrorCode(200);
			}
		}

		///////////////////PRINT_ITEMLIST/////////////////////
		else if (strcmp(tmp, "PRINT_ITEMLIST") == 0)
		{
			flog << "========" << cmd << "========" << endl;
			cout << "========" << cmd << "========" << endl;
			int start = 0, end = 0;
			if (PRINT_ITEMLIST(fpgrowth)) {
				printSuccessCode();
			}
			else {
				printErrorCode(300);
			}
		}

		///////////////////PRINT_FPTREE/////////////////////
		else if (strcmp(tmp, "PRINT_FPTREE") == 0)
		{
			flog << "========" << cmd << "========" << endl;
			cout << "========" << cmd << "========" << endl;
			if (PRINT_FPTREE()) {
				printSuccessCode();
			}
			else {
				printErrorCode(400);
			}
		}

		///////////////////PRINT_BPTREE/////////////////////
		else if (strcmp(tmp, "") == 0)
		{

		}

		///////////////////PRINT_CONFIDENCE/////////////////////
		else if (strcmp(tmp, "PRINT_CONFIDENCE") == 0)
		{
			flog << "========" << cmd << "========" << endl;
			cout << "========" << cmd << "========" << endl;
			if (LOAD()) {
				printSuccessCode();
			}
			else {
				printErrorCode(600);
			}
		}

		///////////////////PRINT_RANGE/////////////////////
		else if (strcmp(tmp, "PRINT_RANGE") == 0)
		{
			flog << "========" << cmd << "========" << endl;
			cout << "========" << cmd << "========" << endl;
			if (LOAD()) {
				printSuccessCode();
			}
			else {
				printErrorCode(700);
			}
		}

		///////////////////SAVE/////////////////////
		else if (strcmp(tmp, "SAVE") == 0)
		{
			flog << "========" << cmd << "========" << endl;
			if (SAVE()) {
				printSuccessCode();
			}
			else {
				printErrorCode(800);
			}
		}

		///////////////////EXIT/////////////////////
		else if (strcmp(tmp, "EXIT") == 0)
		{
			flog << "========" << cmd << "========" << endl;
			cout << "========" << cmd << "========" << endl;
			if (LOAD()) {
				printSuccessCode();
			}
			else {
				printErrorCode(900);
			}
		}
		else {
			cout << "error command" << endl; //command error
		}
	}
	fin.close();
	return;
}

bool Manager::LOAD()
{
	ifstream fmarket;
	fmarket.open("market.txt");
	//ifstream fmarket("market.txt"); //market.txt open
	if (!fmarket)
	{
		flog << "File Open Error" << endl;
		return false;
	}//file open error

	if (fpgrowth->getHeaderTable()->getindexTable().size()) {
		return false;
	} //already exist

	while (!fmarket.eof()) {
		char items[256]; //on line read
		fmarket.getline(items, 256); //on line read
		char* item;
		item = strtok(items, "\t");
		while (item != NULL) {
			fpgrowth->createTable(item, 1);
			item = strtok(NULL, "\t"); //string truncation
		}
	}
	fmarket.close();

	fmarket.open("market.txt"); //market.txt open

	fpgrowth->getHeaderTable()->descendingIndexTable(); //Sort Descending

	fpgrowth->getHeaderTable()->insertTable_map(threshold); //create data table

	while (!fmarket.eof()) {
		char items[256];
		fmarket.getline(items, 256);
		char* item;
		list<string>* item_array = new list<string>;
		item = strtok(items, "\t");

		while (item != NULL) {
			int n = 0;
			n = fpgrowth->getHeaderTable()->find_frequency(item);
			if (n >= threshold) {
				int check = 0;
				list<string>::iterator iter = item_array->begin(); //iterator
				for (iter = (*item_array).begin(); iter != (*item_array).end(); iter++) {
					if (n > fpgrowth->getHeaderTable()->find_frequency(*iter)) {
						item_array->insert(iter, item); //insert, sort descending
						check = 1;
						break;
					}
				}
				if (check == 0) //final
					item_array->push_back(item);
			}
			//cout << item <<"\t" << n << endl; //check
			item = strtok(NULL, "\t"); //tok
		}

		fpgrowth->createFPtree(fpgrowth->getTree(), fpgrowth->getHeaderTable(), *item_array, 1);
		//create FPtree
	}
	return true;
}




bool Manager::BTLOAD()
{
	ifstream fresult;
	fresult.open("result.txt"); //result1.txt open
	if (!fresult)
	{
		flog << "File Open Error" << endl;
		return false;
	}//file open error

	//already exist

	while (!fresult.eof()) {
		char items[256]; //one line read
		fresult.getline(items, 256);
		char* fre;
		int fre_i;
		char* item;
		fre = strtok(items, "\t");
		fre_i = atoi(fre);
		set<string> s;
		while (1) {
			item = strtok(NULL, "\t");
			if (item == NULL)
				break;
			s.insert(item);
		}
		bptree->Insert(fre_i, s);
	}
	return true;
}

bool Manager::PRINT_ITEMLIST() {
	if (fp_growth->getHeaderTable() == NULL)
		return false;

	cout << "Item\tFrequency" << endl;

	list<pair<int, string>> li = fp_growth->getHeaderTable()->getindexTable(); //list
	for (auto it = li.begin(); it != li.end(); it++) {
		cout << (*it).second << " " << (*it).first << endl; // print item
		flog << (*it).second << " " << (*it).first << endl; // print item
	}

	return true;
}

bool Manager::PRINT_FPTREE() {
	if (fpgrowth->getHeaderTable() == NULL)
		return false;

	cout << "{StandardItem,Frequency} {Path_Item,Frequency}\n";

	fpgrowth->getHeaderTable()->ascendingIndexTable(); //Sort ascending

	list<pair<int, string>> li = fpgrowth->getHeaderTable()->getindexTable(); //list
	for (auto it = li.begin(); it != li.end(); it++) {
		if ((*it).first >= threshold) {
			//	fpgrowth.find((*it).second)
			map<string, FPNode*> iter = fpgrowth->getHeaderTable()->getdataTable();
			auto it_print = iter.find((*it).second); //find item
			FPNode* temp_list = new FPNode;
			FPNode* temp_parent = new FPNode; //alloc
			temp_list = (*it_print).second;
			cout << "{" << (*it_print).first << "," << fpgrowth->getHeaderTable()->find_frequency((*it_print).first) << "}" << endl;
			flog << "{" << (*it_print).first << "," << fpgrowth->getHeaderTable()->find_frequency((*it_print).first) << "}" << endl;

			while (temp_list != NULL) { //print linked item
				temp_parent = temp_list;
				while (temp_parent->getParent() != NULL) { //print linked parent
					cout << "(" << temp_parent->getItem() << "," << temp_parent->getFrequency() << ") ";
					flog << "(" << temp_parent->getItem() << "," << temp_parent->getFrequency() << ") ";
					temp_parent = temp_parent->getParent();
				}
				temp_list = temp_list->getNext();
				cout << endl;
				flog << endl;
			}
			cout << endl;
		}
	}
	return true;
}

bool Manager::PRINT_BPTREE(char* item, int min_frequency) {
	
}

bool Manager::PRINT_CONFIDENCE(char* item, double rate) {
	return false;
}

bool Manager::PRINT_RANGE(char* item, int start, int end) {
	return false;
}

void Manager::printErrorCode(int n) {				//ERROR CODE PRINT
	flog << ERROR " << n << " << endl;
	flog << "=======================" << endl << endl;
}

void Manager::printSuccessCode() {//SUCCESS CODE PRINT 
	flog << "Success" << endl;
	flog << "=======================" << endl << endl;
}

