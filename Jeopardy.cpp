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
#include <chrono>
using namespace std;
using namespace chrono;

//read file based on file name and year
unordered_map<int, vector<string>> readFile(string fileName)
{
	unordered_map<int, vector<string>> data;
	string question;
	string price;
	string categories;
	string answer;
	string index;
	string line;
	ifstream readFile(fileName);


	getline(readFile, line);

	while (getline(readFile, line))
	{
		vector<string> temp;

		stringstream s_stream(line);

		getline(s_stream, index, '\t');
		int ind = stoi(index);

		getline(s_stream, index, '\t');
		getline(s_stream, index, '\t');

		getline(s_stream, categories, '\t');
		temp.push_back(categories);

		getline(s_stream, price, '\t');
		price.erase(0, 1);
		temp.push_back(price);

		getline(s_stream, question, '\t');
		temp.push_back(question);

		getline(s_stream, answer, '\t');
		answer.pop_back();
		temp.push_back(answer);

		data.insert({ ind, temp });
	}
	return data;
}

//add edges to the graphs
void addEdge(vector <pair<int, int> > adj[], int from, int to, int weight) {
	//index of to and weight
	adj[from].push_back(make_pair(to, weight));
	adj[to].push_back(make_pair(from, weight));
}

//dijkstra Algorithm
vector<int> dijkstraAlg(int startIndex, int endIndex, vector<pair<int, int>> adj[])
{

	int distance[100000]; //output array of dist[i] will holdest the shortest distance from src to i
	bool visited[100000]; // shorest distance from src to i is finalized

	vector<int> previous[100000];

	unordered_set<int> finished;
	int size = 100000;

	for (int i = 0; i < size; i++)
	{
		distance[i] = INT_MAX;
		visited[i] = false;
		previous[i].push_back(startIndex);
	}

	distance[startIndex] = 0;
	int current = startIndex;

	while (true)
	{
		visited[current] = true;
		for (int i = 0; i < adj[current].size(); i++)
		{
			//from 0 to the first index
			int temp = adj[current][i].first;
			int distanceCount = distance[current] + adj[current][i].second;
			if (previous[temp][i] == startIndex && temp != startIndex)
				previous[temp][0] = current;

			if (distanceCount < distance[temp])
			{
				distance[temp] = distanceCount;
				previous[temp] = previous[current];
				previous[temp].push_back(current);
				finished.insert(temp);
			}
		}
		finished.erase(current);
		if (finished.empty())
		{
			break;
		}

		int min = INT_MAX;
		int index = 0;
		for (auto num : finished)
		{
			if (distance[num] < min)
			{
				min = distance[num];
				index = num;
			}
		}
		current = index;
	}
	if (startIndex != endIndex)
		previous[endIndex].erase(previous[endIndex].begin());
	return previous[endIndex];
}

//Bellman_ford Algorithm
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
	for (int i = 0; i < vectors - 1; i++)
	{
		//they have it where you get the source of an index
		for (int j = source; j < source + vectors; j++)
		{
			for (int k = 0; k < graph[j].size(); k++)
			{
				int start = j; // source== index 0
				int end = graph[j][k].first;
				int weight = graph[j][k].second;
				if (pathIndex[end][k] == source && end != source)
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
	if (source != destination)
		pathIndex[destination].erase(pathIndex[destination].begin());

	return pathIndex[destination];
}



int main()
{


	unordered_map<int, vector<string>> data;

	//use the algorithm to find all path and use the end index to output the result of this path as questions
	//menu driven program
	cout << "Welcome to the best Jeopardy Resoruce you can find to help\n"
		<< "prepare you for that finanically changing game of your life.\n" << endl;

	bool contGame = true;
	//To go through the vector of indexes
	int questionNumDij = 0;
	int questionNumBell = 0;
	int totalMonies = 0;

	vector<int> results;
	while (contGame) {
		int option;
		cout << "1. Get a random question from a Round" << endl;
		cout << "2. Total amount of earnings" << endl;
		cout << "3. Outprint all questions and answers" << endl;
		cout << "4. Compare time taken for each algorithm" << endl;
		cout << "5. Quit" << endl;
		cin >> option;
		cout << endl;

		//if the user wants questions
		if (option == 1) {
			cout << "Choose which year you would like questions from (2004-2012): ";
			int year;
			cin >> year;

			string fileName = to_string(year) + "_questions.tsv";
			data = readFile(fileName);
			//const int dataSize = data.size();
			vector<pair<int, int>>* adj = new vector<pair<int, int>>[data.size()];
			for (int i = 0; i < data.size(); i++) {
				addEdge(adj, i, rand() % data.size(), (rand() % 20) + 1);
				addEdge(adj, i, rand() % data.size(), (rand() % 20) + 1);
				addEdge(adj, i, rand() % data.size(), (rand() % 20) + 1);
			}

			cout << "Which algorithm would you like to use to generate the questions?" << endl;
			cout << "1. Dijkstra's Algorithm" << endl;
			cout << "2. Bellman Ford Algorithm" << endl;
			cin >> option;
			cout << endl;

			if (option == 1) {
				//comment out later
//                cout << indexDij.size() << endl;
				int startDij = rand() % 10;
				int endDij = rand() % data.size() - 1;
				while (endDij < startDij) {
					endDij = rand() % data.size() - 1;
				}
				vector<int> indexDij = dijkstraAlg(startDij, endDij, adj);

				//ask how many questions would you like
				cout << "How many questions would you like?" << endl;
				cin >> option;
				int vectIndex = questionNumDij;
				string answer;
				getline(cin, answer);
				for (int i = 0; i < option; i++) {
					results.push_back(indexDij.at(i + vectIndex));
					cout << data[indexDij.at(i + vectIndex)].at(2) << endl;
					getline(cin, answer);
					transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
					string correctAns = data[indexDij.at(i + vectIndex)].at(3);
					transform(correctAns.begin(), correctAns.end(), correctAns.begin(), ::tolower);
					if (answer == correctAns) {
						cout << "Correct" << endl;
						totalMonies += stoi(data[i + vectIndex].at(1));
					}
					else {
						cout << "Incorrect" << endl;
						cout << "The right answer is: " << endl;
						cout << data[indexDij.at(i + vectIndex)].at(3) << endl;
						totalMonies -= stoi(data[i + vectIndex].at(1));
					}

					questionNumDij++;
				}
			}
			//if the user chose bellman ford
			if (option == 2) {
				vector<int> bellManFordIndex = Bellman_Ford(adj, 0, data.size() - 1, data.size());
				cout << "How many questions would you like?" << endl;
				cin >> option;
				int vectIndex = questionNumBell;
				string answer;
				getline(cin, answer);
				for (int i = 0; i < option; i++) {
					//                    cout << bellManFordIndex.at(i+vectIndex) << endl;
					results.push_back(bellManFordIndex.at(i + vectIndex));
					cout << data[bellManFordIndex.at(i + vectIndex)].at(2) << endl;
					getline(cin, answer);
					transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
					string correctAns = data[bellManFordIndex.at(i + vectIndex)].at(3);
					transform(correctAns.begin(), correctAns.end(), correctAns.begin(), ::tolower);
					if (answer == correctAns) {
						cout << "Correct" << endl;
						totalMonies += stoi(data[i + vectIndex].at(1));
					}
					else {
						cout << "Incorrect" << endl;
						cout << "The right answer is: " << endl;
						cout << data[bellManFordIndex.at(i + vectIndex)].at(3) << endl;
						totalMonies -= stoi(data[i + vectIndex].at(1));
					}

					questionNumBell++;
				}
			}
			continue;
		}
		//get the points
		if (option == 2) {
			cout << "Total amount of earnings: $" << totalMonies << endl;
		}
		//print all the questions asked
		if (option == 3) {
			if (results.empty()) {
				cout << "No questions yet!" << endl;
			}
			for (int i = 0; i < results.size(); i++) {
				cout << data[results.at(i)].at(2) << endl;
				cout << data[results.at(i)].at(3) << endl;
				cout << endl;
			}
		}
		//compare the two algorithm's times
		if (option == 4) {
			//Change these so that both have same start and end index
			//start has to be less than end
			unordered_map<int, vector<string>> data1;
			data1 = readFile("2012_questions.tsv");
			vector<pair<int, int>> *adj1 = new vector<pair<int, int>>[data1.size()];
			for (int i = 0; i < data1.size(); i++) {
				addEdge(adj1, i, rand() % data1.size(), (rand() % 20) + 1);
				addEdge(adj1, i, rand() % data1.size(), (rand() % 20) + 1);
				addEdge(adj1, i, rand() % data1.size(), (rand() % 20) + 1);
			}


			int startIndex = 0;
			auto start = high_resolution_clock::now();
			vector<int> dijTime = dijkstraAlg(startIndex, data1.size() - 1, adj1);
			auto end = high_resolution_clock::now();
			//            auto duration = duration_cast<milliseconds>(end - start);
			auto duration = duration_cast<milliseconds>(end - start);
			cout << "Time taken for Dijkstra's Algorithm: " << duration.count() << " milliseconds" << endl;

			start = high_resolution_clock::now();
			vector<int> bellTime = Bellman_Ford(adj1, startIndex, data1.size() - 1, data1.size());
			end = high_resolution_clock::now();
			//            duration = duration_cast<milliseconds>(end - start);
			duration = duration_cast<milliseconds>(end - start);
			cout << "Time taken for Bellman Ford Algorithm: " << duration.count() << " milliseconds" << endl;
			cout << endl;
		}
		if (option == 5) {
			contGame = false;
		}

        
	}
	return 0;
}