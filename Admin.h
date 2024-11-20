#ifndef ADMIN_H
#define ADMIN_H

#include "BusRoute.h"
#include <string>
#include <conio.h>
#include <ctime> 
using namespace std;

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
		void hienThiTramVaKetNoi(BusRoute& route);
};
Admin::Admin(){
	adminName="admin";
	adminPass="12345";
}
bool Admin::authenticate() {
    string user, pass;
    char ch;
    bool showPassword = false;
    int attempts = 0;
    while (attempts < 3) {
        cout << "Nhập tên đăng nhập: ";
        if (attempts == 0) {
            cin.ignore();
        }
        getline(cin, user);
        cout << "Nhập mật khẩu: ";
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
			setTextColor(10);
            cout << "Đăng nhập thành công!" << endl;
			setTextColor(15);
            return true;
        } else {
            attempts++;
			setTextColor(12);
            cout << "Sai tên đăng nhập hoặc mật khẩu. \n";
			setTextColor(15);
            if (attempts < 3) {
                cout << "Vui lòng nhập lại. Còn " << 3 - attempts << " lần nhập\n";
            }
        }
    }
	setTextColor(14);
	cout << "Đăng nhập thất bại! Đăng nhập lại sau: \n";
	setTextColor(15);
    clock_t start_time = clock();
    int lock_duration = 30; 
    while (true) {
        clock_t current_time = clock();
        double elapsed_time = (double)(current_time - start_time) / CLOCKS_PER_SEC;
        int remaining_time = lock_duration - (int)elapsed_time;

        if (remaining_time <= 0) {
			cout << "\r                                    \r"; 
    		cout.flush();
			clearScreen();
            break;
        }else if(remaining_time<4){
			cout << "\rThời gian còn lại: " ;setTextColor(12);cout<< remaining_time << " s ";setTextColor(15);
        	cout.flush();
		}else{
			cout << "\rThời gian còn lại: " << remaining_time << " s ";
        	cout.flush(); 
		}
    }
    return false;
}
/*hien thi all tram va ket noi giua cac tram*/
/*loi khi dang nhap mà thoat r nhap lai khong duoc*/
void Admin::thietLapTram(BusRoute& route) {
    if (route.getNumStops() > 0) {
        cout << "Hiện tại đã có " << route.getNumStops() << " trạm.\n";
        cout << "Bạn muốn:\n";
		setTextColor(9);
		cout << "=====================================================\n";
        cout << "|";
		setTextColor(2);
		cout << " 1. Thiết lập mới.                            ";
		setTextColor(9);
		cout << "     |\n";
		cout << "|";
		setTextColor(2);
		cout << " 2. Cập nhật (thêm trạm mới từ trạm tiếp theo).";
		setTextColor(9);
		cout << "    |\n";
		cout << "|";
		setTextColor(2);
		cout << " 0. Thoát.                                         ";
		setTextColor(9);
		cout << "|\n";
		cout << "=====================================================\n";
        setTextColor(14);
		cout << "=> Nhập lựa chọn: ";
		setTextColor(15);
        int choice;
        do {
            cin >> choice;
            if (cin.fail() || (choice < 0 || choice > 2)) {
                setTextColor(14);
                cout << "Vui lòng nhập 0, 1 hoặc 2.\n";
                setTextColor(15);
                cin.clear();
                cin.ignore(10000, '\n');
            } else {
                break;
            }
        } while (true);
        switch (choice) {
            case 1: 
                route.clearStops();
				clearScreen();
                cout << "Danh sách trạm đã được xóa.\n";
				char choice;
				do {
					setTextColor(10);
					cout << "Bạn có muốn tiếp tục (y/n): ";
					cin >> choice;
					setTextColor(15);
					if (choice == 'y' || choice == 'Y') {
						break; 
					} else if (choice == 'n' || choice == 'N') {
						cout << "Thoát.\n";
						return; 
					} else {
						setTextColor(14);
						cout << "Vui lòng nhập y or n.\n";
						setTextColor(15);
					}
				} while (true);
            case 2: 
                cout << "Cập nhật từ trạm số " << route.getNumStops() + 1 << ".\n";
                break;
            case 0: 
                clearScreen();
                return;
        }
    }
    int stops;
    while(true) {
        cout << "Nhập số lượng trạm: ";
        cin >> stops;
        if (cin.fail()) {
            setTextColor(14);
            cout << "Vui lòng nhập số.\n";
            setTextColor(15);
			cin.clear();
			cin.ignore(1000, '\n');
            continue;
        } else if (!cin.fail() && stops < 2) {
            setTextColor(14);
            cout << "Nhập tối thiểu 2 trạm.\n";
            setTextColor(15);
			continue;
        } else if (stops > 100) {
            setTextColor(14);
            cout << "Số lượng trạm không được quá 100.\n";
            setTextColor(15);
			continue;
        } else{
			break;
		}
    }
    int currentStops = route.getNumStops();
    route.setNumStops(currentStops + stops);
    cin.ignore(); 
    if (currentStops == 0) {
        route.nhapTenTram(0); 
    } else {
        route.nhapTenTram(currentStops);
    }

    for (int i = 0; i < route.getNumStops(); i++) {
        for (int j = 0; j < route.getNumStops(); j++) {
            if (i < currentStops && j < currentStops) continue;
            route.setDistance(i, j, (i == j) ? 0 : INF);
        }
    }
    cout << "Đã thiết lập " << route.getNumStops() << " trạm." << endl;
    route.nhapKhoangCachTheoTen();
	clearScreen();
	setTextColor(10);
	cout <<"Thiết lập thành công!"<<endl;
	setTextColor(14);
}
void Admin::xoaTram(BusRoute& route) {
	string tenTramCanXoa;
	cout << "Nhập tên trạm cần xóa: ";
	cin.ignore();
	getline(cin, tenTramCanXoa);
	int idx = route.timTram(tenTramCanXoa);
	while (idx == -1) {
		setTextColor(14);
		cout << "Trạm không tồn tại!" << endl;
		setTextColor(15);
		cout << "Nhập tên trạm cần xóa: ";
		getline(cin, tenTramCanXoa);
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
	clearScreen();
	setTextColor(10);
	cout << "Đã xóa trạm " << tenTramCanXoa << " và cập nhật lại các kết nối." << endl;
	setTextColor(15);
}
void Admin::themTram(BusRoute& route) {
	if (route.getNumStops() >= MAX) {
		setTextColor(14);
		cout << "Không thể thêm trạm đã đến giới hạn tối đa!" << endl;
		setTextColor(15);
		return;
	}
	string tenTramMoi;
	cout << "Nhập tên trạm mới: ";
	cin.ignore();
	getline(cin, tenTramMoi);
	while (route.timTram(tenTramMoi) != -1) {
		setTextColor(14);
		cout << "Tên trạm đã tồn tại." << endl;
		setTextColor(15);
		cout << "Nhập tên trạm mới: ";
		getline(cin, tenTramMoi);
	}
	route.setNameStop(route.getNumStops(), tenTramMoi);
	int tramMoiIdx = route.getNumStops();
	route.setNumStops(tramMoiIdx + 1);
	string tram1, tram2;
	int khoangCach1, khoangCach2;
	while (true) {
		cout << "Nhập trạm kết nối với trạm mới (nhập '0' để dừng): ";
		getline(cin, tram2);
		if(tram2==tenTramMoi){
			setTextColor(14);
			cout << "Không được nhập trùng."<< endl;
			setTextColor(15);
			continue;
		}
		if (tram2 == "0") {break;}
		int idxTram2 = route.timTram(tram2);
		if (idxTram2 == -1) {
			setTextColor(14);
		    cout << "Trạm không tồn tại!" << endl;
			setTextColor(15);
		    continue;
		}
		cout << "Nhập trạm hiện đang kết nối với trạm "<<tram2<<" (nhập '0' nếu không có): ";
		getline(cin, tram1);
		if(tram1==tenTramMoi||tram1==tram2){
			setTextColor(14);
			cout << "Không được nhập trùng."<< endl;
			setTextColor(15);continue;
		}
		if (tram1 == "0") {
		    cout << "Nhập khoảng cách từ " << tenTramMoi << " đến " << tram2 << ": ";
			while(true){
				cin >> khoangCach2;
				cin.ignore();
				if(cin.fail()||khoangCach2<=0){
					cin.clear();
					cin.ignore(1000, '\n');
					setTextColor(12);
					cout <<"Không hợp lệ"<<endl;
					setTextColor(15);
					cout << "Nhập lại khoảng cách giữa " << tenTramMoi << " và " << tram2 << ": ";		
				}else {
					break;
				}
			}
			if (khoangCach2 > 0) {
		        route.setDistance(tramMoiIdx, idxTram2, khoangCach2);
		        route.setDistance(idxTram2, tramMoiIdx, khoangCach2);
				cout << "Đã cập nhật khoảng cách giữa " << tenTramMoi << " va " << tram2 << "." << endl;
		    } else {
				setTextColor(12);
		        cout << "Khoảng cách không hợp lệ!" << endl;
				setTextColor(15);
			}
			continue;
		}
		int idxTram1 = route.timTram(tram1);
		if (idxTram1 == -1) {
			setTextColor(12);
		    cout << "Trạm " << tram1 <<" không hợp lệ!" << endl;
			setTextColor(15);
		    continue;
		}
		if (route.getDistance(idxTram1, idxTram2) != INF) {
		    cout << "Xóa khoảng cách giữa trạm " << tram1 << " và trạm " << tram2 << endl;
		    route.setDistance(idxTram1, idxTram2, INF);
		    route.setDistance(idxTram2, idxTram1, INF);
		    cout << "Nhập khoảng cách từ  " << tram1 << " đến " << tenTramMoi << ": ";
			while(true){
				cin >> khoangCach1;
		    	cin.ignore();
				if(cin.fail()||khoangCach1<=0){
					cin.clear();
					cin.ignore(1000, '\n');
					setTextColor(12);
					cout <<"Không hợp lệ"<<endl;
					setTextColor(15);
					cout << "Nhập lại khoảng cách giữa " << tram1 << " và " << tenTramMoi << ": ";		
				}else {
					break;
				}
			}
			cout << "Nhập khoảng cách từ " << tenTramMoi << " đến " << tram2 << ": ";
		    while(true){
				cin >> khoangCach2;
		    	cin.ignore();
				if(cin.fail()||khoangCach2<=0){
					cin.clear();
					cin.ignore(1000, '\n');
					setTextColor(12);
					cout <<"Không hợp lệ"<<endl;
					setTextColor(15);
					cout << "Nhập lại khoảng cách giữa " << tenTramMoi << " và " << tram2 << ": ";		
				}else {
					break;
				}
			}
			if (khoangCach1 > 0 && khoangCach2 > 0) {
		        route.setDistance(idxTram1, tramMoiIdx, khoangCach1);
		        route.setDistance(tramMoiIdx, idxTram1, khoangCach1);
				route.setDistance(tramMoiIdx, idxTram2, khoangCach2);
		        route.setDistance(idxTram2, tramMoiIdx, khoangCach2);
				cout << "Đã cập nhật khoảng cách " << tram1 << " -> " << tenTramMoi << " -> " << tram2 << "." << endl;
		    } else {
				setTextColor(12);
		        cout << "Khoảng cách không hợp lệ!" << endl;
				setTextColor(15);
		    }
		} else {
		    cout << "Trạm " << tram1 << " và trạm " << tram2 << " không có kết nối trực tiếp!" << endl;
		}
	}
	cout << "Đã thêm trạm mới " << tenTramMoi << " và cập nhật các kết nối." << endl;
}
#include <iomanip>  // For std::setw and std::left

void Admin::hienThiTramVaKetNoi(BusRoute& route) {
    clearScreen();
    setTextColor(14);
    cout << "========================================================" << endl;
    cout << "|   "; setTextColor(15);
    cout << std::setw(50) << std::left << "Danh sách các trạm và kết nối:"; 
    setTextColor(14);
    cout << "          |" << endl;
    cout << "========================================================" << endl;

    if (route.getNumStops() == 0) {
        setTextColor(14);
        cout << "| "; setTextColor(15); 
        cout << std::setw(54) << std::left << "Danh sách chưa có trạm và kết nối"; 
        setTextColor(14); 
        cout << "         |" << endl;
        cout << "========================================================" << endl;
        return;
    }

    for (int i = 0; i < route.getNumStops(); i++) {
        cout << "| "; setTextColor(15); 
        cout << std::setw(50) << std::left << ("Trạm " + route.getNameStop(i) + " kết nối với:");
        setTextColor(14); 
        cout << "           |" << endl;

        bool hasConnection = false;
        for (int j = 0; j < route.getNumStops(); j++) {
            int distance = route.getDistance(i, j);
            if (i != j && distance != INF) {
                cout << "|   "; setTextColor(15);
                cout << std::setw(50) << std::left 
                     << ("- Trạm " + route.getNameStop(j) + " với khoảng cách: " + std::to_string(distance));
                setTextColor(14); 
                cout << "        |" << endl;
                hasConnection = true;
            }
        }

        if (!hasConnection) {
            setTextColor(14);
            cout << "|   "; setTextColor(15); 
            cout << std::setw(50) << std::left << "- Chưa có kết nối với trạm nào.";
            setTextColor(14); 
            cout << "|" << endl;
        }
        cout << "========================================================" << endl;
    }
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
	while(true){
		cin >> khoangCach;
	    cin.ignore();
		if(cin.fail()||khoangCach<=0){
			cin.clear();
			cin.ignore(1000, '\n');
			setTextColor(14);
			cout <<"Không hợp lệ"<<endl;
			setTextColor(15);
			cout << "Nhập lại khoảng cách mới giữa " << tram1 << " và " << tram2 << ": ";		
		}else {
			break;
		}
	}
	int idx1 = route.timTram(tram1);
	int idx2 = route.timTram(tram2);
	if (idx1 != -1 && idx2 != -1 && khoangCach > 0) {
	    route.setDistance(idx1, idx2, khoangCach);
	    cout << "Đã cập nhất khoảng cách giữa " << tram1 << " và " << tram2 << " thành " << khoangCach << "." << endl;
	} else {
		setTextColor(14);
	    cout << "Trạm không tồn tại!" << endl;
		setTextColor(15);
	}
}
#endif
