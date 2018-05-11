/*==============================================================================
Zachary Hadjah                    April 27th 2018
Junior Year                       Data Structures/ Algorithm Analysis
  
This program reads a mathematical expression from the user and then checks whether
the expression is valid based on where the scope openers and closers are placed. 
 
 * Stack class - 
    This class will have public functions that can put in and take out items  
    characters inside the stack itself. It has a Node pointer that will point to
    the next node in the stack
 * void describeProgram() - 
    Brief description of the program itself 
 * void read_expression(char expression[80])
    Will read the user's mathematical expression and will determine whether or 
    not the it is valid. 
 * void check_expression(char expression[80], bool& valid) - 
    Accepts the expression that was entered and reports
    on whether it was valid or invalid, based upon the value of the
    boolean, valid.  It will show the expression and then report whether it is 
    valid or not valid.
 * void report_result(char expression[80], bool valid) - 
    This function is to accept the expression entered in by the user along with 
    the value of valid that indicates whether the expression was valid or not. 
    It is then to send the expression to the screen and to an external file, 
    “scope.txt”, along with a message that indicates whether the expression is 
    valid or invalid in its use of scope openers and closers.
 * bool another()-
    This program describes the program to the user.
=============================================================================*/
#include<iostream>
#include<cctype>
#include<fstream>
#include<cstdlib>
#include<istream>
using namespace std;

struct NodeType;
typedef NodeType* Nodeptr;
typedef char StackType;

class Stack
{
    public:
           bool IsEmpty()const;
           bool IsFull() const;
           void Push(StackType newItem);
           StackType StackTop() const;
           void Pop();
           Stack();
           ~Stack();

    private:
            Nodeptr top;
};

struct NodeType
{
    StackType item;
    Nodeptr link;
};

// Function declarations 
void describeProgram();
void read_expression(char expression[80]);
void check_expression(char expression[80], bool& valid); 
void report_result(char expression[80], bool valid);
bool another();

int main()
{
	char expression[80];  //Expression to be read from the keyboard
	bool valid;           //true id expression is valid, false otherwise  
	
    do
    {
        read_expression(expression);
        check_expression(expression, valid);
        report_result(expression, valid);
    }while(another());

	system("PAUSE");
	return 0;
}


Stack::Stack()
{
   top = NULL;
}

Stack::~Stack()
{
   Nodeptr p;
   while(top != NULL)
   {
      p = top;
      top = top->link;
      delete p;
   };
   cout<<"Stack has been reallocated to the heap."<<endl;
   return;
}

bool Stack::IsEmpty() const
{
   return (top == NULL);
}

bool Stack::IsFull() const
{
	int* p;
   return (!(p = new int));
}

void Stack::Push(StackType newItem)
{
   Nodeptr q;
   q = new NodeType;
   q->item = newItem;
   q->link = top;
   top = q;
   return;
}

StackType Stack::StackTop() const
{
   return top->item;
}

void Stack::Pop()
{
   Nodeptr p;
   p = top;
   top = top->link;
   delete p;
   return;
}

void describeProgram()
{ 
    cout << "This program prompts the user for a mathematical expression. After,"
            "the program will check to see whether the expression is valid or "
            "invalid. After its validity is confirmed or denied, the program will"
            " let the user know. The user will be asked if they want to repeat "
            "the program.";     
}

void read_expression(char expression[80])
{
    cout << "Enter your mathematical expression: \n";
    cin.ignore();
    cin.getline(expression, 80);
    
    while(expression == NULL)
    {
        cout << "Please enter a valid expression: \n";
        cin.ignore();        
        cin.getline( expression, 80);
    }
    return;
}

void check_expression(char expression[80], bool& valid)
{
    Stack symbStack;  
    char symbol, top_symb;  
    int i = 0; 

    valid = true;  
    symbol = expression[i];
    
    while(symbol != '\0') 
    {
        if( symbol == '{' || symbol == '[' || symbol == '(' )
        {
            symbStack.Push(symbol);
        }

        else if( symbol == '}' || symbol == ']' || symbol == ')' )
        {
            if(symbStack.IsEmpty())
            {
                cout << "Expression is invalid! \n";
                valid = false;
                return;
            }

            else
            {
                top_symb = symbStack.StackTop();
                symbStack.Pop();
            }    

            if(  (top_symb != '(' && symbol == ')') ||  
                 (top_symb != '[' && symbol == ']') ||
                 (top_symb != '{' && symbol == '}')  )
            {
                valid = false;
            }
        }
        i++;  
        symbol = expression[i]; 
    }
    
    if(!(symbStack.IsEmpty()))
        valid = false;	
    return;     
}

void report_result(char expression[80], bool valid)
{
    ofstream toFile;
    toFile.open("scope.txt",ios::out);
    
    if(!valid)
    {
        cout << "\n The expression: " << expression << " was an invalid expression \n";
        toFile << "\n The expression: " << expression << " was an invalid expression \n";
    }
    
    else
    {
        cout << "\n The expression: " << expression << " was a valid expression \n";
        toFile << "\n The expression: " << expression << " was a valid expression \n";
    }
    toFile.close(); 
    
    return;
}


bool another()
{
    char response;
    cout << "\n Do you wish to run this program again (Y or N) \n";
    cin >> response;     
        
    while((response!= 'N') && (response!= 'Y') && 
          (response!= 'y') && (response!= 'n'))
    {
        cout << "Please enter a valid response";
        cin >> response;
    }
    
    response = toupper(response);
    
    return response == 'Y';
}


