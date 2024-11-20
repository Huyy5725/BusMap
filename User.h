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
        void saveToFile(const std::string& filename);
        void loadFromFile(const std::string& filename);
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
        setTextColor(14);
        cout << "Đã đạt giới hạn tối đa người dùng!" << endl;
        setTextColor(15);
        return;
    }
    string identifier, username, gmail, password;
    while (true) {
        cout << "Nhập tên đăng nhập hoặc email: ";
        cin.ignore();
        getline(cin, identifier);
        bool isEmail = isValidEmail(identifier);
        if (isEmail) {
            gmail = identifier;
            bool emailExists = false;
            for (int i = 0; i < soLuongNguoiDung; i++) {
                if (accounts[i].gmail == gmail) {
                    emailExists = true;
                    break;
                }
            }
            if (emailExists) {
                setTextColor(14);
                cout << "Email đã được đăng ký! Vui lòng nhập Email khác." << endl;
                setTextColor(15);
                continue;  
            }
            break; 
        } else {
            if (identifier.find('@') != string::npos) {
                setTextColor(14);
                cout << "Email không hợp lệ! Vui lòng nhập đúng định dạng email." << endl;
                setTextColor(15);
                continue; 
            }

            username = identifier;
            if (username.empty()) {
                setTextColor(14);
                cout << "Tên đăng nhập không được để trống!" << endl;
                setTextColor(15);
                continue; 
            }
            bool usernameExists = false;
            for (int i = 0; i < soLuongNguoiDung; i++) {
                if (accounts[i].username == username) {
                    usernameExists = true;
                    break;
                }
            }
            if (usernameExists) {
                setTextColor(14);
                cout << "Tên đăng nhập đã tồn tại! Vui lòng nhập tên khác." << endl;
                setTextColor(15);
                continue; 
            }
            break; 
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
        if (password.find(' ') != string::npos) {
            setTextColor(14);
            cout << "\nMật khẩu không được chứa khoảng trắng!" << endl;
            setTextColor(15);
            password.clear(); // Reset mật khẩu để người dùng nhập lại
        } else if (password.empty()) {
            setTextColor(14);
            cout << "\nMật khẩu không được để trống!" << endl;
            setTextColor(15);
        }
    } while(password.empty());
    accounts[soLuongNguoiDung].username = username;
    accounts[soLuongNguoiDung].gmail = gmail;
    accounts[soLuongNguoiDung].password = password;
    soLuongNguoiDung++;
    setTextColor(10);
    cout << "\nĐăng ký thành công!" << endl;
    setTextColor(15);
    saveToFile("user.txt");
}
bool User::dangNhap() {
    loadFromFile("user.txt");
    if (currentUserIndex != -1) { 
        setTextColor(14);
        cout << "Bạn phải đăng xuất trước khi đăng nhập!" << endl;
        setTextColor(15);
        return false;
    }
    if (soLuongNguoiDung == 0) {
        setTextColor(14);
        cout << "Không có tài khoản nào. Vui lòng đăng ký trước!" << endl;
        setTextColor(15);
        return false;
    }
    string username, password;
    char ch;
    bool showPassword = false;
    int attempts = 0; 
    while (attempts < 3) { 
        do {
            cout << "Nhập tên đăng nhập: ";
            getline(cin >> std::ws, username);
            if (username.empty()) {
                setTextColor(14);
                cout << "Tên đăng nhập không được để trống!" << endl;
                setTextColor(15);
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
            if (password.find(' ') != string::npos) {
                setTextColor(14);
                cout << "\nMật khẩu không được chứa khoảng trắng!" << endl;
                setTextColor(15);
                password.clear(); // Reset mật khẩu để người dùng nhập lại
            } else if (password.empty()) {
                setTextColor(14);
                cout << "\nMật khẩu không được để trống!" << endl;
                setTextColor(15);
            }
        } while (password.empty());
        for (int i = 0; i < soLuongNguoiDung; i++) {
            if (accounts[i].username == username && accounts[i].password == password||(accounts[i].gmail == username && accounts[i].password == password)) {
                currentUserIndex = i;
                setTextColor(10);
                cout << "\nĐăng nhập thành công!" << endl;
                setTextColor(15);
                return true;
            }
        }
        cout << "\nSai tên đăng nhập hoặc mật khẩu!\n";
        attempts++;
        if (attempts < 3) {
            cout << "Vui lòng nhập lại. Còn " << 3 - attempts << " lần nhập\n";
        }
        if (attempts >= 3) {
            setTextColor(12);
            cout << "Đăng nhập thất bại! Đăng nhập sau:\n";
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
                }else{
                    cout << "\rThời gian còn lại: " << remaining_time << " s ";
                    cout.flush(); 
                }
            }
        }
    }
    return false;
}
void User::dangXuat() {
    if (currentUserIndex != -1) {
        currentUserIndex = -1;
        setTextColor(10);
        cout << "Đăng xuất thành công!" << endl;
        setTextColor(15);
    } else {
        setTextColor(14);
        cout << "Không có tài khoản nào đăng nhập." << endl;
        setTextColor(15);
    }
}
void User::timDuongDiNganNhat(BusRoute& route) {
    if (currentUserIndex == -1) {
        setTextColor(14);
        cout << "Bạn phải đăng nhập trước khi tìm đường!" << endl;
        setTextColor(15);
        return;
    }
   string startTram, endTram, stopoverTram;
    do {
        cout << "Nhập trạm xuất phát: ";
        cin.ignore();
        getline(cin, startTram);
        if (startTram.empty()) {
            setTextColor(14);
            cout << "Tên trạm không được để trống!" << endl;
            setTextColor(15);
        }
    } while (startTram.empty());

    do {
        cout << "Nhập trạm đến: ";
        getline(cin, endTram);
        if (endTram.empty()) {
            setTextColor(14);
            cout << "Tên trạm không được để trống!" << endl;
            setTextColor(15);
        }
    } while (endTram.empty());
    int menuChoice;
    bool hasStopover = false;
    bool reverseRoute = false;
    do {
        setTextColor(9);
        cout << "==================================";
        cout << "\n|";
        setTextColor(15);
        cout << "              Menu              ";
        setTextColor(9); cout << "|\n";
        cout << "==================================\n";
        cout <<"| ";setTextColor(15);
        cout << "1. Thêm điểm dừng              ";
        setTextColor(9); cout << "|\n";
        cout <<"| ";setTextColor(15);
        cout << "2. Đảo chiều hành trình        ";
        setTextColor(9);cout << "|\n";
        cout <<"| ";setTextColor(15);
        cout << "3. Tìm đường đi hiện tại       ";
        setTextColor(9);cout << "|\n";
        cout <<"| ";setTextColor(15);
        cout << "4. Thoát                       ";
        setTextColor(9);cout << "|\n";
        cout << "==================================\n";
        setTextColor(14);
        cout << "=> Nhập lựa chọn: ";
        setTextColor(15);
        cin >> menuChoice;
        clearScreen();
        if (cin.fail()) {
            clearScreen();
            setTextColor(14);
            cout << "Vui lòng nhập lại.\n";
            setTextColor(15);
			cin.clear();
			cin.ignore(1000, '\n');
            continue;
        }
        
        switch (menuChoice) {
            case 1: {
                while(true){
                    cout << "Nhập trạm dừng: ";
                    cin.ignore();
                    getline(cin, stopoverTram);
                    if (stopoverTram.empty()) {
                        cout << "Tên trạm không được để trống!" << endl;
                        continue;
                    }else if(stopoverTram == startTram||stopoverTram == endTram){
                        cout <<"Không được nhập trùng." <<endl;
                        continue;
                    }else {
                        hasStopover = true;
                        cout << "Đã thêm điểm dừng: " << stopoverTram << endl;
                    }
                    break;
                }break;
            }
            case 2: {
                reverseRoute = !reverseRoute;
                cout << "Đã " << (reverseRoute ? "bật" : "tắt") << " đảo chiều hành trình.\n";
                break;
            }
            case 3: {
                if (hasStopover) {
                    cout << "\nTìm đường từ " << startTram << " đến " << stopoverTram << " đến " << endTram << "...\n";
                    route.dijkstra(startTram, stopoverTram);
                    route.dijkstra(stopoverTram, endTram);
                } else {
                    cout << "\nTìm đường từ " << startTram << " đến " << endTram << "...\n";
                    route.dijkstra(startTram, endTram);
                }

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
                break;
            }
            case 4: {
                cout << "Thoát menu.\n";
                break;
            }
            default:
                cout << "Lựa chọn không hợp lệ, vui lòng chọn lại.\n";
                break;
        }
    } while (menuChoice != 4);
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
    setTextColor(3);
    const int maxLength = 80;
    cout << string(maxLength, '=') << endl;
    cout << "|                        Lịch sử tìm kiếm của  " 
         << left << setw(maxLength - 50) << accounts[currentUserIndex].username
         << "  |" << endl;
    cout << string(maxLength, '=') << endl;

    for (int i = 0; i < soLanTimKiem[currentUserIndex]; i++) {
        tm* thoiGianTm = localtime(&thoiGianTimKiem[currentUserIndex][i]);
        if (thoiGianTm) {
            cout << "| " << left << setw(15) << lichSuTimKiem[currentUserIndex][i][0]  
                 << " -> " 
                 << left << setw(30) << lichSuTimKiem[currentUserIndex][i][1]  
                 << "(Thời gian: " 
                 << put_time(thoiGianTm, "%d/%m/%y %H:%M")  
                 << setw(20) << ") |"  
                 << endl;  
        } else {
            cout << "| Lỗi khi lấy thời gian tìm kiếm!                        |" << endl;
        }
    }
    cout << string(maxLength, '=') << endl;
    setTextColor(15);
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
    cout << "===================================================\n";
    
    setTextColor(7);
}
void User::saveToFile(const std::string& filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << soLuongNguoiDung << endl;
        for (int i = 0; i < soLuongNguoiDung; i++) {
            outFile << accounts[i].username << endl;
            outFile << accounts[i].gmail << endl;
            outFile << accounts[i].password << endl; 
        }
        outFile.close();
    } 
}
void User::loadFromFile(const std::string& filename) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        inFile >> soLuongNguoiDung; 
        inFile.ignore();
        
        for (int i = 0; i < soLuongNguoiDung; i++) {
            getline(inFile, accounts[i].username);
            getline(inFile, accounts[i].gmail);
            getline(inFile, accounts[i].password);
        }

        inFile.close();
        
    }
}

#endif
