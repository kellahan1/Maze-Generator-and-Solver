#ifndef BENs_NODE
#define BENs_NODE

#include <cstdlib>
#include <ostream>
#include <iostream>

using namespace std;


class Node
{
	public:

		// Constructors
		Node()
        {
            data = 0;
            visited = 0;
        	parent = NULL;
        	up = NULL;
        	right = NULL;
        	down = NULL;
            left = NULL;
        }

        //setters
        void set_position(int a)
        {
            position = a;
        }
        void set_visited(int a)
        {
            visited = a;
        }
        void set_data(int new_data)
        {
            data = new_data;
        }

        void set_parent(Node* new_parent)
        {
            parent = new_parent;
        }

        void set_up(Node* new_a)
        {
            up = new_a;
        }

        void set_right(Node* new_b)
        {
            right = new_b;
        }

        void set_down(Node* new_c)
        {
            down = new_c;
        }

        void set_left(Node* new_d)
        {
            left = new_d;
        }

        //getters
        int get_position()
        {
            return position;
        }
        int get_visited()
        {
            return visited;
        }
        int get_data()
        {
            //cout<<"pos"<<position<<"data"<<data<<endl;
            return data;
        }

        Node* get_parent()
        {
            return parent;
        }

        Node* get_up()
        {
            return up;
        }

        Node* get_right()
        {
            return right;
        }

        Node* get_down()
        {
            return down;
        }

        Node* get_left()
        {
            return left;
        }
    private:
        int position;//position on grid
        int visited;//node status
        int data;//boarder code
        Node* parent;//parent node
        Node* up;//upward node
        Node* right;// right node
        Node* down;//downward node
        Node* left;//left node
};

#endif
