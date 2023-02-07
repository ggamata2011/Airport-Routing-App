// Guiller Gamata
//BFS Airport Routing

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <queue>

using namespace std;
void FillCity(string cities[],int &size);
void FillList(string cities[],vector<int> alists[],int size);
void SearchPath(vector<int> alists[], int size, int start, int dest,string cities[]);
void print(int parent[], int size, int start, int end,string cities[]);

int main()
{
int size = 0;;

//Array of strings used to store all city
string city[1000];

//a list is used as an adjacency list from a certain city
vector<int> alists[1000];
string input = "blank";
FillCity(city,size);
FillList(city,alists,size);
cout << "Finished Reading Cities from file";
//used for comparing city and state
string compcity;
string State;
//will hold index for StartingCity and Destination City
int StartingCity;
int DestinationCity;
//holds matches for Starting ot DestinationCity
vector<int> searchlist;
bool match;


while(input != "quit")
{



do{


cout << "\n\nEnter a city name or 'quit' to quit" << endl;
cout << "----------" << endl;
cout << "Starting City:";
cin.clear();
getline(cin,input);

match = true;
if(input != "quit")
{

//looks for cities/countries containing name and putting it in search
for(int i = 0; i < size; i++)
{
   compcity = city[i];
   compcity = compcity.substr(0,input.length());
   State = city[i];
   //pick off State or country
   for(int j = 0; j < State.length();j++)
   {
       if(State[j] == ',')
       {
           //picks up State or country by itself
           State = State.substr(j+2,State.length());
           //picks off part of it so we can compare it with input
           State = State.substr(0,input.length());
       }
   }

   //increments the array location of destination
   if(input == compcity || input == State)
   {
     searchlist.push_back(i);
   }
}
//end adding searchlist

//looks for countries containing name
int choice = 0;

if(searchlist.size() != 0)
{
cout << "\nAll matching Names:\n\n";


for(int i = 0; i < searchlist.size();i++)
{
   cout << "\n" << i << " : " << city[searchlist[i]] << endl;
}

do
{
  cout << "\n Pick A City: ";
  cin >> choice;
  cin.ignore();
  StartingCity = searchlist[choice];

}
while(choice < 0 || choice >= searchlist.size());
}
else
{
    cout << "\n\nNo Match, Try again\n";
    match = false;

}

}
}while(match == false);

//Starting city Destination Selected, can clear searchlist and compcity and state
searchlist.clear();
//======================================
//======================================

if(input != "quit")
{
do{
cout << "\n\nEnter a Destination City" << endl;
cout << "----------" << endl;
cout << "Destination City:";
//cin.ignore();
cin.clear();
getline(cin,input);
match = true;
//looks for cities/countries containing name and putting it in search
for(int i = 0; i < size; i++)
{
   compcity = city[i];
   compcity = compcity.substr(0,input.length());
   State = city[i];

   //pick off State or country
   for(int j = 0; j < State.length();j++)
   {
       if(State[j] == ',')
       {
           //picks up State or country by itself
           State = State.substr(j+2,State.length());
           //picks off part of it so we can compare it with input
           State = State.substr(0,input.length());
       }

   }
   //increments the array location of destination
   if(input == compcity || input == State)
   {
     searchlist.push_back(i);
   }
}
//end adding searchlist
int choice = 0;
if(searchlist.size()!= 0)
{
//displays all matching names
cout << "\nAll matching Names:\n\n";
for(int i = 0; i < searchlist.size();i++)
{
   cout << "\n" << i << " : " << city[searchlist[i]] << endl;
}
//city selection
do
{
  cout << "\n Pick A City: ";
  cin >> choice;
  DestinationCity = searchlist[choice];

}
while(choice < 0 || choice >= searchlist.size());

}
else
{
    cout << "\n\nNo Match, Try again\n";
    match = false;
}

}while(match == false);
// end destination selection
//===========================================
//Display Results here =========
cout << "\n\nRoute From : \n\n" << city[StartingCity] << ": to :" << city[DestinationCity] << endl;
cout << "\n\n";
SearchPath(alists,size,StartingCity,DestinationCity,city);


searchlist.clear();
cin.ignore();
}


}
//end while loop

cout << "\nBye!";
return 0;

}

//PRINTS OUT PATH
void print(int parent[], int size, int start, int end,string cities[]) {
	if (end != start)
        {
		print(parent, size, start, parent[end],cities);
	    }
	cout << "->" << cities[end];
}


//BREADTH FIRST SEARCH

//uses BFS to parse adjacency list to find the shortest path to any Node/Destination from current Node/Destination
void SearchPath(vector<int> alists[], int size, int start, int dest,string cities[])
{
    int * parent = new int[size];
    for (int i = 0; i< size; i++)
    {
      parent[i] = -1;
    }
    parent[start] = start;
    queue<int> q;
    q.push(start);
    bool found = false;
    while (!q.empty() && !found)
        {
        int v = q.front();
        q.pop();
        if (v == dest)
            found = true;
        else for (int i = 0; i < alists[v].size(); i++)
        {
            int w = alists[v][i];
            if (parent[w] == -1)
            {
                parent[w] = v;
                q.push(w);
            }
        }
    }
    if (found)
    {
        print(parent,size,start,dest,cities);
    }
    else
       {
        cout << "No Path Found";
       }
    cout << endl;
    delete [] parent;
}

//Function just to fill the city list from a text file
void FillCity(string cities[],int &size)
{
ifstream in;
in.open("connections.txt");
string line,full;
string spec;

//get first line
getline(in,line);

while(in)
{

//cuts out specifier which is either "To", "From", or a blank " ";
//cout << line << endl;
spec = line.substr(0,5);

if(spec == "From:")
{
    //size++;
    //cout << spec << endl;
    full = line.substr(7,line.length());
    //cout << full << ";" << endl;
    cities[size++] = full;
}

//proceed to next line
getline(in,line);

}

in.close();

//anything beyond the 125 cities, are all cities that can only receive
in.open("connections.txt");

//get first line
getline(in,line);

//-----------------------------------
while(in)
{
// only getting name of cities no specifier needed
full = line.substr(7,line.length());
bool contains = false;

//search through cities
for(int i = 0; i < size;i++)
{
 if(full == cities[i])
 {
     contains = true;
 }

}
//-----------------------------------
//city is not on list, add at end of list
if(contains == false)
{
cities[size++] = full;
}

//proceed to next line
getline(in,line);
}

in.close();
}

//Fills the adjacency list per city, keeping track the number of adjacent cities
void FillList(string cities[],vector<int> alist[],int size)
{
ifstream in;
in.open("connections.txt");
string line,full;
int Findex = 0;
string spec;

//get first line
getline(in,line);

while(in)
{
spec = line.substr(0,5);
full = line.substr(7,line.length());

//searched through all the From cities and keeps an index of
if(spec == "From:")
{

   for(int i = 0;i < 125;i++)
   {
      if(full == cities[i])
      {
          Findex = i;
      }
   }

}

if(spec == "To  :" || spec == "     ")
{


//pushes onto alist the destination while keeping track what its connected to
  for(int i = 0; i < size;i++)
  {
    if(full == cities[i])
    {
        alist[Findex].push_back(i);
    }

  }

}
//go to next line
getline(in,line);
}

in.close();




}
