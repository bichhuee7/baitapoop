#include <iostream>
#include <string>
#include <cctype>
using namespace std;
string chuan_hoa(string s) {
    for (int i = 0; i < s.length(); i++) {
        s[i] = toupper(s[i]);
    }
    return s;
}
class phuong_tien {
private:
    int ma_xe;
    string loai_xe;
    int gio_vao;
    int tg_do;
    double phi_do;
    bool dang_do;
public:
    phuong_tien() {
        ma_xe = 0;
        loai_xe = "";
        gio_vao = 0;
        tg_do = 0;
        phi_do = 0;
        dang_do = false;
    }
    phuong_tien(int ma, string loai, int gio, int tg) {
        ma_xe = ma;
        loai_xe = loai;
        gio_vao = gio;
        tg_do = tg;
        dang_do = true;
        phi_do = tinh_phi();
    }
    int get_ma() {
        return ma_xe;
    }
    string get_loai() {
        return loai_xe;
    }
    double tinh_phi() {
        double gia = 0;
        if (loai_xe == "CAR")
            gia = 6000;
        else if (loai_xe == "MOTORCYCLE")
            gia = 4000;
        else if (loai_xe == "BICYCLE")
            gia = 2000;
        double tong = 0;
        for (int i = 1; i <= tg_do; i++) {
            if (i <= 2) {
                if ((gio_vao >= 6 && gio_vao <= 9) ||
                    (gio_vao >= 15 && gio_vao <= 18)) {
                    tong += gia * 1.3;
                }
                else {
                    tong += gia * 0.95;
                }
            }
            else {
                tong += gia * 0.9;
            }
        }
        return tong;
    }
    void hien_thi() {
        cout << ma_xe << "\t\t"
             << loai_xe << "\t\t"
             << gio_vao << "\t\t"
             << tg_do << "\t\t"
             << phi_do << endl;
    }
};
class bai_xe {
private:
    int ma_bai;
    string kich_thuoc;
    phuong_tien pt1, pt2, pt3;
    bool co1, co2, co3;
public:
    bai_xe() {
        ma_bai = 0;
        kich_thuoc = "";
        co1 = false;
        co2 = false;
        co3 = false;
    }
    bai_xe(int ma, string kt) {
        ma_bai = ma;
        kich_thuoc = kt;
        co1 = false;
        co2 = false;
        co3 = false;
    }
    int get_ma_bai() {
        return ma_bai;
    }
    int suc_chua() {
        if (kich_thuoc == "S")
            return 1;
        else if (kich_thuoc == "M")
            return 2;
        else
            return 3;
    }
    int so_xe() {
        return co1 + co2 + co3;
    }
    bool con_cho() {
        return so_xe() < suc_chua();
    }
    bool chua(int ma) {
        if (co1 && pt1.get_ma() == ma)
            return true;
        if (co2 && pt2.get_ma() == ma)
            return true;

        if (co3 && pt3.get_ma() == ma)
            return true;

        return false;
    }
    bool them(phuong_tien xe) {
        if (!con_cho())
            return false;
        if (!co1) {
            pt1 = xe;
            co1 = true;
        }
        else if (!co2 && suc_chua() >= 2) {
            pt2 = xe;
            co2 = true;
        }
        else if (!co3 && suc_chua() >= 3) {
            pt3 = xe;
            co3 = true;
        }
        else {
            return false;
        }
        return true;
    }
    bool xoa(int ma) {
        if (co1 && pt1.get_ma() == ma) {
            pt1 = pt2;
            pt2 = pt3;
            co1 = co2;
            co2 = co3;
            co3 = false;
            return true;
        }
        if (co2 && pt2.get_ma() == ma) {
            pt2 = pt3;
            co2 = co3;
            co3 = false;
            return true;
        }
        if (co3 && pt3.get_ma() == ma) {
            co3 = false;
            return true;
        }
        return false;
    }
    void hien_thi() {
        cout << "\nMa bai xe: " << ma_bai << endl;
        cout << "Kich thuoc: " << kich_thuoc << endl;
        cout << "So xe hien tai: " << so_xe()
             << "/" << suc_chua() << endl;
        cout << "\nMa xe\t\tLoai xe\t\tGio vao\t\tThoi gian\tPhi do\n";
        if (co1)
            pt1.hien_thi();
        if (co2)
            pt2.hien_thi();

        if (co3)
            pt3.hien_thi();
    }
    void co_loai(string loai, int &dem, double &tong) {
        if (co1 && pt1.get_loai() == loai) {
            dem++;
            tong += pt1.tinh_phi();
        }
        if (co2 && pt2.get_loai() == loai) {
            dem++;
            tong += pt2.tinh_phi();
        }
        if (co3 && pt3.get_loai() == loai) {
            dem++;
            tong += pt3.tinh_phi();
        }
    }
    void liet_ke_loai(string loai) {
        if (co1 && pt1.get_loai() == loai)
            pt1.hien_thi();

        if (co2 && pt2.get_loai() == loai)
            pt2.hien_thi();

        if (co3 && pt3.get_loai() == loai)
            pt3.hien_thi();
    }
};
class SystemInterface {
private:
    bai_xe ds_bai[3];
    bool co_bai[3];
public:
    SystemInterface() {
        for (int i = 0; i < 3; i++) {
            co_bai[i] = false;
        }
    }
    void tao_bai_xe() {
        int ma;
        string kt;
        cout << "Nhap ma bai xe: ";
        cin >> ma;
        for (int i = 0; i < 3; i++) {
            if (co_bai[i] && ds_bai[i].get_ma_bai() == ma) {
                cout << "Ma bai xe da ton tai!\n";
                return;
            }
        }
        int vi_tri = -1;
        for (int i = 0; i < 3; i++) {
            if (!co_bai[i]) {
                vi_tri = i;
                break;
            }
        }
        if (vi_tri == -1) {
            cout << "He thong da day bai xe!\n";
            return;
        }
        cout << "Nhap kich thuoc bai (S/M/L): ";
        cin >> kt;
        kt = chuan_hoa(kt);
        if (kt != "S" && kt != "M" && kt != "L") {
            cout << "Kich thuoc khong hop le!\n";
            return;
        }
        ds_bai[vi_tri] = bai_xe(ma, kt);
        co_bai[vi_tri] = true;

        cout << "Tao bai xe thanh cong!\n";
    }
    void them_phuong_tien() {
        int ma_xe, gio, tg;
        string loai;
        cout << "Nhap ma xe: ";
        cin >> ma_xe;
        for (int i = 0; i < 3; i++) {
            if (co_bai[i] && ds_bai[i].chua(ma_xe)) {
                cout << "Ma xe da ton tai!\n";
                return;
            }
        }
        cout << "Nhap loai xe (Car/Motorcycle/Bicycle): ";
        cin >> loai;
        loai = chuan_hoa(loai);
        if (loai != "CAR" &&
            loai != "MOTORCYCLE" &&
            loai != "BICYCLE") {
            cout << "Loai xe khong hop le!\n";
            return;
        }
        cout << "Nhap gio vao (0-23): ";
        cin >> gio;
        if (gio < 0 || gio > 23) {
            cout << "Gio vao khong hop le!\n";
            return;
        }
        cout << "Nhap thoi gian do (1-23): ";
        cin >> tg;
        if (tg < 1 || tg > 23) {
            cout << "Thoi gian do khong hop le!\n";
            return;
        }
        phuong_tien xe(ma_xe, loai, gio, tg);
        for (int i = 0; i < 3; i++) {
            if (co_bai[i] && ds_bai[i].them(xe)) {
                cout << "Them xe thanh cong!\n";
                cout << "Phi do xe: " << xe.tinh_phi()
                     << " VND\n";
                cout << "Xe duoc xep vao bai: "
                     << ds_bai[i].get_ma_bai() << endl;
                return;
            }
        }
        cout << "Khong con bai xe phu hop!\n";
    }
    void xoa_bai_xe() {
        int ma;
        cout << "Nhap ma bai xe can xoa: ";
        cin >> ma;
        for (int i = 0; i < 3; i++) {
            if (co_bai[i] && ds_bai[i].get_ma_bai() == ma) {
                co_bai[i] = false;
                ds_bai[i] = bai_xe();
                cout << "Xoa bai xe thanh cong!\n";
                return;
            }
        }
        cout << "Khong tim thay bai xe!\n";
    }
    void xoa_phuong_tien() {
        int ma;
        cout << "Nhap ma xe can xoa: ";
        cin >> ma;
        for (int i = 0; i < 3; i++) {
            if (co_bai[i] && ds_bai[i].xoa(ma)) {
                cout << "Xoa phuong tien thanh cong!\n";
                return;
            }
        }
        cout << "Khong tim thay phuong tien!\n";
    }
    void hien_thi_tat_ca() {
        bool co = false;
        for (int i = 0; i < 3; i++) {
            if (co_bai[i]) {
                ds_bai[i].hien_thi();
                co = true;
            }
        }
        if (!co)
            cout << "He thong chua co bai xe!\n";
    }
    void hien_thi_mot_bai() {
        int ma;
        cout << "Nhap ma bai xe: ";
        cin >> ma;
        for (int i = 0; i < 3; i++) {
            if (co_bai[i] && ds_bai[i].get_ma_bai() == ma) {
                ds_bai[i].hien_thi();
                return;
            }
        }
        cout << "Khong tim thay bai xe!\n";
    }
    void liet_ke_phuong_tien() {
        string loai;
        cout << "Nhap loai xe can liet ke: ";
        cin >> loai;
        loai = chuan_hoa(loai);
        if (loai != "CAR" &&
            loai != "MOTORCYCLE" &&
            loai != "BICYCLE") {
            cout << "Loai xe khong hop le!\n";
            return;
        }
        cout << "\nDanh sach xe " << loai << ":\n";
        cout << "Ma xe\t\tLoai xe\t\tGio vao\t\tThoi gian\tPhi do\n";
        int dem = 0;
        for (int i = 0; i < 3; i++) {
            if (co_bai[i]) {
                ds_bai[i].liet_ke_loai(loai);
            }
        }
    }
    void thong_ke() {
        string loai;
        cout << "Nhap loai xe can thong ke: ";
        cin >> loai;
        loai = chuan_hoa(loai);
        if (loai != "CAR" &&
            loai != "MOTORCYCLE" &&
            loai != "BICYCLE") {
            cout << "Loai xe khong hop le!\n";
            return;
        }
        int tong_xe = 0;
        double tong_phi = 0;
        cout << "\nTHONG KE THEO BAI XE\n";
        for (int i = 0; i < 3; i++) {
            if (co_bai[i]) {
                int dem = 0;
                double phi = 0;
                ds_bai[i].co_loai(loai, dem, phi);
                cout << "Bai xe " << ds_bai[i].get_ma_bai()
                     << ": " << dem << " xe"
                     << ", Tong phi: " << phi << " VND\n";

                tong_xe += dem;
                tong_phi += phi;
            }
        }
        cout << "\nTONG KET TOAN HE THONG\n";
        cout << "Loai xe: " << loai << endl;
        cout << "Tong so xe: " << tong_xe << endl;
        cout << "Tong phi do: " << tong_phi << " VND\n";
    }
    void runMenu() {
        int chon;
        do {
            cout << "\n========== QUAN LY BAI XE ==========\n";
            cout << "1. Tao bai xe\n";
            cout << "2. Them phuong tien\n";
            cout << "3. Xoa bai xe\n";
            cout << "4. Xoa phuong tien\n";
            cout << "5. Hien thi tat ca bai xe\n";
            cout << "6. Hien thi mot bai xe\n";
            cout << "7. Liet ke phuong tien theo loai\n";
            cout << "8. Thong ke theo loai xe\n";
            cout << "9. Thoat\n";
            cout << "===================================\n";
            cout << "Nhap lua chon: ";
            cin >> chon;
            switch (chon) {
            case 1:
                tao_bai_xe();
                break;
            case 2:
                them_phuong_tien();
                break;
            case 3:
                xoa_bai_xe();
                break;
            case 4:
                xoa_phuong_tien();
                break;
            case 5:
                hien_thi_tat_ca();
                break;
            case 6:
                hien_thi_mot_bai();
                break;
            case 7:
                liet_ke_phuong_tien();
                break;
            case 8:
                thong_ke();
                break;
            case 9:
                cout << "Ket thuc chuong trinh!\n";
                break;

            default:
                cout << "Lua chon khong hop le!\n";
            }
        } while (chon != 9);
    }
};
int main() {
    SystemInterface ht;
    ht.runMenu();
    return 0;
}
