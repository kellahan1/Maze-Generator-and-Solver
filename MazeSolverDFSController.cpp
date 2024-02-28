#ifndef BENs_Solver
#define BENs_Solver
#include <iostream>
#include <fstream>
#include <stack>
#include <cstdlib>
#include "MazeSolver.h"
using namespace std;



int main(int argc, char *argv[])
{
    clock_t t;
    t = clock();
    string filename = argv[1]; //store passed in filename in string
    string data;//string to store file data

    ifstream mazefile(filename + ".txt");//open file
    getline(mazefile, data);//put file data into data string var

    mazefile.close();

    //setting n, m;
    string temp;
    int i = 0;//dimensions of maze

    //take first chars before ',' and store in temp then cast to in and store in n
    while(data.at(i) != ',')
    {
        temp += data.at(i);
        i++;
    }
    int n = stoi(temp);
    cout<<n<<endl;
    temp = "";//reset temp
    i++;//step over comma (',')

    //take next chars before ':' and store in m
    while(data.at(i) != ':')
    {
        temp += data.at(i);
        i++;
    }
    int m = stoi(temp);
    cout<<m<<endl;
    temp = "";
    i++;

    //start MazeSolver
    MazeSolver* maze1 = new MazeSolver(n, m);

    //take next chars before next ':' and store in start
    while(data.at(i) != ':')
    {
        temp += data.at(i);
        i++;
    }
    int start = stoi(temp);
    maze1->set_start(start);//set maze start point
    cout<<"start"<<start<<endl;
    temp = "";
    i++;
    //take next chars before next ':' and store in finish
    while(data.at(i) != ':')
    {
        temp += data.at(i);
        i++;
    }
    int finish = stoi(temp);
    maze1->set_finish(finish);//set maze finish point
    cout<<"finishh"<<finish<<endl;
    temp = "";
    i++;



    //pass in data for boarders
    for(int j = 1; j < n*m+1; j++)
    {
        temp = data.at(i);
        maze1->boarder(j, stoi(temp));
        i++;
        temp = "";
    }
    maze1->DFSsolve(maze1->get_start());
    cout << maze1->get_solution() << endl;

    cout << "Time elapsed: " << (clock() - t)<< endl << maze1->get_step() << "steps to the finish" << endl; // prints elapsed time.
    return 0;
};


#endif
