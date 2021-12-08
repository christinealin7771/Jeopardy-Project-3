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

//vector<vector<string>> readFile()
//{
//    vector<vector<string>> vect;
//    string question;
//    string price;
//    string categories;
//    string answer;
//    string index;
//    string line;
//    ifstream readFile("Jeopardy_cleaned_tsv.tsv");
//
//
//    getline(readFile, line);
//
//    while(getline(readFile, line))
//    {
//        vector<string> temp;
//
//        stringstream s_stream(line);
//
//        getline(s_stream, index, '\t');
//        temp.push_back(index);
//
//        getline(s_stream, categories, '\t');
//        temp.push_back(categories);
//
//        getline(s_stream, price, '\t');
//        temp.push_back(price);
//
//        getline(s_stream, question, '\t');
//        temp.push_back(question);
//
//        getline(s_stream, answer, '\t');
//        temp.push_back(answer);
//
//        vect.push_back(temp);
//
//    }
//
//    return vect;
//
//}

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

// int dijkstraAlg (int startIndex, int endIndex, vector<pair<int,int>> adj[])
// {
//     //vector<int> pathIndex; //storing the index of the shorest path to endIndex
//     int distance[213298]; //output array of dist[i] will holdest the shortest distance from src to i
//     bool visited[213298]; // shorest distance from src to i is finalized
    
//     //vector<int> previous[213298];

//     unordered_set<int> finished;
//     int size = 213298;

//     for(int i = 0; i < size; i++)
//     {
//         distance[i] = INT_MAX;
//         visited[i] = false;
//        // previous[i].push_back(-1);
//     }

//     distance[startIndex] = 0;
//     int current = startIndex;

//     while(true)
//     {
//         visited[current] = true;
//         for(int i = 0; i < adj[current].size(); i++)
//         {
//             //from 0 to the first index
//             int temp = adj[current][i].first;
//             int distanceCount = distance[current] + adj[current][i].second;
//             // if(previous[temp][0] == -1)
//             // {
//             //     previous[temp][0] = current;
//             // }

//             if(distanceCount < distance[temp])
//             {
//                 distance[temp] = distanceCount;
//                 // previous[temp] = previous[current];
//                 // previous[temp].push_back(current);
//                 finished.insert(temp);
//             }
//         }
//         finished.erase(current);
//         //pathIndex.push_back(current);
//         if(finished.empty())
//             break;
//         int min = INT_MAX;
//         int index = 0;
//         for(auto num: finished)
//         {
//             if(distance[num] < min)
//             {
//                 min = distance[num];
//                 index = num;
//             }
//         }
//         current = index;
//     }
//     //return previous[endIndex];
//     return 1;
// }



int main()
{
//    vector<vector<string>> vect = readFile();
    unordered_map<int, vector<string>> data = readFile();
//    unordered_map <question, vector<string>> data;

    //array of vector storing pairs
    vector<pair<int, int> > adj[213298];
    //use the first int in pair as the index and the second as the weight 
    for (int i = 0; i < 213298; i++) {
        addEdge(adj, i, rand() % 213298, (rand() % 20) + 1);
        addEdge(adj, i, rand() % 213298, (rand() % 20) + 1);
        addEdge(adj, i, rand() % 213298, (rand() % 20) + 1);
    }

    int startIndex = (rand() % 1000);
    int endIndex = (rand() % 3000) + 2000;

  
    //cout << dijkstraAlg(startIndex, endIndex, adj) << endl;

    //cout << "hello" << endl;;
    // for(int i = 0; i < 5; i++)
    //     cout << pathIndex[i] << endl; 

    //cout << adj[0][0].first << endl;
    //use the algorithm to find all path and use the end index to output the result of this path as questions

    // //menu driven program
    // cout << "Welcome to the best Jeopardy Resoruce you can find to help\n"
    //     << "prepare you for that finanically changing game of your life.\n" << endl;

    // int option;
    // //Option 1: First ask for a round they want then ask what price level they want
    // cout << "1. Get a random question from a Round" << endl;
    // cout << "2. List of Percentages Answered Correctly Per Price Level" << endl;
    // cout << "3. Quit" << endl;
    // cin >> option;



    return 0;
}