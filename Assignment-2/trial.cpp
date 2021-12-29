// Including essential libraries
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;
// It is observed keeping load factor close to 0.75 generally yields better performance
// Here n = 20,000 and resulting m = n/alpha = 26.667*10^3, so we can take 27,000

// Custom data type for defining the node in the hashmap
struct node
{
	struct node* link = NULL;
	string username;
	string password;
};


// Creation of node
struct node* createNode(string username, string password){
	struct node* temp = new node;
	temp->username = username;
	temp->password = password;
	temp->link = NULL;
	return temp;
}

//Compute the hash value of the string
int computeHash(string username,int p, int m){
	int value = 0,w = 1,sum=0;
	for(int i=0;i<username.length();i++){
		sum = ((username[i]-'0')*w) % m;
		value = (value + sum)%m;
		w *= p;
	}
	value = (value+m)%m;
	return value;
}

// Insert into the hash table
void insertToHash(struct node* temp,vector<struct node*>& hashTable, int hashValue){
	if(hashTable[hashValue]==NULL){
		hashTable[hashValue] = temp;
	}
	else{
		temp->link = hashTable[hashValue];
		hashTable[hashValue] = temp;
	}
}

//read function
void readfn(const string& path,int p,int m){
	fstream fin;
	fin.open(path, ios::in);
	string line,username_t,password_t;
	string word;
	struct node* tempNode=NULL;
	int counter=0,hashValue=0;
	vector<struct node*> hashTable(m,NULL);
	if(fin.is_open()){
		while(getline(fin,line,'\n')){
			cout<<line<<endl;
			int pos = line.find(','),end=line.find('\n');
			username_t = line.substr(0,pos);
			password_t = line.substr(pos+1,end);
			tempNode = createNode(username_t,password_t);
			hashValue = computeHash(username_t,p,m);
			insertToHash(tempNode,hashTable,hashValue);
			cout<<hashTable[hashValue]->username<<"  "<<hashTable[hashValue]->password<<endl;
			counter++;
		}
		cout<<"counter : "<<counter<<endl;
	}
	else{
		cout<<"Check the csv file location, its not there where you want."<<endl;
		exit(0);
	}
}

// Creating a hash table
vector<struct node*> createHashTable(const string& path, int p, int m){
	vector<struct node*> hashTable(m,NULL);
	fstream fin;
	fin.open(path, ios::in);
	string line,username_t,password_t;
	string word;
	struct node* tempNode=NULL;
	int hashValue = 0;
	if(fin.is_open()){
		while(getline(fin,line,'\n')){
			int pos = line.find(','),end=line.find('\n');
			username_t = line.substr(0,pos);
			password_t = line.substr(pos+1,end);
			tempNode = createNode(username_t,password_t);
			hashValue = computeHash(username_t,p,m);
			insertToHash(tempNode,hashTable,hashValue);
		}
	}
	else{
		cout<<"Check the csv file location, its not there where you want."<<endl;
		exit(0);
	}
	return hashTable;

}

void printHashTable(vector<struct node*>& hashTable){
	struct node* temp = NULL;
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
	int hashVal = computeHash(username,p,m);
	struct node* search = hashTable[hashVal];
	while(search!=NULL){
		if(search->username==username){
			cout<<"Found -> "<<search->username<< " : "<<search->password<<endl;
			break;
		}
		else{
			search = search->link;
		}
	}
	if(search==NULL){
		cout<<"Not found"<<endl;
	}
	return search;
}

int main(void){
	// Ready your hash table
	string path = "userInfo.csv";

	int p = 11, m = 10;
	cout<<"Processing data, creating Hash table..."<<endl;
	vector<struct node*> hashTable = createHashTable(path,p,m);
	cout<<"Created Hash table Succesfully!"<<endl;
	// printHashTable(hashTable);
	
	string uname = "lifeincolorft";
	struct node* s = findUsername(uname,hashTable,p,m);
	// struct node* t = createNode("")

	// // Now take the user input
	string username,password;
	cout<<"Enter the username : "<<endl;
	cin >> username;
	cout<<"Entered username : "<<username<<endl;
	//Check if the username is available
	struct node* res = findUsername(username,hashTable,p,m);
	if(res==NULL){
		cout<<"The username is not available!"<<endl;
	}
	else{
		cout<<"Enter the password : "<<endl;
		cin >> password;
		if(password!=res->password){
			cout<<"Incorrect password!!"<<endl;
			cout<<"Actual password : "<<res->password<<endl;
			cout<<password.length()<<" "<<res->password.length()<<endl;	
			cout<<"Last char : "<<res->password[res->password.length()-1]<<endl;
		}
		else{
			cout<<"Login Successfull!!"<<endl;
		}
	}

	
}
