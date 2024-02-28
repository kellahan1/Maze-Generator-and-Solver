#ifndef BENs_Maze
#define BENs_Maze

#include <cstdlib>
#include <ostream>
#include <iostream>
#include <stack>
#include "Node.h"

using namespace std;


class MazeSolver
{
public:
    MazeSolver(int Un, int Um)
    {
        n = Un;
        m = Um;
        MazeGrid = new Node[n*m];//create array of node pointers to hold grid that makes up maze

        for(int i = 1; i < (n*m)+1; i++)
        {
            MazeGrid[i].set_position(i);//set grid position for each position in array
        }
        ConnectGrid();//conect the nodes together as grid


    }






    //setters for boarder codes, start and finish
    void boarder(int a, int b)
    {
        MazeGrid[a].set_data(b);
    }
    void set_start(int a)
    {
        start = &MazeGrid[a];
    }
    void set_finish(int a)
    {
        finish = &MazeGrid[a];
    }

    Node* get_start()
    {
        return start;
    }
    string get_solution()
    {
        return solution;
    }
    int get_step()
    {
        return step;
    }

    //connects node into grid
    void ConnectGrid()//connect nodes in 2d array to be a traversable grid
    {
        for ( int i = 1; i < (n*m)+1; i++ )
        {
            if(MazeGrid[i].get_position() == 1) //if top left corner vertex 2 neighbours
            {
                //connect right and downward neighbours
                MazeGrid[i].set_right(&MazeGrid[i+1]);
                MazeGrid[i].set_down(&MazeGrid[i+m]);
            }
            else if(i == m)// if top right corner vertex 2 neighbours
            {
                //connect downward and left neighbours
                MazeGrid[i].set_down(&MazeGrid[i+m]);
                MazeGrid[i].set_left(&MazeGrid[i-1]);
            }
            else if(i == n*m)// if bottom right corner vertex 2 neighbours
            {
                //connect upward and left neighbours
                MazeGrid[i].set_up(&MazeGrid[i-m]);
                MazeGrid[i].set_left(&MazeGrid[i-1]);
            }
            else if(i == ((n-1)*m)+1)//if bottom left corner vertex 2 neighbours
            {
                //connect upward and right neighbours
                MazeGrid[i].set_up(&MazeGrid[i-m]);
                MazeGrid[i].set_right(&MazeGrid[i+1]);
            }
            else if(i > 1 && i < m)//if top edge vertex (not corner) 3 neighbours
            {
                //connect right left and downward neighbours
                MazeGrid[i].set_right(&MazeGrid[i+1]);
                MazeGrid[i].set_down(&MazeGrid[i+m]);
                MazeGrid[i].set_left(&MazeGrid[i-1]);
            }
            else if(i != m && i !=(m*n) && (i % m == 0))//if right edge vertex (not corner) 3 neighbours
            {
                //connect upward, downward and left neighbours
                MazeGrid[i].set_up(&MazeGrid[i-m]);
                MazeGrid[i].set_down(&MazeGrid[i+m]);
                MazeGrid[i].set_left(&MazeGrid[i-1]);
            }
            else if(i > ((n-1)*m)+1 && i < (n*m))//if bottom edge vertex (not corner) 3 neighbours
            {
                //connect uhpwar, right and left neighbours
                MazeGrid[i].set_up(&MazeGrid[i-m]);
                MazeGrid[i].set_right(&MazeGrid[i+1]);
                MazeGrid[i].set_left(&MazeGrid[i-1]);
            }
            else if(i != 1 && i != ((n-1)*m)+1 && ((i-1) % m) == 0)//if left edge vertex (not corner) 3 neighbours
            {
                //connect upward, right and downward neighbours
                MazeGrid[i].set_up(&MazeGrid[i-m]);
                MazeGrid[i].set_right(&MazeGrid[i+1]);
                MazeGrid[i].set_down(&MazeGrid[i+m]);
            }
            else //otherwise vertex is in from edge thus having 4 neighbours
            {

                //connect all neighbours
                MazeGrid[i].set_up(&MazeGrid[i-m]);
                MazeGrid[i].set_right(&MazeGrid[i+1]);
                MazeGrid[i].set_down(&MazeGrid[i+m]);
                MazeGrid[i].set_left(&MazeGrid[i-1]);
            }

        }
    }

    void DFSsolve(Node* a)
    {
        /*if(a->get_up()!=NULL)
        {
            cout <<a->get_position()<<"up data "<<a->get_up()->get_position()<<endl;

        }
        else
        {
            cout <<a->get_position()<<"up data NULL"<<endl;
        }
        if(a->get_right()!=NULL)
        {
            cout <<a->get_position()<<"right data "<<a->get_right()->get_position()<<endl;

        }
        else
        {
            cout <<a->get_position()<<"right data NULL"<<endl;
        }
        if(a->get_down()!=NULL)
        {
            cout <<a->get_position()<<"down data "<<a->get_down()->get_position()<<endl;

        }
        else
        {
            cout <<a->get_position()<<"down data NULL"<<endl;
        }
        if(a->get_left()!=NULL)
        {
            cout <<a->get_position()<<"left data "<<a->get_left()->get_position()<<endl;

        }
        else
        {
            cout <<a->get_position()<<"left data NULL"<<endl;
        }*/
        step++;
        int sec;
        a->set_visited(1);
        solution += to_string(a->get_position())+",";
        if(a == finish)
        {
            solution += ")";
            fin++;
            return;
        }

        int D = 1;//int that hold direction check counter
        while(D < 5)//t will incriment each time a dirention is checked/seardhed until all 4 are done
        {

            if(D == 1)//if R=1 check upward neighbour
            {

                if(a->get_up() != NULL && a->get_up()->get_visited() != 1 && (a->get_up()->get_data() == 2 ||a->get_up()->get_data() == 3))//if upward neighbour is not NULL AND not visited perform DFS on that node
                {
                    //cout<<"win D1"<<endl;
                    a->get_up()->set_parent(a);//set upward node parent to current node
                    DFSsolve(a->get_up());//recursive call on next node
                    D++;//incriment t
                    sec++;
                    if(sec > 0 && fin != 1)
                    {
                        step++;
                        solution += to_string(a->get_position())+",";
                    }
                }
                else//cant enter upward node
                {
                    D++;//incriment t
                }
            }
            else if(D == 2)//if R=2 check right neighbour
            {
                if(a->get_right() != NULL && a->get_right()->get_visited() != 1 && (a->get_data() == 1 ||a->get_data() == 3))//if right neighbour is not NULL AND not visited perform DFS on that node
                {
                    a->get_right()->set_parent(a);//set right node parent to current node
                    DFSsolve(a->get_right());//recursive call on next node
                    D++;//incriment t
                    sec++;
                    if(sec > 0 && fin != 1)
                    {
                        step++;
                        solution += to_string(a->get_position())+",";
                    }
                }
                else//cant enter upward node
                {
                    D++;//incriment t
                }
            }
            else if(D == 3)//if R=3 check downward neighbour
            {
                if(a->get_down() != NULL && a->get_down()->get_visited() != 1 && (a->get_data() ==  2||a->get_data() == 3))//if downward neighbour is not NULL AND not visited perform DFS on that node
                {
                    a->get_down()->set_parent(a);//set downward node parent to current node
                    DFSsolve(a->get_down());//recursive call on next node
                    D++;//incriment t
                    sec++;
                    if(sec > 0 && fin != 1)
                    {
                        step++;
                        solution += to_string(a->get_position())+",";
                    }
                }
                else//cant enter upward node
                {
                    D++;//incriment t
                }
            }
            else if(D == 4)//if R=4 check left neighbour
            {
                if(a->get_left() != NULL && a->get_left()->get_visited() != 1 && (a->get_left()->get_data() == 1 ||a->get_left()->get_data() == 3))//if left neighbour is not NULL AND not visited perform DFS on that node
                {
                    a->get_left()->set_parent(a);//set left node parent to current node
                    DFSsolve(a->get_left());//recursive call on next node
                    D++;//incriment t
                    sec++;
                    if(sec > 0 && fin != 1)
                    {
                        step++;
                        solution += to_string(a->get_position())+",";
                    }
                }
                else
                {
                    return;
                    D++;//incriment t
                }
            }
        }

        return;
    }

private:
    string solution = "(";
    Node* start;
    Node* finish;
    int step;
    int fin;//counter
    int n;//N = rows
    int m;//M = columns
    Node* MazeGrid;
    stack<Node*> stackA;
    stack<Node*> stackB;
    stack<Node*> stackC;
};
#endif
