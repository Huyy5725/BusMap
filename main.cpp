#include "BusRoute.h"
#include "Admin.h"
#include "User.h"
#include <iostream>
#include <windows.h>

using namespace std;

void displayMainMenu();
void displayAdminMenu();
void displayUserMenu();
void setTextColor(int color);

void clearScreen();
int main() {
    SetConsoleOutputCP(CP_UTF8);
    BusRoute route;
    Admin admin;
    User user;
    route.loadFromFile("bus_route_data.txt");
    int luaChon;
    do {
        displayMainMenu();
        cin >> luaChon;
        clearScreen();
        switch (luaChon) {
            case 1:
                if (admin.authenticate()) {
                    int adminChoice;
                    clearScreen();
                    setTextColor(10);
                    cout <<"Đăng nhập thành công!"<<endl;
                    setTextColor(15);
                    do {
                        displayAdminMenu();
                        cin >> adminChoice;
                        clearScreen();
                        switch (adminChoice) {
                            case 1: admin.thietLapTram(route); break;
                            case 2: admin.themTram(route); break;
                            case 3: admin.xoaTram(route); break;
                            case 4: admin.capNhatKhoangCach(route); break;
                            case 5: admin.hienThiTramVaKetNoi(route);break;
                            case 0: break;
                            default: 
                                setTextColor(4);
                                cout << "Lựa chọn không hợp lệ.\n";
                                setTextColor(15);
                        }
                    } while (adminChoice != 0);
                }
                break;
            case 2: {
                int userChoice;
                do {
                    displayUserMenu();
                    cin >> userChoice;
                    clearScreen();
                    switch (userChoice) {
                        case 1: user.dangKyTaiKhoan();break;
                        case 2: user.dangNhap(); break;
                        case 3: user.dangXuat(); break;
                        case 4: user.hienThiDanhSachTram(route); break;
                        case 5: user.timDuongDiNganNhat(route); break;
                        case 6: user.hienThiLichSuTimKiem(); break;
                        case 0: {
                            setTextColor(10);
                            cout << "HẸN GẶP LẠI BẠN!\n";
                            setTextColor(15);break;
                        }
                        default: 
                            setTextColor(4);
                            cout << "Lựa chọn không hợp lệ.\n";
                            setTextColor(15);
                    }
                } while (userChoice != 0);
                break;
            }
            case 0:
                cout << "Thoát chương trình.\n";
                route.saveToFile("bus_route_data.txt");
                break;
            default:
                setTextColor(4);
                cout << "Lựa chọn không hợp lệ.\n";
                setTextColor(15);
        }
    } while (luaChon != 0);
    setTextColor(7); 
    return 0;
}
void displayMainMenu() {
    setTextColor(9);
    cout << "\n========================================\n";
    cout << "|               ";
    setTextColor(15);
    cout << "MENU CHÍNH";
    setTextColor(9);
    cout << "             |\n";
    cout << "========================================\n";
    cout << "|  ";
    setTextColor(15);
    cout << "1. Admin";
    setTextColor(9);
    cout << "                            |\n";
    cout << "|  ";
    setTextColor(15);
    cout << "2. User";
    setTextColor(9);
    cout << "                             |\n";
    cout << "|  ";
    setTextColor(15);
    cout << "0. Thoát";
    setTextColor(9);
    cout << "                            |\n";
    cout << "========================================\n";
    setTextColor(14);
    cout << "=> Nhập lựa chọn: ";
    setTextColor(15);
}

void displayAdminMenu() {
    setTextColor(5);
    cout << "\n========================================\n";
    cout << "|               ";
    setTextColor(15);
    cout << "MENU ADMIN";
    setTextColor(5);
    cout << "             |\n";
    cout << "========================================\n";
    cout << "|  ";
    setTextColor(15);
    cout << "1. Thiết lập trạm";
    setTextColor(5);
    cout << "                   |\n";  
    cout << "|  ";
    setTextColor(15);
    cout << "2. Thêm trạm";
    setTextColor(5);
    cout << "                        |\n"; 
    cout << "|  ";
    setTextColor(15);
    cout << "3. Xóa trạm";
    setTextColor(5);
    cout << "                         |\n"; 
    cout << "|  ";
    setTextColor(15);
    cout << "4. Cập nhật khoảng cách";
    setTextColor(5);
    cout << "             |\n";  
    cout << "|  ";
    setTextColor(15);
    cout << "5. Hiển thị tất cả trạm và kết nối.";
    setTextColor(5);
    cout << " |\n";  
    cout << "|  ";
    setTextColor(15);
    cout << "0. Quay lại";
    setTextColor(5);
    cout << "                         |\n"; 
    cout << "========================================\n";
    setTextColor(14);
    cout << "=> Nhập lựa chọn: ";
    setTextColor(15);
}
void displayUserMenu() {
    setTextColor(5);
    cout << "\n========================================\n";
    cout << "|               ";
    setTextColor(15);
    cout << "MENU USER";
    setTextColor(5);
    cout << "              |\n";
    cout << "========================================\n";
    cout << "|  ";
    setTextColor(15);
    cout << "1. Đăng kí tài khoản";
    setTextColor(5);
    cout << "                |\n";
    cout << "|  ";
    setTextColor(15);
    cout << "2. Đăng nhập";
    setTextColor(5);
    cout << "                        |\n";
    cout << "|  ";
    setTextColor(15);
    cout << "3. Đăng xuất";
    setTextColor(5);
    cout << "                        |\n";
    cout << "|  ";
    setTextColor(15);
    cout << "4. Hiển thị danh sách trạm";
    setTextColor(5);
    cout << "          |\n";
    cout << "|  ";
    setTextColor(15);
    cout << "5. Tìm kiếm đường đi ngắn nhất";
    setTextColor(5);
    cout << "      |\n";
    cout << "|  ";
    setTextColor(15);
    cout << "6. Lịch sử tìm kiếm";
    setTextColor(5);
    cout << "                 |\n";
    cout << "|  ";
    setTextColor(15);
    cout << "0. Quay lại";
    setTextColor(5);
    cout << "                         |\n";
    cout << "========================================\n";
    setTextColor(14);
    cout << "=> Nhập lựa chọn: ";
    setTextColor(15);
}
