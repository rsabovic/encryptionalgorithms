//Rejhan Sabovic Simplified DES Encryption and Decryption
#include<iostream>
#include <bitset>

using namespace std;

bitset<12> decrypt(string, string, int);
bitset<12> simplifiedDES(string, string, int, int);
string setKey(string, int);
bitset<12> merge(bitset<6>, bitset<6>);
string sBoxes(bitset<8>);
bitset<8> expansion(bitset<8>);

// S-Boxes declared globally 
string sBoxTable1[2][8] = { {"101", "010", "001", "110", "011", "100", "111", "000" }, { "001","100", "110", "010", "000", "111", "101", "011"} };
string sBoxTable2[2][8] = { {"100", "000", "110", "101", "111", "001", "011", "010" }, { "101","011", "000", "111", "110", "010", "001", "100" } };

// expansion function
// Accepts an 8 bit variable and performs the basic expansion function
// Returns the expanded variables
bitset<8> expansion(bitset<8> expanded)
{
	expanded[7] = expanded[5];
	expanded[6] = expanded[4];
	expanded[5] = expanded[2];
	expanded[4] = expanded[3];
	expanded[3] = expanded[5];
	expanded[2] = expanded[4];
	return expanded;
}

// sBoxes function
// Accepts an 8 bit variable and performs S-Box calculations using the globally declared S-Box tables
// Returns a string of the bits that the calculations compute
string sBoxes(bitset<8> hold)
{
	// Creates s1 and s2 variables
	bitset<4> s1{};			
	bitset<4> s2{};

	// Loop to split the original 8 bit variable into two 4 bit variables
	for (int i = 7; i >= 4; i--)			
	{
		s1[i - 4] = hold[i];
		s2[i - 4] = hold[i - 4];
	}
	string R1String = "";
	int row;
	row = s1[3];
	s1[3] = 0;
	cout << "S1: " << sBoxTable1[row][s1.to_ullong()] << endl;
	R1String.append(sBoxTable1[row][s1.to_ullong()]);
	row = s2[3];
	s2[3] = 0;
	cout << "S2: " << sBoxTable2[row][s2.to_ullong()] << endl;
	R1String.append(sBoxTable2[row][s2.to_ullong()]);
	return R1String;
}

// merge function
// Accepts two 6 bit variables and combines them into one 12 bit variable
// Returns a 12 bit variable
bitset<12> merge(bitset<6> left, bitset<6> right)
{
	bitset<12> cipher;
	cipher[0] = left[0];
	cipher[1] = left[1];
	cipher[2] = left[2];
	cipher[3] = left[3];
	cipher[4] = left[4];
	cipher[5] = left[5];
	cipher[6] = right[0];
	cipher[7] = right[1];
	cipher[8] = right[2];
	cipher[9] = right[3];
	cipher[10] = right[4];
	cipher[11] = right[5];
	return cipher;
}

// setKey function
// Accepts a key string and a round number and calculates the appropriate key for the current round
// Returns a valid key string for the current round
string setKey(string key, int round)
{
	round--;
	if (round == 0)
		key = key.substr(round, (key.length() - 1));
	else
	{
		string temp = key.substr(0, round);
		key = key.substr(round, (key.length() - 1));
		key = key.append(temp);
	}
	return key;
}

// simplifiedDES function
// Accepts a plain text string, a key string, the number of rounds to calculate, and a 0 to keep track of the current round
// This is the main driver, it calls all the other functions in the proper order and handles in between maintenance to complete the calculations
// Returns the final cipher after all the rounds
bitset<12> simplifiedDES(string pText, string strKey, int rounds, int roundNumber)
{
	//SET KEY
	bitset<8> key{ setKey(strKey, roundNumber) };
	cout << "Round " << roundNumber << " key: " << key << endl;

	//DIVISION
	string left, right;
	left = pText.substr(0, ((pText.length() / 2)));
	right = pText.substr(((pText.length() / 2)), pText.length());
	bitset<8> lPlain{ left }, rPlain{ right };
	bitset<6> L0{ left }, R0{ right };

	//EXPANSION
	rPlain = expansion(rPlain);
	cout << "Expansion: " << rPlain << endl;

	//XOR
	rPlain ^= key;
	cout << "Expansion XOR key: " << rPlain << endl;

	//S-BOXES
	bitset<6> postBox{ sBoxes(rPlain) };
	
	//XOR
	postBox ^= L0;
	bitset<12> cipher = merge(postBox, R0);
	cout << cipher << endl << endl;
	if (rounds > 1)
		return simplifiedDES(cipher.to_string(), strKey, --rounds, ++roundNumber);
	else
		return cipher;
}

// decrypt function
// Accepts a cipher text string, a key string, the number of rounds to calculate
// Essentially a reverse of the SDES function
// Returns the plain text after all the rounds
bitset<12> decrypt(string cText, string strKey, int rounds) //110101001010
{
	bitset<8> key{ setKey(strKey, rounds) };
	cout << "Round " << rounds << " key: " << key << endl;
	string left, right;
	right = cText.substr(0, ((cText.length() / 2)));
	left = cText.substr(((cText.length() / 2)), cText.length());
	bitset<8> lPlain{ left }, rPlain{ right };
	bitset<6> L0{ left }, R0{ right };
	rPlain = expansion(rPlain);
	cout << "Expansion: " << rPlain << endl;
	rPlain ^= key;
	cout << "Expansion XOR key: " << rPlain << endl;
	bitset<6> postBox{ sBoxes(rPlain) };
	postBox ^= L0;
	bitset<12> plain = merge(R0, postBox);
	cout << plain << endl << endl;
	if (rounds > 1)
		return decrypt(plain.to_string(), strKey, --rounds);
	else
		return plain;
	return 0;
}

int main()
{
	string ptextString = "100010110101";
	string keyString = "111000111";
	cout << "-----------------------------------------------" << endl << "SDES Encryption" << endl << "-----------------------------------------------" << endl;
	bitset<12> ctext = simplifiedDES(ptextString, keyString, 4, 1);
	cout << "-----------------------------------------------" << endl << "SDES Decryption" << endl << "-----------------------------------------------" << endl;
	bitset<12> ptext = decrypt(ctext.to_string(), keyString, 4);
	return 0;
}
