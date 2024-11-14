#ifndef USER_H
#define USER_H

#include "BusRoute.h"
#include <string>
#include <ctime>
#include <iomanip>
#include <conio.h>
#include <regex>

const int MAX_USERS = 1000;
const int MAX_SEARCH_HISTORY=20;
struct UserAccount { 
    string username;
    string password;
    string gmail;
};

class User : public BusRoute {
    private:
        UserAccount accounts[MAX_USERS];
        int soLuongNguoiDung;
        int currentUserIndex;
        string lichSuTimKiem[MAX_USERS][MAX_SEARCH_HISTORY][2];
        time_t thoiGianTimKiem[MAX_USERS][MAX_SEARCH_HISTORY];      
        int soLanTimKiem[MAX_USERS];       
    public:
        User();
        void dangKyTaiKhoan();
        bool isValidEmail(const string& email);
        bool dangNhap();
        void dangXuat();
        void timDuongDiNganNhat(BusRoute& route);
        void hienThiLichSuTimKiem() const;
        void hienThiDanhSachTram(const BusRoute& busRoute) const;
};
User::User() {
    soLuongNguoiDung = 0;
    currentUserIndex = -1;
    for (int i = 0; i < MAX_USERS; i++) {
        soLanTimKiem[i] = 0;
    }
}
bool User::isValidEmail(const string& email) {
    const string validDomains[] = {
        "@gmail.com", "@yahoo.com", "@hotmail.com", "@outlook.com",
        "@icloud.com", "@aol.com", "@zoho.com", "@protonmail.com",
        "@mail.com", "@st.utc2.edu.vn", "@yandex.com"
    };
    const int domainCount = sizeof(validDomains) / sizeof(validDomains[0]);
    size_t atPos = email.find('@');
    if (atPos == string::npos || atPos == 0 || atPos == email.length() - 1) {
        return false; 
    }
    string domain = email.substr(atPos);
    bool domainIsValid = false;
    for (int i = 0; i < domainCount; ++i) {
        if (domain == validDomains[i]) {
            domainIsValid = true;
            break;
        }
    }
    if (!domainIsValid) return false;
    for (size_t i = 0; i < atPos; ++i) {
        char ch = email[i];
        if (!(isalnum(ch) || ch == '.' || ch == '_')) {
            return false;
        }
    }
    return true;
}
void User::dangKyTaiKhoan() {
    if (soLuongNguoiDung >= MAX_USERS) {
        cout << "Đã đạt giới hạn tối đa người dùng!" << endl;
        return;
    }
    string identifier, username, gmail, password;
    cout << "Nhập tên đăng nhập hoặc email: ";
    cin.ignore();
    getline(cin, identifier);
    //Kiem tra xem co dung dinh dang mail
    bool isEmail = isValidEmail(identifier);
    if (isEmail) {
        gmail = identifier;
        for (int i = 0; i < soLuongNguoiDung; i++) {
            if (accounts[i].gmail == gmail) {
                cout << "Email đã được đăng ký! Vui lòng nhập Email khác." << endl;
                return;
            }
        }
    } else {
        if (identifier.find('@') != string::npos) {
            cout << "Email không hợp lệ! Vui lòng nhập đúng định dạng email." << endl;
            return;
        }
        username = identifier;
        if (username.empty()) {
            cout << "Tên đăng nhập không được để trống!" << endl;
            return;
        }
        for (int i = 0; i < soLuongNguoiDung; i++) {
            if (accounts[i].username == username) {
                cout << "Tên đăng nhập đã tồn tại! Vui lòng nhập tên khác." << endl;
                return;
            }
        }
    }
    char ch;
    bool showPassword = false;
    do {
        cout << "Nhập mật khẩu: ";
        password.clear();
        while (true) {
            ch = _getch();
            if (ch == 13) { 
                break;
            } else if (ch == 9) { 
                showPassword = !showPassword;
                cout << "\rNhập mật khẩu: ";
                if (showPassword) {
                    cout << password;
                } else {
                    for (size_t i = 0; i < password.length(); ++i) {
                        cout << '*';
                    }
                }
                continue;
            } else if (ch == 8 && !password.empty()) { 
                password.pop_back();
                cout << "\b \b";
            } else if (ch >= 32 && ch <= 126) { 
                password += ch;
                cout << (showPassword ? ch : '*');
            }
        }
        if(password.empty()){ cout << "\nMật khẩu không được để trống!" << endl; }
    } while(password.empty());
    accounts[soLuongNguoiDung].username = username;
    accounts[soLuongNguoiDung].gmail = gmail;
    accounts[soLuongNguoiDung].password = password;
    soLuongNguoiDung++;
    cout << "\nĐăng ký thành công!" << endl;
}
bool User::dangNhap() {
    if (currentUserIndex != -1) { 
        cout << "Bạn phải đăng xuất trước khi đăng nhập!" << endl;
        return false;
    }
    if (soLuongNguoiDung == 0) {
        cout << "Không có tài khoản nào. Vui lòng đăng ký trước!" << endl;
        return false;
    }
    string username, password;
    char ch;
    bool showPassword = false;
    int attempts = 0; 
    while (attempts < 3) { 
        do {
            cout << "Nhập tên đăng nhập: ";
            cin.ignore();
            getline(cin, username);
            if (username.empty()) {
                cout << "Tên đăng nhập không được để trống!" << endl;
            }
        } while (username.empty());
        do {
            cout << "Nhập mật khẩu: ";
            password.clear();
            while (true) {
                ch = _getch();
                if (ch == 13) { 
                    break;
                } else if (ch == 9) { 
                    showPassword = !showPassword;
                    cout << "\rNhập mật khẩu: ";
                    if (showPassword) {
                        cout << password;
                    } else {
                        for (size_t i = 0; i < password.length(); ++i) {
                            cout << '*';
                        }
                    }
                    continue;
                } else if (ch == 8 && !password.empty()) { 
                    password.pop_back();
                    cout << "\b \b";
                } else if (ch >= 32 && ch <= 126) { 
                    password += ch;
                    cout << (showPassword ? ch : '*');
                }
            }
            if (password.empty()) {
                cout << "\nMật khẩu không được để trống!" << endl;
            }
        } while (password.empty());
        for (int i = 0; i < soLuongNguoiDung; i++) {
            if (accounts[i].username == username && accounts[i].password == password||(accounts[i].gmail == username && accounts[i].password == password)) {
                currentUserIndex = i;
                cout << "\nĐăng nhập thành công!" << endl;
                return true;
            }
        }
        cout << "\nSai tên đăng nhập hoặc mật khẩu!\n";
        attempts++;
        if (attempts < 3) {
            cout << "Vui lòng nhập lại. Còn " << 3 - attempts << " lần nhập\n";
        }
        if (attempts >= 3) {
            cout << "Đăng nhập thất bại! Đăng nhập sau:\n";
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
        }
    }
    return false;
}
void User::dangXuat() {
    if (currentUserIndex != -1) {
        currentUserIndex = -1;
        cout << "Đăng xuất thành công!" << endl;
    } else {
        cout << "Không có tài khoản nào đăng nhập." << endl;
    }
}
void User::timDuongDiNganNhat(BusRoute& route) {
    if (currentUserIndex == -1) {
        cout << "Bạn phải đăng nhập trước khi tìm đường!" << endl;
        return;
    }
   string startTram, endTram, stopoverTram;
    do {
        cout << "Nhập trạm xuất phát: ";
        cin.ignore();
        getline(cin, startTram);
        if (startTram.empty()) {
            cout << "Tên trạm không được để trống!" << endl;
        }
    } while (startTram.empty());

    do {
        cout << "Nhập trạm đến: ";
        getline(cin, endTram);
        if (endTram.empty()) {
            cout << "Tên trạm không được để trống!" << endl;
        }
    } while (endTram.empty());
    cout << "Bạn có muốn thêm điểm dừng không? (y/n): ";
    char choice;
    cin >> choice;
    bool hasStopover = (choice == 'y' || choice == 'Y');
    if (hasStopover) {
        do {
            cout << "Nhập trạm dừng: ";
            cin.ignore();
            getline(cin, stopoverTram);
            if (stopoverTram.empty()) {
                cout << "Tên trạm không được để trống!" << endl;
            }
        } while (stopoverTram.empty());
        cout << "\nTìm đường từ " << startTram << " đến " << stopoverTram << " đến " << endTram << "...\n";
        route.dijkstra(startTram, stopoverTram);
        route.dijkstra(stopoverTram, endTram);

    } else {
        route.dijkstra(startTram, endTram);
    }
    cout << "Bạn có muốn đảo chiều hành trình không? (y/n): ";
    cin >> choice;
    bool reverseRoute = (choice == 'y' || choice == 'Y');
    if (reverseRoute) {
        if (hasStopover) {
            cout << "\nTìm đường quay lại từ " << endTram << " đến " << stopoverTram << " đến " << startTram << "...\n";
            route.dijkstra(endTram, stopoverTram);
            route.dijkstra(stopoverTram, startTram);
        } else {
            cout << "\nTìm đường quay lại từ " << endTram << " đến " << startTram << "...\n";
            route.dijkstra(endTram, startTram);
        }
    }
    if (soLanTimKiem[currentUserIndex] < MAX_SEARCH_HISTORY) {
        lichSuTimKiem[currentUserIndex][soLanTimKiem[currentUserIndex]][0] = startTram;
        lichSuTimKiem[currentUserIndex][soLanTimKiem[currentUserIndex]][1] = endTram;
        thoiGianTimKiem[currentUserIndex][soLanTimKiem[currentUserIndex]] = time(nullptr);
        soLanTimKiem[currentUserIndex]++;
    } else {
        cout << "Số lần tìm kiếm đã đạt giới hạn tối đa.\n";
    }
}
void User::hienThiLichSuTimKiem() const {
    if (currentUserIndex == -1) {
        cout << "Bạn phải đăng nhập trước khi xem lịch sử!" << endl;
        return;
    }
    if (soLanTimKiem[currentUserIndex] == 0) {
        cout << "Người dùng chưa có lịch sử tìm kiếm." << endl;
        return;
    }
    
    // Khung tiêu đề
    cout << "=====================================================================" << endl;
    cout << "|                   Lịch sử tìm kiếm của " << accounts[currentUserIndex].username;
    cout << "                   |" << endl;
    cout << "|===================================================================|" << endl;
    for (int i = 0; i < soLanTimKiem[currentUserIndex]; i++) {
        tm* thoiGianTm = localtime(&thoiGianTimKiem[currentUserIndex][i]);
        if (thoiGianTm) {
            cout << "| " << lichSuTimKiem[currentUserIndex][i][0] << " -> " 
                 << lichSuTimKiem[currentUserIndex][i][1] << " (Thời gian: " 
                 << put_time(thoiGianTm, "%d/%m/%y %H:%M") << ")"
                 << setw(32) << " |" << endl;  
        } else {
            cout << "| Lỗi khi lấy thời gian tìm kiếm!                        |" << endl;
        }
    }
    
    cout << "=====================================================================" << endl;
}

void User::hienThiDanhSachTram(const BusRoute& busRoute) const {
    int soLuongTram = busRoute.getNumStops();
     setTextColor(6);
    cout << "\n=========== Danh sách các trạm hiện có ============\n";
    for (int i = 0; i < soLuongTram; ++i) {
        cout << "| ";
        
        setTextColor(15); 
        cout << "- Trạm: " << busRoute.getNameStop(i);
        setTextColor(6); 
        cout << string(40 - busRoute.getNameStop(i).size(), ' ') << "|\n";
    }
    cout << "====================================================\n";
    
    setTextColor(7);
}
#endif
