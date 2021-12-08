#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <climits>
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
    ifstream readFile("Jeopardy_cleaned_tsv.tsv");


    getline(readFile, line);

    while(getline(readFile, line))
    {
        vector<string> temp;

        stringstream s_stream(line);

        getline(s_stream, index, '\t');
//        temp.push_back(index);
        int ind = stoi(index);

        getline(s_stream, categories, '\t');
        temp.push_back(categories);

        getline(s_stream, price, '\t');
        temp.push_back(price);

        getline(s_stream, question, '\t');
        temp.push_back(question);

        getline(s_stream, answer, '\t');
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



int main()
{
//    vector<vector<string>> vect = readFile();
    unordered_map<int, vector<string>> data = readFile();
//    unordered_map <question, vector<string>> data;

    //array of vector storing pairs
    
    //use the first int in pair as the index and the second as the weight 

    vector<pair<int, int> > adj[100000];
    for (int i = 0; i < 100000; i++) {
        addEdge(adj, i, rand() % 100000, (rand() % 20) + 1);
        addEdge(adj, i, rand() % 100000, (rand() % 20) + 1);
        addEdge(adj, i, rand() % 100000, (rand() % 20) + 1);
    }

    // vector<pair<int, int>> adj[7];
    // addEdge(adj, 0, 1, 1);
    // addEdge(adj,0, 3, 3);
    // addEdge(adj, 0, 5, 2);
    // addEdge(adj, 1, 4, 7);
    // addEdge(adj, 1, 2, 2);
    // addEdge(adj, 1, 3, 1);
    // addEdge(adj, 2, 3, 6);
    // addEdge(adj, 2, 4, 10);
    // addEdge(adj, 5, 3, 4);
    // addEdge(adj, 3, 6, 4);

    //change the index
    int startIndex = 10;
    int endIndex = 10000;
   
    vector<int> index = dijkstraAlg(startIndex, endIndex, adj);


    //use the algorithm to find all path and use the end index to output the result of this path as questions

    //menu driven program
    cout << "Welcome to the best Jeopardy Resoruce you can find to help\n"
        << "prepare you for that finanically changing game of your life.\n" << endl;

    int option;
    //Option 1: First ask for a round they want then ask what price level they want
    cout << "1. Get a random question from a Round" << endl;
    cout << "2. List of Percentages Answered Correctly Per Price Level" << endl;
    cout << "3. Quit" << endl;
    cin >> option;



    return 0;
}