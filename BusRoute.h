#ifndef BUSROUTE_H
#define BUSROUTE_H

#include <string>
#include<iostream>
#include <fstream>
#include <windows.h>

using namespace std;

const int MAX = 100; //so luong tram toi da 
const int INF = 999999;

// Hàm để thay đổi màu văn bản
void setTextColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void clearScreen() {
    #ifdef _WIN32
        system("CLS");
    #else
        system("clear");
    #endif
}

class BusRoute {
	private:
	    int numStops;                //so luong tram
	    int distance[MAX][MAX];      //luu khoang cach giua cac tram
	    string nameStop[MAX];        //luu ten cac tram
	public:
	    BusRoute();
	    int getNumStops() const;
	    void setNumStops(int stops);
	    
	    string getNameStop(int index) const;
	    void setNameStop(int index, string name);
	    
	    int getDistance(int tram1, int tram2) const;
	    void setDistance(int tram1, int tram2, int khoangCach);
	    
	    void nhapTenTram();
	    void nhapKhoangCachTheoTen();
	    int timTram(const string& tenTram) const;
	    void dijkstra(const string& startTram, const string& endTram);
	    void inDuongDi(int parent[], int i);
	    int minDistance(int dist[], bool visited[]);
	    string nhapTenTramKhongTrung(BusRoute& route);

		void saveToFile(const std::string& filename);
		void loadFromFile(const std::string& filename);
};
BusRoute::BusRoute() {
	numStops = 0;
	for (int i = 0; i < MAX; i++) {
	    for (int j = 0; j < MAX; j++) {
	        distance[i][j] = (i == j) ? 0 : INF;
	    }
	}
}
int BusRoute::getNumStops() const { 
	return numStops; 
}
void BusRoute::setNumStops(int stops) { 
	numStops = stops; 
}
string BusRoute::getNameStop(int index) const{ 
	return nameStop[index]; 
}
void BusRoute::setNameStop(int index, string name) { 
	nameStop[index] = name; 
}
int BusRoute::getDistance(int tram1, int tram2) const { 
	return distance[tram1][tram2]; 
}
void BusRoute::setDistance(int tram1, int tram2, int khoangCach) {
	distance[tram1][tram2] = khoangCach;
	distance[tram2][tram1] = khoangCach;
}
void BusRoute::nhapTenTram() {
	for (int i = 0; i < numStops; i++) {
		cout << "Nhập tên trạm " << i + 1 << ": ";
		nameStop[i] = nhapTenTramKhongTrung(*this);  
	}
}
void BusRoute::nhapKhoangCachTheoTen() {
	string tram1, tram2;
	int khoangCach;
	while (true) {
	    cout << "Nhập trạm xuất phát (tên trạm, nhập '0' để kết thúc): ";
	    getline(cin, tram1);
		if (tram1 == "0") break;
		while(timTram(tram1)==-1){
			cout << "Trạm không tồn tại!" << endl;
			cout << "Nhập trạm xuất phát: ";getline(cin, tram1);
		}
	    
	    cout << "Nhập trạm đến (tên trạm): ";
	    getline(cin, tram2);
		while(timTram(tram1)==-1){
			cout << "Trạm không tồn tại!" << endl;
			cout << "Nhập trạm xuất đến: ";getline(cin, tram2);
		}
	    cout << "Nhập khoảng cách giữa " << tram1 << " và " << tram2 << ": ";
	    cin >> khoangCach;
	    cin.ignore(); 
		while(khoangCach<0){
			cout << "Nhập lại khoảng cách giữa " << tram1 << " và " << tram2 << ": ";
			cin >> khoangCach;
	    	cin.ignore(); 
		}
	    int idx1 = timTram(tram1);
	    int idx2 = timTram(tram2);	
	    if (idx1 != -1 && idx2 != -1) {
	        setDistance(idx1, idx2, khoangCach);
	    } else {
	        cout << "Trạm không tồn tại!" << endl;
	    }
	}
}
int BusRoute::timTram(const string& tenTram) const {
	for (int i = 0; i < numStops; i++) {
	    if (nameStop[i] == tenTram) {
	        return i;
	    }
	}
	return -1; 
}
void BusRoute::dijkstra(const string& startTram, const string& endTram) {
	int start = timTram(startTram);
	int end = timTram(endTram);
	if (start == -1 || end == -1) {
	    cout << "Trạm xuất phát hoặc trạm đến không tồn tại!" << endl;
	    return;
	}
	int dist[MAX];
	bool visited[MAX];
	int parent[MAX];
	for (int i = 0; i < numStops; i++) {
	    dist[i] = INF;
	    visited[i] = false;
	    parent[i] = -1;
	}
	dist[start] = 0;
	for (int count = 0; count < numStops - 1; count++) {
	    int u = minDistance(dist, visited);
	    if (u == -1) break;
	    visited[u] = true;
		for (int v = 0; v < numStops; v++) {
	    	if (!visited[v] && getDistance(u, v) != INF && dist[u] + getDistance(u, v) < dist[v]) {
	            dist[v] = dist[u] + getDistance(u, v);
	            parent[v] = u;
	        }
	    }
	}
	if (dist[end] == INF) {
	    cout << "Không có tuyến trực tiếp từ " << startTram << " tới " << endTram << "." << endl;
	} else {
	    cout << "Khoảng cách ngắn nhất giữa " << startTram << " và " << endTram << " là: " << dist[end] << endl;
	    cout << "Đường đi: ";
	        inDuongDi(parent, end);
	        cout << endTram << endl;
	}
}
void BusRoute::inDuongDi(int parent[], int i) {
	if (parent[i] == -1) {
	    return;
	}
	inDuongDi(parent, parent[i]);
	cout << nameStop[parent[i]] << " -> ";
}
int BusRoute::minDistance(int dist[], bool visited[]) {
	int min = INF, min_index = -1;
	for (int i = 0; i < numStops; i++) {
	if (!visited[i] && dist[i] <= min) {
	    min = dist[i], min_index = i;
	}
	}
	return min_index;
}
string BusRoute::nhapTenTramKhongTrung(BusRoute& route) {
	string tenTram;
	while (true) {
		getline(cin, tenTram);
		bool tenTrung = false;
		for (int i = 0; i < route.getNumStops(); i++) {
		    if (route.getNameStop(i) == tenTram) {
		        tenTrung = true;
		        cout << "Tên trạm đã tồn tại. Vui lòng nhập lại!" << endl;
		        break;
		    }
		}
		if (!tenTrung) {
		    break;
		}
	}
	return tenTram;
}
void BusRoute::saveToFile(const std::string& filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << numStops << endl;
        for (int i = 0; i < numStops; i++) {
            outFile << nameStop[i] << endl;
        }
        for (int i = 0; i < numStops; i++) {
            for (int j = 0; j < numStops; j++) {
                outFile << distance[i][j] << " ";
            }
            outFile << endl;
        }
        outFile.close();
    } else {
        cerr << "Không thể mở file để ghi!" << endl;
    }
}
void BusRoute::loadFromFile(const std::string& filename) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        inFile >> numStops;
        inFile.ignore(); 
        for (int i = 0; i < numStops; i++) {
            getline(inFile, nameStop[i]);
        }
        for (int i = 0; i < numStops; i++) {
            for (int j = 0; j < numStops; j++) {
                inFile >> distance[i][j];
            }
        }
        inFile.close();
    } else {
        cerr << "Không thể mở file để đọc!" << endl;
    }
}
#endif
