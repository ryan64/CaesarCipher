#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void encrypt(string);
void decrypt(string);
int numberOfLines(string); 

int main() //The user interface, where the user decides on what he wants the program to do. 
{
	string key; //variable to store a string type. 
	int number = 0; //variable to store a int type.
	while (number < 1) 
	{
		cout << "----------Encryption Or Decryption ----------" << endl; 
		cout << "Please enter 'en' for encryption or 'de' for decryption: "; 
		cin >> key; //user gets to input a string. 
		
		if (key == "en")
		{
			cout << "Okay, the files 'text.txt', and 'encryptionKey.txt' and being processed." << endl; 
			encrypt("text.txt"); //calls on encrypt function, passing the file containing text. 
			cout << "Your file 'text.txt' is now encrypted, please check for the 'encryptedText.txt' file." << endl; 
			number++; //once the number is increased by one, the loop is stopped.  
		}
		else if (key == "de")
		{
			cout << "Okay, the files 'encryptedText.txt' and 'encryptionKey.txt' are being processed." << endl; 
			decrypt("encryptedText.txt"); //calls on the decrypt function, passing the file containing encrypted text. 
			cout << "Your file 'encryptedText.txt' is now decrypted, please check for the 'decryptedText.txt' file." << endl; 
			number++; //once the number is increased by one, the loop is stopped. 
		}
		
		else 
		cout << "Sorry, that is not a valid response, please try again..." << endl; //incase the user inputs something other than 'en' or 'de'.
	}
	system("pause"); 
	return 0; 
}

int numberOfLines(string file) //counts the number of lines in the file being processed. 
{
	string line; 
	int number_of_lines = 0; 
	ifstream countLines(file.c_str()); //reads whatever string file comes in.
	while (getline(countLines, line)) number_of_lines++; //number_of_lines is increased by one, as it reads the input. 
	return number_of_lines; //return the number of lines. 
}

void encrypt(string file)
{
	ifstream infile("encryptionKey.txt"); //reads from the file called encryptionKey.txt.
	ofstream outfile("encryptedText.txt"); //writes to a file called encryptedText.txt.
	int encryptionKeySize; //variable to store a int type. 
	encryptionKeySize = numberOfLines("encryptionKey.txt"); //calls on the numberOfLines function to determine the number of lines of the encryption key and store it. 
	char* pointerOne = new char[encryptionKeySize]; //size of the dynamic array determined by encryptionkey. 
	char* pointerTwo = new char[encryptionKeySize]; //size of the dynamic array determined by encryptionkey. 
	
	for (int i = 0; i < encryptionKeySize; i++) //will copy the encryption key line by line into two arrays. 
	{
		infile >> pointerOne[i];
		infile >> pointerTwo[i]; 
	}
	
	infile.close(); //close the input stream. 
	ifstream newinfile(file.c_str()); //open a new input stream. 
	string line; 
	
	while (!newinfile.eof()) //while not at the end of the new input stream file. 
	{
		getline(newinfile, line);	//puts each line into the line string.
		int lineEnd = 0;
		
		while (line[lineEnd] != '\0') //number of characters in the string is counted here
		{	
			lineEnd++; 
		}
		
		for (int j = 0; j < lineEnd; j++) //will run through each character in the string.
		{	
			for (int k = 0; k < encryptionKeySize; k++) //will run through each character in the key.
			{	
				if (line[j] == pointerOne[k]) 
				{	
					line[j] = pointerTwo[k]; //if the string char matches the key char it will change to the key's other side (unencrypted to encrypted). 
					break;	//this is to ensure that the char is not changed more times than it needs to.
				}
			}
		}
		
		outfile << line << endl;	//this will write the changed contents to the encryptedText file.
	}
	
	newinfile.close(); //make sure to close streams associated. 
	outfile.close(); //make sure to close streams associated. 
}

void decrypt(string file)
{
	ifstream infile("encryptionKey.txt"); //reads from the file called encryptionKey.txt.
	ofstream outfile("decryptedText.txt"); //writes to a file called decryptedText.txt.
	int encryptionKeySize; //variable to store a int type. 
	encryptionKeySize = numberOfLines("encryptionKey.txt"); //calls on the numberOfLines function to determine the number of lines of the encryption key and store it. 
	char* pointerOne = new char[encryptionKeySize]; //size of the dynamic array determined by encryptionkey. 
	char* pointerTwo = new char[encryptionKeySize]; //size of the dynamic array determined by encryptionkey. 
	
	for (int i = 0; i < encryptionKeySize; i++) //will copy the encryption key line by line into two arrays. 
	{
		infile >> pointerOne[i];
		infile >> pointerTwo[i]; 
	}
	
	infile.close(); //close the input stream. 
	ifstream newinfile(file.c_str()); //open a new input stream. 
	string line; 
	
	while (!newinfile.eof()) //while not at the end of the new input stream file. 
	{
		getline(newinfile, line);	//puts each line into the line string.
		int lineEnd = 0;
		
		while (line[lineEnd] != '\0') //number of characters in the string is counted here
		{	
			lineEnd++; 
		}
		
		for (int j = 0; j < lineEnd; j++) //will run through each character in the string.
		{	
			for (int k = 0; k < encryptionKeySize; k++) //will run through each character in the key.
			{	
				if (line[j] == pointerTwo[k]) 
				{	
					line[j] = pointerOne[k]; //if the string char matches the key char it will change to the key's other side (encrypted to unencrypted). 
					break;	//this is to ensure that the char is not changed more times than it needs to.
				}
			}
		}
		
		outfile << line << endl;	//this will write the changed contents to the decryptedText file.
	}
	
	newinfile.close(); //make sure to close streams associated. 
	outfile.close(); //make sure to close streams associated. 
}


