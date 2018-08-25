#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cfloat>
#include <cstring>
#include <vector>
#include <iomanip>
#include <list>

using namespace std;

class Grid
{
public:
    // constructor
    Grid()
    {
        _d = DBL_MAX; // #include<cfloat>
        _pi = NULL;
        _isPath = false;
        _isDone = false;  
    }

    // public member functions
    int getX() { return _x; }
    int getY() { return _y; }
    bool isPath() { return _isPath; }
    bool isDone() { return _isDone; }
    double getD() { return _d; }
    Grid *getPi() { return _pi; }

    void setX(int x) { _x = x; }
    void setY(int y) { _y = y; }
    void setPath() { _isPath = true; }
    void setDone() { _isDone = true; }
    void setD(double d) { _d = d; }
    void setPi(Grid *pi) { _pi = pi; }

private:
    // data members
    int _x, _y; // x & y coordinates
    bool _isPath;
    bool _isDone; 
    double _d;
    Grid *_pi;
};

// global variable
vector< vector<Grid> > map;
vector< vector<double> > horizontalEdge;
vector< vector<double> > verticalEdge;
list<Grid *> priorityQ;

// functions
void printMap();
void printEdgeWeights();
void relax(Grid *u, Grid *v, double w);
Grid *extractMin();

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        cout << "Usage: ./bfs [input_case]" << endl;
        system("pause");
        exit(EXIT_FAILURE);
    }

    /* parse the input file */
    fstream inFile;
    inFile.open(argv[1], fstream::in);
    if(!inFile.is_open())
    {
        cout << "The input file is not opened!" << endl;
        system("pause");
        exit(EXIT_FAILURE);
    }

    char buffer[100];
    int boundaryX, boundaryY;
    int sourceX, sourceY;
    int targetX, targetY;

    while(inFile >> buffer)
    {
        if(strcmp(buffer, "boundary") == 0)
        {
            inFile >> buffer;
            boundaryX = atoi(buffer);
            inFile >> buffer;
            boundaryY = atoi(buffer);
        }
        else if(strcmp(buffer, "source") == 0)
        {
            inFile >> buffer;
            sourceX = atoi(buffer);
            inFile >> buffer;
            sourceY = atoi(buffer);
        }
        else if(strcmp(buffer, "target") == 0)
        {
            inFile >> buffer;
            targetX = atoi(buffer);
            inFile >> buffer;
            targetY = atoi(buffer);
        }
        else if(strcmp(buffer, "horizontal") == 0)
        {
            inFile >> buffer >> buffer;
            horizontalEdge.resize(boundaryX);
            for(int i = 0; i < boundaryX; ++i)
            {
                horizontalEdge[i].resize(boundaryY - 1);
            }
            for(int i = 0; i < boundaryX; ++i)
            {
                for(int j = 0; j < boundaryY - 1; ++j)
                {
                    inFile >> buffer;
                    horizontalEdge[i][j] = atof(buffer);
                }
            }
        }
        else if(strcmp(buffer, "vertical") == 0)
        {
            inFile >> buffer >> buffer;
            verticalEdge.resize(boundaryX - 1);
            for(int i = 0; i < boundaryX - 1; ++i)
            {
                verticalEdge[i].resize(boundaryY);
            }
            for(int i = 0; i < boundaryX - 1; ++i)
            {
                for(int j = 0; j < boundaryY; ++j)
                {
                    inFile >> buffer;
                    verticalEdge[i][j] = atof(buffer);
                }
            }
        }
        else
        {
            cout << "Unmatched string in the input file!" << endl;
        }
    }

    /* initialize the routing map */
    map.resize(boundaryX);
    for(int i = 0; i < boundaryX; ++i)
    {
        map[i].resize(boundaryY);
    }

    for(int i = 0; i < boundaryX; ++i)
    {
        for(int j = 0; j < boundaryY; ++j)
        {
            map[i][j].setX(i);
            map[i][j].setY(j);
            if((i == sourceX && j == sourceY) || ( i == targetX && j == targetY))
                map[i][j].setPath();
        }
    }

    cout << "--------------------" << endl;
    cout << "   Initial Map" << endl;
    cout << "--------------------" << endl;
    printMap();
    printEdgeWeights();
    
    
    priorityQ.push_back(&map[sourceX][sourceY]);
    map[sourceX][sourceY].setD(0);
    
    
    /* Dijkstra */
    // To Do:
	while(!priorityQ.empty() && map[targetX][targetY].isDone()==false) //&& map[targetX][targetY].isDone()==false
	{
		  Grid *u, *v;
		  double w;
		  u=extractMin();
		  map[u->getX()][u->getY()].setDone();
		  
		  if((u->getX()+1) < boundaryX)
		  {
		  	v=&map[u->getX()+1][u->getY()];
		  	w=verticalEdge[u->getX()][u->getY()];
		  	relax(u, v, w);
		  }
		  if((u->getY()+1) < boundaryY)
		  {
		  	v=&map[u->getX()][u->getY()+1];
		  	w=horizontalEdge[u->getX()][u->getY()];
		  	relax(u, v, w);
		  }
		  if(u->getX() > 0)
		  {
		  	v=&map[u->getX()-1][u->getY()];
		  	w=verticalEdge[u->getX()-1][u->getY()];
		  	relax(u, v, w);
		  }
		  if(u->getY() > 0)
		  {
		  	v=&map[u->getX()][u->getY()-1];
		  	w=horizontalEdge[u->getX()][u->getY()-1];
		  	relax(u, v, w);
		  }
	}
	
    /* Construct the Path */
    // To Do:
    Grid *t, *m;
    double min;
    t=&map[targetX][targetY];
	while(t!=&map[sourceX][sourceY])
    {
		m=t->getPi(); //©¹¦^§ä 
		m->setPath();
		t=m;                                                                                     
    } 
	
	cout << " " << endl;
	cout << "--------------------" << endl;
    cout << "   Final Map" << endl;
    cout << "--------------------" << endl;
    
	printMap();
	cout << "-------------------------------------------" << endl;
	cout << "Total cost from the source to the target : " << map[targetX][targetY].getD() << endl;
	
    system("pause");
    return 0;
}

void relax(Grid *u, Grid *v, double w)
{
    // To Do: 
	if(v->getD() > u->getD()+w)
	{
		v->setD(u->getD()+w);
		v->setPi(u);		
	}  
	if(v->isDone()==false)
	{
		priorityQ.push_back(v);
		v->setDone();
	}
}

Grid *extractMin()
{
    // To Do:
    list<Grid *>::iterator min =priorityQ.begin();
    for(list<Grid *>::iterator it =priorityQ.begin(); it != priorityQ.end(); ++it)
    {
    	if((*it)->getD() < (*min)->getD())
    	{
    		min = it;
		}
	}
	Grid *minGrid = *min;
	priorityQ.erase(min);
	return minGrid;
}

void printMap()
{
    cout << "Routing map:" << endl;
    for(int i = 0; i < map.size(); ++i)
    {
        for(int j = 0; j < map[0].size(); ++j)
        {
            if(map[i][j].isPath())
                cout << setw(2) << "*";
            else
                cout << setw(2) << "-";
        }
        cout << endl;
    }
    cout << "d map:" << endl;
    for(int i = 0; i < map.size(); ++i)
    {
        for(int j = 0; j < map[0].size(); ++j)
        {
            if(map[i][j].getD() == DBL_MAX)
                cout << setw(6) << "-";
            else
                cout << setw(6) << setprecision(2) << map[i][j].getD();
        }
        cout << endl;
    }
    cout << "pi map:" << endl;
    for(int i = 0; i < map.size(); ++i)
    {
        for(int j = 0; j < map[0].size(); ++j)
        {
            if(map[i][j].getPi() == NULL)
                cout << "- ";
            else
            {
                Grid *current = &map[i][j];
                Grid *pi = map[i][j].getPi();
                if(pi->getX() < current->getX())
                    cout << "u ";
                else if(pi->getX() > current->getX())
                    cout << "d ";
                else if(pi->getY() < current->getY())
                    cout << "l ";
                else
                    cout << "r ";
            }
        }
        cout << endl;
    }
}

void printEdgeWeights()
{
    cout << "Horizontal edge weigths:" << endl;
    for(int i = 0; i < horizontalEdge.size(); ++i)
    {
        for(int j = 0; j < horizontalEdge[0].size(); ++j)
        {
            cout << setprecision(2) << fixed << horizontalEdge[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Vertical edge weigths:" << endl;
    for(int i = 0; i < verticalEdge.size(); ++i)
    {
        for(int j = 0; j < verticalEdge[0].size(); ++j)
        {
            cout << setprecision(2) << fixed << verticalEdge[i][j] << " ";
        }
        cout << endl;
    }
}

