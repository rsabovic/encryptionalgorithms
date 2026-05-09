// Rejhan Sabovic
// RSA Encryption and Decryption

#include <iostream>
#include <string>
#include<algorithm>

using namespace std;

string map[2][67] = { { "a",  "b",  "c",  "d",  "e",  "f",  "g",  "h",  "i",  "j",  "k",  "l",  "m",  "n",  "o",  "p",  "q",  "r",  "s",  "t",  "u",  "v",  "w",  "x",  "y",  "z",  "A",  "B",  "C",  "D",  "E",  "F",  "G",  "H",  "I",  "J",  "K",  "L",  "M",  "N",  "O",  "P",  "Q",  "R",  "S",  "T",  "U",  "V",  "W",  "X",  "Y",  "Z",  "0",  "1",  "2",  "3",  "4",  "5",  "6",  "7",  "8",  "9",  " ",  ".",  ",",  ";",  "?"}  
			   ,{       "00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "60", "61", "62", "63", "64", "65", "66"} };

string mappingltn(string alpha)
{
	string numerical = "";

	for (int i = 0; i < alpha.length(); i++)
	{
		for (int ctr = 0; ctr < 67; ctr++)
		{
			if (alpha.substr(i,1) == map[0][ctr])
			{
				numerical += map[1][ctr];
			}
		}
	}
	return numerical;
}

string mappingntl(string numerical)
{
	string alphabetical = "";

	for (int i = 0; i < numerical.length()/2; i++)
	{
		for (int ctr = 0; ctr < 67; ctr++)
		{
			if (numerical.substr(i*2, 2) == map[1][ctr])
			{
				alphabetical += map[0][ctr];
			}
		}
	}
	return alphabetical;
}

int gcd(int val1, int val2)
{
	int quotient;
	int remainder = val2;
	while (1)
	{
		if (val1 % val2 != 0)
		{
			quotient = val1 / val2;
			remainder = val1 % val2;
			cout << val1 << '\t' << val2 << '\t' << quotient << '\t' << remainder << endl;
			val1 = val2;
			val2 = remainder;
		}
		else
			break;
	}
	return remainder;
}


int gcdFind(int val1, int starter)
{
	int val2 = starter + 1;
	cout << "Divid\tDivis\tQuot\tRemain" << endl;
	while (gcd(val1, val2) != 1)
	{
		val2++;
	} 
	return val2;
}

int multInverse(int a, int b)
{
	int s = 0;
	int old_s = 1;
	int t = 1;
	int old_t = 0;
	int r = b;
	int old_r = a;
	int quotient = 0;
	int temp;
	int round = 0;
	while ((old_r - (old_r / r) * r) != 0)
	{
		round++;
		quotient = old_r / r;
		temp = r;
		r = old_r - quotient * r;
		old_r = temp;
		temp = s;
		s = old_s - quotient * s;
		old_s = temp;
		temp = t;
		t = old_t - quotient * t;
		old_t = temp;
	}
	if (s < 0)
		s += 10800;
	return s;
}

string tform(string ptext, int* key)
{
	int e = *key;
	int n = *(key + 1);
	int pint = stoll(ptext);
	int a = pint;
	int result = pint;
	int temp = 0;
	for (int i = 1; i < e; i++)
	{
		result = ((result % n) * (a % n)) % n;
	}
	

	return to_string(result);
}

int countDigits(int n)
{
	if (n / 10 == 0)
		return 1;
	return 1 + countDigits(n / 10);
}

string RSAEncryption(string ptext, int* publicKey)
{
	string holding[48];
	string ctext[48];
	string result = "";
	int n = *(publicKey + 1);
	int precision;
	int maxDigits = countDigits(n);
	ptext = mappingltn(ptext);
	for (int i = 0; i < (ptext.length() / 4); i++)
	{
		holding[i] = ptext.substr(i*4, 4);
	}
	for (int i = 0; i < (ptext.length() / 4); i++)
	{
		ctext[i] = tform(holding[i], publicKey);
		precision = maxDigits - min(maxDigits, (int)ctext[i].length());
		ctext[i] = string(precision, ' ').append(ctext[i]);
	}

	for (int i = 0; i < (ptext.length() / 4); i++)
	{
		result = result + ctext[i];
	}
	return result;
}

string RSADecryption(string ctext, int* privateKey)
{
	string holding[48];
	string ctextArr[48];
	string result = "";
	int n = *(privateKey + 1);
	int maxDigits = countDigits(n);
	int precision;
	for (int i = 0; i < (ctext.length() / maxDigits); i++)
	{
		holding[i] = ctext.substr(i * maxDigits, maxDigits);
	}
	for (int i = 0; i < (ctext.length() / maxDigits); i++)
	{
		ctextArr[i] = tform(holding[i], privateKey);
		precision = 4 - min(4, (int)ctextArr[i].length());
		ctextArr[i] = string(precision, '0').append(ctextArr[i]);
	}

	for (int i = 0; i < (ctext.length() / maxDigits); i++)
	{
		result += ctextArr[i];
	}
	cout << "Plaintext: " << result << endl;
	result = mappingntl(result);
	return result;
}

int** keyGeneration(int p, int q)
{
	int** noed = new int*[5];
	for (int i = 0; i < 5; i++)
	{
		noed[i] = new int[4];
	}
	noed[0][0] = (int)p * (int)q;
	noed[0][1] = ((int)p - 1) * ((int)q - 1);
	noed[0][2] = gcdFind(noed[0][1], 1);
	noed[0][3] = multInverse(noed[0][2], noed[0][1]);
	cout << "Multiplicative Inverse: " << noed[0][2] << "^(-1) (mod " << noed[0][1] << ") = " << noed[0][3] << endl << endl;
	for (int i = 1; i < 5; i++)
	{
		noed[i][0] = noed[0][0];
		noed[i][1] = noed[0][1];
		noed[i][2] = gcdFind(noed[0][1], noed[i-1][2]);
		noed[i][3] = multInverse(noed[i][2], noed[i][1]);
		cout << "GCDFIND returns " << noed[i][2] << endl;
		cout << "Multiplicative Inverse: " << noed[i][2] << "^(-1) (mod " << noed[i][1] << ") = " << noed[i][3] << endl << endl;
	}

	cout << "RSA Key Information:" << endl;
	cout << "Phi: " << noed[0][1] << endl;
	cout << "n: " << noed[0][0] << endl;
	cout << "The list of the 5 e's: [";
	for (int i = 0; i < 5; i++)
		cout << noed[i][2] << ", ";
	cout << "]" << endl;
	cout << "The list of the 5 d's: [";
	for (int i = 0; i < 5; i++)
		cout << noed[i][3] << ", ";
	cout << "]" << endl;
	return noed;
}


int main()
{
	string str = "How are you?";
	//string str = "Public key cryptography.";
	int p = 73;
	int q = 151;
	int** noed = keyGeneration(p, q);
	int PU[5][2];
	int PR[5][2];
	int temp[2];
	for (int i = 0; i < 5; i++)
	{
		PU[i][0] = noed[i][2];
		PU[i][1] = noed[i][0];
		PR[i][0] = noed[i][3];
		PR[i][1] = noed[i][0];
	}
	cout << endl << endl << endl;
	for(int i = 0; i < 5; i++)
	{
		cout << "Public Key: (" << PU[i][0] << ", " << PU[i][1] << ")" << endl;
		temp[0] = PU[i][0];
		temp[1] = PU[i][1];
		string ctext = RSAEncryption(str, temp);
		cout << "Ciphertext: " << ctext << endl;
		cout << "Private Key: (" << PR[i][0] << ", " << PR[i][1] << ")" << endl;
		temp[0] = PR[i][0];
		temp[1] = PR[i][1];
		string ptext = RSADecryption(ctext, temp);
		cout << endl;
	}
	return 0;
}