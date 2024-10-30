#ifndef ADMIN_H
#define ADMIN_H

#include "BusRoute.h"
#include <string>

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
	cout << "Nhap ten dang nhap: ";
	cin.ignore();
	getline(cin, user);
	cout << "Nhap mat khau: ";
	getline(cin, pass);
	return (user == adminName && pass == adminPass);
}
void Admin::thietLapTram(BusRoute& route) {
	int stops;
	do{
	    cout << "Nhap so luong tram: ";
	    cin >> stops;
	}while(stops<1||stops>100);
	    route.setNumStops(stops);
	    cin.ignore(); 
	    route.nhapTenTram();
		for (int i = 0; i < route.getNumStops(); i++) {
	        for (int j = 0; j < route.getNumStops(); j++) {
	            route.setDistance(i, j, (i == j) ? 0 : INF);
	        }
	    }
	cout << "Da thiet lap " << route.getNumStops() << " tram." << endl;
	    route.nhapKhoangCachTheoTen();
}
void Admin::xoaTram(BusRoute& route) {
	string tenTramCanXoa;
	cout << "Nhap ten tram can xoa: ";
	cin.ignore();
	getline(cin, tenTramCanXoa);
	int idx = route.timTram(tenTramCanXoa);
	if (idx == -1) {
		cout << "Tram khong ton tai!" << endl;
		return;
	}
	int ketNoi[MAX];
	int soLuongKetNoi = 0;
	for (int i = 0; i < route.getNumStops(); i++) {
		if (route.getDistance(i, idx) != INF && i != idx) {
		    ketNoi[soLuongKetNoi++] = i;  // L�u tr?m c� k?t n?i v?i tr?m b? x�a
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
	cout << "Da xoa tram " << tenTramCanXoa << " va cap nhat cac ket noi." << endl;
}
void Admin::themTram(BusRoute& route) {
	if (route.getNumStops() >= MAX) {
		cout << "Khong the them tram, da den gioi han toi da!" << endl;
		return;
	}
	string tenTramMoi;
	cout << "Nhap ten tram moi: ";
	cin.ignore();
	getline(cin, tenTramMoi);
	if (route.timTram(tenTramMoi) != -1) {
		cout << "Ten tram da ton tai, khong the them tram moi." << endl;
		return;
	}
	route.setNameStop(route.getNumStops(), tenTramMoi);
	int tramMoiIdx = route.getNumStops();
	route.setNumStops(tramMoiIdx + 1);
	string tram1, tram2;
	int khoangCach1, khoangCach2;
	while (true) {
		cout << "Nhap ten tram ket noi voi tram moi (nhap '0' de dung): ";
		getline(cin, tram2);
		if (tram2 == "0") {break;}
		int idxTram2 = route.timTram(tram2);
		if (idxTram2 == -1) {
		    cout << "Tram khong ton tai!" << endl;
		    continue;
		}
		cout << "Nhap tram hien dang ket noi voi tram "<<tram2<<": ";
		getline(cin, tram1);
		if (tram1 == "0") {
		    cout << "Nhap khoang cach tu " << tenTramMoi << " den " << tram2 << ": ";
		    cin >> khoangCach2;
		    cin.ignore();
			if (khoangCach2 > 0) {
		        route.setDistance(tramMoiIdx, idxTram2, khoangCach2);
		        route.setDistance(idxTram2, tramMoiIdx, khoangCach2);
				cout << "Da cap nhat khoang cach giua " << tenTramMoi << " va " << tram2 << "." << endl;
		    } else {
		        cout << "Khoang cach khong hop le!" << endl;
			}
			continue;
		}
		int idxTram1 = route.timTram(tram1);
		if (idxTram1 == -1) {
		    cout << "Tram 1 khong ton tai!" << endl;
		    continue;
		}
		if (route.getDistance(idxTram1, idxTram2) != INF) {
		    cout << "Xoa khoang cach giua tram " << tram1 << " va tram " << tram2 << endl;
		    route.setDistance(idxTram1, idxTram2, INF);
		    route.setDistance(idxTram2, idxTram1, INF);
		    cout << "Nhap khoang cach tu " << tram1 << " den " << tenTramMoi << ": ";
		    cin >> khoangCach1;
		    cin.ignore();
			cout << "Nhap khoang cach tu " << tenTramMoi << " den " << tram2 << ": ";
		    cin >> khoangCach2;
		    cin.ignore();
			if (khoangCach1 > 0 && khoangCach2 > 0) {
		        route.setDistance(idxTram1, tramMoiIdx, khoangCach1);
		        route.setDistance(tramMoiIdx, idxTram1, khoangCach1);
				route.setDistance(tramMoiIdx, idxTram2, khoangCach2);
		        route.setDistance(idxTram2, tramMoiIdx, khoangCach2);
				cout << "Da cap nhat khoang cach giua " << tram1 << " -> " << tenTramMoi << " -> " << tram2 << "." << endl;
		    } else {
		        cout << "Khoang cach khong hop le!" << endl;
		    }
		} else {
		    cout << "Tram " << tram1 << " va tram " << tram2 << " khong co ket noi truc tiep!" << endl;
		}
	}
	cout << "Da them tram moi " << tenTramMoi << " va cap nhat cac ket noi." << endl;
}
void Admin::capNhatKhoangCach(BusRoute& route) {
	string tram1, tram2;
	int khoangCach;
	cout << "Nhap tram xuat phat (ten tram): ";
	cin.ignore();
	getline(cin, tram1);
	cout << "Nhap tram den (ten tram): ";
	getline(cin, tram2);
	cout << "Nhap khoang cach moi: ";
	cin >> khoangCach;
	cin.ignore(); 
	int idx1 = route.timTram(tram1);
	int idx2 = route.timTram(tram2);
	if (idx1 != -1 && idx2 != -1 && khoangCach > 0) {
	    route.setDistance(idx1, idx2, khoangCach);
	    cout << "Da cap nhat khoang cach giua " << tram1 << " va " << tram2 << " thanh " << khoangCach << "." << endl;
	} else {
	    cout << "Tram khong ton tai hoac khoang cach khong hop le!" << endl;
	}
}

#endif
