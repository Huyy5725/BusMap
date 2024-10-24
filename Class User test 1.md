struct UserAccount {
    string username;
    string password;
    int soLanTimKiem;
    string lichSuTimKiem[MAX_HISTORY]; // Lịch sử tìm kiếm của mỗi người dùng
};

class User : public BusRoute {
private:
    int soLanTimKiem;
    string lichSuTimKiem[MAX][2];
    UserAccount accounts[MAX_USERS]; // Mảng tĩnh lưu trữ tài khoản
    int soLuongNguoiDung; // Số lượng người dùng đã đăng ký
    int currentUserIndex; // Chỉ số người dùng hiện tại sau khi đăng nhập

public:
    User() : soLanTimKiem(0), soLuongNguoiDung(0), currentUserIndex(-1) {}

    // Hàm đăng ký tài khoản người dùng
    void dangKyTaiKhoan() {
        if (soLuongNguoiDung >= MAX_USERS) {
            cout << "Da dat gioi han toi da nguoi dung!" << endl;
            return;
        }

        string username, password;
        cout << "Nhap ten dang nhap: ";
        cin.ignore();
        getline(cin, username);

        // Kiểm tra tên đăng nhập đã tồn tại chưa
        for (int i = 0; i < soLuongNguoiDung; i++) {
            if (accounts[i].username == username) {
                cout << "Ten dang nhap da ton tai. Vui long chon ten khac!" << endl;
                return;
            }
        }

        cout << "Nhap mat khau: ";
        getline(cin, password);

        // Lưu tài khoản mới vào mảng
        accounts[soLuongNguoiDung].username = username;
        accounts[soLuongNguoiDung].password = password;
        soLuongNguoiDung++;

        cout << "Dang ky thanh cong!" << endl;
    }

    // Hàm đăng nhập người dùng
    bool dangNhap() {
        if (soLuongNguoiDung == 0) {
            cout << "Khong co tai khoan. Vui long dang ki truoc!" << endl;
            return false;
        }

        string username, password;
        cout << "Nhap ten dang nhap: ";
        cin.ignore();
        getline(cin, username);
        cout << "Nhap mat khau: ";
        getline(cin, password);

        // Kiểm tra thông tin đăng nhập
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

    void timDuongDiNganNhat(BusRoute& route) {
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
            soLanTimKiem++;
        }
    }

    void hienThiLichSuTimKiem() const {
        if (currentUserIndex == -1) {
            cout << "Ban phai đang nhap truoc khi xem lich su!" << endl;
            return;
        }

        cout << "Lich su tim kiem:\n";
        for (int i = 0; i < soLanTimKiem; i++) {
            cout << lichSuTimKiem[i][0] << " -> " << lichSuTimKiem[i][1] << endl;
        }
    }

    void hienThiTatCaTram(BusRoute route) const {
        if (currentUserIndex == -1) {
            cout << "Ban phai đang nhap truoc khi xem danh sach tram!" << endl;
            return;
        }

        cout << "Danh sach tat ca cac tram:\n";
        for (int i = 0; i < route.getNumStops(); i++) {
            cout << i + 1 << ". " << route.getNameStop(i) << endl;
        }
    }
};
