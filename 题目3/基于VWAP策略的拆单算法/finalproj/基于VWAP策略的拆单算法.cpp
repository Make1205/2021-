#include<bits/stdc++.h>
using namespace std;

// global file path 
// #define f1 "./data/csv/y1pv.csv"
// #define f2 "./data/csv/y2pv.csv"
// #define f3 "./data/csv/y3pv.csv"
// #define f4 "./data/csv/y4pv.csv"
// #define f5 "./data/csv/y5pv.csv"
// #define f6 "./data/csv/y6pv.csv"
// #define f7 "./data/csv/y7pv.csv"
// #define f8 "./data/csv/y8pv.csv"
// #define f9 "./data/csv/y9pv.csv"
// #define f10 "./data/csv/y10pv.csv"





// read the csv file to get market data
void rd(const string &filePath, vector<vector<string>> &mdt)
{
	ifstream inFile(filePath);
	string lineStr;
	// read csv line by line
	while (getline(inFile, lineStr))
	{
		stringstream ss(lineStr);
		string str;
		vector<string> lineArray;
		// read one line separated by comma
		while (getline(ss, str, ','))
			lineArray.push_back(str);
		mdt.push_back(lineArray);
	}
}

// calculate volume 
double cv(vector<vector<string>> &mdt,const string csv)
{
	int n = mdt.size() - 1; // skip the first title line
	ofstream oFile;
	double ts = 0.00;
	double tv=0.00, pri, provol,propri;
    oFile.open(csv, ios::out | ios::trunc);
	oFile<<"pred 40t vol"<<","<<"prop"<<","<<"act vol"<<","<<"av1"<<","<<"av2"<<","<<"av3"<<","<<"av4"<<","<<"av5"<<endl;
	// for (int i = 1; i <= 4000; i++)
	// {
	// 	double hp = atof(mdt[i][3].c_str());
	// 	ts += hp;
	// }
	ts=atof(mdt[3999][3].c_str());
	for (int i = 0; i <= 99;i++)
	{
		tv = 0.00;
		pri = 0.00;
		propri = 0.00;
		for (int j = 1; j <= 40;j++)
		{
			int cnt = j + i * 40;
			double v = atof(mdt[cnt][3].c_str());
			double p = atof(mdt[cnt][1].c_str());
			if(i*40+j>1)
			{
				double v0 = atof(mdt[cnt-1][3].c_str());
				pri += (v-v0) * p;
			}
			else{
				pri += (v) * p;
			}
			tv =atof(mdt[(i+1)*40][3].c_str());
		}
		if(i!=0)
		{
			tv -=atof(mdt[(i)*40][3].c_str());
		}
		propri = pri / tv;
		provol = tv / ts;
		double ans = provol * 4e4;
		oFile << tv << "," << provol << "," << ans << "," << ans * 0.4 << "," << ans * 0.2 << "," << ans * 0.2 << "," << ans * 0.1 << "," << ans * 0.1 << "," << propri << endl;
	}
	oFile.close();
	return propri;
}

// // calculate price
// double cp(vector<vector<string>> &mdt)
// {
// 	int n = mdt.size() - 1; // skip the first title line
// 	double price_sum = 0.0;
// 	for (int i = 1; i <= n; i++)
// 	{
// 		// get the price and volume according to table structure
// 		double hp = atof(mdt[i][9].c_str());
// 		double lp = atof(mdt[i][10].c_str());
// 		double price = (hp + lp) / 2;
// 		// compute price sum and time sum
// 		// here use the 1 min K-line data, so total time is n minutes
// 		price_sum += price;
// 	}

// 	return price_sum / n;
// }




int main()
{
	// const string kFilePath = "./data/csv/y5pv.csv";
	string ch;
	cin >> ch;
	string kfp="./data/csv/y"+ch+"pv.csv";
	string csv = "./res/"+ch + ".csv";
	vector<vector<string>> mdt;
	rd(kfp,mdt);
	cout << cv(mdt,csv) << endl;
	// cout << "TWAP: " << cv(mdt) << endl;
	return 0;
}