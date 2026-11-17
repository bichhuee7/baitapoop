#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;
class Vehicle {
private:
    string maXe;
    string loaiXe;
    string gioVao;
    double thoiGianGui;
    double phiGuiXe;
public:
    Vehicle() {
        maXe = "";
        loaiXe = "";
        gioVao = "";
        thoiGianGui = 0;
        phiGuiXe = 0;
    }
    Vehicle(string ma, string loai, string gio, double thoiGian) {
        maXe = ma;
        loaiXe = loai;
        gioVao = gio;
        thoiGianGui = thoiGian;
        phiGuiXe = tinhPhi();
    }
    string layMaXe() {
        return maXe;
    }
    string layLoaiXe() {
        return loaiXe;
    }
    string layGioVao() {
        return gioVao;
    }
    double layThoiGianGui() {
        return thoiGianGui;
    }
    double layPhiGuiXe() {
        return phiGuiXe;
    }
    void datMaXe(string ma) {
        maXe = ma;
    }
    void datLoaiXe(string loai) {
        loaiXe = loai;
    }
    void datGioVao(string gio) {
        gioVao = gio;
    }
    void datThoiGianGui(double thoiGian) {
        thoiGianGui = thoiGian;
        phiGuiXe = tinhPhi();
    }
    double tinhPhi() {
        double donGia;
        if (loaiXe == "Xe may")
            donGia = 5000;
        else if (loaiXe == "O to")
            donGia = 20000;
        else if (loaiXe == "Xe dap")
            donGia = 2000;
        else
            donGia = 10000;
        return donGia * thoiGianGui;
    }
    void hienThi() {
        cout << left
             << setw(15) << maXe
             << setw(15) << loaiXe
             << setw(15) << gioVao
             << setw(15) << thoiGianGui
             << setw(15) << phiGuiXe << endl;
    }
};
class ParkingLot {
private:
    string maBai;
    char kichThuoc;
    int sucChua;
    int soXeHienTai;
    Vehicle** danhSachXe;
public:
    ParkingLot(string ma = "", char kichThuocBai = 'S') {
        maBai = ma;
        kichThuoc = kichThuocBai;
        if (kichThuoc == 'S')
            sucChua = 1;
        else if (kichThuoc == 'M')
            sucChua = 2;
        else
            sucChua = 3;
        soXeHienTai = 0;
        danhSachXe = new Vehicle*[sucChua];
        for (int i = 0; i < sucChua; i++)
            danhSachXe[i] = NULL;
    }
    ~ParkingLot() {
        for (int i = 0; i < soXeHienTai; i++) {
            delete danhSachXe[i];
            danhSachXe[i] = NULL;
        }
        delete[] danhSachXe;
        danhSachXe = NULL;
    }
    ParkingLot(const ParkingLot& doiTuongKhac) {
        maBai = doiTuongKhac.maBai;
        kichThuoc = doiTuongKhac.kichThuoc;
        sucChua = doiTuongKhac.sucChua;
        soXeHienTai = doiTuongKhac.soXeHienTai;
        danhSachXe = new Vehicle*[sucChua];
        for (int i = 0; i < sucChua; i++) {
            danhSachXe[i] = NULL;
            if (i < soXeHienTai && doiTuongKhac.danhSachXe[i] != NULL)
                danhSachXe[i] = new Vehicle(*doiTuongKhac.danhSachXe[i]);
        }
    }
    ParkingLot& operator=(const ParkingLot& doiTuongKhac) {
        if (this != &doiTuongKhac) {
            for (int i = 0; i < soXeHienTai; i++)
                delete danhSachXe[i];
            delete[] danhSachXe;
            maBai = doiTuongKhac.maBai;
            kichThuoc = doiTuongKhac.kichThuoc;
            sucChua = doiTuongKhac.sucChua;
            soXeHienTai = doiTuongKhac.soXeHienTai;
            danhSachXe = new Vehicle*[sucChua];
            for (int i = 0; i < sucChua; i++) {
                danhSachXe[i] = NULL;
                if (i < soXeHienTai && doiTuongKhac.danhSachXe[i] != NULL)
                    danhSachXe[i] = new Vehicle(*doiTuongKhac.danhSachXe[i]);
            }
        }
        return *this;
    }
    string layMaBai() {
        return maBai;
    }
    int laySoXeHienTai() {
        return soXeHienTai;
    }
    int laySucChua() {
        return sucChua;
    }
    void moRong() {
        int sucChuaMoi = sucChua * 2;
        Vehicle** mangMoi = new Vehicle*[sucChuaMoi];
        for (int i = 0; i < sucChuaMoi; i++)
            mangMoi[i] = NULL;
        for (int i = 0; i < soXeHienTai; i++)
            mangMoi[i] = danhSachXe[i];
        delete[] danhSachXe;
        danhSachXe = mangMoi;
        sucChua = sucChuaMoi;
    }
    void themXe(Vehicle* xe) {
        if (xe == NULL)
            return;
        for (int i = 0; i < soXeHienTai; i++) {
            if (danhSachXe[i]->layMaXe() == xe->layMaXe()) {
                cout << "Ma xe da ton tai trong bai!" << endl;
                return;
            }
        }
        if (soXeHienTai == sucChua)
            moRong();
        danhSachXe[soXeHienTai] = xe;
        soXeHienTai++;
        cout << "Them xe thanh cong!" << endl;
    }
    void xoaXe(string ma) {
        int viTri = -1;
        for (int i = 0; i < soXeHienTai; i++) {
            if (danhSachXe[i]->layMaXe() == ma) {
                viTri = i;
                break;
            }
        }
        if (viTri == -1) {
            cout << "Khong tim thay xe!" << endl;
            return;
        }
        delete danhSachXe[viTri];
        danhSachXe[viTri] = NULL;
        for (int i = viTri; i < soXeHienTai - 1; i++)
            danhSachXe[i] = danhSachXe[i + 1];
        soXeHienTai--;
        danhSachXe[soXeHienTai] = NULL;
        cout << "Xoa xe thanh cong!" << endl;
    }
    void hienThiDanhSachXe() {
        cout << left
             << setw(15) << "Ma xe"
             << setw(15) << "Loai xe"
             << setw(15) << "Gio vao"
             << setw(15) << "So gio gui"
             << setw(15) << "Phi gui" << endl;
        for (int i = 0; i < soXeHienTai; i++)
            danhSachXe[i]->hienThi();
    }
    void hienThi() {
        cout << "\nMa bai: " << maBai;
        cout << "\nKich thuoc: " << kichThuoc;
        cout << "\nSuc chua: " << sucChua;
        cout << "\nSo xe hien tai: " << soXeHienTai << endl;
    }
    int hienThiXeTheoLoai(string loai) {
        int soLuong = 0;
        for (int i = 0; i < soXeHienTai; i++) {
            if (danhSachXe[i]->layLoaiXe() == loai) {
                danhSachXe[i]->hienThi();
                soLuong++;
            }
        }
        return soLuong;
    }
    double tinhTongPhi() {
        double tongPhi = 0;
        for (int i = 0; i < soXeHienTai; i++)
            tongPhi += danhSachXe[i]->layPhiGuiXe();
        return tongPhi;
    }
};
class SystemInterface {
private:
    int sucChuaBai;
    int soBaiHienTai;
    ParkingLot** danhSachBai;
public:
    SystemInterface() {
        sucChuaBai = 5;
        soBaiHienTai = 0;
        danhSachBai = new ParkingLot*[sucChuaBai];
        for (int i = 0; i < sucChuaBai; i++)
            danhSachBai[i] = NULL;
    }
    ~SystemInterface() {
        for (int i = 0; i < soBaiHienTai; i++) {
            delete danhSachBai[i];
            danhSachBai[i] = NULL;
        }
        delete[] danhSachBai;
        danhSachBai = NULL;
    }
    SystemInterface(const SystemInterface& doiTuongKhac) {
        sucChuaBai = doiTuongKhac.sucChuaBai;
        soBaiHienTai = doiTuongKhac.soBaiHienTai;
        danhSachBai = new ParkingLot*[sucChuaBai];
        for (int i = 0; i < sucChuaBai; i++) {
            danhSachBai[i] = NULL;
            if (i < soBaiHienTai && doiTuongKhac.danhSachBai[i] != NULL)
                danhSachBai[i] = new ParkingLot(*doiTuongKhac.danhSachBai[i]);
        }
    }
    SystemInterface& operator=(const SystemInterface& doiTuongKhac) {
        if (this != &doiTuongKhac) {
            for (int i = 0; i < soBaiHienTai; i++)
                delete danhSachBai[i];
            delete[] danhSachBai;
            sucChuaBai = doiTuongKhac.sucChuaBai;
            soBaiHienTai = doiTuongKhac.soBaiHienTai;
            danhSachBai = new ParkingLot*[sucChuaBai];
            for (int i = 0; i < sucChuaBai; i++) {
                danhSachBai[i] = NULL;
                if (i < soBaiHienTai && doiTuongKhac.danhSachBai[i] != NULL)
                    danhSachBai[i] = new ParkingLot(*doiTuongKhac.danhSachBai[i]);
            }
        }
        return *this;
    }
    int timBai(string ma) {
        for (int i = 0; i < soBaiHienTai; i++) {
            if (danhSachBai[i]->layMaBai() == ma)
                return i;
        }
        return -1;
    }
    void moRongHeThong() {
        int sucChuaMoi = sucChuaBai * 2;
        ParkingLot** mangMoi = new ParkingLot*[sucChuaMoi];
        for (int i = 0; i < sucChuaMoi; i++)
            mangMoi[i] = NULL;
        for (int i = 0; i < soBaiHienTai; i++)
            mangMoi[i] = danhSachBai[i];
        delete[] danhSachBai;
        danhSachBai = mangMoi;
        sucChuaBai = sucChuaMoi;
    }
    void themBaiDo() {
        string maBai;
        char kichThuoc;
        cout << "Nhap ma bai: ";
        cin >> maBai;
        if (timBai(maBai) != -1) {
            cout << "Ma bai da ton tai!" << endl;
            return;
        }
        cout << "Nhap kich thuoc (S/M/L): ";
        cin >> kichThuoc;
        if (kichThuoc >= 'a' && kichThuoc <= 'z')
            kichThuoc -= 32;
        if (kichThuoc != 'S' && kichThuoc != 'M' && kichThuoc != 'L') {
            cout << "Kich thuoc khong hop le!" << endl;
            return;
        }
        if (soBaiHienTai == sucChuaBai)
            moRongHeThong();
        danhSachBai[soBaiHienTai] = new ParkingLot(maBai, kichThuoc);
        soBaiHienTai++;
        cout << "Tao bai do thanh cong!" << endl;
    }
    void themXeVaoBai() {
        string maBai, maXe, loaiXe, gioVao;
        double thoiGianGui;
        cout << "Nhap ma bai: ";
        cin >> maBai;
        int viTri = timBai(maBai);
        if (viTri == -1) {
            cout << "Khong tim thay bai do!" << endl;
            return;
        }
        cout << "Nhap ma xe: ";
        cin >> maXe;
        cout << "Nhap loai xe (Xe may/O to/Xe dap): ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, loaiXe);
        cout << "Nhap gio vao: ";
        getline(cin, gioVao);
        cout << "Nhap so gio gui: ";
        cin >> thoiGianGui;
        if (thoiGianGui <= 0) {
            cout << "Thoi gian gui khong hop le!" << endl;
            return;
        }
        Vehicle* xe = new Vehicle(maXe, loaiXe, gioVao, thoiGianGui);
        int soXeTruoc = danhSachBai[viTri]->laySoXeHienTai();
        danhSachBai[viTri]->themXe(xe);
        if (danhSachBai[viTri]->laySoXeHienTai() == soXeTruoc)
            delete xe;
    }
    void xoaBaiDo() {
        string maBai;
        cout << "Nhap ma bai can xoa: ";
        cin >> maBai;
        int viTri = timBai(maBai);
        if (viTri == -1) {
            cout << "Khong tim thay bai do!" << endl;
            return;
        }
        delete danhSachBai[viTri];
        danhSachBai[viTri] = NULL;
        for (int i = viTri; i < soBaiHienTai - 1; i++)
            danhSachBai[i] = danhSachBai[i + 1];
        soBaiHienTai--;
        danhSachBai[soBaiHienTai] = NULL;
        cout << "Xoa bai do thanh cong!" << endl;
    }
    void layXeRa() {
        string maBai, maXe;
        cout << "Nhap ma bai: ";
        cin >> maBai;
        int viTri = timBai(maBai);
        if (viTri == -1) {
            cout << "Khong tim thay bai do!" << endl;
            return;
        }
        cout << "Nhap ma xe can xoa: ";
        cin >> maXe;
        danhSachBai[viTri]->xoaXe(maXe);
    }
    void hienThiTatCaBai() {
        if (soBaiHienTai == 0) {
            cout << "Chua co bai do nao!" << endl;
            return;
        }
        for (int i = 0; i < soBaiHienTai; i++) {
            cout << "\n========== BAI DO " << i + 1 << " ==========";
            danhSachBai[i]->hienThi();
        }
    }
    void hienThiXeTheoBai() {
        string maBai;
        cout << "Nhap ma bai: ";
        cin >> maBai;
        int viTri = timBai(maBai);
        if (viTri == -1) {
            cout << "Khong tim thay bai do!" << endl;
            return;
        }
        cout << "\nDanh sach xe trong bai " << maBai << endl;
        danhSachBai[viTri]->hienThiDanhSachXe();
    }
    void lietKeXeTheoLoai() {
        string loaiXe;
        int tongSoXe = 0;
        cout << "Nhap loai xe can tim: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, loaiXe);
        cout << "\nDanh sach xe loai: " << loaiXe << endl;
        cout << left
             << setw(15) << "Ma xe"
             << setw(15) << "Loai xe"
             << setw(15) << "Gio vao"
             << setw(15) << "So gio gui"
             << setw(15) << "Phi gui" << endl;
        for (int i = 0; i < soBaiHienTai; i++)
            tongSoXe += danhSachBai[i]->hienThiXeTheoLoai(loaiXe);
        cout << "Tong so xe tim thay: " << tongSoXe << endl;
    }
    void tinhPhiTrungBinh() {
        double tongPhi = 0;
        int tongSoXe = 0;
        for (int i = 0; i < soBaiHienTai; i++) {
            tongPhi += danhSachBai[i]->tinhTongPhi();
            tongSoXe += danhSachBai[i]->laySoXeHienTai();
        }
        cout << fixed << setprecision(2);
        cout << "Tong so xe: " << tongSoXe << endl;
        cout << "Tong phi gui xe: " << tongPhi << " VND" << endl;
        if (tongSoXe > 0)
            cout << "Phi gui xe trung binh: " << tongPhi / tongSoXe << " VND" << endl;
        else
            cout << "Chua co xe nao trong he thong!" << endl;
    }
    void chayMenu() {
        int luaChon;
        do {
            cout << "\n========== QUAN LY BAI DO XE ==========" << endl;
            cout << "1. Tao bai do xe" << endl;
            cout << "2. Them xe vao bai" << endl;
            cout << "3. Xoa bai do xe" << endl;
            cout << "4. Xoa xe khoi bai" << endl;
            cout << "5. Hien thi tat ca bai do" << endl;
            cout << "6. Hien thi xe theo bai" << endl;
            cout << "7. Liet ke xe theo loai" << endl;
            cout << "8. Thong ke phi gui xe trung binh" << endl;
            cout << "9. Thoat" << endl;
            cout << "Nhap lua chon: ";
            cin >> luaChon;
            switch (luaChon) {
                case 1:
                    themBaiDo();
                    break;
                case 2:
                    themXeVaoBai();
                    break;
                case 3:
                    xoaBaiDo();
                    break;
                case 4:
                    layXeRa();
                    break;
                case 5:
                    hienThiTatCaBai();
                    break;
                case 6:
                    hienThiXeTheoBai();
                    break;
                case 7:
                    lietKeXeTheoLoai();
                    break;
                case 8:
                    tinhPhiTrungBinh();
                    break;
                case 9:
                    cout << "Da thoat chuong trinh!" << endl;
                    break;
                default:
                    cout << "Lua chon khong hop le!" << endl;
            }
        } while (luaChon != 9);
    }
};
int main() {
    SystemInterface heThong;
    heThong.chayMenu();
    return 0;
}
