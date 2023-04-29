#include<iostream>
#include<map>
#include<list>
#include<climits>
#include<vector>
using namespace std;
#define nV 9
class neighbour
{
public:
	string name;
	int distance;

	neighbour(string name,int distance)
	{
		this->name=name;
		this->distance=distance;
	}
};
class graph{
public:
	map<string,list<neighbour>> neighbourMap;
	void addEdge(string u,string v,int w)
	{
	
		neighbourMap[u].push_back(neighbour(v,w));
		neighbourMap[v].push_back(neighbour(u,w));
	}

	void print()
	{
		for(auto x:neighbourMap)
		{
			list<neighbour> neighbourList=x.second;
			cout<<x.first<<": ";
			for(auto y:neighbourList)
			{
				cout<<y.name<<" "<<y.distance<<";";
			}
			cout<<endl<<endl;

		}
	}

};
void floydWarshall(vector<vector<long long int>> nums)
{
	long long int cost[9][9];
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			cost[i][j]=nums[i][j];
		}
	}
	for(int k=0;k<9;k++)
	{
		for(int i=0;i<9;i++)
		{
			for(int j=0;j<9;j++)
			{
				if(cost[i][k]+cost[k][j]<cost[i][j])
				{
					cost[i][j]=cost[i][k]+cost[k][j];
				}
			}
		}
	}
	
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
			cout<<cost[i][j]<<" ";
		cout<<endl;
	}
}

int main()
{
	graph g;
	//temp3->cafe
	//temp1->parking
	//temp2->SC shopping complex
	g.addEdge("Gaming Center1","Shopping Complex",10);
	g.addEdge("Gaming Center1","Cafe",12);
	g.addEdge("Shopping Complex","Recharge Center",18);
	g.addEdge("Cinema","Recharge Center",7);
	g.addEdge("Cinema","Food Court",23);
	g.addEdge("Food Court","Home",34);
	g.addEdge("Food Court","Gaming Center2",30);
	g.addEdge("Home","Cafe",41);
	g.addEdge("Parking","Cinema",25);
	g.addEdge("Parking","Cafe",21);
	int max=INT_MAX;
	vector<vector<long long>> wMatrix{{0,41,max,max,max,max,34,max,max},
								{41,0,12,max,max,max,max,max,21},
								{max,12,0,10,max,max,max,max,max},
								{max,max,10,0,18,max,max,max,max},
								{max,max,max,18,0,7,max,max,max},
								{max,max,max,max,7,0,23,max,25},
								{34,max,max,max,max,23,0,30,max},
								{max,max,max,max,max,max,30,0,max},
								{max,21,max,max,max,25,max,max,0}};
	//floydWarshall(wMatrix);
	g.print();
	string dest;
	vector<string> names{"Gaming Center1","Gaming Center2","Food Court","Recharge Center","Parking","Cafe","Cinema","Home"};
	vector<string> path{"Home"};
	int pathDist=0;
	cout<<endl<<"You are at home!!";
	cout<<endl<<"Where do you want to go?";
	getline(cin,dest);
	cout<<"Enter your path:";
	string place;
	string prev="Home";
	getline(cin,place);
	while(place!=dest)
	{
		path.push_back(place);
		list<neighbour> neighbourList=g.neighbourMap[place];
		for(auto x:neighbourList)
		{
			if(x.name==prev)
			{
				pathDist+=x.distance;
				break;
			}
		}
		prev=place;
		getline(cin,place);
	}
	list<neighbour> neighbourList=g.neighbourMap[place];
	for(auto x:neighbourList)
	{
		if(x.name==prev)
		{
			pathDist+=x.distance;
			break;
		}
	}
	return 0;
}