#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <limits>
using namespace std;

class MayBay {
private:
    string _soHieu;
    int _soCho;
public:
    MayBay() : _soHieu(""), _soCho(0) {}
    MayBay(const string& sh, int sc) : _soHieu(sh), _soCho(sc) {}

    const string& getSoHieu() const { return _soHieu; }
    void setSoHieu(const string& v) { _soHieu = v; }

    int getSoCho() const { return _soCho; }
    void setSoCho(int v) { _soCho = v; }

    void WriteToStream(ostream& os) const {
        os << _soHieu << endl;
        os << _soCho << endl;
    }

    static MayBay ReadFromStream(istream& is) {
        MayBay mb;
        getline(is, mb._soHieu);
        is >> mb._soCho;
        is.ignore(numeric_limits<streamsize>::max(), '\n');
        return mb;
    }
};

class KhachHang {
private:
    int _soThuTu;
    string _CMND;
    string _hoTen;
public:
    KhachHang() : _soThuTu(0), _CMND(""), _hoTen("") {}
    KhachHang(int stt, const string& cmnd, const string& ht) : _soThuTu(stt), _CMND(cmnd), _hoTen(ht) {}

    int getSoThuTu() const { return _soThuTu; }
    void setSoThuTu(int v) { _soThuTu = v; }

    const string& getCMND() const { return _CMND; }
    void setCMND(const string& v) { _CMND = v; }

    const string& getHoTen() const { return _hoTen; }
    void setHoTen(const string& v) { _hoTen = v; }

    void WriteToStream(ostream& os) const {
        os << _soThuTu << endl;
        os << _CMND << endl;
        os << _hoTen << endl;
    }

    static KhachHang ReadFromStream(istream& is) {
        KhachHang kh;
        is >> kh._soThuTu;
        is.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(is, kh._CMND);
        getline(is, kh._hoTen);
        return kh;
    }
};

class Ve {
private:
    string _maVe;
    string _maChuyenBay;
    KhachHang _thongTinKhachHang;
    string _soGhe;
public:
    Ve() : _maVe(""), _maChuyenBay(""), _thongTinKhachHang(), _soGhe("") {}
    Ve(const string& mv, const string& mcb, const string& sg, const KhachHang& kh)
        : _maVe(mv), _maChuyenBay(mcb), _thongTinKhachHang(kh), _soGhe(sg) {
    }

    const string& getMaVe() const { return _maVe; }
    void setMaVe(const string& v) { _maVe = v; }

    const string& getMaChuyenBay() const { return _maChuyenBay; }
    void setMaChuyenBay(const string& v) { _maChuyenBay = v; }

    const KhachHang& getThongTinKhachHang() const { return _thongTinKhachHang; }
    KhachHang& getThongTinKhachHang() { return _thongTinKhachHang; }
    void setThongTinKhachHang(const KhachHang& v) { _thongTinKhachHang = v; }

    const string& getSoGhe() const { return _soGhe; }
    void setSoGhe(const string& v) { _soGhe = v; }

    bool SaveToFile() const {
        if (_maVe.empty()) return false;
        string tenFile = _maVe + ".txt";
        ofstream file(tenFile);
        if (!file.is_open()) {
            cout << "File khong ton tai";
            return false;
        }

        file << _maVe << endl;
        file << _maChuyenBay << endl;
        file << _soGhe << endl;
        file << _thongTinKhachHang.getSoThuTu() << endl;
        file << _thongTinKhachHang.getCMND() << endl;
        file << _thongTinKhachHang.getHoTen() << endl;

        file.close();
        return true;
    }

    static bool LoadFromFile(const string& maVe, Ve& veOut) {
        string tenFile = maVe + ".txt";
        ifstream file(tenFile);
        if (!file.is_open()) {
            cout << "File khong ton tai";
            return false;
        }
        getline(file, veOut._maVe);
        getline(file, veOut._maChuyenBay);
        getline(file, veOut._soGhe);
        int stt = 0;
        file >> stt;
        veOut._thongTinKhachHang.setSoThuTu(stt);
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        string cmnd;
        string hoten;
        getline(file, cmnd);
        getline(file, hoten);
        veOut._thongTinKhachHang.setCMND(cmnd);
        veOut._thongTinKhachHang.setHoTen(hoten);
        file.close();
        return true;
    }

    void WriteReferenceToStream(ostream& os) const {
        os << _maVe << endl;
    }
};

class ChuyenBay {
private:
    string _maChuyenBay;
    string _soHieuMayBay;
    string _ngayKhoiHanh;
    string _sanBayDen;
    string _trangThai;
    list<Ve> _danhSachVe;
    list<string> _danhSachGheTrong;
public:
    ChuyenBay() : _maChuyenBay(""), _soHieuMayBay(""), _ngayKhoiHanh(""), _sanBayDen(""), _trangThai(""), _danhSachVe(), _danhSachGheTrong() {}
    ChuyenBay(const string& ma, const string& sh, const string& ngay, const string& sbd, const string& tt,
        const list<Ve>& dsVe, const list<string>& dsGheTrong)
        : _maChuyenBay(ma), _soHieuMayBay(sh), _ngayKhoiHanh(ngay), _sanBayDen(sbd), _trangThai(tt), _danhSachVe(dsVe), _danhSachGheTrong(dsGheTrong) {
    }

    const string& getMaChuyenBay() const { return _maChuyenBay; }
    void setMaChuyenBay(const string& v) { _maChuyenBay = v; }

    const string& getSoHieuMayBay() const { return _soHieuMayBay; }
    void setSoHieuMayBay(const string& v) { _soHieuMayBay = v; }

    const string& getNgayKhoiHanh() const { return _ngayKhoiHanh; }
    void setNgayKhoiHanh(const string& v) { _ngayKhoiHanh = v; }

    const string& getSanBayDen() const { return _sanBayDen; }
    void setSanBayDen(const string& v) { _sanBayDen = v; }

    const string& getTrangThai() const { return _trangThai; }
    void setTrangThai(const string& v) { _trangThai = v; }

    list<Ve>& GetDanhSachVe() { return _danhSachVe; }
    const list<Ve>& GetDanhSachVe() const { return _danhSachVe; }

    list<string>& GetDanhSachGheTrong() { return _danhSachGheTrong; }
    const list<string>& GetDanhSachGheTrong() const { return _danhSachGheTrong; }

    void WriteToStream(ostream& os) const {
        os << _maChuyenBay << endl;
        os << _soHieuMayBay << endl;
        os << _ngayKhoiHanh << endl;
        os << _sanBayDen << endl;
        os << _trangThai << endl;
        os << _danhSachVe.size() << endl;
        for (const Ve& ve : _danhSachVe) {
            os << ve.getMaVe() << endl;
        }
        os << _danhSachGheTrong.size() << endl;
        for (const auto& ghe : _danhSachGheTrong) {
            os << ghe << endl;
        }
    }

    // Read a ChuyenBay from stream (expects fields in same order written by WriteToStream)
    static ChuyenBay ReadFromStream(istream& is) {
        ChuyenBay cb;
        getline(is, cb._maChuyenBay);
        getline(is, cb._soHieuMayBay);
        getline(is, cb._ngayKhoiHanh);
        getline(is, cb._sanBayDen);
        getline(is, cb._trangThai);

        int soVe = 0;
        is >> soVe;
        is.ignore(numeric_limits<streamsize>::max(), '\n');
        for (int j = 0; j < soVe; ++j) {
            string maVe;
            getline(is, maVe);
            Ve veMoi;
            if (Ve::LoadFromFile(maVe, veMoi)) {
                veMoi.setMaVe(maVe);
                cb._danhSachVe.push_back(veMoi);
            }
            else {
                // partial fallback
                Ve fallback;
                fallback.setMaVe(maVe);
                fallback.setMaChuyenBay(cb._maChuyenBay);
                cb._danhSachVe.push_back(fallback);
            }
        }

        int soGhe = 0;
        is >> soGhe;
        is.ignore(numeric_limits<streamsize>::max(), '\n');
        for (int j = 0; j < soGhe; ++j) {
            string ghe;
            getline(is, ghe);
            cb._danhSachGheTrong.push_back(ghe);
        }

        return cb;
    }
};

class Admin {
private:
    string _tenDangNhap;
    string _matKhau;

public:
    Admin() : _tenDangNhap(""), _matKhau("") {}
    Admin(const string& user, const string& pass) : _tenDangNhap(user), _matKhau(pass) {}

    const string& getTenDangNhap() const { return _tenDangNhap; }
    void setTenDangNhap(const string& v) { _tenDangNhap = v; }

    const string& getMatKhau() const { return _matKhau; }
    void setMatKhau(const string& v) { _matKhau = v; }

    void WriteToStream(ostream& os) const {
        os << _tenDangNhap << endl;
        os << _matKhau << endl;
    }

    static Admin ReadFromStream(istream& is) {
        Admin admin;
        getline(is, admin._tenDangNhap);
        getline(is, admin._matKhau);
        return admin;
    }
};

// ---------- Existing top-level file functions updated to use class methods ----------

void DocFileVeRieng(const string& maVe, Ve& ve) {
    Ve::LoadFromFile(maVe, ve);
}

void GhiFileMayBay(const vector<MayBay>& dsMayBay, const string& mayBay) {
    ofstream file("MayBay.txt");
    if (!file.is_open()) {
        cout << "File khong ton tai";
        return;
    }
    file << dsMayBay.size() << endl;
    for (const auto& mb : dsMayBay) {
        mb.WriteToStream(file);
    }
    file.close();
}

void DocFileMayBay(vector<MayBay>& dsMayBay, const string& mayBay) {
    dsMayBay.clear();
    ifstream file("MayBay.txt");
    if (!file.is_open()) {
        cout << "File khong ton tai";
        return;
    }
    int n;
    file >> n;
    file.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < n; i++) {
        MayBay mb = MayBay::ReadFromStream(file);
        dsMayBay.push_back(mb);
    }
    file.close();
}

void GhiFileKhachHang(const vector<KhachHang>& dsKhachHang, const string& khachHang) {
    ofstream file("KhachHang.txt");
    if (!file.is_open()) {
        cout << "File khong ton tai";
        return;
    }

    file << dsKhachHang.size() << endl;
    for (const auto& kh : dsKhachHang) {
        kh.WriteToStream(file);
    }
    file.close();
}

void DocFileKhachHang(vector<KhachHang>& dsKhachHang, const string& khachHang) {
    dsKhachHang.clear();
    ifstream file("KhachHang.txt");
    if (!file.is_open()) {
        cout << "File khong ton tai";
        return;
    }

    int n;
    file >> n;
    file.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < n; i++) {
        KhachHang kh = KhachHang::ReadFromStream(file);
        dsKhachHang.push_back(kh);
    }
    file.close();
}

void GhiFileChuyenBay(const vector<ChuyenBay>& dsChuyenBay, const string& chuyenBay) {
    ofstream file("ChuyenBay.txt");
    if (!file.is_open()) {
        cout << "File khong ton tai";
        return;
    }
    file << dsChuyenBay.size() << endl;
    for (const auto& cb : dsChuyenBay) {
        cb.WriteToStream(file);
    }
    file.close();
}

void DocFileChuyenBay(vector<ChuyenBay>& dsChuyenBay, const string& chuyenBay) {
    dsChuyenBay.clear();
    ifstream file("ChuyenBay.txt");
    if (!file.is_open()) {
        cout << "File khong ton tai";
        return;
    }
    int n;
    file >> n;
    file.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int i = 0; i < n; i++) {
        ChuyenBay cb = ChuyenBay::ReadFromStream(file);
        dsChuyenBay.push_back(cb);
    }
    file.close();
}

void GhiFileAdmin(const vector<Admin>& dsAdmin, const string& adminFile) {
    ofstream file("Admin.txt");
    if (!file.is_open()) {
        cout << "File khong ton tai";
        return;
    }

    file << dsAdmin.size() << endl;
    for (const auto& admin : dsAdmin) {
        admin.WriteToStream(file);
    }
    file.close();
}

void DocFileAdmin(vector<Admin>& dsAdmin, const string& adminFile) {
    dsAdmin.clear();
    ifstream file("Admin.txt");
    if (!file.is_open()) {
        cout << "File khong ton tai";
        return;
    }
    int n;
    file >> n;
    file.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int i = 0; i < n; i++) {
        Admin admin = Admin::ReadFromStream(file);
        dsAdmin.push_back(admin);
    }
    file.close();
}

void GhiFileVe(const Ve& ve) {
    ve.SaveToFile();
}

bool SoHieuDuyNhat(const vector<MayBay>& dsMayBay, const string& soHieuMoi) {
    for (const auto& mb : dsMayBay) {
        if (mb.getSoHieu() == soHieuMoi) {
            return false;
        }
    }
    return true;
}

bool MaDuyNhat(const vector<ChuyenBay>& dsChuyenBay, const string& maMoi) {
    for (const auto& cb : dsChuyenBay) {
        if (cb.getMaChuyenBay() == maMoi) {
            return false;
        }
    }
    return true;
}

list<string> TaoDanhSachGheTrong(int soCho) {
    list<string> danhsachGhe;
    for (int i = 1; i <= soCho; ++i) {
        string soGhe;
        if (i < 10) {
            soGhe = "0" + to_string(i);
        }
        else {
            soGhe = to_string(i);
        }
        danhsachGhe.push_back(soGhe);
    }
    return danhsachGhe;
}

void KhoiTaoDuLieuMau() {
    vector<MayBay> dsMayBay = {
        MayBay("VN-A101", 100),
        MayBay("VN-B202", 50),
        MayBay("VN-C303", 200)
    };
    GhiFileMayBay(dsMayBay, "");

    vector<KhachHang> dsKhachHang = {
        KhachHang(1, "0011223344", "Nguyen Van A"),
        KhachHang(2, "0022334455", "Tran Thi B"),
        KhachHang(3, "0033445566", "Le Van C"),
        KhachHang(4, "0044556677", "Pham Thi D"),
        KhachHang(5, "0055667788", "Hoang Van E"),
        KhachHang(6, "0066778899", "Dang Thi F"),
        KhachHang(7, "0077889900", "Bui Van G"),
        KhachHang(8, "0088990011", "Vo Thi H"),
        KhachHang(9, "0099001122", "Do Van I"),
        KhachHang(10, "0011223300", "Ngo Thi K")
    };
    GhiFileKhachHang(dsKhachHang, "");

    vector<ChuyenBay> dsChuyenBay;

    ChuyenBay cb1;
    cb1.setMaChuyenBay("CB001");
    cb1.setSoHieuMayBay("VN-A101");
    cb1.setNgayKhoiHanh("2025-11-15");
    cb1.setSanBayDen("Ha Noi");
    cb1.setTrangThai("1");

    cb1.GetDanhSachGheTrong() = TaoDanhSachGheTrong(100);

    Ve ve1;
    ve1.setMaChuyenBay("CB001");
    ve1.setSoGhe("01");
    ve1.setThongTinKhachHang(dsKhachHang[0]);
    ve1.setMaVe(ve1.getMaChuyenBay() + ve1.getSoGhe());
    cb1.GetDanhSachVe().push_back(ve1);
    cb1.GetDanhSachGheTrong().remove(ve1.getSoGhe());
    GhiFileVe(ve1);

    Ve ve2;
    ve2.setMaChuyenBay("CB001");
    ve2.setSoGhe("02");
    ve2.setThongTinKhachHang(dsKhachHang[1]);
    ve2.setMaVe(ve2.getMaChuyenBay() + ve2.getSoGhe());
    cb1.GetDanhSachVe().push_back(ve2);
    cb1.GetDanhSachGheTrong().remove(ve2.getSoGhe());
    GhiFileVe(ve2);

    dsChuyenBay.push_back(cb1);

    ChuyenBay cb2 = ChuyenBay("CB002", "VN-B202", "2025-12-01", "TP Ho Chi Minh", "1", {}, TaoDanhSachGheTrong(50));
    dsChuyenBay.push_back(cb2);

    ChuyenBay cb3 = ChuyenBay("CB003", "VN-C303", "2025-12-15", "Da Nang", "2", {}, TaoDanhSachGheTrong(200));
    dsChuyenBay.push_back(cb3);

    ChuyenBay cb4;
    cb4.setMaChuyenBay("CB004");
    cb4.setSoHieuMayBay("VN-A101");
    cb4.setNgayKhoiHanh("2026-01-01");
    cb4.setSanBayDen("Hue");
    cb4.setTrangThai("0");
    cb4.GetDanhSachGheTrong() = TaoDanhSachGheTrong(100);

    ChuyenBay cb5;
    cb5.setMaChuyenBay("CB005");
    cb5.setSoHieuMayBay("VN-B202");
    cb5.setNgayKhoiHanh("2026-01-15");
    cb5.setSanBayDen("Can Tho");
    cb5.setTrangThai("3");
    // cb5 has empty danhSachGheTrong

    dsChuyenBay.push_back(cb4);
    dsChuyenBay.push_back(cb5);

    GhiFileChuyenBay(dsChuyenBay, "");

    vector<Admin> dsAdmin = {
        Admin("SonTung-MTP", "363636")
    };
    GhiFileAdmin(dsAdmin, "");
    cout << "Khoi tao du lieu thanh cong\n";
}

int main() {
    KhoiTaoDuLieuMau();
}