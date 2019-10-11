/*
	First name	Tianyi
	Last name		Peng
	Student ID	01382700
	Username		tp17 (e.g. aaa123)
*/

//IMPORTANT: before submitting your source code, please make sure to comment your main function (needed for automated testing)


#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <ctime>
#include <cstdlib>

#define ASIZE 128
// do not use using namespace std

// do not alter the struct declaration
struct node {
	char id;
	node* north;
	node* south;
	node* east;
	node* west;
};

// do not alter the typedef
typedef node* nodeptr;

/////////////////////////////////////////
// Functions declarations (prototypes) //
/////////////////////////////////////////

// do not alter these functions declarations

void build_basic_maze(nodeptr& start, nodeptr& finish);
// builds the basic maze displayed in page 1

nodeptr traverse_maze(const nodeptr& start, const std::string& path);
// traverses the maze using a predefined path

void solve_interactively(const nodeptr& start, const nodeptr& finish, std::string& path);
// allows the user to solve the maze interactively

nodeptr random_walk(const nodeptr& start, const nodeptr& finish, std::string& path);
// simulates a random walk in the maze

void solve_queue(const nodeptr& start, const nodeptr& finish, std::string& path);
// an improvement of the random walk: solves the maze using a queue to store the unvisited neighbours of the current node

void solve_stack(const nodeptr& start, const nodeptr& finish, std::string& path);
// an improvement of the random walk: solves the maze using a stack to store the unvisited neighbours of the current node


// you can define and add use additional functions if you might need to

///////////////////
// ain function //
//////////////////

//IPORTANT (Reminder): before submitting your source code, please make sure to comment your main function (needed for automated testing)
int main() {
	nodeptr start = NULL;
  nodeptr finish = NULL;
	nodeptr tmp;
	std::string input;
  build_basic_maze(start, finish);
	nodeptr stop;

  std::cout<<"start = "<< start->id << std::endl;
  std::cout<<"finish = "<< finish->id << std::endl;

//	std::cout<<"Enter the path you wish to take: "<<std::endl;
//		std::cin>>input;

//	stop = traverse_maze(start, input);

//  std::cout<<"The path takes you to node: "<<stop->id<<std::endl;

  solve_interactively(start, finish, input);

//	solve_queue(start, finish, input);
//	tmp = random_walk(start, finish, input);



//	std::cout<<input<<std::endl;



  	return 0;
}





/////////////////////////////////////////////
// Functions definitions (implementations) //
/////////////////////////////////////////////

// YOUR CODE HERE
void build_basic_maze(nodeptr& start, nodeptr& finish){
    nodeptr tmpA = new node;
    tmpA->id = 'A';

    nodeptr tmpB = new node;
    tmpB->id = 'B';

    nodeptr tmpC = new node;
    tmpC->id = 'C';

    nodeptr tmpD = new node;
    tmpD->id = 'D';

    nodeptr tmpE = new node;
    tmpE->id = 'E';

    nodeptr tmpF = new node;
    tmpF->id = 'F';

    nodeptr tmpG = new node;
    tmpG->id = 'G';

    nodeptr tmpH = new node;
    tmpH->id = 'H';

    nodeptr tmpI = new node;
    tmpI->id = 'I';

    nodeptr tmpJ = new node;
    tmpJ->id = 'J';

    nodeptr tmpK = new node;
    tmpK->id = 'K';

    nodeptr tmpL = new node;
    tmpL->id = 'L';

    tmpA->north = tmpA;    tmpA->east = tmpB;    tmpA->south = tmpE;   tmpA->west = tmpA;

    tmpE->north = tmpA;    tmpE->east = tmpE;    tmpE->south = tmpI;   tmpE->west = tmpE;
    tmpI->north = tmpE;     tmpI->east = tmpJ;    tmpI->south = tmpI;   tmpI->west = tmpI;
    tmpJ->north = tmpJ;     tmpJ->east = tmpJ;    tmpJ->south = tmpJ;   tmpJ->west = tmpI;

    tmpB->north = tmpB;     tmpB->east = tmpB;    tmpB->south = tmpF;   tmpB->west = tmpA;
    tmpF->north = tmpB;     tmpF->east = tmpG;    tmpF->south = tmpF;   tmpF->west = tmpF;
    tmpG->north = tmpC;     tmpG->east = tmpH;    tmpG->south = tmpK;   tmpG->west = tmpF;

    tmpC->north = tmpC;     tmpC->east = tmpD;    tmpC->south = tmpG;   tmpC->west = tmpC;
    tmpD->north = tmpD;     tmpD->east = tmpD;    tmpD->south = tmpD;   tmpD->west = tmpC;

    tmpH->north = tmpH;     tmpH->east = tmpH;    tmpH->south = tmpL;   tmpH->west = tmpG;
    tmpK->north = tmpG;     tmpK->east = tmpK;    tmpK->south = tmpK;   tmpK->west = tmpK;

    tmpL->north = tmpH;     tmpL->east = tmpL;    tmpL->south = tmpL;   tmpL->west = tmpL;

		start = tmpA;       finish = tmpL;
}

nodeptr traverse_maze(const nodeptr& start, const std::string& path){
	nodeptr tmp = start;
	for(int i = 0; i<path.length(); i++){
		if (path[i] == 'N' ) {
		tmp = tmp->north;
	  }
	  if (path[i] == 'E') {
	      tmp = tmp->east;

	  }
	  if (path[i] == 'S') {
	      tmp = tmp->south;

	  }
	  if (path[i] == 'W') {
	      tmp = tmp->west;
	  }
	}
	return tmp;
}

void solve_interactively(const nodeptr& start, const nodeptr& finish, std::string& path){

	char input;
	nodeptr tmp = start;
	path = " "; //reset path

	while(tmp != finish){
		std::cout<<"You are in room "<<tmp->id<<" of the maze."<<std::endl;
		std::cout<<"You can go: ";
    if(tmp->north != tmp){
      std::cout<<"(N)orth, ";
    }
    if(tmp->east != tmp){
      std::cout<<"(E)ast, ";
    }
    if(tmp->south != tmp){
      std::cout<<"(S)outh, ";
    }
    if(tmp->west != tmp){
      std::cout<<"(W)est, ";
    }
		std::cout<<"or (Q)uit.";
		std::cout<<std::endl;

		std::cin>>input;

    if(input == 'Q'){
			std::cout<<"you quit!"<<std::endl;
      return;
    }

//make sure any other inputs do not effect
		if((input == 'N')||(input == 'E')||(input == 'S')||(input == 'W')){
			path += input;
		}

    tmp = traverse_maze(start, path);
	}
  std::cout<<"Congratulations, you reached the finish!"<<std::endl;
}


nodeptr random_walk(const nodeptr& start, const nodeptr& finish, std::string& path){
    std::srand(std::time(NULL));
    nodeptr tmp = start;
    path = ""; //reset path
    int limit = 50;                 // set limit for random_walk
    for(int i = 0; i < limit; i++) {
        std::string availabledir = "";

        if (tmp->north != tmp) {
            availabledir.append("N");
        }
        if (tmp->south != tmp) {
            availabledir.append("S");
        }
        if (tmp->east != tmp) {
            availabledir.append("E");
        }
        if (tmp->west != tmp) {
            availabledir.append("W");
        }

        path = path + availabledir[rand()%availabledir.length()];
        tmp = traverse_maze(start, path);
        if (tmp == finish) {
            std::cout<<"The random walk was finished within the limit of "<<limit<<" steps!"<< std::endl;
            std::cout<<"It is solved in " << i+1 <<std::endl;

            return tmp;
        }
    }
        std::cout<<"The random walk could not be finished in "<< limit << " steps!"<<std::endl;

        return tmp;
}

void solve_queue(const nodeptr& start, const nodeptr& finish, std::string& path){
    std::queue<nodeptr> unvisited, visited;
    nodeptr tmp = start;
    path = path + tmp->id;
    visited.push(tmp);

    if(tmp != finish && path[path.length()-1] != finish->id){

        if (tmp->north != tmp && path.find((tmp->north)->id) == std::string::npos ) {
            unvisited.push(tmp->north);
        }
        if (tmp->south != tmp && path.find((tmp->south)->id) == std::string::npos ) {
            unvisited.push(tmp->south);
        }
        if (tmp->east != tmp && path.find((tmp->east)->id) == std::string::npos ) {
            unvisited.push(tmp->east);
        }
        if (tmp->west != tmp && path.find((tmp->west)->id) == std::string::npos ) {
            unvisited.push(tmp->west);
        }

        while (!unvisited.empty() && path.find(finish->id) == std::string::npos ) {
            tmp = unvisited.front();
            unvisited.pop();

            solve_queue(tmp, finish, path); // recursion starts

            if (tmp->id == path[path.length()-1] && tmp != finish) { // check if dead end
                tmp = visited.front();
                path = path + tmp->id;
            }
        }
    }
    nodeptr current = start;

//following code is turing path from storing id to directions
    if(current->id == path[0]){
        std::cout<<"Node ID travelled: " << path << std::endl;
        for(int i = 0; path[path.size()-1] == finish->id && i<path.size() ; i++){

            if(((current->north)->id) == path[i+1]){
                path[i]='N';
                current=current->north;
            }
            else if(((current->south)->id) == path[i+1]){
                path[i]='S';
                current=current->south;
            }
            else if(((current->east)->id) == path[i+1]){
                path[i]='E';
                current=current->east;
            }
            else if(((current->west)->id) == path[i+1]){
                path[i]='W';
                current=current->west;
            }

        }
        path.erase(path.size()-1);
    }
}
// similar to queue
void solve_stack(const nodeptr& start, const nodeptr& finish, std::string& path){
    std::stack<nodeptr> unvisited, visited;
    nodeptr tmp = start;
    path = path + tmp->id;
    visited.push(tmp);

    if(tmp != finish && path[path.length()-1] != finish->id){

        if (tmp->north != tmp && path.find((tmp->north)->id) == std::string::npos ) {
            unvisited.push(tmp->north);
        }
        if (tmp->south != tmp && path.find((tmp->south)->id) == std::string::npos ) {
            unvisited.push(tmp->south);
        }
        if (tmp->east != tmp && path.find((tmp->east)->id) == std::string::npos ) {
            unvisited.push(tmp->east);
        }
        if (tmp->west != tmp && path.find((tmp->west)->id) == std::string::npos ) {
            unvisited.push(tmp->west);
        }

        while (!unvisited.empty() && path.find(finish->id) == std::string::npos ) {
            tmp = unvisited.top();
            unvisited.pop();

            solve_stack(tmp, finish, path);

            if (tmp->id == path[path.length()-1] && tmp != finish) {
                tmp = visited.top();
                path = path + tmp->id;
            }
        }
    }

    nodeptr current = start;

    if(current->id == path[0]){
        std::cout<<"Node ID travelled: " << path << std::endl;
        for(int i = 0; path[path.size()-1] == finish->id && i<path.size() ; i++){

            if(((current->north)->id) == path[i+1]){
                path[i]='N';
                current=current->north;
            }
            else if(((current->south)->id) == path[i+1]){
                path[i]='S';
                current=current->south;
            }
            else if(((current->east)->id) == path[i+1]){
                path[i]='E';
                current=current->east;
            }
            else if(((current->west)->id) == path[i+1]){
                path[i]='W';
                current=current->west;
            }

        }
        path.erase(path.size()-1);
    }
}
