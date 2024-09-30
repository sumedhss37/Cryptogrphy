#include <iostream>
#include <stdio.h>
#include <string.h>

char the_file[] = "01_cipher8.txt"; /*THIS IS FILE TO LOAD, please change according to your location */

float my_ic(char arr[]);
int my_comparer(char arr[]);
int my_blockdivider(int divisor);
void my_decryption();


int x = 0, y = 0, z = 0, value = 0, flag = 0, n1 = 0, x1 = 0, x2 = 0;
int alpha_counter[26] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int got_key[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int key_len = 0;
float ans = 0, final_ic = 0;
char cipher[2500];
char ptext[2500];
char pressed = ' ';
FILE *fp;


int main(int argc, char** argv[])
{
	//Get from file
	/*******************************GET DATA FROM FILE*********************/
	printf("Press '1' to read cipher text from file or press any key for already present cipher text\n");
	printf("\nOption:");
	printf("\a");
	std::cin>>pressed;
	printf("\n\n");

	if (pressed == '1')
	{
		fp = fopen(the_file, "rb");

		if (fp != NULL)
		{
			while (!feof(fp))
			{
				fgetc(fp);
				n1++;
			}
			fclose(fp);

			fp = fopen(the_file, "r");

			for (x1 = 0, x2 = 0; x1 < n1; x1++)
			{
				fscanf(fp, "%c", &cipher[x2]);

				if ((cipher[x2] >= 'A' && cipher[x2] <= 'Z') || (cipher[x2] >= 'a' && cipher[x2] <= 'z'))
				{
					x2 = x2 + 1;
				}

				else
				{
					//x2=x2-1;
				}

			}

			fclose(fp);

			//Get from file
		}

		else
		{
			printf("\nFILEPOINTER === NULL\n");
		}
	}
	else
	{

		//strcpy(cipher,"ICJEVAQIPWBCIJRQFVIFAZCPQYMJAHNGFYDHWEQRNARELKBRYGPCSPKWBUPGKBKZWDSZXSAFZLOIWETVPSITQISOTFKKVTQPSEOWKPVRLJIECHOHITFPSUDXXARCLJSNLUBOIPRJHYPIEFJERBTVMUQOIJZAGYLOHSEOHWJFCLJGGTWACWEKEGKZNASGEKAIETWARJEDPSJYHQHILOEBKSHAJVYWKTKSLOBFEVQQTPHZWERZAARVHISOTFKOGCRLCJLOKTRYDHZZLQYSFYWDSWZOHCNTQCPRDLOARVHSOIERCSKSHNARVHLSRNHPCXPWDSILPLZVQLJOENLWZJFSLCIEDJRRYXJRVCVPOEOLJUFYRQFGLUPHYLWISOTFKWJERNSTZQMIVCWDSCZVPHVCUEHFCBEBKPAWGEPZISOTFKOEODNWQZQWHYPVAHKWHISEEGAHRTOEGCPIPHFJRQ");	
		strcpy(cipher, "QVXYKTAPZGPPFHBUMNWHDONUPHBTEEXTQDVVZFNZQDLLZSXSQSLHZDKLBEESQNMFQTBUFHBZHEKFDEIBSNTUOEMVMLEOUSVPDCNTETTUOELWUEKYQFHBZDTRUNWVRTTUFAEPLIGNEAMPEFTJFIHUUMTRQBHSPTHHEKRVGRXEOEESQNVFFOFVHETSUTMSQFHYFHBZSEGAXEFHZSTPPTALBOLAYALAQRXUFEKPZGMOQRHVYFHSXOPLPBRHZOMOQRMYMVXSQRTSEOWLFABUQDYVDLTJWOYOARLLETALZEPJAMXYIALHEHHYFLTYSEUVZEWFQLEVIFTJQDPYUNDSQDHSPMTUIIMOSRTFNULOKERLNRHDEOOLDHTUSIGNNRBNTTXFQSHMMNBUPEYPZIMLSRTFUSAJALHYBIXYDEMVAKAPEFXLFOYMFHXAMBELETHVPUIHZDEHKDHDZOGHNEWATAMOMDULQNZVFRXHPYYVDHBTSLTUOIGNZOPHZDMOQNTAFHXUQWVVYEKDTOPPFHTNXOHTKAGKFIKLPFTJQWTZIETYULRAMKBUSOYMTILDDAIZIIMOFHXHUDHMTILZQROHZTTUPNHAXOHRUNZHFPBLDRXMDOFDMRTUPPXHOEUVAKYPHEVOMPMLDOGL");
	}

	for(int i=0;i<strlen(cipher);i++){
        cipher[i] = toupper(cipher[i]);
    } //covert all the Alphabets in Capital

	printf("Cipher Text:\n");
	for (x = 0; x<strlen(cipher); x++)
	{
		printf("%c", cipher[x]); //print the Ciphertext
		//printf("%d \n",cipher[x]);
		//A-> 65 (ASCI VALUE)
	}
	printf("\n\nTotal Alphabets === %d\n", strlen(cipher));

	printf("\n\nPerforming Index of Coincidence Test:\n");
	final_ic = my_ic(cipher);
	printf("\nThe I.C value is: %3.10f", final_ic); //upto 10 point value of I.C

	if (final_ic > 0.060 && final_ic<0.070) //tolerance for 0.065
	{
		printf("\nThe alogrithm is Mono-Alphabetic");
	}

	else
	{
		printf("\nThe alogrithm is Poly-Alphabetic\n");
		printf("\nFinding Key Length:\n");
		printf("\nStarting Iterations:\n\n");

		for (int block_counter = 1; block_counter <= 9; block_counter++)
		{
			flag = my_blockdivider(block_counter);
			if (flag == 1)
			{
				break;
			}

		}

		if (key_len != 0)
		{
			my_decryption();
		}

		else
		{
			printf("\nDecryption was not successful as I.C value were not close to 0.065\n");
		}
	}

	printf("\n");

	return 0;
}


float my_ic(char arr[])
{
	char temp;
	int length = 0;
	int alphabet_counter[26] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	float value = 0, result = 0;

	for (length = 0; length<strlen(arr); length++)
	{
		temp = arr[length];
		temp = temp - 65; // A-->0 .... Z-->25
		if (temp >= 0 && temp <= 25)
		{
			alphabet_counter[temp] = alphabet_counter[temp] + 1;
		}
	}

	for (x = 0; x<26; x++)
	{
		value = (alphabet_counter[x])*(alphabet_counter[x] - 1); // ni * ni-1
		value = value / (strlen(arr)*(strlen(arr) - 1)); //n * n-1
		result = result + value; //adding all the results
	}

	//printf("%f \n",result);
	return result;
}


int my_blockdivider(int divisor)
{
	int length = 0, dummy = 1, value = 0; //lenght for length of ciphertext, dummy for padding

	float ans = 0, res = 0;

	divisor = divisor + 1;
	length = strlen(cipher);

	//padding with letter 0
	while ((strlen(cipher) % divisor) != 0)
	{
		cipher[length] = '0';
		length++;

	}
	cipher[length] = '\0'; //adding NULL CHARACTER
	//padding with letter 0

	value = (strlen(cipher)) / divisor;

	if (divisor == 2)
	{
		char c1[2700], c2[2700], c3[2700], c4[2700], c5[2700], c6[2700], c7[2700], c8[2700], c9[2700];
		for (z = 0; z<value; z++)
		{
			c1[z] = cipher[2 * z];
			c2[z] = cipher[(2 * z) + 1];
		}
		c1[z] = '\0';
		c2[z] = '\0';
		ans = 0;

		res = my_ic(c1);
		ans = ans + res;
		res = my_ic(c2);
		ans = ans + res;
		ans = ans / divisor;

		printf("Average I.C of the %d blocks were=== %3.8f\n", divisor, ans);

		if (ans >= 0.059 && ans <= 0.071) // range for 0.065
		{
			printf("Got Key Length and it is %d\n\n", divisor);
			key_len = 2;
			int temporary = 0, temporary2 = 0;
			int myans = 0;

			myans = my_comparer(c1); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[0] = myans + 65;

			myans = my_comparer(c2); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[1] = myans + 65;


			return 1;
		}
		else
		{
			printf("Key Length is not %d\n\n", divisor);
		}

	}

	else if (divisor == 3)
	{
		char c1[2700], c2[2700], c3[2700], c4[2700], c5[2700], c6[2700], c7[2700], c8[2700], c9[2700];
		for (z = 0; z<value; z++)
		{
			c1[z] = cipher[3 * z];
			c2[z] = cipher[(3 * z) + 1];
			c3[z] = cipher[(3 * z) + 2];
		}
		c1[z] = '\0';
		c2[z] = '\0';
		c3[z] = '\0';
		ans = 0;
		res = my_ic(c1);
		ans = ans + res;
		res = my_ic(c2);
		ans = ans + res;
		res = my_ic(c3);
		ans = ans + res;
		ans = ans / divisor;

		printf("Average I.C of the %d blocks were=== %3.8f\n", divisor, ans);

		if (ans >= 0.059 && ans <= 0.071) // range for 0.065
		{
			printf("Got Key Length and it is %d\n\n", divisor);
			key_len = 3;
			int temporary = 0, temporary2 = 0;
			int myans = 0;

			myans = my_comparer(c1); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[0] = myans + 65;

			myans = my_comparer(c2); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[1] = myans + 65;


			myans = my_comparer(c3); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[2] = myans + 65;
			return 1;
		}
		else
		{
			printf("Key Length is not %d\n\n", divisor);
		}
	}

	else if (divisor == 4)
	{
		char c1[2700], c2[2700], c3[2700], c4[2700], c5[2700], c6[2700], c7[2700], c8[2700], c9[2700];
		for (z = 0; z<value; z++)
		{
			c1[z] = cipher[4 * z];
			c2[z] = cipher[(4 * z) + 1];
			c3[z] = cipher[(4 * z) + 2];
			c4[z] = cipher[(4 * z) + 3];
		}
		c1[z] = '\0';
		c2[z] = '\0';
		c3[z] = '\0';
		c4[z] = '\0';

		ans = 0;
		res = my_ic(c1);
		ans = ans + res;
		res = my_ic(c2);
		ans = ans + res;
		res = my_ic(c3);
		ans = ans + res;
		res = my_ic(c4);
		ans = ans + res;
		ans = ans / divisor;

		printf("Average I.C of the %d blocks were=== %3.8f\n", divisor, ans);
		if (ans >= 0.059 && ans <= 0.071) // range for 0.065
		{
			printf("Got Key Length and it is %d\n\n", divisor);
			key_len = 4;
			int myans = 0;

			myans = my_comparer(c1); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}

			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[0] = myans + 65;

			myans = my_comparer(c2); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}

			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[1] = myans + 65;
			myans = my_comparer(c3); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}

			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[2] = myans + 65;

			myans = my_comparer(c4); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}

			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[3] = myans + 65;

			return 1;
		}
		else
		{
			printf("Key Length is not %d\n\n", divisor);
		}
	}

	else if (divisor == 5)
	{
		char c1[2700], c2[2700], c3[2700], c4[2700], c5[2700], c6[2700], c7[2700], c8[2700], c9[2700];
		for (z = 0; z<value; z++)
		{
			c1[z] = cipher[5 * z];
			c2[z] = cipher[(5 * z) + 1];
			c3[z] = cipher[(5 * z) + 2];
			c4[z] = cipher[(5 * z) + 3];
			c5[z] = cipher[(5 * z) + 4];
		}
		c1[z] = '\0';
		c2[z] = '\0';
		c3[z] = '\0';
		c4[z] = '\0';
		c5[z] = '\0';
		ans = 0;
		res = my_ic(c1);
		ans = ans + res;
		res = my_ic(c2);
		ans = ans + res;
		res = my_ic(c3);
		ans = ans + res;
		res = my_ic(c4);
		ans = ans + res;
		res = my_ic(c5);
		ans = ans + res;
		ans = ans / divisor;

		printf("Average I.C of the %d blocks were=== %3.8f\n", divisor, ans);

		if (ans >= 0.059 && ans <= 0.071) // range for 0.065
		{
			printf("Got Key Length and it is %d\n\n", divisor);
			key_len = 5;
			int temporary = 0, temporary2 = 0;
			int myans = 0;

			myans = my_comparer(c1); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[0] = myans + 65;

			myans = my_comparer(c2); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[1] = myans + 65;

			myans = my_comparer(c3); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[2] = myans + 65;

			myans = my_comparer(c4); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[3] = myans + 65;

			myans = my_comparer(c5); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[4] = myans + 65;

			return 1;
			//}
			//printf("\nWhen block was replaced with %d=%c the Value was %d\n\n",xx+64,xx+64,myans);

		}
		else
		{
			printf("Key Length is not %d\n\n", divisor);
		}

	}

	else if (divisor == 6)
	{
		char c1[2700], c2[2700], c3[2700], c4[2700], c5[2700], c6[2700], c7[2700], c8[2700], c9[2700];
		for (z = 0; z<value; z++)
		{
			c1[z] = cipher[6 * z];
			c2[z] = cipher[(6 * z) + 1];
			c3[z] = cipher[(6 * z) + 2];
			c4[z] = cipher[(6 * z) + 3];
			c5[z] = cipher[(6 * z) + 4];
			c6[z] = cipher[(6 * z) + 5];
		}
		c1[z] = '\0';
		c2[z] = '\0';
		c3[z] = '\0';
		c4[z] = '\0';
		c5[z] = '\0';
		c6[z] = '\0';

		ans = 0;
		res = my_ic(c1);
		ans = ans + res;
		res = my_ic(c2);
		ans = ans + res;
		res = my_ic(c3);
		ans = ans + res;
		res = my_ic(c4);
		ans = ans + res;
		res = my_ic(c5);
		ans = ans + res;
		res = my_ic(c6);
		ans = ans + res;
		ans = ans / divisor;

		printf("Average I.C of the %d blocks were=== %3.8f\n", divisor, ans);

		if (ans >= 0.059 && ans <= 0.071) // range for 0.065
		{
			printf("Got Key Length and it is %d\n\n", divisor);
			key_len = 6;
			int temporary = 0, temporary2 = 0;
			int myans = 0;

			myans = my_comparer(c1); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[0] = myans + 65;

			myans = my_comparer(c2); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[1] = myans + 65;

			myans = my_comparer(c3); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[2] = myans + 65;

			myans = my_comparer(c4); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[3] = myans + 65;

			myans = my_comparer(c5); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[4] = myans + 65;

			myans = my_comparer(c6); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[5] = myans + 65;

			return 1;
		}
		else
		{
			printf("Key Length is not %d\n\n", divisor);
		}
	}

	else if (divisor == 7)
	{
		char c1[2700], c2[2700], c3[2700], c4[2700], c5[2700], c6[2700], c7[2700], c8[2700], c9[2700];
		for (z = 0; z<value; z++)
		{
			c1[z] = cipher[7 * z];
			c2[z] = cipher[(7 * z) + 1];
			c3[z] = cipher[(7 * z) + 2];
			c4[z] = cipher[(7 * z) + 3];
			c5[z] = cipher[(7 * z) + 4];
			c6[z] = cipher[(7 * z) + 5];
			c7[z] = cipher[(7 * z) + 6];
		}
		c1[z] = '\0';
		c2[z] = '\0';
		c3[z] = '\0';
		c4[z] = '\0';
		c5[z] = '\0';
		c6[z] = '\0';
		c7[z] = '\0';

		ans = 0;
		res = my_ic(c1);
		ans = ans + res;
		res = my_ic(c2);
		ans = ans + res;
		res = my_ic(c3);
		ans = ans + res;
		res = my_ic(c4);
		ans = ans + res;
		res = my_ic(c5);
		ans = ans + res;
		res = my_ic(c6);
		ans = ans + res;
		res = my_ic(c7);
		ans = ans + res;
		ans = ans / divisor;

		printf("Average I.C of the %d blocks were=== %3.8f\n", divisor, ans);

		if (ans >= 0.059 && ans <= 0.071) // range for 0.065
		{
			printf("Got Key Length and it is %d\n\n", divisor);
			key_len = 7;
			int temporary = 0, temporary2 = 0;
			int myans = 0;

			myans = my_comparer(c1); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[0] = myans + 65;

			myans = my_comparer(c2); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[1] = myans + 65;

			myans = my_comparer(c3); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[2] = myans + 65;

			myans = my_comparer(c4); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[3] = myans + 65;

			myans = my_comparer(c5); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[4] = myans + 65;

			myans = my_comparer(c6); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[5] = myans + 65;

			myans = my_comparer(c7); // myans LOCATION of alphabet
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[6] = myans + 65;
			return 1;
		}
		else
		{
			printf("Key Length is not %d\n\n", divisor);
		}
	}

	else if (divisor == 8)
	{
		char c1[2700], c2[2700], c3[2700], c4[2700], c5[2700], c6[2700], c7[2700], c8[2700], c9[2700];
		for (z = 0; z<value; z++)
		{
			c1[z] = cipher[8 * z];
			c2[z] = cipher[(8 * z) + 1];
			c3[z] = cipher[(8 * z) + 2];
			c4[z] = cipher[(8 * z) + 3];
			c5[z] = cipher[(8 * z) + 4];
			c6[z] = cipher[(8 * z) + 5];
			c7[z] = cipher[(8 * z) + 6];
			c8[z] = cipher[(8 * z) + 7];
		}
		c1[z] = '\0';
		c2[z] = '\0';
		c3[z] = '\0';
		c4[z] = '\0';
		c5[z] = '\0';
		c6[z] = '\0';
		c7[z] = '\0';
		c8[z] = '\0';

		ans = 0;
		res = my_ic(c1);
		ans = ans + res;
		res = my_ic(c2);
		ans = ans + res;
		res = my_ic(c3);
		ans = ans + res;
		res = my_ic(c4);
		ans = ans + res;
		res = my_ic(c5);
		ans = ans + res;
		res = my_ic(c6);
		ans = ans + res;
		res = my_ic(c7);
		ans = ans + res;
		res = my_ic(c8);
		ans = ans + res;
		ans = ans / divisor;

		printf("Average I.C of the %d blocks were=== %3.8f\n", divisor, ans);

		if (ans >= 0.059 && ans <= 0.071) // range for 0.065
		{
			printf("Got Key Length and it is %d\n\n", divisor);
			key_len = 8;
			int temporary = 0, temporary2 = 0;
			int myans = 0;

			myans = my_comparer(c1); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[0] = myans + 65;

			myans = my_comparer(c2); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[1] = myans + 65;

			myans = my_comparer(c3); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[2] = myans + 65;

			myans = my_comparer(c4); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[3] = myans + 65;

			myans = my_comparer(c5); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[4] = myans + 65;

			myans = my_comparer(c6); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[5] = myans + 65;

			myans = my_comparer(c7); // myans LOCATION of alphabet
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[6] = myans + 65;

			myans = my_comparer(c8); // myans LOCATION of alphabet
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[7] = myans + 65;

			return 1;
		}
		else
		{
			printf("Key Length is not %d\n\n", divisor);
		}
	}

	else if (divisor == 9)
	{
		char c1[2700], c2[2700], c3[2700], c4[2700], c5[2700], c6[2700], c7[2700], c8[2700], c9[2700];
		for (z = 0; z<value; z++)
		{
			c1[z] = cipher[9 * z];
			c2[z] = cipher[(9 * z) + 1];
			c3[z] = cipher[(9 * z) + 2];
			c4[z] = cipher[(9 * z) + 3];
			c5[z] = cipher[(9 * z) + 4];
			c6[z] = cipher[(9 * z) + 5];
			c7[z] = cipher[(9 * z) + 6];
			c8[z] = cipher[(9 * z) + 7];
			c8[z] = cipher[(9 * z) + 8];
		}
		c1[z] = '\0';
		c2[z] = '\0';
		c3[z] = '\0';
		c4[z] = '\0';
		c5[z] = '\0';
		c6[z] = '\0';
		c7[z] = '\0';
		c8[z] = '\0';
		c9[z] = '\0';
		ans = 0;
		res = my_ic(c1);
		ans = ans + res;
		res = my_ic(c2);
		ans = ans + res;
		res = my_ic(c3);
		ans = ans + res;
		res = my_ic(c4);
		ans = ans + res;
		res = my_ic(c5);
		ans = ans + res;
		res = my_ic(c6);
		ans = ans + res;
		res = my_ic(c7);
		ans = ans + res;
		res = my_ic(c8);
		ans = ans + res;
		res = my_ic(c9);
		ans = ans + res;

		ans = ans / divisor;

		printf("Average I.C of the %d blocks were=== %3.8f\n", divisor, ans);

		if (ans >= 0.059 && ans <= 0.071) // range for 0.065
		{
			printf("Got Key Length and it is %d\n\n", divisor);
			key_len = 9;
			int temporary = 0, temporary2 = 0;
			int myans = 0;

			myans = my_comparer(c1); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[0] = myans + 65;

			myans = my_comparer(c2); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[1] = myans + 65;

			myans = my_comparer(c3); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[2] = myans + 65;

			myans = my_comparer(c4); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[3] = myans + 65;

			myans = my_comparer(c5); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[4] = myans + 65;

			myans = my_comparer(c6); // myans LOCATION of alphabet
			//myans=myans-4;//LOCATION of E-4 to get A
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[5] = myans + 65;

			myans = my_comparer(c7); // myans LOCATION of alphabet
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[6] = myans + 65;

			myans = my_comparer(c8); // myans LOCATION of alphabet
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[7] = myans + 65;

			myans = my_comparer(c9); // myans LOCATION of alphabet
			if (myans < 0)
			{
				myans = myans + 26;
			}
			printf("\nGot the alphabet and it is %c\n\n", myans + 65);
			got_key[8] = myans + 65;
			return 1;
		}
		else
		{
			printf("Key Length is not %d\n\n", divisor);
		}

		return 0; //key not 2-9
	}

}
int my_comparer(char arr[])
{
	char temp;
	float temp222 = 0, temp333 = 0;
	int length = 0, pos = 0, sim = 0;
	int alphabet_counter2[26] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	float all_rf = 0;
	float relative_freq[26] = { 8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, .153, .772, 4.025, 2.406, 6.749, 7.507, 1.929, .095, 5.987, 6.327, 9.056, 2.758, .978, 2.360, .150, 1.974, .074 };
	float relative_freq_avg[26] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	float comparer[26] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	float value[26] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	float mylow = 0;
	float calculator[26] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


	for (length = 0; length<26; length++)
	{
		all_rf = all_rf + relative_freq[length];
	}

	for (length = 0; length<26; length++)
	{
		relative_freq[length] = relative_freq[length] / 100;
	}


	for (sim = 0; sim<26; sim++)
	{
		for (length = 0; length<26; length++)
		{
			alphabet_counter2[length] = 0; comparer[length] = 0;
		}

		for (length = 0; length<strlen(arr); length++)
		{
			char dumx;
			dumx = arr[length];
			dumx = dumx - 65;

			while (dumx<0)
			{
				dumx = dumx + 26;
			}
			dumx = dumx % 26;

			temp = dumx - sim;

			while (temp<0)
			{
				temp = temp + 26;
			}
			temp = temp % 26;

			if (temp >= 0 && temp <= 25)
			{
				alphabet_counter2[temp] = alphabet_counter2[temp] + 1;
			}
		}
		temp333 = 0;


		for (length = 0; length<26; length++)
		{
			temp222 = alphabet_counter2[length];
			temp222 = temp222 / (strlen(arr));
			comparer[length] = relative_freq[length] - temp222;
			if (comparer[length] < 0)
			{
				comparer[length] = comparer[length] * (-1);
			}
			temp333 = temp333 + comparer[length];
		}

		calculator[sim] = temp333;

	}


	/* lowest value of calculator[x] will show least error with the orignal relative freq table, and that will be the right alphabet*/
	pos = 0;
	mylow = calculator[0];
	for (sim = 0; sim<26; sim++)
	{
		if (mylow > calculator[sim])
		{
			mylow = calculator[sim];
			pos = sim;
		}
	}

	/* lowest value of calculator[x] will show least error with the orignal relative freq table, and that will be the right alphabet*/
	return pos;
}

void my_decryption(void)
{
	int s_c = 0, s_k = 0;
	for (x1 = 0, x2 = 0; x1<strlen(cipher); x1++)
	{
		x2 = x2%key_len;

		s_c = cipher[x1] - 65;
		s_k = got_key[x2] - 65;

		ptext[x1] = s_c - s_k;

		while (ptext[x1] < 0)
		{
			ptext[x1] = ptext[x1] + 26;
		}

		ptext[x1] = ptext[x1] % 26;

		ptext[x1] = ptext[x1] + 65;
		x2 = x2 + 1;
	}

	printf("\n The Decrypted Plain text is:\n");
	for (x1 = 0; x1<strlen(ptext); x1++)
	{
		printf("%c ", ptext[x1]);
	}
}