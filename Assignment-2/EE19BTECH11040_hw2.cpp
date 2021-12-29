// Including essential libraries
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;


// Custom data type for defining the node in the hashmap
struct node
{
	struct node* link = NULL;			//Linking pointer
	string username;					//Username
	string password;					//Password
};


// Creation of node
struct node* createNode(string username, string password){
	struct node* temp = new node;		//Allocating newnode
	temp->username = username;			//Initializing username
	temp->password = password;          //Initializing password
	temp->link = NULL;                  //Initializing next link
	return temp;                        //Returning the new created node
}

//Compute the hash value of the string
int computeHash(string username,int p, int m){
	int value = 0,w = 1,sum=0;
	for(int i=0;i<username.length();i++){         //Computing the weighted sum wrt to characters 
		sum = ((username[i]-'0')*w) % m;          //of the string and operating on the modulus
		value = (value + sum)%m;
		w *= p;
	}
	value = (value+m)%m;
	return value;
}

// Insert into the hash table
void insertToHash(struct node* temp,vector<struct node*>& hashTable, int hashValue){
	if(hashTable[hashValue]==NULL){				 //Insertion for first time
		hashTable[hashValue] = temp;
	}
	else{                                        //Resolving collision via chaining
		temp->link = hashTable[hashValue];
		hashTable[hashValue] = temp;
	}
}

// Creating a hash table
vector<struct node*> createHashTable(const string& path, int p, int m){
	vector<struct node*> hashTable(m,NULL);      //Initializing a hash table
	fstream fin;                                 //file streamer
	fin.open(path, ios::in);                     //Opening the csv file
	string line,username_t,password_t;           //Initializing the string variables
	struct node* tempNode=NULL;                  //Temporary node pointer used in operations
	int hashValue = 0;                           //Initializng the hash value
	if(fin.is_open()){							 //File open check
		while(getline(fin,line,'\n')){           //Reading the line
			int pos = line.find(','),end=line.find('\n'); //Finding the delimiter
			username_t = line.substr(0,pos);	 //Extracting the username
			password_t = line.substr(pos+1,line.length()-username_t.length()-1); //Extracting password
			if(password_t[password_t.length()-1]==(char)13) //Removing the carry return if present
				password_t = line.substr(pos+1,password_t.length()-1);
			tempNode = createNode(username_t,password_t);  //Creating corresponding node
			hashValue = computeHash(username_t,p,m);       //Computing hash value for the node
			insertToHash(tempNode,hashTable,hashValue);    //Inserting the node to the hash table
		}
	}
	else{
		cout<<"Check the csv file location, its not there where it has to be."<<endl;
		exit(0);
	}
	return hashTable;
}

//printing the hash table
void printHashTable(vector<struct node*>& hashTable){
	struct node* temp = NULL;
	cout<<"---------------HASH TABLE----------------"<<endl;
	for(int i=0;i<hashTable.size();i++){
		if(hashTable[i]!=NULL){
			cout<<i<<" : ";
			temp = hashTable[i];
			while(temp!=NULL){
				cout<<temp->username<<"--> ";
				temp = temp->link;
			}
			cout<<"NULL"<<endl;
		}
	}
}

// Searching for username
struct node* findUsername(string username,vector<struct node*>&hashTable,int p,int m){
	int hashVal = computeHash(username,p,m);                //Computing the hash for given string
	struct node* search = hashTable[hashVal];               //Search node in the hash chain
	while(search!=NULL){									//Traversing the chain
		if(search->username==username){                     //Finding the chain
			// cout<<"Found -> "<<search->username<< " : "<<search->password<<endl;
			break;
		}
		else{
			search = search->link;
		}
	}
	return search;                                          //Returning the result
}

int main(void){
	// Ready your hash table
	string path = "userInfo.csv";								//Path
	// It is observed keeping load factor close to 0.75 generally yields better performance
	// Here n = 20,000 and resulting m = n/alpha = 26.667*10^3, so we can take 27,000	
	int p = 11, m = 27000;
	cout<<"Processing data, creating Hash table..."<<endl;
	vector<struct node*> hashTable = createHashTable(path,p,m);
	cout<<"Created Hash table Succesfully!"<<endl;
	// printHashTable(hashTable);

	// // Now take the user input
	string username,password;
	cout<<"Enter the username : ";
	cin >> username;
	cout<<"Entered username : "<<username<<endl;
	//Check if the username is available
	struct node* res = findUsername(username,hashTable,p,m);
	if(res==NULL){
		cout<<"The username is not available!"<<endl;
	}
	//Check on password, username exists
	else{
		cout<<"Enter the password : "<<endl;
		cin >> password;
		if(password!=res->password){						//Wrong password
			cout<<"Incorrect password!!"<<endl;
			// cout<<"Actual password : "<<res->password<<endl;
		}
		else{                                               //Correct password
			cout<<"Login Successfull!!"<<endl;
		}
	}

	
}
