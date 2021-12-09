#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <climits>
#include <algorithm>
#include <stdlib.h>
using namespace std;

unordered_map<int, vector<string>> readFile()
{
    unordered_map<int, vector<string>> data;
    string question;
    string price;
    string categories;
    string answer;
    string index;
    string line;
    ifstream readFile("Jeopardy_cleaned_tsv_updated.tsv");


    getline(readFile, line);

    while(getline(readFile, line))
    {
        vector<string> temp;

        stringstream s_stream(line);

        getline(s_stream, index, '\t');
        int ind = stoi(index);

        getline(s_stream, categories, '\t');
        temp.push_back(categories);

        getline(s_stream, price, '\t');
        price.erase(0,1);
        temp.push_back(price);

        getline(s_stream, question, '\t');
        temp.push_back(question);

        getline(s_stream, answer, '\t');
        answer.pop_back();
        temp.push_back(answer);

        data.insert({ind, temp});
    }
    return data;
}

void addEdge(vector <pair<int, int> > adj[], int from, int to, int weight) {
    //index of to and weight
    adj[from].push_back(make_pair(to, weight));
    adj[to].push_back(make_pair(from, weight));
}

vector<int> dijkstraAlg (int startIndex, int endIndex, vector<pair<int,int>> adj[])
{
   
    int distance[100000]; //output array of dist[i] will holdest the shortest distance from src to i
    bool visited[100000]; // shorest distance from src to i is finalized

    vector<int> previous[100000];

    unordered_set<int> finished;
    int size = 100000;
  
    for(int i = 0; i < size; i++)
    {
        distance[i] = INT_MAX;
        visited[i] = false;
        previous[i].push_back(startIndex);
    }

    distance[startIndex] = 0;
    int current = startIndex;

    while(true)
    {
        visited[current] = true;
        for(int i = 0; i < adj[current].size(); i++)
        {
            //from 0 to the first index
            int temp = adj[current][i].first;
            int distanceCount = distance[current] + adj[current][i].second;
            if(previous[temp][i] == startIndex && temp != startIndex)
              previous[temp][0] = current;

            if(distanceCount < distance[temp])
            {
                distance[temp] = distanceCount;
                previous[temp] = previous[current];
                previous[temp].push_back(current);
                finished.insert(temp);
            }
        }
        finished.erase(current);
        if(finished.empty())
        {
          break;
        }
            
        int min = INT_MAX;
        int index = 0;
        for(auto num: finished)
        {
            if(distance[num] < min)
            {
                min = distance[num];
                index = num;
            }
        }
        current = index;
    }
    if(startIndex != endIndex)
      previous[endIndex].erase(previous[endIndex].begin());
    return previous[endIndex];
}

vector<int> Bellman_Ford(vector<pair<int, int>> graph[], int source, int destination, int adjSize)
{
	int vectors = adjSize;
	vector<int> distances;
  vector<int> pathIndex[100000];

	for (int i = 0; i < vectors; i++)
  {
    distances.push_back(INT_MAX);
    pathIndex[i].push_back(source);
  }
		
	distances[source] = 0;

  //number of vertices - 1 loops
	for (int i = 0 ; i < vectors - 1; i++)
	{
    //they have it where you get the source of an index
		for (int j = source; j < source + vectors; j++)
		{
      for(int k = 0; k < graph[j].size(); k++)
      {
        int start = j; // source== index 0
        int end = graph[j][k].first;
        int weight = graph[j][k].second;
        if(pathIndex[end][k] == source && end != source)
              pathIndex[end][0] = start;
        if (distances[start] != INT_MAX && distances[start] + weight < distances[end])
        {
          pathIndex[end] = pathIndex[start];
          pathIndex[end].push_back(start);
          distances[end] = distances[start] + weight;


        }
          
      }
			
		}
	}
  if(source != destination)
      pathIndex[destination].erase(pathIndex[destination].begin());

	return pathIndex[destination];
}





int main()
{
    unordered_map<int, vector<string>> data = readFile();


    //array of vector storing pairs
    
    //use the first int in pair as the index and the second as the weight 

//    vector<pair<int, int>> adj[100000];
//    for (int i = 0; i < 100000; i++) {
//        addEdge(adj, i, rand() % 100000, (rand() % 20) + 1);
//        addEdge(adj, i, rand() % 100000, (rand() % 20) + 1);
//        addEdge(adj, i, rand() % 100000, (rand() % 20) + 1);
//        edgeNum += 6;
//    }

     vector<pair<int, int>> adj[7];
     addEdge(adj, 0, 1, 1);
     addEdge(adj,0, 3, 3);
     addEdge(adj, 0, 5, 2);
     addEdge(adj, 1, 4, 7);
     addEdge(adj, 1, 2, 2);
     addEdge(adj, 1, 3, 1);
     addEdge(adj, 2, 3, 6);
     addEdge(adj, 2, 4, 10);
     addEdge(adj, 5, 3, 4);
     addEdge(adj, 3, 6, 4);

    //used to test bellman ford
    // vector<pair<int, int>> adj[7];
    //  addEdge2(adj, 0, 1, 3);
    //  addEdge2(adj,0, 2, 8);
    //  addEdge2(adj, 1, 4, 6);
    //  addEdge2(adj, 1, 3, 6);
    //  addEdge2(adj, 1, 2, 7);
    //  addEdge2(adj, 3, 1, 5);
    //  addEdge2(adj, 3, 2, 9);
    //  addEdge2(adj, 4, 3, 1);

     //a=0, b= 1, c= 2, d=3, e=4

    //change the index
//    int startIndex = 10;
//    int endIndex = 10000;
    int startIndex = 0;
    int endIndex = 6;

  
    vector<int> bellManFordIndex = Bellman_Ford(adj, startIndex, endIndex, 7);

    //use the algorithm to find all path and use the end index to output the result of this path as questions
    //menu driven program
    cout << "Welcome to the best Jeopardy Resoruce you can find to help\n"
        << "prepare you for that finanically changing game of your life.\n" << endl;

    bool contGame = true;
    //To go through the vector of indexes for Dijkstra's
    int questionNumDij = 0;
    int totalMonies = 0;
    vector<int> results;
    while (contGame) {
        int option;
        cout << "1. Get a random question from a Round" << endl;
        cout << "2. Total amount of earnings" << endl;
        cout << "3. Outprint all questions and answers" << endl;
        cout << "4. Quit" << endl;
        cin >> option;

        if (option == 1) {
            cout << "Which algorithm would you like to use to generate the questions?" << endl;
            cout << "1. Dijkstra's Algorithm" << endl;
            cout << "2. I forgot the name of the other one" << endl;
            cin >> option;

            if (option == 1) {
                vector<int> index = dijkstraAlg(startIndex, endIndex, adj);
                //comment out later
                cout << index.size() << endl;
                cout << "How many questions would you like?" << endl;
                cin >> option;
                int vectIndex = questionNumDij;
                string answer;
                getline(cin, answer);
                for (int i = 0; i < option; i++) {
                    results.push_back(i+vectIndex);
                    cout << data[index.at(i+vectIndex)].at(2) << endl;
                    getline(cin, answer);
                    transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
                    string correctAns = data[i+vectIndex].at(3);
                    transform(correctAns.begin(), correctAns.end(), correctAns.begin(), ::tolower);
                    if (answer == correctAns) {
                        cout << "Correct" << endl;
                        totalMonies += stoi(data[i+vectIndex].at(1));
                    }
                    else {
                        cout << "Incorrect" << endl;
                        cout << "The right answer is: " << endl;
                        cout << data[i+vectIndex].at(3) << endl;
                        totalMonies -= stoi(data[i+vectIndex].at(1));
                    }
                    questionNumDij++;
                }
            }
            continue;
        }
        if (option == 2) {
            cout << "Total amount of earnings: $" << totalMonies << endl;
        }
        if (option == 3) {
            for (int i = 0; i < results.size(); i++) {
                cout << data[i].at(2) << endl;
                cout << data[i].at(3) << endl;
                cout << endl;
            }
        }
        if (option == 4) {
            contGame = false;
        }
    }
    return 0;
}