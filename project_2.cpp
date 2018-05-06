//-------------------------------------------------------------
//Project 2
//
// Aaron Hill
// University Of Louisville
// CECS 564-01
// 2017/03/21
//--------------------------------------------------------------
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <bitset>
#include <fstream>
using namespace std;

unsigned long int c_1state = 0;
unsigned long int c_2state = 0;

//returns the next 8 bits from c1 shifting
unsigned short int c1(char x[]=NULL)
{
	string result;
	unsigned short int r[8];
	stringstream ss;
	stringstream sa;
	unsigned long int k;

	if(x != NULL){
		for( int i = 0; i < 4; i++){
			ss << x[i];
		}
		ss >> hex >> k;
		ss.clear();
	}
	else {
		ss << c_1state;
		ss >> k;
		ss.clear();
	}
	bitset<17> b(k);
	if(x != NULL){
		//initializes least sig bit to 1

		b <<=1;
		b.flip(0);
	}
	//	  cout << b.to_string() << endl;
	//C1(c) = x^17 + x^3 + 1
	for( int i=0; i < 8; i++){
		if(b[16]^b[2]){
			r[i] = 1;
		}
		else {r[i] = 0;}

	/*	  cout << "i: " << i << ":  ";
		cout << b[16] ;
			cout << " " ;
			cout << b[2];
			cout << " " ;
			cout << (b[16]^b[2]) << " " << r[i];
			cout << endl;
	*/
		b >>= 1;
		b.set(16,r[i]);
			//cout << b.to_string() <<endl;
	}


/*for (int i=0; i<18; i++){
	cout << i << ": " << b[i] <<endl;
}*/
	c_1state = b.to_ulong();
	//ss.clear();
	for (int i =0; i<8; i++){
	 	sa << r[i];
//	  	  cout << r[i];
	}
//	  cout << " ";
	//ss<< dec << r;
	result = sa.str();
//	  cout << result << " ";
	sa.clear();
	bitset<8> a (result);
//	  cout << "first" << result << "   " << a << "   " << (unsigned short int)a.to_ulong() <<endl;
	return (unsigned short int)a.to_ulong();


}
//returns the next 8 bits from c2 shifting
unsigned short int c2(char x[]=NULL)
{
	string result;
	unsigned short int r[8];
	stringstream ss;
	stringstream sa;
	unsigned long int k;

	if(x != NULL){
		for( int i = 4; i < 10; i++){
			ss << x[i];
		}
		ss >> hex >> k;
		ss.clear();
	}
	else {
		ss << c_2state;
		ss >> k;
		ss.clear();
	}
	bitset<25> b(k);
	if(x != NULL){
		//initializes least sig bit to 1

		b <<=1;
		b.flip(0);
	}
//	  	  cout << b.to_string() << endl;
	//C2(x) = x^25 + x^8 + x^6 + x^2 + 1
	for( int i=0; i < 8; i++){
		if((b[24] + b[7]+b[5]+b[1])%2 > 0){
			r[i] = 1;
		}
		else {r[i] = 0;}

/*	  	  cout << "i: " << i << ":  ";
		cout << b[24] ;
			cout << " " ;
			cout << b[7];
			cout << " " ;
			cout << b[5];
			cout << " " ;
			cout << b[1];
			cout << " " ;
			cout << ((b[24] + b[7]+b[5]+b[1])%2) << " " << (b[24]^b[7]^b[5]^b[1])<<" " << r[i];
			cout << endl;
*/
		b >>= 1;
		b.set(24,r[i]);
//	  	  	  cout << b.to_string() <<endl;
	}


/*for (int i=0; i<18; i++){
	cout << i << ": " << b[i] <<endl;
}*/
	c_2state = b.to_ulong();
	//ss.clear();
	for (int i =0; i<8; i++){
	 	sa << r[i];
//	  	  cout << r[i];
	}
//	  cout << " ";
	//ss<< dec << r;
	result = sa.str();
//	  cout << result << " ";
	sa.clear();
	bitset<8> a (result);

//	  cout << "second" << result << "   " << a << "   " << (unsigned short int)a.to_ulong() <<endl;

	return (unsigned short int)a.to_ulong();

}
//returns carry bit and c is edited
unsigned short int fullAdd(bitset<8> a, bitset<8> b, bitset<8> &c, unsigned short int carry){

	//key bytes
	for(int i=0; i<8; i++){
		c[i] = (a[i]+b[i]+carry)%2;

	//	  cout << a[i] << " + " << b[i] << " + " << carry << " = " << c[i] <<endl;
		if(a[i]+b[i]+carry>1){
			carry=1;
		}
		else{carry=0;}
	}

	return carry;
}
//encrypt file with name 'sf' given key 'x'
//
void crypt(char x[],string sf){
	bitset<8> a (c1(x));
	bitset<8> b (c2(x));
	bitset<8> c;
	unsigned short int carry = 0;

//	  cout << "\n c: " << c <<endl;
	ifstream input;
	ofstream output;
	stringstream bob;
	streampos size;
	char *  memblock;
	unsigned long int p;
	char q;
	bitset<8> * del;
	string of;
	input.open(sf.c_str(), ios::binary);
	if(input.is_open())
	{
		input.seekg(0, input.end);
		size = input.tellg();
		memblock = new char [size];
		cout << size;
		input.seekg (0, input.beg);
		input.read(memblock, size);
	//	  delete memblock;
	//	  cout << size << "   " << sizeof(memblock) <<"     " << sizeof(*memblock) << "          " << (int)size << endl;
		int s = (int)size;
		del = new bitset<8> [s];
		for(int i=0; i<size; i++){
			del[i] = (memblock[i]);
		}
		/*
		cout << numBitsets << "        " << finalBitset << endl;
		cout << "size of memblock: " << sizeof(*memblock) << endl << "input.tellg(): " << size <<endl;
		bitset<8> temp[9];
		for( int i=0; i < 9; i++){
		
			temp[i] = (memblock[i]);
			cout << "temp: " << temp[i] <<endl;
			cout << "mem[0]: " <<memblock[i] <<endl;
			//cout << memblock[i];
		}
		cout << endl;
		*/
		input.close();
		cout << "Output Filename" << endl;
		cin >> of;
		output.open(of.c_str(), ios::binary);
		//SPACES ARE BEING FILLED WITH REPEAT CHARACTERS; CREATE SECOND FILE TO COMPARE P,Q values
		if(output.is_open())
		{
			//output <<  "       c:" << c ;
			//output << "a: " <<a << "      b: " << b << "         del[1] " << (del[1]) << "        XOR: " << (c^=del[1]) << endl;
			
			for(int ii=0; ii<size; ii++){
			//	  cout << "a: " << a << "           b: " << b <<"    carry: " << carry;
				carry=fullAdd(a,b,c, carry);
			//	  cout << "    c: " <<c <<endl;
				p = ((c^=del[ii]).to_ulong());
			//	  cout << endl << p << "   " ;
				bob.put((char)p);
				bob.read((char*)(&q),1);		
				bob.clear();	
			//	  cout << q << " \n";
				output.put(q);
				a = c1();
				b = c2();	 	 	 
			}
			output.close();
		}
		else cout << "Unable to open output file\n";
	}
	else cout << "Unable to open input file\n";
}

//
//decrypt file with name 'sf' given key 'x'
//

//main driver
int main()
{
	char key[10];
	unsigned short int c_1;
	//c_2;
	//unsigned long int k;
	char cmd[7];
	bool cont = true;
	string sourceFile;
	do
	{
		cout << "Enter command"<<endl
			<<"Available commands are \n \"e[E]ncrypt\" \n \"d[D]ecrypt\" \n \"exit\" "<<endl;
		cin >> cmd;
		if( !strcmp(cmd,"encrypt") || !strcmp(cmd,"Encrypt") || !strcmp(cmd,"e") || !strcmp(cmd,"E"))
		{
			cout << "Enter 40 bit key (as string of 10 hex digits)" <<endl;
			cin >> key;
			cout << system("dir")<<endl;
			cout << "Input Filename" <<endl;
			cin >> sourceFile;
			//cout << sourceFile;
			crypt(key, sourceFile);
			memset(&key[0], 0, sizeof(key));
			cout << key[4];
			
		//	  c2(key, c_1);
		}
		else if( !strcmp(cmd,"decrypt") || !strcmp(cmd,"Decrypt") || !strcmp(cmd,"d") || !strcmp(cmd,"D"))
		{
		//	  cout << "decrypt" << endl << !strcmp(cmd,"decrypt");
			cout << "Enter 40 bit key (as string of 10 hex digits)" <<endl;
			cin >> key;
			cout << system("dir")<<endl;
			cout << "Input Filename" <<endl;
			cin >>sourceFile;
			crypt(key, sourceFile);
		//	  cont = false;
		}
		else if( !strcmp(cmd, "exit") || !strcmp(cmd, "Exit") || !strcmp(cmd,"x") || !strcmp(cmd,"X")){
			cont = false;
		}
		else
		{
			cout << "invalid command" << endl;
			cont = true;
		}

	}while(cont == true);
//	  cout <<cmd;
	return 0;
}

