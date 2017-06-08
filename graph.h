#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <set>
#include <tuple>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stack>
#include <queue>

using namespace std;

class DSU
{
private:
	vector<int> p;
	vector<int> rank;
public:
	DSU(int N) : p(N + 1), rank(N + 1)
	{
		for (int x = 0; x <= N; ++x) {
			p[x] = x;
			rank[x] = 0;
		}
	}
	int find(int x)
	{
		if (p[x] == x)
		return x; 
		else return p[x] = find(p[x]);
	}
	void unite(int x, int y)
	{
		if ((x = find(x)) == (y = find(y)))
			return;
		if (rank[x] <  rank[y])
			p[x] = y;
		else
			p[y] = x;

		if (rank[x] == rank[y])
			++rank[x];
	}
	bool checkConnectivity()
	{
		for (int i = 1; i < p.size() - 1; i++)
		{
			if (find(p[i]) != find(p[i + 1])) return false;
		}
		return true;
	}

};

class Graph
{
private:
	char typeOfGraph;
	int N = 0;
	int M = 0;
	bool W;
	bool D;
	vector<vector<int>>  AdjMatrix;
	vector<map<int, int>> AdjList;
	vector<tuple<int, int, int>>  ListOfEdges;
	void ClearAll()
	{
		AdjList.clear();
		AdjMatrix.clear();
		ListOfEdges.clear();
		N = M = D = W = 0;
	}
	static bool cmpTuple(const tuple<int, int, int> &t1, const tuple<int, int, int> &t2)
	{
		if (get<2>(t1) != get<2>(t2))
			return (get<2>(t1) < get<2>(t2));
		else
			if (get<0>(t1) != get<0>(t2))
				return (get<0>(t1) < get<0>(t2));
			else
				return (get<1>(t1) < get<1>(t2));
	}

	void init(char v, int d, int w, int n, int m)
	{
		typeOfGraph = v;
		D = d;
		W = w;
		N = n;
		M = m;
		switch (typeOfGraph)
		{
		case 'C':
			AdjMatrix.resize(N);
			for (int i = 0; i < N; i++)
				AdjMatrix[i].resize(N);
			break;
		case 'L':
			AdjList.resize(N);
			break;
		case 'E':
			ListOfEdges.resize(M);
			break;
		}

	}

	void ReadAdjMatrix()
	{
		int w;
		cin >> N >> D >> W;
		AdjMatrix.resize(N);
		for (int i = 0; i < N; i++)
		{
			AdjMatrix[i].resize(N);
			for (int j = 0; j < N; j++)
			{
				cin >> w;
				if (w) M++;
				AdjMatrix[i][j] = w;
			}
		}
		if (!D) M /= 2;
	}
	void ReadAdjList()
	{
		string str = "";
		cin >> N >> D >> W;
		AdjList.resize(N);
		getline(cin, str);
		for (int i = 0; i < N; i++)
		{
			getline(cin, str);
			istringstream stringStream(str);//превращает строку в поток
			int k, w = 1;
			while (stringStream && str.size() != 0)
			{
				stringStream >> k;
				if (W)
				{
					stringStream >> w;
				}
				AdjList[i][k] = w;
				if (!D) AdjList[k - 1][i + 1] = w;
			}
			M += AdjList[i].size();
		}
	}
	void ReadListOfEdges()
	{
		cin >> N >> M >> D >> W;
		ListOfEdges.resize(M);
		for (int i = 0; i < M; i++)
		{
			int ai, bi, w = 1;
			if (W)
				cin >> ai >> bi >> w;
			else
				cin >> ai >> bi;
			get<0>(ListOfEdges[i]) = ai;
			get<1>(ListOfEdges[i]) = bi;
			get<2>(ListOfEdges[i]) = w;
		}
	}

	void addEdgeAdjMatrix(int from, int to, int weight)
	{
		from--;
		to--;
		AdjMatrix[from][to] = weight;
		if (!D) AdjMatrix[to][from] = weight;
	}
	void addEdgeAdjList(int from, int to, int weight)
	{
		AdjList[from - 1][to] = weight;
		if (!D) AdjList[to - 1][from] = weight;
	}
	void addEdgeListOfEdges(int from, int to, int weight)
	{
		ListOfEdges.resize(M);
		get<0>(ListOfEdges[M - 1]) = from;
		get<1>(ListOfEdges[M - 1]) = to;
		get<2>(ListOfEdges[M - 1]) = weight;
	}

	void writeAdjMatrix()
	{
		cout << typeOfGraph << ' ' << N << endl;
		cout << D << ' ' << W << endl;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N - 1; j++)
				cout << AdjMatrix[i][j] << ' ';
			cout << AdjMatrix[i][N - 1] << endl;
		}
	}
	void writeAdjList()
	{
		cout << typeOfGraph << ' ' << N << endl;
		cout << D << ' ' << W << endl;
		for (int i = 0; i < N; i++)
		{
			int AdjListSize = AdjList[i].size();
			int k = 0;
			for (auto it = AdjList[i].begin(); it != AdjList[i].end(); it++)
			{
				if (k == AdjListSize - 1)
				{
					if (W) cout << it->first << ' ' << it->second;
					else cout << it->first;
				}
				else
				{
					if (W) cout << it->first << ' ' << it->second << ' ';
					else cout << it->first << ' ';
				}
				k++;
			}
			cout << endl;
		}
	}
	void writeListOfEdges()
	{
		cout << typeOfGraph << ' ' << N << ' ' << M << endl;
		cout << D << ' ' << W << endl;
		for (int i = 0; i < M; i++)
		{
			if (W) cout << get<0>(ListOfEdges[i]) << ' ' << get<1>(ListOfEdges[i]) << ' ' << get<2>(ListOfEdges[i]);
			else cout << get<0>(ListOfEdges[i]) << ' ' << get<1>(ListOfEdges[i]);
			cout << endl;
		}
	}

	void removeEdgeAdjMatrix(int from, int to)
	{
		from--;
		to--;
		if (D) AdjMatrix[from][to] = 0;
		else
		{
			AdjMatrix[from][to] = 0;
			AdjMatrix[to][from] = 0;
		}
	}
	void removeEdgeAdjList(int from, int to)
	{
		auto result1 = AdjList[from - 1].find(to);
		auto result2 = AdjList[to - 1].find(from);
		if (result1 != AdjList[from - 1].end() && result2 != AdjList[to - 1].end())
		{
			AdjList[from - 1].erase(result1);
			AdjList[to - 1].erase(result2);
		}
	}
	void removeEdgeListOfEdges(int from, int to)
	{
		for (auto it = ListOfEdges.begin(); it != ListOfEdges.end(); it++)
		{
			if (D)
			{
				if (get<0>(*it) == from && get<1>(*it) == to)
				{
					ListOfEdges.erase(it);
					break;
				}
			}
			else
			{
				if (get<0>(*it) == from && get<1>(*it) == to || get<0>(*it) == to && get<1>(*it) == from)
				{
					ListOfEdges.erase(it);
					break;
				}
			}
		}
	}

	void changeEdgeAdjMatrix(int from, int to, int newWeight, int tmpToReturn)
	{
		from--;
		to--;
		tmpToReturn = AdjMatrix[from][to];
		AdjMatrix[from][to] = newWeight;
		if (!D) AdjMatrix[to][from] = newWeight;
	}
	void changeEdgeAdjList(int from, int to, int newWeight, int tmpToReturn)
	{
		auto result1 = AdjList[from - 1].find(to);
		auto result2 = AdjList[to - 1].find(from);
		if (result1 != AdjList[from - 1].end() && result2 != AdjList[to - 1].end())
		{
			tmpToReturn = result1->second;
			result1->second = newWeight;
			result2->second = newWeight;
		}
		else if (result1 != AdjList[from - 1].end())
		{
			tmpToReturn = result1->second;
			result1->second = newWeight;
		}
		if (result2 != AdjList[to - 1].end())
		{
			tmpToReturn = result2->second;
			result2->second = newWeight;
		}
	}
	void changeEdgeListOfEdges(int from, int to, int newWeight, int tmpToReturn)
	{
		for (auto it = ListOfEdges.begin(); it != ListOfEdges.end(); it++)
		{
			if (D)
			{
				if (get<0>(*it) == from && get<1>(*it) == to)
				{
					tmpToReturn = get<2>(*it);
					get<2>(*it) = newWeight;
					break;
				}
			}
			else
			{
				if (get<0>(*it) == from && get<1>(*it) == to || get<0>(*it) == to && get<1>(*it) == from)
				{
					tmpToReturn = get<2>(*it);
					get<2>(*it) = newWeight;
					break;
				}
			}
		}
	}

	void AdjListToAdjMatrix()
	{
		AdjMatrix.resize(N);
		for (int i = 0; i < N; i++) AdjMatrix[i].resize(N);
		for (int i = 0; i < N; i++)
		{
			for (auto it = AdjList[i].begin(); it != AdjList[i].end(); it++)
			{
				int ay = it->first;
				int aw = it->second;
				AdjMatrix[i][ay - 1] = aw;
				if (!D) AdjMatrix[ay - 1][i] = aw;
			}
		}
		AdjList.clear();
		AdjList.shrink_to_fit();
		typeOfGraph = 'C';
	}
	void ListOfEdgesToAdjMatrix()
	{
		AdjMatrix.resize(N);
		for (int i = 0; i < N; i++) AdjMatrix[i].resize(N);
		for (int i = 0; i < M; i++)
		{
			int ax = get<0>(ListOfEdges[i]);
			int ay = get<1>(ListOfEdges[i]);
			int aw = get<2>(ListOfEdges[i]);
			AdjMatrix[ax - 1][ay - 1] = aw;
			if (!D) AdjMatrix[ay - 1][ax - 1] = aw;
		}
		ListOfEdges.clear();
		ListOfEdges.shrink_to_fit();
		typeOfGraph = 'C';
	}
	void AdjMatrixToAdjList()
	{
		AdjList.resize(N);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
			{
				if (AdjMatrix[i][j] != 0)
				{
					AdjList[i][j + 1] = AdjMatrix[i][j];
					if (!D) AdjList[j][i + 1] = AdjMatrix[i][j];
				}
			}
		AdjMatrix.clear();
		AdjMatrix.shrink_to_fit();
		typeOfGraph = 'L';
	}
	void ListOfEdgesToAdjList()
	{
		AdjList.resize(N);
		for (int i = 0; i < M; i++)
		{
			int ax = get<0>(ListOfEdges[i]);
			int ay = get<1>(ListOfEdges[i]);
			int aw = get<2>(ListOfEdges[i]);
			AdjList[ax - 1][ay] = aw;
			if (!D) AdjList[ay - 1][ax] = aw;
		}
		ListOfEdges.clear();
		ListOfEdges.shrink_to_fit();
		typeOfGraph = 'L';
	}
	void AdjMatrixToListOfEdges()
	{

		ListOfEdges.resize(M);
		int k = 0;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
			{
				if (AdjMatrix[i][j] != 0)
				{
					if (!D && i < j || D)
					{
						get<0>(ListOfEdges[k]) = i + 1;
						get<1>(ListOfEdges[k]) = j + 1;
						get<2>(ListOfEdges[k]) = AdjMatrix[i][j];
						k++;
					}
				}
			}
		AdjMatrix.clear();
		AdjMatrix.shrink_to_fit();
		typeOfGraph = 'E';

	}
	void AdjListToListOfEdges()
	{
		ListOfEdges.resize(M);
		int k = 0;
		for (int i = 0; i < N; i++)
		{
			for (auto it = AdjList[i].begin(); it != AdjList[i].end(); it++)
			{
				int ay = it->first;
				int aw = it->second;
				if (!D && i < ay || D)
				{
					get<0>(ListOfEdges[k]) = i + 1;
					get<1>(ListOfEdges[k]) = ay;
					get<2>(ListOfEdges[k]) = aw;
					k++;
				}
			}
		}
		AdjList.clear();
		AdjList.shrink_to_fit();
		typeOfGraph = 'E';

	}
public:
	Graph() {};
	Graph(int nN) :typeOfGraph('E'), D(0), W(1), N(nN), M(0) {};
	Graph(char ntype, bool nD, bool nW, int nN, int nM) : typeOfGraph(ntype), D(nD), W(nW), N(nN), M(nM)
	{
		switch (typeOfGraph)
		{
		case 'C':
		{
			AdjMatrix.resize(N);
			for (int i = 0; i < N; i++)
				AdjMatrix[i].resize(N);
			break;
		}
		case 'L':
		{
			AdjList.resize(N);
			break;
		}
		case 'E':
		{
			ListOfEdges.resize(M);
			break;
		}
		}
	}
	void readGraph(string fileName)
	{
		ClearAll();
		freopen(fileName.c_str(), "r", stdin); //перенаправить стандартный поток ввода в файл
		cin >> typeOfGraph;
		switch (typeOfGraph)
		{
		case 'C':
			ReadAdjMatrix();
			break;
		case 'L':
			ReadAdjList();
			break;
		case 'E':
			ReadListOfEdges();
			break;
		}
	}
	void addEdge(int from, int to, int weight)
	{
		M++;
		switch (typeOfGraph)
		{

		case 'C':
			addEdgeAdjMatrix(from, to, weight);
			break;
		case 'L':
			addEdgeAdjList(from, to, weight);
			break;
		case 'E':
			addEdgeListOfEdges(from, to, weight);
			break;
		}
	}
	void writeGraph(string fileName)
	{
		freopen(fileName.c_str(), "w", stdout);
		switch (typeOfGraph)
		{
		case 'C':
			writeAdjMatrix();
			break;
		case 'L':
			writeAdjList();
			break;
		case 'E':
			writeListOfEdges();
			break;
		}
	}
	void removeEdge(int from, int to)
	{
		switch (typeOfGraph)
		{
			M--;
		case 'C':
			removeEdgeAdjMatrix(from, to);
			break;
		case 'L':
			removeEdgeAdjList(from, to);
			break;
		case 'E':
			removeEdgeListOfEdges(from, to);
			break;
		}
	}
	int changeEdge(int from, int to, int newWeight)
	{
		int tmpToReturn = 0;
		switch (typeOfGraph)
		{
		case 'C':
			changeEdgeAdjMatrix(from, to, newWeight, tmpToReturn);
			break;
		case 'L':
			changeEdgeAdjList(from, to, newWeight, tmpToReturn);
			break;
		case 'E':
			changeEdgeListOfEdges(from, to, newWeight, tmpToReturn);
			break;
		}
		return tmpToReturn;
	}
	void transformToAdjMatrix()
	{
		switch (typeOfGraph)
		{
		case 'C':
			break;
		case 'L':
			AdjListToAdjMatrix();
			break;
		case 'E':
			ListOfEdgesToAdjMatrix();
			break;
		}
	}
	void transformToAdjList()
	{
		switch (typeOfGraph)
		{
		case 'C':
			AdjMatrixToAdjList();
			break;
		case 'L':
			break;
		case 'E':
			ListOfEdgesToAdjList();
			break;
		}
	}
	void transformToListOfEdges()
	{
		switch (typeOfGraph)
		{
		case 'C':
			AdjMatrixToListOfEdges();
			break;
		case 'L':
			AdjListToListOfEdges();
			break;
		case 'E':
			break;
		}
	}

	Graph getSpanningTreePrima()
	{
		Graph graph(N);
		vector <int> vMin(N + 1, 9999999);
		vector <int> vPar(N + 1, -1);
		set<int> used;
		set<pair<int, int>> q;
		int temp = 0;

		q.insert(make_pair(0, 1));
		vMin[1] = 0;
		transformToAdjList();

		for (int i = 1; i <= N; i++)
			used.insert(i);


		while (temp<N)
		{
			temp++;
			if (q.empty()) q.insert(make_pair(0, *used.begin()));
			int v = q.begin()->second;
			q.erase(q.begin());
			for (auto j = AdjList[v - 1].begin(); j != AdjList[v - 1].end(); j++)
			{
				int to = j->first;
				int cost = j->second;
				if (cost < vMin[to] && used.find(to) != used.end())
				{
					q.erase(make_pair(vMin[to], to));
					vMin[to] = cost;
					vPar[to] = v;
					q.insert(make_pair(vMin[to], to));
				}
			}
			used.erase(v);
			if (!q.empty())
				graph.addEdge(vPar[q.begin()->second], q.begin()->second, q.begin()->first);
		}
		return graph;
	}
	Graph getSpanningTreeKruscal()
	{
		Graph graph(N);
		transformToListOfEdges();
		sort(ListOfEdges.begin(), ListOfEdges.end(), cmpTuple);
		DSU dsu(N);

		for (int i = 0; i < M; i++)
		{
			int a = get<0>(ListOfEdges[i]);
			int b = get<1>(ListOfEdges[i]);
			int w = get<2>(ListOfEdges[i]);
			if (dsu.find(a) != dsu.find(b))
			{
				graph.addEdge(a, b, w);
				dsu.unite(a, b);
			}
		}
		return graph;
	}
	Graph getSpanningTreeBoruvka()
	{
		Graph graph(N);
		transformToListOfEdges();
		DSU dsu(N);
		int k = N;

		while (k > 1)
		{
			bool flag = true;
			vector<int> c(N + 1, -1);

			for (int i = 0; i < M; i++)
			{
				int a = dsu.find(get<0>(ListOfEdges[i]));
				int b = dsu.find(get<1>(ListOfEdges[i]));
				int w = get<2>(ListOfEdges[i]);
				if (a != b)
				{
					if (c[a] == -1 || w < get<2>(ListOfEdges[c[a]]))
					{
						c[a] = i;
						flag = false;
					}
					if (c[b] == -1 || w < get<2>(ListOfEdges[c[b]]))
					{
						c[b] = i;
						flag = false;
					}
				}
			}

			if (flag)
				break;

			for (int i = 1; i <= N; i++)
			{
				if (c[i] != -1)
				{
					int a = get<0>(ListOfEdges[c[i]]);
					int b = get<1>(ListOfEdges[c[i]]);
					int w = get<2>(ListOfEdges[c[i]]);
					if (dsu.find(a) != dsu.find(b))
					{
						graph.addEdge(a, b, w);
						dsu.unite(a, b);
						k--;
					}
				}
			}
		}
		return graph;
	}
	int checkEuler(bool &circleExist)
	{
		DSU dsu(N);
		bool dsuFlag = false;
		int result = 1, odd = 0;
		vector <int> power(N + 1, 0);
		transformToListOfEdges();
		for (int i = 0; i < M; i++)
		{
			power[get<0>(ListOfEdges[i])]++;
			power[get<1>(ListOfEdges[i])]++;
		}
		for (int i = 1; i <= N; i++)
		{
			if (power[i] % 2 == 1)
			{
				odd++;
				result = i;
			}
		}
		for (int i = 0; i < M; i++)
		{
			int a = get<0>(ListOfEdges[i]);
			int b = get<1>(ListOfEdges[i]);
			int w = get<2>(ListOfEdges[i]);
			if (dsu.find(a) != dsu.find(b))
			{
				dsu.unite(a, b);
			}
		}
		dsuFlag = dsu.checkConnectivity();
		if (odd == 0) circleExist = true; else circleExist = false;
		if ((odd == 0 || odd == 2) && dsuFlag) return result;
		else return 0;
	}
	bool isBridge(int n1, int n2)
	{
		Graph g('L', D, W, N, M);
		DSU dsu(N);
		transformToAdjList();
		for (int i = 0; i < N; i++)
		{
			g.AdjList[i] = AdjList[i];
		}
		g.removeEdge(n1, n2);
		for (int i = 0; i < N; i++)
		{
			int a = i + 1;
			auto j = g.AdjList[i].begin();
			while( j != g.AdjList[i].end())
			{
				j++;
				int b = j->first;
				if (dsu.find(a) != dsu.find(b))
				{
					dsu.unite(a, b);
				}
			}
		}
		return !dsu.checkConnectivity();
	}
	vector<int> getEuleranTourFleri() 
	{
		vector<int> result;
		bool circleExist;
		int start = checkEuler(circleExist);
		if (start == 0)
			return result;
		transformToAdjList();
		Graph g(*this);
		int currV = start;
		result.push_back(currV);
		while (true) {
			int deg = g.AdjList[currV - 1].size();
			if (deg == 0)
				break;
			bool fl = true;
			for (auto& i : g.AdjList[currV - 1]) {
				int nextV = i.first;
				if ((deg == 1) || !g.isBridge(currV, nextV)) {
					fl = false;
					g.removeEdge(currV, nextV);
					currV = nextV;
					result.push_back(currV);
					break;
				}
			}
			if (fl) {
				int nextV = g.AdjList[currV - 1].begin()->first;
				g.removeEdge(currV, nextV);
				currV = nextV;
				result.push_back(currV);
			}
		}
		return result;
	}

	vector<int> getEuleranTourEffective()
	{
		vector<int> result;
		bool circleExist;
		int start = checkEuler(circleExist);
		if (start == 0)
		{
			return result;
		}

		transformToAdjList();
		Graph g(*this);
		stack<int> stack;
		stack.push(start);

		while (!stack.empty())
		{
			int curV = stack.top();
			for (auto& edge : AdjList[curV - 1])
			{
				int nextV = edge.first;
				stack.push(nextV);
				g.removeEdge(curV, nextV);
				break;
			}
			if (curV == stack.top())
			{
				stack.pop();
				result.push_back(curV);
			}
		}
		return result;
	}
	bool checkBipart(vector <char> &marks)
	{
		queue <int> qV;
		set <int> used;
				transformToAdjList();
		for (int i = 1; i <= N; i++) used.insert(i);
		qV.push(1);
		marks[1] = 'A';
		int kMarks = 1;
		while (!qV.empty())
		{
			int curV = qV.front() - 1;
			char workMark;
			qV.pop();
			for (auto i = AdjList[curV].begin(); i != AdjList[curV].end(); i++)
			{
				if (marks[i->first] != 'A' && marks[i->first] != 'B')
				{
					marks[i->first] = marks[curV + 1] == 'A' ? 'B' : 'A';
					qV.push(i->first);
					kMarks++;
				}
				else if (marks[i->first] == marks[curV + 1]) return false;
			}
			used.erase(curV + 1);
			if (qV.empty() && !used.empty()) qV.push(*used.begin());
		}
		return true;
	}

	bool kuhnDFS(int j, vector <bool> &used, vector <int> &curBipart, vector <bool> &visited)
	{
		if (used[j]) return false;
		used[j] = true;
		for (auto i = AdjList[j - 1].begin(); i != AdjList[j - 1].end(); i++)
		{
			int to = i->first;
			if ((curBipart[to] == -1) || kuhnDFS(curBipart[to], used, curBipart, visited))
			{
				curBipart[to] = j;
				return true;
			}
		}
		return false;
	}
	vector <pair <int, int> > getMaximumMatchingBipart()
	{
		vector <int> curBipart(N + 1, -1);
		vector <pair <int, int> > result;
		vector <char> marks(N + 1, 'N');
		vector <bool> visited(N + 1, false);
		vector <bool> used(N + 1, false);
		set <int> setV;
		for (int i = 1; i <= N; i++) setV.insert(i);
		transformToAdjList();
		for (int i = 1; i <= N; i++)
		{
			if (marks[i] == 'B') continue;
			for (auto j = AdjList[i - 1].begin(); j != AdjList[i - 1].end(); j++)
			{
				if (curBipart[j->first] == -1)
				{
					curBipart[j->first] = i;
					visited[i] = true;
					break;
				}
			}
		}
		if (checkBipart(marks))
		{
			for (int j = 1; j <= N; j++)
			{
				if (visited[j] || marks[j] == 'B')
				{
					used.assign(N + 1, false);
					kuhnDFS(j, used, curBipart, visited);
				}
			}
		}
		for (int i = 1; i <= N; i++)
		{
			if (curBipart[i] != -1 && marks[i] == 'B' && setV.find(curBipart[i]) != setV.end())
			{
				result.push_back(make_pair(i, curBipart[i]));
				setV.erase(curBipart[i]);
			}
		}
		return result;
	}
};


"# Gr" 
