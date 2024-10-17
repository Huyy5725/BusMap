class Admin :public BusRoute {
	private:
		string adminName;
		string adminPass;
	public:
		Admin() : adminName("Tuan Dat"), adminPass("12345") {}
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

