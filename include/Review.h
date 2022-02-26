#ifndef REVIEW_H
#define REVIEW_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <sstream>

using namespace std;

class Review
{
public:
	Review(){};
	~Review(){};

	string id;
	string text;
	int upvotes;
	string app_version;
	string posted_date;

	static vector<Review> readCsv(string path);
	static void writeBinary(Review *data, int n);
	static Review *readBinaryN(int n);
	static void writeElementTxt(Review *data, int n);
	//static Review* accessBinaryI(int i);
	void printElement();

private:
	static int sizeArq(fstream &arq);
	static Review builder(string *object);
};

#endif // REVIEW_H
