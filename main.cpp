#include "BusRoute.h"
#include "Admin.h"
#include "User.h"
#include <iostream>

using namespace std;

int main() {
    BusRoute route;
    Admin admin;
    User user;
    int luaChon;
    do {
        cout << "------------------- MENU -------------------" << endl;
        cout << "1. Admin" << endl;
        cout << "2. User" << endl;
        cout << "0. Thoat" << endl;
        cout << "Nhap lua chon: ";
        cin >> luaChon;

        switch (luaChon) {
            case 1:
                if (admin.authenticate()) {
                    int adminChoice;
                    do {
                        cout << "---------- Admin Menu ----------" << endl;
                        cout << "1. Thiet lap tram" << endl;
                        cout << "2. Them tram" << endl;
                        cout << "3. Xoa tram" << endl;
                        cout << "4. Cap nhat khoang cach" << endl;
                        cout << "0. Quay lai" << endl;
                        cout << "Nhap lua chon: ";
                        cin >> adminChoice;

                        switch (adminChoice) {
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
                        }
                    } while (adminChoice != 0);
                } else {
                    cout << "Sai thong tin dang nhap!" << endl;
                }
                break;

            case 2:
                int userChoice;
                do {
                    cout << "---------- User Menu ----------" << endl;
                    cout << "1. Dang ki tai khoan" << endl;
                    cout << "2. Dang nhap" << endl;
                    cout << "3. Tim kiem duong di ngan nhat" << endl;
                    cout << "4. Lich su tim kiem" << endl;
                    cout << "5. Hien thi tat ca cac tram" << endl;
                    cout << "0. Quay lai" << endl;
                    cout << "Nhap lua chon: ";
                    cin >> userChoice;

                    switch (userChoice) {
                        case 1:
                            user.dangKyTaiKhoan();
                            break;
                        case 2:
                            user.dangNhap();
                            break;
                        case 3:
                            user.timDuongDiNganNhat(route);
                            break;
                        case 4:
                            user.hienThiLichSuTimKiem();
                            break;
                        case 5:
                            user.hienThiTatCaTram(route);
                            break;
                    }
                } while (userChoice != 0);
                break;
        }
    } while (luaChon != 0);

    return 0;
}
