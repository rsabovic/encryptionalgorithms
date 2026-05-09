// Rejhan Sabovic
// Viginere Cipher Encryptor/Decryptor/Analyzer

#include <iostream>
#include <string.h>
#include <iomanip>

using namespace std;

string keyFormat(string, string);
string capitalFormat(string);
string viginereEncrypt(string, string);
string viginereDecrypt(string, string);
string viginereAnalysis(string, int);

int main()
{
	string ptext = "IraAldridgeisafascinatingcharacteranditisparticularlyexcitingthatheperformedinStratfordspendingeightdaysinthetownhevisitedShakespearesBirthplacetwiceandperformedinsevenplaysattheRoyalsShakespeareanTheatreonChapelLaneTheevidencewehaveofhistimeinStratfordhighlightssomeoftheinterestingpartsofhischaracterthewayhemanagedhiscareertofindsuccesstheprejudicehebattledagainstandthemythshebuiltuparoundhisbackgroundmainlythathewasbornaprinceinSenegalThetruthofIraAldridgesbackgroundisthathewasborninNewYorkintopoorparentshisfathertheReverendDanielAldridgewasastrawsellerwhowasalsoalaypreacherIrawasdrawntothetheatrefromanearlyageandstartedbyworkingbackstageattheChathamTheatreinNewYorkwherehebegantogainexperienceinactingtooFindingthatitwasimpossibletopursueacareeractinginAmericahecametoEnglandinattheageoftomakehisnameandinhemadehisdebutplayingOthelloattheRoyaltyTheatreAldridgecontinuedtobattleprejudiceparticularlyinthereviewshereceivedbuthewaspopularwithaudiencesHefoundfurthersuccessbymovingoutofLondontotheprovincesandlaterinlifefoundthegreatestsuccesstouringEurope";
	string key = "leg";
	string ctext = viginereEncrypt(key, ptext);
	cout << "Plain Text Encrypted: " << ctext << endl << endl;
	cout << "Cipher Text decrypted: " << viginereDecrypt(key, ctext) << endl << endl;
	cout  << "Cryptanalysis" << endl;
	ctext = "SVYKPBBMBQIGCEDKWASRYDMLQGFKVYMXCBELNMRSWNKVRSGSVEPVCCHGGDMLQXFKXFOTCBJMBQCNMLCXPKXDYVBCTCXHGXKCSKFDHYIWGXXFOXMGRFOZGCMROHQREIOWNOEPOWZSVRRTJKGCDAGMIYXHNOVDYVKOHGXWCFILZPYIWYDXFOVMIEJCWFKOCCTCKVCKRRRIYDVCYRARENOPJKRCDLCOZGNILMIUOLYFIMPLGCXGWIGXWRBERPSPNLGQLJSKFDWQYQCYJRRIGXXCBIQDMLQTYBXQYJFSWAREPKGROVRRIUKCFOQYXEEOHFSWAKVCOVRYJGXHQEGAOWQDLCZVCTYBSGCRIZKXRVIBKKYSRQDELNXFOQWDLQRIZEMJDYNKVMERBRMQLEAUKPYYLNQYSRJIXFKXFOAYCFMBRYZVGXGCSRQORCQEJDLCDVSDLMPMPKEJNVGNKCCFYMOEBSSXHGCXFKXFOAYCFMBRGXRCGCMBOGXXMZSMBTYBILDWFSWDKXFOVRRIPOZCBILNHYXMCVEJNVGNKCGEQKWRBEUCIJVIPGLMGEQKPQYEJKCNBIYMLCBMPKAYCHPKALDSRRIRRIYDVCPVMWELOEPVCYQIYXHQDEPDIBLCUYVISRELEAUWRKKCKXRRIARERREKDLCKXPOMLXIUISPUAFOVCRIZOKYXXMQEGXIVZIPSILMIGXEADMLQXMYJGXHGXKRRERSXUKWGWTMCWGLPCDSNEVQEIYMEPOIPKGRSRESRYWIPSGYRIAKQCDSCXKJKRBSRYDXFOEEOSDDSKKOCRMQXEKOELNMLRIKKHCRMQNIZEXNVEWSREYXFOPJYERDLCBSWKPRIXFOERBIYVHPSHEOGMXXGXYCNXMLERDPCZVCTYBSGCZEPDMAEPYBPWSRRRIPOZGOAQRIPOGCSZCNFSDLCGEQZSNEPYBAGDLYEHGORAOWFOJMERBPYPDLCBWSMGCCWZIQMFMLQSSDSDVSLNSLDSRRINBSTSRAOWYXHJKXCBMLVMDOJMERBDLCQVCKXCCXQEGAOWQDSSBMLQISBSNO";
	viginereAnalysis(ctext, 3);
	
	return 0;
}

// Analyzes the frequency of letters in order to guess the key using statistics of common letter in the English Language.
string viginereAnalysis(string ctext, int kLength)
{
	int x = 0;
	int hold = 0;
	string chunks = "";
	ctext = capitalFormat(ctext);
	string key = "";
	char mostFreq;
	int highestFreq = 0;

	char dups[26];
	for (int idx = 25; idx >= 0; idx--)
		dups[idx] = -1;
	int dupCheck = 0;

	for (int i = 0; i < ctext.length(); i++)
	{
		if((((i - hold) * kLength) + x) < ctext.length())
			chunks += ctext.at(((i - hold) * kLength) + x);
		if (i >= (int)(((float)(x + 1) / kLength) * ctext.length()) || i == ctext.length() - 1)
		{
			hold = 0;
			hold += (int)(((float)(x + 1) / kLength) * ctext.length());
			x++;
			if (i != ctext.length() - 1)
				i--;
			cout << "Position " << x - 1 << ": " << chunks << endl;
			cout << "Lett\tFreq\tPerc\tBar" << endl;
			for (int c = 65; c < 91; c++)
			{
				char test = c;
				int counter = 0;
				int freq = 0;
				while (chunks[counter])
				{
					if (chunks[counter] == c)
					{
						freq++;
					}
					counter++;
				}
				if (freq == highestFreq)
				{
					dupCheck++;
					dups[dupCheck] = c;
				}
				else if (freq > highestFreq)
				{
					
					for (int idx = 25; idx >= 0; idx--)
						dups[idx] = -1;
					dupCheck = 0;
					highestFreq = freq;
					dups[dupCheck] = c;
				}
				cout << fixed << setprecision(2) << (char)c << '\t' << freq << "\t(" << ((float)freq / chunks.length()) * 100 << ")\t";
				for (int ctr = 1; ctr <= ((float)freq / chunks.length()) * 100; ctr++)
					cout << "*";
				cout << endl;
			}
			highestFreq = 0;
			dups[0] = (dups[0] - 65) - 4;
			if (dups[0] < 0)
				dups[0] += 26;
			key += dups[0] + 65;
			chunks = "";
			dupCheck = 0;
			for (int idx = 25; idx >= 0; idx--)
				dups[idx] = -1;
		}
	}
	cout << "The key is: " << key;
	return chunks;
}

// Decrypts the cipher text using the formatted key
string viginereDecrypt(string key, string ctext)
{
	ctext = capitalFormat(ctext);
	key = keyFormat(key, ctext);
	string ptext = "";
	int c;
	for (int i = 0; i < ctext.length(); i++)
	{
		c = (ctext.at(i) - 65) - (key.at(i) - 65);
		while (c < 0)
		{
			c += 26;
		}
		c += 65;
		ptext += c;
	}
	return ptext;
}

// Encrypts the plain text using the formatted key
string viginereEncrypt(string key, string ptext)
{
	ptext = ptext = capitalFormat(ptext);
	key = keyFormat(key, ptext);
	string ctext = "";
	int c;
	for (int i = 0; i < ptext.length(); i++)
	{
		c = (key.at(i) - 65)+ (ptext.at(i) - 65);
		while (c > 25)
		{
			c -= 26;
		}
		c += 65;
		ctext += c;
	}
	return ctext;
}

// Capitalizes strings so that characters are normalized in the ASCII region of 65->90
string capitalFormat(string lower)
{
	string upper = "";
	int i = 0;
	while (lower[i])
	{
		upper += (char)toupper(lower[i]);
		i++;
	}
	return upper;
}

// Formats the ket to match the length of the plain text for encryption/decryption
string keyFormat(string key, string ptext)
{
	key = capitalFormat(key);
	if (key.length() == ptext.length())
		return key;
	else if (key.length() > ptext.length())
	{
		return key.substr(0, ptext.length() - 1);
	}
	else
	{
		int hold = 0;
		string formatKey = "";
		for (int i = 0; i < ptext.length(); i++)
		{
			hold = i % key.length();
			formatKey = formatKey + key.at(hold);
		}
		return formatKey;
	}
}