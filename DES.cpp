// Rejhan Sabovic DES Encryption

#include <iostream>
#include <bitset>
#include <string>

using namespace std;

string expansion(string);
string hexToBinary(string);

int keyShift[2][16] = { { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 }, { 1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1 } };
string subKeys[16];

//I copied this online, I couldn't manually input all these numbers
int s[8][4][16] = {
		{ 14, 4,  13, 1, 2,  15, 11, 8,  3,  10, 6,  12, 5, 9,  0,  7, 
		  0, 15, 7,  4,  14, 2,  13, 1,  10, 6, 12, 11, 9,  5, 3,  8,
		  4,  1,  14, 8,  13, 6,  2, 11, 15, 12, 9, 7,  3,  10, 5,  0,
		  15, 12, 8,  2, 4,  9,  1,  7, 5,  11, 3,  14, 10, 0,  6,  13 },

		{ 15, 1,  8,  14, 6,  11, 3, 4,  9,  7,  2,  13, 12, 0,  5,  10,
		  3,  13, 4,  7, 15, 2,  8,  14, 12, 0, 1,  10, 6,  9,  11, 5,
		  0, 14, 7,  11, 10, 4,  13, 1,  5,  8,  12, 6,  9,  3, 2,  15,
		  13, 8,  10, 1, 3,  15, 4,  2,  11, 6,  7, 12, 0,  5,  14, 9 },

		{ 10, 0,  9,  14, 6,  3,  15, 5,  1,  13, 12, 7,  11, 4,  2,  8,
		  13, 7,  0,  9,  3,  4, 6,  10, 2,  8,  5,  14, 12, 11, 15, 1,  
		  13, 6,  4,  9,  8,  15, 3,  0,  11, 1,  2,  12, 5,  10, 14, 7,
		  1,  10, 13, 0,  6,  9,  8, 7,  4,  15, 14, 3,  11, 5,  2,  12 },

		{ 7,  13, 14, 3,  0,  6,  9,  10, 1,  2, 8,  5,  11, 12, 4,  15,
		  13, 8,  11, 5,  6,  15, 0, 3,  4,  7, 2,  12, 1,  10, 14, 9, 
		  10, 6,  9,  0, 12, 11, 7, 13, 15, 1,  3,  14, 5,  2,  8,  4,
		  3, 15, 0,  6, 10, 1,  13, 8,  9,  4,  5,  11, 12, 7, 2,  14 },

		{ 2,  12, 4, 1,  7,  10, 11, 6, 8,  5,  3,  15, 13, 0,  14, 9,
		  14, 11, 2,  12, 4, 7,  13, 1,  5,  0, 15, 10, 3, 9,  8,  6,
		  4,  2, 1,  11, 10, 13, 7, 8,  15, 9, 12, 5,  6,  3,  0, 14,
		  11, 8,  12, 7, 1,  14, 2, 13, 6,  15, 0,  9, 10, 4,  5,  3 },

		{ 12, 1,  10, 15, 9,  2,  6,  8,  0,  13, 3, 4, 14, 7, 5, 11,
		  10, 15, 4,  2,  7,  12, 9,  5, 6, 1, 13, 14, 0,  11, 3,  8,
		  9,  14, 15, 5,  2, 8, 12, 3,  7,  0,  4,  10, 1,  13, 11, 6,
		  4,  3, 2, 12, 9,  5,  15, 10, 11, 14, 1,  7,  6,  0,  8, 13 },

		{ 4,  11, 2,  14, 15, 0,  8, 13, 3,  12, 9,  7,  5, 10, 6, 1,
		  13, 0,  11, 7, 4,  9,  1,  10, 14, 3, 5,  12, 2,  15, 8, 6,
		  1, 4,  11, 13, 12, 3,  7, 14, 10, 15, 6,  8,  0,  5, 9,  2,
		  6,  11, 13, 8, 1,  4,  10, 7,  9,  5,  0, 15, 14, 2, 3, 12 },

		{ 13, 2,  8, 4,  6,  15, 11, 1,  10, 9, 3, 14, 5, 0,  12, 7,
		  1,  15, 13, 8,  10, 3,  7, 4, 12, 5, 6,  11, 0, 14, 9,  2,
		  7,  11, 4,  1, 9, 12, 14, 2,  0,  6, 10, 13, 15, 3, 5, 8,
		  2, 1, 14, 7, 4,  10, 8, 13, 15, 12, 9,  0,  3,  5, 6, 11 }
};

// Key is shifted
// Key is using an 8x8 table but we need to use an 8x7 table since we're removing the last column
void keyGeneration(string key, int round)
{
	string derived = "";
	int indexx = 56;
	int indexy = 56;
	for (int x = 0; x <= 2; x++)
	{
		for (int y = 0; y < 7; y++)
		{
			derived += key.at(indexx);
			indexx -= 8;
			if (indexx < 0)
			{
				indexx = indexy + 1;
				indexy = indexx;
			}
		}
	}
	derived += key.at(18);
	derived += key.at(10);
	derived += key.at(2);
	derived += key.at(59);
	derived += key.at(51);
	derived += key.at(43);
	derived += key.at(35);
	indexx = 62;
	indexy = 62;
	for (int x = 4; x <= 6; x++)
	{
		for (int y = 0; y < 7; y++)
		{
			derived += key.at(indexx);
			indexx -= 8;
			if (indexx < 0)
			{
				indexx = indexy - 1;
				indexy = indexx;
			}
		}
	}
	derived += key.at(20);
	derived += key.at(12);
	derived += key.at(4);
	derived += key.at(27);
	derived += key.at(19);
	derived += key.at(11);
	derived += key.at(3);

	string cKey = derived.substr(0, 28);
	string dKey = derived.substr(28, 28);
	string shiftedC = "";
	string shiftedD = "";
	char holdC[2] = { cKey[0], cKey[1] };
	char holdD[2] = { dKey[0], dKey[1] };
	int idx = 0;
	string merged;
	for (int counter = 0; counter < 16; counter++)
	{
		for (int i = 0; i < 28; i++)
		{
			if (i + keyShift[1][counter] > 27)
			{
				shiftedC += holdC[idx];
				shiftedD += holdD[idx];
				idx++;
			}
			else
			{
				shiftedC += cKey[i + keyShift[1][counter]];
				shiftedD += dKey[i + keyShift[1][counter]];
			}
		}
		merged = shiftedC + shiftedD;
		subKeys[counter] = merged;
		shiftedC = "";
		shiftedD = "";
		cKey = merged.substr(0, 28);
		dKey = merged.substr(28, 28);
		holdC[0] = cKey[0];
		holdC[1] = cKey[1];
		holdD[0] = dKey[0];
		holdD[1] = dKey[1];
		idx = 0;
	}
}



string keyCompression(int round)
{
	string merged = subKeys[round - 1];
	char pc2[6][8] = {  
						{merged[13],merged[16],merged[10],merged[23],merged[0],merged[4], merged[2], merged[27]},
						{merged[14],merged[5],merged[20], merged[9],merged[22],merged[18],merged[11],merged[3]}, 
						{merged[25],merged[7],merged[15], merged[6],merged[26],merged[19],merged[12],merged[1]}, 
						{merged[40],merged[51],merged[30],merged[36],merged[46],merged[54],merged[29],merged[39]},
						{merged[50],merged[44],merged[32],merged[47],merged[43],merged[48],merged[38],merged[55]}, 
						{merged[33],merged[52],merged[45],merged[41],merged[49],merged[35],merged[28],merged[31]} 
					 };
	string finalKey = "";
	for (int x = 0; x < 6; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			finalKey += pc2[x][y];
		}
	}
	return finalKey;
}

string hexToBinary(string hex)
{
	unsigned long long temp = stoull(hex, nullptr, 16);
	string binary = bitset<64>(temp).to_string();
	return binary;
}

string derive(string ptext)
{
	cout << "IP" << "\t\t\t";
	string derived = "";
	int indexx = 57;
	int indexy = 57;
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			derived += ptext.at(indexx);
			indexx -= 8;
		}
		if (indexy == 63)
		{
			indexx = 56;
			indexy = 56;
		}
		else
		{
			indexx = indexy + 2;
			indexy = indexx;
		}
	}

	bitset<32> lbits{ derived.substr(0, 32) };
	bitset<32> rbits{ derived.substr(32, 32) };
	cout << hex << lbits.to_ullong() << "\t" << hex << rbits.to_ullong() << endl;;

	return derived;
}

string expansion(string rPlain)
{
	char table[8][6];
	int counter = 0;;
	for (int x = 0; x < 8; x++)
	{
		for (int y = 1; y < 5; y++)
		{
			table[x][y] = rPlain.at(counter);
			counter++;
		}
	}

	table[0][0] = rPlain.at(31);
	table[1][0] = rPlain.at(3);
	table[2][0] = rPlain.at(7);
	table[3][0] = rPlain.at(11);
	table[4][0] = rPlain.at(15);
	table[5][0] = rPlain.at(19);
	table[6][0] = rPlain.at(23);
	table[7][0] = rPlain.at(27);
	table[0][5] = rPlain.at(4);
	table[1][5] = rPlain.at(8);
	table[2][5] = rPlain.at(12);
	table[3][5] = rPlain.at(16);
	table[4][5] = rPlain.at(20);
	table[5][5] = rPlain.at(24);
	table[6][5] = rPlain.at(28);
	table[7][5] = rPlain.at(0);

	string expando = "";
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 6; y++)
		{
			expando += table[x][y];
		}
	}
	return expando;
}

int binaryToInt(string binary)
{
	int result = 0;
	char c;
	for (int i = 0; i < binary.length(); i++)
	{
		if((binary.substr(i,1)) == "1")
			result += pow(2, binary.length() - 1 -i);
	}
	return result;
}

string sboxes(string breakDown)
{
	string combined = "";
	string xCo = "";
	string yCo = "";
	string chunk = "";
	int x;
	int y;
	int sVal;
	string binary = "0000";
	for (int i = 0; i < 8; i++)
	{
		chunk = "";
		chunk = breakDown.substr((i * 6), 6);
		xCo = chunk.substr(0,1) + chunk.substr(5, 1);
		yCo = chunk.substr(1, 1) + chunk.substr(2, 1) + chunk.substr(3, 1) + chunk.substr(4, 1);
		x = binaryToInt(xCo);
		y = binaryToInt(yCo);
		sVal = s[i][x][y];
		for (int z = 3; z >= 0; z--) {
			int k = sVal >> z;
			if (k & 1)
				combined += "1";
			else
				combined += "0";
		}
	}
	return combined;
}

string permSboxes(string pre)
{
	string result = "";
	char perm[4][8] =	{
							{ pre[15],pre[6],pre[19],pre[20],pre[28],pre[11],pre[27],pre[16]},
							{ pre[0],pre[14],pre[22],pre[25],pre[4],pre[17],pre[30],pre[9] },
							{ pre[1],pre[7],pre[23],pre[13],pre[31],pre[26],pre[2],pre[8] },
							{ pre[18],pre[12],pre[29],pre[5],pre[21],pre[10],pre[3],pre[24] } 
						};
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			result += perm[x][y];
		}
	}
	return result;
}

string DES(string ptext, int rounds, int maxRounds)
{
	if(rounds == 1)
		ptext = derive(ptext);
	string key;
	string ogpText = ptext;
	string rPlain = expansion(ptext.substr(32, 63));
	string sboxStuff;
	key = keyCompression(rounds);
	bitset<64> b2{ key };
	bitset<48> rPlainBits{ rPlain }, keyBits{ key };

	rPlainBits ^= keyBits;
	sboxStuff = sboxes(rPlainBits.to_string());
	sboxStuff = permSboxes(sboxStuff);
	bitset<32> step{ sboxStuff };

	bitset<32> lPlainBits{ ogpText.substr(0, 32) };
	step ^= lPlainBits;
	string finalResult = ogpText.substr(32, 63);
	finalResult += step.to_string();

	bitset<32> lbits{ finalResult.substr(0, 32) };
	bitset<32> rbits{ finalResult.substr(32, 32) };

	cout << rounds << "\t" << hex << b2.to_ullong() << "\t" << hex << lbits.to_ullong() << "\t" << hex << rbits.to_ullong() << endl;
	if (rounds != maxRounds)
		finalResult = DES(finalResult, rounds+1, maxRounds);
	return finalResult;
}

int main()
{
	//avalanche Effect PTEXT CHANGE
	//string ptextString = "12468aceeca86420";
	string ptextString = "02468aceeca86420";
	//avalanche Effect KEY CHANGE
	//string keyString = "1f1571c947d9e859";
	string keyString = "0f1571c947d9e859";


	keyGeneration(hexToBinary(keyString), 1);

	DES(hexToBinary(ptextString), 1, 16);

	return 0;
}
