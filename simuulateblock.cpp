#include <bits/stdc++.h>
#include "custom256sha.h"


using namespace std;
bool gencheck(int in)
{
	if(in == 0)
		return true;
	return false;
}
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return buf;
}
struct block
{
	int data;
	string timestamp;
	string prev_hash;
	string hash;
	int nonce;
};
void generatechain(block * chain)
{
	for(int i = 0;i<N;i++)
	{
		if(gencheck(i))
			cout<<"Genesis Block :"<<endl;
		else
			cout<<"Block Number : "<<i+1<<endl;
		cout<<"Data : "<<chain[i].data<<endl;
		cout<<"Previous Hash : "<<chain[i].prev_hash<<endl;
		cout<<"Timestamp : "<<chain[i].timestamp<<endl;
		cout<<"Hash : "<<chain[i].hash<<endl;
	}
}
int main(int argc, char* argv[])
{
	int N;
	cin>>N;
	cout<<"Blocks to be generated: "<<N<<endl;
	block * chain = new block [N];
	for(int i = 0;i<N;i++)
	{
		int data;
		cout<<"Enter data for block "<<i+1<<endl;	
		cin>>data;
		chain[i].data = data;
		chain[i].timestamp = currentDateTime();
		if(gencheck(i))
			chain[i].prev_hash = '0';
		else
			chain[i].prev_hash = chain[i-1].hash;
		string rawhash;
		rawhash.append(to_string(data)).append(chain[i].timestamp).append(chain[i].prev_hash);
		vector<unsigned char> hash(custom256sha::k_digest_size); 
		custom256sha::hash256(rawhash.begin(), rawhash.end(), hash.begin(), hash.end());
		string hashed = custom256sha::bytes_to_hex_string(hash.begin(), hash.end());
		chain[i].hash = hashed;
	}
	cout<<"Printing the generated chain:"<<endl;
	generatechain(chain);
   return 0;
}
