#ifndef USER_H
#define USER_H

#include "BusRoute.h"
#include <string>

const int MAX_USERS = 1000;
struct UserAccount {
    string username;
    string password;
};
class User : public BusRoute {
	private:
	    int soLanTimKiem;
	    string lichSuTimKiem[MAX][2];
	    UserAccount accounts[MAX_USERS];//luu tai khoan user
	    time_t thoiGianTimKiem[MAX];
	    int soLuongNguoiDung; 
	    int currentUserIndex; 
	public:
	    User();
	    void dangKyTaiKhoan();    
	    bool dangNhap();
	    void timDuongDiNganNhat(BusRoute& route);
	
	    void hienThiLichSuTimKiem() const;
	
	    void hienThiTatCaTram(BusRoute route) const;
};
User::User(){
	soLanTimKiem=0;
	soLuongNguoiDung=0;
	currentUserIndex=-1;
}
void User::dangKyTaiKhoan() {
    if (soLuongNguoiDung >= MAX_USERS) {
        cout << "Da dat gioi han toi da nguoi dung!" << endl;
        return;
    }
    string username, password;
    cout << "Nhap ten dang nhap: ";
    cin.ignore();
    getline(cin, username);
    for (int i = 0; i < soLuongNguoiDung; i++) {
        if (accounts[i].username == username) {
            cout << "Ten dang nhap da ton tai. Vui long chon ten khac!" << endl;
            return;
        }
    }
    cout << "Nhap mat khau: ";
    getline(cin, password);
    accounts[soLuongNguoiDung].username = username;
    accounts[soLuongNguoiDung].password = password;
    soLuongNguoiDung++;
	cout << "Dang ky thanh cong!" << endl;
}
bool User::dangNhap() {
    if (soLuongNguoiDung == 0) {
        cout << "Không có tài khoản nào. Vui long dang ki truoc!" << endl;
        return false;
    }
    string username, password;
    cout << "Nhap ten dang nhap: ";
    cin.ignore();
    getline(cin, username);
    cout << "Nhap mat khau: ";
    getline(cin, password);
    for (int i = 0; i < soLuongNguoiDung; i++) {
        if (accounts[i].username == username && accounts[i].password == password) {
            currentUserIndex = i;
            cout << "Dang nhap thanh cong!" << endl;
        	return true;
        }
    }
    cout << "Sai ten dang nahp hoac mat khau!" << endl;
    return false;
}
void User::timDuongDiNganNhat(BusRoute& route) {
    if (currentUserIndex == -1) {
        cout << "Ban phai dang nhap truoc khi tim duong!" << endl;
        return;
    }
    string startTram, endTram;
    cout << "Nhap tram xuat phat: ";
    cin.ignore();
    getline(cin, startTram);
    cout << "Nhap tram den: ";
    getline(cin, endTram);
    route.dijkstra(startTram, endTram);
    if (soLanTimKiem < MAX) {
        lichSuTimKiem[soLanTimKiem][0] = startTram;
        lichSuTimKiem[soLanTimKiem][1] = endTram;
        thoiGianTimKiem[soLanTimKiem] = time(0);
        soLanTimKiem++;
    }
}
void User::hienThiLichSuTimKiem() const {
    if (currentUserIndex == -1) {
        cout << "Ban phai dang nhap truoc khi xem lich su!" << endl;
        return;
    }
    cout << "Lich su tim kiem:\n";
    for (int i = 0; i < soLanTimKiem; i++) {
        string thoiGian = ctime(&thoiGianTimKiem[i]); // Chuy?n �?i th?i gian th�nh chu?i
        if (!thoiGian.empty() && thoiGian[thoiGian.length() - 1] == '\n') {
		    thoiGian.erase(thoiGian.length() - 1); // Removes the last character
		}

        cout << lichSuTimKiem[i][0] << " -> " << lichSuTimKiem[i][1] << " (Thoi gian: " << thoiGian << ")" << endl;
    }
}

void User::hienThiTatCaTram(BusRoute route) const {
    if (currentUserIndex == -1) {
        cout << "Ban phai đang nhap truoc khi xem danh sach tram!" << endl;
        return;
    }
	cout << "Danh sach tat ca cac tram:\n";
    for (int i = 0; i < route.getNumStops(); i++) {
        cout << i + 1 << ". " << route.getNameStop(i) << endl;
    }
}

#endif
