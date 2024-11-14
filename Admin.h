#ifndef ADMIN_H
#define ADMIN_H

#include "BusRoute.h"
#include <string>
#include <conio.h>
#include <ctime> 

class Admin : public BusRoute {
	private:
	    string adminName;
	    string adminPass;
	
	public:
	    Admin();	
	    bool authenticate();	
	    void thietLapTram(BusRoute& route);	
	    void xoaTram(BusRoute& route);		
		void themTram(BusRoute& route);
	    void capNhatKhoangCach(BusRoute& route);
};
Admin::Admin(){
	adminName="admin";
	adminPass="1";
}
bool Admin::authenticate() {
    string user, pass;
    char ch;
    bool showPassword = false;
    int attempts = 0;

    while (attempts < 3) {
        cout << "Nhap ten dang nhap: ";
        if (attempts == 0) {
            cin.ignore();
        }
        getline(cin, user);
        cout << "Nhap mat khau: ";
        pass.clear();
        while (true) {
            ch = _getch();
            if (ch == 13) { 
                break;
            } else if (ch == 9) { 
                showPassword = !showPassword;
                cout << "\rNhập mật khẩu: ";
                if (showPassword) {
                    cout << pass;
                } else {
                    for (size_t i = 0; i < pass.length(); ++i) {
                        cout << '*';
                    }
                }
                continue;
            } else if (ch == 8 && !pass.empty()) { 
                pass.pop_back();
                cout << "\b \b";
            } else if (ch >= 32 && ch <= 126) { 
                pass += ch;
                cout << (showPassword ? ch : '*');
            }
        }
        cout << endl;
        if (user == adminName && pass == adminPass) {
            cout << "Đăng nhập thành công!" << endl;
            return true;
        } else {
            attempts++;
            cout << "Sai tên đăng nhập hoặc mật khẩu. ";
            if (attempts < 3) {
                cout << "Vui lòng nhập lại. Còn " << 3 - attempts << " lần nhập\n";
            }
        }
    }
	cout << "Đăng nhập thất bại! Đăng nhập lay sau: \n";
    clock_t start_time = clock();
    int lock_duration = 30; 
    while (true) {
        clock_t current_time = clock();
        double elapsed_time = (double)(current_time - start_time) / CLOCKS_PER_SEC;
        int remaining_time = lock_duration - (int)elapsed_time;

        if (remaining_time <= 0) {
			cout<<endl;
            break;
        }
        cout << "\rThời gian còn lại: " << remaining_time << " s ";
        cout.flush(); 
    }
    return false;
}
void Admin::thietLapTram(BusRoute& route) {
	int stops;
	do {
        cout << "Nhập số lượng trạm: ";cin >> stops;
        if (cin.fail()) {
            cout << "Vui lòng nhập số.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        } 
        else if (!cin.fail()&&stops < 2) {
            cout << "Nhập tối thiểu 2 trạm.\n";
        }
        else if (stops > 100) {
            cout << "Số lượng trạm không được quá 100.\n";
        }
    } while (stops < 2 || stops > 100);
	route.setNumStops(stops);
	cin.ignore(); 
	route.nhapTenTram();
	for (int i = 0; i < route.getNumStops(); i++) {
	    for (int j = 0; j < route.getNumStops(); j++) {
	        route.setDistance(i, j, (i == j) ? 0 : INF);
	    }
	}
	cout << "Đã thiết lập " << route.getNumStops() << " trạm." << endl;
	route.nhapKhoangCachTheoTen();
}
void Admin::xoaTram(BusRoute& route) {
	string tenTramCanXoa;
	cout << "Nhập tên trạm cần xóa: ";
	cin.ignore();
	getline(cin, tenTramCanXoa);
	int idx = route.timTram(tenTramCanXoa);
	if (idx == -1) {
		cout << "Trạm không tồn tại!" << endl;
		return;
	}
	int ketNoi[MAX];
	int soLuongKetNoi = 0;
	for (int i = 0; i < route.getNumStops(); i++) {
		if (route.getDistance(i, idx) != INF && i != idx) {
		    ketNoi[soLuongKetNoi++] = i;  
		}
	}
	for (int i = 0; i < soLuongKetNoi; i++) {
		for (int j = i + 1; j < soLuongKetNoi; j++) {
		    int tram1 = ketNoi[i];
		    int tram2 = ketNoi[j];
		    int khoangCachMoi = route.getDistance(tram1, idx) + route.getDistance(idx, tram2);
		    if (khoangCachMoi < route.getDistance(tram1, tram2)) {
		        route.setDistance(tram1, tram2, khoangCachMoi);
		    }
		}
	}
	for (int i = idx; i < route.getNumStops() - 1; i++) {
		route.setNameStop(i, route.getNameStop(i + 1));
	}
	for (int i = idx; i < route.getNumStops() - 1; i++) {
		for (int j = 0; j < route.getNumStops(); j++) {
		    route.setDistance(i, j, route.getDistance(i + 1, j));
		    route.setDistance(j, i, route.getDistance(j, i + 1));
		}
	}
	route.setNumStops(route.getNumStops() - 1);
	cout << "Đã xóa trạm " << tenTramCanXoa << " và cập nhật lại các kết nối." << endl;
}
void Admin::themTram(BusRoute& route) {
	if (route.getNumStops() >= MAX) {
		cout << "Không thể thêm trạm đã đến giới hạn tối đa!" << endl;
		return;
	}
	string tenTramMoi;
	cout << "Nhập trạm mới: ";
	cin.ignore();
	getline(cin, tenTramMoi);
	if (route.timTram(tenTramMoi) != -1) {
		cout << "Tên trạm đã tồn tại." << endl;
		return;
	}
	route.setNameStop(route.getNumStops(), tenTramMoi);
	int tramMoiIdx = route.getNumStops();
	route.setNumStops(tramMoiIdx + 1);
	string tram1, tram2;
	int khoangCach1, khoangCach2;
	while (true) {
		cout << "Nhập trạm kết nối với trạm mới (nhập '0' để dừng): ";
		getline(cin, tram2);
		if (tram2 == "0") {break;}
		int idxTram2 = route.timTram(tram2);
		if (idxTram2 == -1) {
		    cout << "Trạm không tồn tại!" << endl;
		    continue;
		}
		cout << "Nhập trạm hiện đang kết nối với trạm "<<tram2<<": ";
		getline(cin, tram1);
		if (tram1 == "0") {
		    cout << "Nhập khoảng cách từ " << tenTramMoi << " đến " << tram2 << ": ";
		    cin >> khoangCach2;
		    cin.ignore();
			while(khoangCach2<0){
				cout << "Nhập lại khoảng cách: ";
				cin >> khoangCach2;
			}
			if (khoangCach2 > 0) {
		        route.setDistance(tramMoiIdx, idxTram2, khoangCach2);
		        route.setDistance(idxTram2, tramMoiIdx, khoangCach2);
				cout << "Đã cập nhật khoảng cách giữa " << tenTramMoi << " va " << tram2 << "." << endl;
		    } else {
		        cout << "Khoảng cách không hợp lệ!" << endl;
			}
			continue;
		}
		int idxTram1 = route.timTram(tram1);
		if (idxTram1 == -1) {
		    cout << "Tram " << tram1 <<" không hợp lệ!" << endl;
		    continue;
		}
		if (route.getDistance(idxTram1, idxTram2) != INF) {
		    cout << "Xóa khoảng cách giữa tram " << tram1 << " va tram " << tram2 << endl;
		    route.setDistance(idxTram1, idxTram2, INF);
		    route.setDistance(idxTram2, idxTram1, INF);
		    cout << "Nhập khoảng cách từ  " << tram1 << " đến " << tenTramMoi << ": ";
		    cin >> khoangCach1;
		    cin.ignore();
			while(khoangCach1<0){
				cout << "Nhập lại khoảng cách: ";
				cin >> khoangCach1;
			}
			cout << "Nhập khoảng cách từ " << tenTramMoi << " đến " << tram2 << ": ";
		    cin >> khoangCach2;
		    cin.ignore();
			while(khoangCach2<0){
				cout << "Nhập lại khoảng cách: ";
				cin >> khoangCach2;
			}
			if (khoangCach1 > 0 && khoangCach2 > 0) {
		        route.setDistance(idxTram1, tramMoiIdx, khoangCach1);
		        route.setDistance(tramMoiIdx, idxTram1, khoangCach1);
				route.setDistance(tramMoiIdx, idxTram2, khoangCach2);
		        route.setDistance(idxTram2, tramMoiIdx, khoangCach2);
				cout << "Đã cập nhật khoảng cách " << tram1 << " -> " << tenTramMoi << " -> " << tram2 << "." << endl;
		    } else {
		        cout << "Khoảng cách không hợp lệ!" << endl;
		    }
		} else {
		    cout << "Trạm " << tram1 << " và trạm " << tram2 << " không có kết nối trực tiếp!" << endl;
		}
	}
	cout << "Đã thêm trạm mới " << tenTramMoi << " và cập nhật các kết nối." << endl;
}
void Admin::capNhatKhoangCach(BusRoute& route) {
	string tram1, tram2;
	int khoangCach;
	cout << "Nhập trạm xuất phát: ";
	cin.ignore();
	getline(cin, tram1);
	cout << "Nhập trạm đến: ";
	getline(cin, tram2);
	cout << "Nhập khoảng cách mới: ";
	cin >> khoangCach;
	cin.ignore(); 
	while(khoangCach<0){
		cout << "Nhập lại khoảng cách: ";
		cin >> khoangCach;
	}
	int idx1 = route.timTram(tram1);
	int idx2 = route.timTram(tram2);
	if (idx1 != -1 && idx2 != -1 && khoangCach > 0) {
	    route.setDistance(idx1, idx2, khoangCach);
	    cout << "Đã cập nhất khoảng cách giữa " << tram1 << " và " << tram2 << " thành " << khoangCach << "." << endl;
	} else {
	    cout << "Trạm không tồn tại!" << endl;
	}
}

#endif
