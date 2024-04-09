#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <set>
#include <fstream>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

ifstream fin("input.txt");

void sortmyvector(vector<string> &resB, map<string, int> &ageByName) {
	int len = resB.size();
	for (int i = 0; i < len - 1; i++) {
		for (int j = i + 1; j < len; j++) {
			if (ageByName[resB[i]] > ageByName[resB[j]]) {
				swap(resB[i], resB[j]);
			}
			else if (ageByName[resB[i]] == ageByName[resB[j]]) {
				if (resB[i] > resB[j]) {
					swap(resB[i], resB[j]);
				}
			}
		}
	}
}

void solve() {
	////////////////////INPUT//////////////////////////////////
	int nrUsers, age, nrTopics, nrTopicSubtopics, nrSubtopics;
	string name, topic, subtopic;
	map<string, string> topicsBySubtopics;
	map<string, vector<string>> topicsByName, namesByTopics;
	map<string, int> ageByName;

	fin >> nrUsers;
	for (int i = 0; i < nrUsers; i++) {
		fin >> name >> age >> nrTopics;
		ageByName.insert(make_pair(name, age));
		for (int j = 0; j < nrTopics; j++) {
			fin >> topic;
			topicsByName[name].push_back(topic);
			namesByTopics[topic].push_back(name);
		}
	}

	fin >> nrTopicSubtopics;
	for (int i = 0; i < nrTopicSubtopics; i++) {
		fin >> topic >> nrSubtopics;
		for (int j = 0; j < nrSubtopics; j++) {
			fin >> subtopic;
			topicsBySubtopics.emplace(make_pair(subtopic, topic));
		}
	}
	///////////////CERINTA A///////////////////////////////////////
	string cerinta;
	int budget, targetAge, nrPromos;
	string aux;
	vector<string> promo;
	vector<string> resA, resB, resAux;

	fin >> cerinta;
	

	for (auto& it : topicsByName[cerinta]) {
		resA.push_back(it);
		string temp = it;
		while (topicsBySubtopics.count(temp) != 0) {
			temp = topicsBySubtopics[temp];
			if(find(resA.begin(), resA.end(), temp) == resA.end())
				resA.push_back(temp);
		}
	}

	sort(resA.begin(), resA.end());

	cout << resA.size() << " ";
	for (auto& i : resA)
		cout << i << " ";
	cout << "\n";
	///////////////////CERINTA B////////////////////////////////////////
	fin >> budget >> targetAge >> nrPromos;
		for (int i = 0; i < nrPromos; i++) {
			fin >> aux;
			promo.push_back(aux);
		}
	for (auto& i : ageByName) {
		i.second = abs(i.second - targetAge);
	}

	while (resB.size() < 3) {
		for (auto& iterPromo : promo) {
			for (auto& names : namesByTopics[iterPromo]) {
				if(find(resB.begin(), resB.end(), names) == resB.end() && 
					find(resAux.begin(), resAux.end(), names) == resAux.end())
					resAux.push_back(names);
			}
			iterPromo = topicsBySubtopics[iterPromo];
		}
		sortmyvector(resAux, ageByName);
		for (auto& i : resAux)
			resB.push_back(i);
		resAux.clear();
	}

	cout << resB.size() << " ";
	for (int i = 0; i < budget; i++) {
		cout << resB[i] << " ";
	}
}
void solveB() {

}

int main() {
	//ll t; cin >> t; while (t--)

		solve();
}