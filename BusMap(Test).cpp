//Nguyen Gia Huy-Nguyen Hoang Tuan Dat-Hong Kim Dung
#include <iostream>

#include<string>
using namespace std;

const int MAX = 100; // So luong tram toi da
const int INF = 999999; 

class BusRoute {
	public:
	    int numStops;                // So luong tram
	    int distance[MAX][MAX];      // Ma tran khoang cach giua cac tram
	
	    // Ham khoi tao
	    BusRoute() {
	        numStops = 0; 
	        for (int i = 0; i < MAX; i++) {
	            for (int j = 0; j < MAX; j++) {
	                distance[i][j] = (i == j) ? 0 : INF; // Khoang cach tu tram den chinh no la 0, cac tram khac la vo cuc
	            }
	        }
	    }
	
	    // Ham nhap khoang cach giua hai tram bang ten
	    virtual void nhapKhoangCachTheoTen() {
	        int tram1, tram2, khoangCach;
	
	        while (true) {
	            cout << "Nhap tram xuat phat (so thu tu, nhap 0 de ket thuc): ";
	            cin >> tram1;
	            if (tram1 == 0) break; // Dung nhap khi nhap 0
	            cout << "Nhap tram den (so thu tu): ";
	            cin >> tram2;
	
	            cout << "Nhap khoang cach giua tram " << tram1 << " va tram " << tram2 << ": ";
	            cin >> khoangCach;
	
	            if (khoangCach > 0) { // Chi ghi nhan khoang cach duong
	                distance[tram1 - 1][tram2 - 1] = khoangCach; // Ghi nhan khoang cach
	                distance[tram2 - 1][tram1 - 1] = khoangCach; // Ghi nhan khoang cach hai chieu
	            }
	        }
	    }
	
	    // Ham tim tram co khoang cach nho nhat trong tap hop chua duoc xet
	    int minDistance(int dist[], bool visited[]) {
	        int min = INF, min_index = -1;
	
	        for (int i = 0; i < numStops; i++) {
	            if (!visited[i] && dist[i] <= min) {
	                min = dist[i], min_index = i;
	            }
	        }
	        return min_index;
	    }
	
	    // Thuat toan Dijkstra tim tuyen ngan nhat giua tram bat dau va cac tram khac
	    virtual void dijkstra(int start, int end) {
	        int dist[MAX];    // Mang luu khoang cach ngan nhat tu tram bat dau den cac tram
	        bool visited[MAX]; // Mang kiem tra cac tram da duoc xet hay chua
	        int parent[MAX];   // Mang luu vet de xac dinh duong di
	
	        // Khoi tao cac tram ban dau
	        for (int i = 0; i < numStops; i++) {
	            dist[i] = INF;
	            visited[i] = false;
	            parent[i] = -1; // Khong co tram truoc
	        }
	        dist[start] = 0; // Khoang cach tu tram bat dau den chinh no la 0
	
	        // Thuc hien thuat toan Dijkstra
	        for (int count = 0; count < numStops - 1; count++) {
	            int u = minDistance(dist, visited); // Tim tram co khoang cach nho nhat
	            if (u == -1) break; // Neu khong con tram nao de xet
	            visited[u] = true; // Danh dau tram nay da duoc xet
	
	            for (int v = 0; v < numStops; v++) {
	                if (!visited[v] && distance[u][v] != INF && dist[u] + distance[u][v] < dist[v]) {
	                    dist[v] = dist[u] + distance[u][v];
	                    parent[v] = u; // Luu tram truoc cua v la u
	                }
	            }
	        }
	
	        // In ra duong di va khoang cach
	        if (dist[end] == INF) {
	            cout << "Khong co tuyen truc tiep giua tram " << start + 1 << " va tram " << end + 1 << "." << endl;
	        } else {
	            cout << "Khoang cach ngan nhat giua tram " << start + 1 << " va tram " << end + 1 << " la: " << dist[end] << endl;
	            cout << "Duong di: ";
	            inDuongDi(parent, end);
	            cout << end + 1 << endl;
	        }
	    }
	
	    // Ham in ra duong di tu tram bat dau den tram ket thuc
	    virtual void inDuongDi(int parent[], int i) {
	        if (parent[i] == -1) {
	            return;
	        }
	        inDuongDi(parent, parent[i]);
	        cout << parent[i] + 1 << " -> ";
	    }
	};


class Admin :public BusRoute {
	private:
		string adminName;
		string adminPass;
	public:
		Admin() : adminName("admin"), adminPass("1") {}
		bool authenticate() {
	        string user, pass;
	        cout << "Nhap ten dang nhap: ";
	        cin.ignore();
	        getline(cin,user);
	        cout << "Nhap mat khau: ";
	        getline(cin,pass);
	        return (user == adminName && pass == adminPass);
	    }
		//tao moi cac tram
	    void thietLapTram(BusRoute &route) {
	        cout << "Nhap so luong tram: ";
	        cin >> route.numStops;
	        for (int i = 0; i < route.numStops; i++) {
	            for (int j = 0; j < route.numStops; j++) {
	                route.distance[i][j] = (i == j) ? 0 : INF; 
	            }
	        }
	
	        cout << "Da thiet lap " << route.numStops << " tram." << endl;
	
	        // Nhap khoang cach giua cac tram
	        route.nhapKhoangCachTheoTen();
	    }
	    void themTram(BusRoute &route) {
	        if (numStops >= MAX) {
	            cout << "Khong the them tram, da den gioi han toi da!" << endl;
	            return;
	        }
	        int tramMoi;
	        cout << "Nhap tram moi (so thu tu): ";
	        cin >> tramMoi;
	
	        if (tramMoi <= numStops) {
	            cout << "Tram da ton tai!" << endl;
	            return;
	        }
	        numStops++;
	        int tramKe, khoangCach;
	        cout << "Nhap tram ket noi (so thu tu): ";
	        cin >> tramKe;
	
	        if (tramKe > 0 && tramKe <= numStops - 1) {
	            cout << "Nhap khoang cach giua tram " << tramMoi << " va tram " << tramKe << ": ";
	            cin >> khoangCach;
	            distance[tramKe - 1][tramMoi - 1] = khoangCach; 
	            distance[tramMoi - 1][tramKe - 1] = khoangCach;
	        } else {
	            cout << "Tram ket noi khong hop le!" << endl;
	        }
	    }
	    void xoaTram(BusRoute &route) {
	        int tramXoa;
	        cout << "Nhap tram can xoa (so thu tu): ";
	        cin >> tramXoa;
	
	        if (tramXoa <= 0 || tramXoa > numStops) {
	            cout << "Tram khong hop le!" << endl;
	            return;
	        }
	        tramXoa--;
	        for (int i = 0; i < numStops; i++) {
	            distance[tramXoa][i] = INF; 
	            distance[i][tramXoa] = INF;
	        }
	        numStops--;
	        cout << "Da xoa tram " << tramXoa + 1 << endl;
	    }
	    void capNhatKhoangCach(BusRoute &route) {
	        int tram1, tram2, khoangCach;
	        cout << "Nhap tram 1 (so thu tu): ";
	        cin >> tram1;
	        cout << "Nhap tram 2 (so thu tu): ";
	        cin >> tram2;
	
	        cout << "Nhap khoang cach moi giua tram " << tram1 << " va tram " << tram2 << ": ";
	        cin >> khoangCach;
	
	        distance[tram1 - 1][tram2 - 1] = khoangCach; 
	        distance[tram2 - 1][tram1 - 1] = khoangCach;
	        cout << "Da cap nhat khoang cach giua tram " << tram1 << " va tram " << tram2 << endl;
	    }
	
	 
	    void capNhatKetNoi(BusRoute &route) {
	        nhapKhoangCachTheoTen();
	    }
	};

class User :public BusRoute  {
public:
    void timDuongDi(BusRoute &route) {
        int tram1, tram2;
        cout << "Nhap tram xuat phat: ";
        cin >> tram1;
        cout << "Nhap tram den: ";
        cin >> tram2;
        route.dijkstra(tram1 - 1, tram2 - 1);
    }
};

int main() {
    BusRoute route; 
    Admin admin;
    User user;

    int choice;
    do {
        cout << "=== MENU CHINH ===" << endl;
        cout << "1. Admin" << endl;
        cout << "2. User" << endl;
        cout << "3. Thoat" << endl;
        cout << "Nhap lua chon cua ban: ";
        cin >> choice;
		switch(choice){
			case 1:
				if(admin.authenticate()){
					int adminChoice;
		            do {
		               	cout << "=== MENU ADMIN ===" << endl;
				        cout << "1. Thiet lap tram\n";
				        cout << "2. Them tram\n";
				        cout << "3. Xoa tram\n";
				        cout << "4. Cap nhat khoang cach\n";
				        cout << "5. Cap nhat ket noi\n";
				        cout << "0. Thoat\n";
				        cout << "Nhap lua chon: ";
		                cin >> adminChoice;
		
		                switch(adminChoice){
		                	case 1:
		                		admin.thietLapTram(route); 
		                		break;
		                	case 2:
		                		admin.themTram(route);
		                		break;
		                	case 3:
		                		admin.xoaTram(route);
		                		break;
		                	case 4:
		                		admin.capNhatKhoangCach(route);
		                		break;
		                	case 5:
		                		admin.capNhatKetNoi(route);
		                		break;
		                	
						}
		            } while (adminChoice != 0);
				}else {
                    cout << "Dang nhap khong thanh cong." << endl;
                }
				break;
	        case 2:
	        	int userChoice;
	            do {
	                cout << "=== MENU USER ===" << endl;
                    cout << "1. Tim duong di ngan nhat" << endl;
                    cout << "2. Thoat" << endl;
	                cout << "Nhap lua chon: ";
	                cin >> userChoice;
					switch(userChoice){
						case 1:
							user.timDuongDi(route);
						case 2:
							break;
							
					}	                
	            } while (userChoice != 2);
	            break;
	        case 3:
                cout << "Thoat chuong trinh..." << endl;
                break;
	        default:
                cout << "Lua chon khong hop le!" << endl;
		}
    } while (choice != 0);

    return 0;
}

