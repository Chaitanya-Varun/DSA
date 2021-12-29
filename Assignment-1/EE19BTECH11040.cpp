// Including essential libraries
#include <bits/stdc++.h>
#include <fstream>
using namespace std;

#define MAX 500				//Max Capacity of the stack
double arr[MAX];            //Stack as an array
int top=-1;				    //Top Variable

//Function for checking the stack is empty
bool isEmpty(){
	if(top==-1){			//No element is filled in the stack
		return true;
	}
	return false;
}
//Function to print the stack
void printStack(){
	if(!isEmpty()){			//Checking the stack is empty
		cout<<"Stack : ";
		for(int i=0;i<=top;i++){
			cout<<arr[i]<<" ";
		}
		cout<<""<<endl;
	}
	else
		cout<<"Stack Empty"<<endl;
}
//Function to return the top most element in the stack
double topElement(){
	if(!isEmpty()){			//the stack is not empty
		return arr[top];	//return the top
	}
	else{
		cout<<"Stack is Empty for showing top element"<<endl;
		return -1;
	}
}
//Function for performing the pop operation
double pop(){		
	if(!isEmpty()){			//The stack is not empty
		top -= 1;           //Decrementing the top by 1
		printStack();		//Printing the stack
		return arr[top+1];	//Return the popped element
	}
	else{
		cout<<"Stack is Empty for pop"<<endl;
		return -1;
	}
}
//Function for performing the push operation
int push(double val){		
	if(top+1>=MAX){			//Check for max capacity of stack
		cout<<"Max Capacity of Stack Reached"<<endl;
		return -1;
	}
	top+=1;					//Incrementing the top by 1
	arr[top]=val;			//Writing down the new element
	printStack();			//Printing the stack
	return 0;
}
//Function for performing operations
double operate(double a, double b, char op){
	double res=0;			//Initiating the result variable double
	cout<<"Operaters "<<a<<" "<<b<<" "<<op<<endl;
	switch(op){
		case '+':			//Addition
			res = (a+b);break;
		case '-':			//Subtraction
			res=(b-a);break;
		case '*':			//Multiplication
			res= (a*b);break;
		case '/':			//Division
			if(a!=0){
				res=(b/a);break;
			}
	}
	cout<<"Operation Result : "<<res<<endl;
	return res;				//Return result
}
//Function for evaluating a postfix expression in form of a string
int evaluatePostfix(string exp){
	int num;				//var for storing the read number
	char op;				//var for storing the read character
	int length = exp.size();//Length of the arithmetic expression
	top=-1;					//Initializing the stack variable top
	//Traversing the expression
	for(int i=0;i<length;i++){
		char temp = exp[i];								//Reading the character
		cout<<"Char read :"<<temp<<endl;				
		if(temp==','||(temp=='\n')||temp==' ')continue; //Redundant characters
		if(isdigit(temp)){								//Checking for the read character is a number
			num = 0;									//Iniatialising as zero
			while(exp[i]!=','&&exp[i]!='\n'){			//Obtaining the integer from the string
				// cout<<num<<" Before "<<exp[j]<<endl;
				num = num*10 + (int)(exp[i]-'0');		//Adding digits according to their decimal weights
				// cout<<"After : "<<num<<endl;
				i++;
			};
			// cout<<exp[i]<<endl;
			push((double)num);							//Pushng onto the stack

		}
		else if(temp == '-'&& i<length-2 && isdigit(exp[i+1])){
			i++;										//Check for a negative number
			num=0;										//Obtaining the integer
			while(exp[i]!=','&&exp[i]!='\n'){
				num = num*10 + (int)(exp[i]-'0');	
				i++;
			}
			num*=-1; 								   //Making the read integer negative 
			push((double)num);
		}
		else if(temp=='+'||temp=='-'||temp=='*'||temp=='/'){	//Read character is operator
			double a = pop();						   //Popping the first element from stack
			double b = pop();						   //Popping the second element from stack
			if(temp=='/'&&a==0){                       //Check for division by zero
				cout<<"Invalid Expression - Division by Zero"<<endl;
				exit(1);
			}
			cout<<"Operation : "<<temp<<endl;
			double res = operate(a,b,temp);				//Operating
			push(res);									//Pushing the resul onto the stack
		}
	}
	//Check the final result
	if(top!=0){											//Only the result must be in stack for 
		cout<<"Invalid Postfix Expression"<<endl;		//valid expression
		return -1;
	}
	else{
		double result = pop();							//Print the result
		cout<<"The given Postfix Expression evaluates to "<<fixed<<setprecision(6)<<result<<endl;
		return result;
	}
	return 0;
}

int main(){
	string exp = "4,5,6,*,+,\n";
	cout<<"Postfix Expression : "<<exp<<endl;
	double result = evaluatePostfix(exp);
	return 0;
}