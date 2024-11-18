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
	    
	    void nhapTenTram(int currentStops);
	    void nhapKhoangCachTheoTen();
	    int timTram(const string& tenTram) const;
	    void dijkstra(const string& startTram, const string& endTram);
	    void inDuongDi(int parent[], int i);
	    int minDistance(int dist[], bool visited[]);
	    string nhapTenTramKhongTrung(BusRoute& route);
		void clearStops();

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
void BusRoute::nhapTenTram(int currentStops) {
	for (int i = currentStops ; i < numStops; i++) {
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
		if(timTram(tram1)==-1){
			cout << "Trạm không tồn tại!" << endl;continue;
		}
	    cout << "Nhập trạm đến (tên trạm): ";
	    getline(cin, tram2);
		if(tram2==tram1){
			cout << "Không được nhập trùng."<<endl;
			continue;
		}
		if(timTram(tram2)==-1){
			cout << "Trạm không tồn tại!" << endl;continue;
		}
	    cout << "Nhập khoảng cách giữa " << tram1 << " và " << tram2 << ": ";
	     
		while(true){
			cin >> khoangCach;
	    	cin.ignore();
			if(cin.fail()||khoangCach<0){
				cin.clear();
				cin.ignore(1000, '\n');
				cout <<"Không hợp lệ"<<endl;
				cout << "Nhập lại khoảng cách giữa " << tram1 << " và " << tram2 << ": ";		
			}else {
				break;
			}
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
	setTextColor(15);
	if (dist[end] == INF) {
	    cout << "Không có tuyến trực tiếp từ " << startTram << " tới " << endTram << "." << endl;
	} else {
	    double distanceInMeters = dist[end] * 100;
		if (distanceInMeters >= 1000) {
			cout << "Khoảng cách ngắn nhất giữa " << startTram << " và " << endTram << " là: " 
				<< distanceInMeters / 1000.0 << " km" << endl;
		} else {
			cout << "Khoảng cách ngắn nhất giữa " << startTram << " và " << endTram << " là: " 
				<< distanceInMeters << " m" << endl;
		}
		double travelTimeInHours = distanceInMeters / 5000.0; 
		double totalMinutes = travelTimeInHours * 60.0; 
		int roundedMinutes = (totalMinutes > 0 && totalMinutes < 1) ? 1 : (int)(totalMinutes + 0.5);
		int hours = roundedMinutes / 60;
		int minutes = roundedMinutes % 60;
		if (minutes == 60) {
			minutes = 0;
			hours += 1;
		}
		cout << "Thời gian dự tính để đến: ";
		if (hours > 0) {
			cout << hours << " giờ ";
		}
		cout << minutes << " phút." << endl;
		cout << "Đường đi: ";
		inDuongDi(parent, end);
		cout << endTram << endl;
	}
}
int countConnections(int stopIndex, int numStops, const int distance[MAX][MAX]) {
    int count = 0;
    for (int i = 0; i < numStops; i++) {
        if (distance[stopIndex][i] != INF && distance[stopIndex][i] != 0) {
            count++;
        }
    }
    return count;
}
void BusRoute::inDuongDi(int parent[], int i) {
    if (parent[i] == -1) {
        return;
    }
    inDuongDi(parent, parent[i]);
    int connectionCount = countConnections(parent[i], numStops, distance);
    
    if (connectionCount > 3) {
		setTextColor(12); // Màu đỏ
	} else if (connectionCount == 3) {
		setTextColor(14); // Màu vàng
	} else {
		setTextColor(10);// Màu xanh
	}
    cout << nameStop[parent[i]] << " -> ";
	setTextColor(10);
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
void BusRoute::clearStops() {
    numStops = 0;  
    for (int i = 0; i < MAX; i++) {
        nameStop[i].clear();  
    }
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            distance[i][j] = (i == j) ? 0 : INF; 
        }
    }
}

#endif
