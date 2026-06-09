#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <algorithm>

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

using namespace std;
struct Barang {
    string kodeBarang;
    string namaBarang;
    double harga;
    int    stok;
};
void bersihkanInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void cetakGaris() {
    cout << "+" << string(10, '-')
         << "+" << string(25, '-')
         << "+" << string(15, '-')
         << "+" << string(8,  '-')
         << "+" << endl;
}

string formatRupiah(double angka) {
    long long nilai = static_cast<long long>(angka);
    string s = to_string(nilai);

    int n = s.size();
    for (int i = n - 3; i > 0; i -= 3)
        s.insert(i, ".");
    return "Rp " + s;
}

bool kodeAda(const vector<Barang>& inv, const string& kode) {
    for (const auto& b : inv)
        if (b.kodeBarang == kode) return true;
    return false;
}

void tambahBarang(vector<Barang>& inv) {
    system(CLEAR);
    cout << "       TAMBAH BARANG BARU    \n";

    Barang b;
    while (true) {
        cout << "Kode Barang  : ";
        getline(cin, b.kodeBarang);
        if (b.kodeBarang.empty()) {
            cout << "  [!] Kode tidak boleh kosong.\n";
            continue;
        }
        if (kodeAda(inv, b.kodeBarang)) {
            cout << "  [!] Kode sudah digunakan, gunakan kode lain.\n";
            continue;
        }
        break;
    }

    while (true) {
        cout << "Nama Barang  : ";
        getline(cin, b.namaBarang);
        if (b.namaBarang.empty()) {
            cout << "  [!] Nama tidak boleh kosong.\n";
            continue;
        }
        break;
    }

    while (true) {
        cout << "Harga (Rp)   : ";
        if (cin >> b.harga) {
            if (b.harga < 0) {
                cout << "  [!] Harga tidak boleh negatif.\n";
            } else {
                bersihkanInput();
                break;
            }
        } else {
            cout << "  [!] Masukkan angka yang valid.\n";
            bersihkanInput();
        }
    }

    while (true) {
        cout << "Stok   : ";
        if (cin >> b.stok) {
            if (b.stok < 0) {
                cout << "  [!] Stok tidak boleh negatif.\n";
            } else {
                bersihkanInput();
                break;
            }
        } else {
            cout << "  [!] Masukkan angka yang valid.\n";
            bersihkanInput();
        }
    }

    inv.push_back(b);
    cout << "\n  Barang \"" << b.namaBarang << "\" berhasil ditambahkan!\n";
}

void tampilkanSemuaBarang(const vector<Barang>& inv) {
    system(CLEAR);
    cout << "    DAFTAR SEMUA BARANG     \n";

    if (inv.empty()) {
        cout << "  (Belum ada data barang.)\n";
        return;
    }

    cetakGaris();
    cout << "| " << left  << setw(9)  << "KODE"
         << " | " << setw(24) << "NAMA BARANG"
         << " | " << setw(14) << "HARGA"
         << " | " << setw(7)  << "STOK"
         << " |" << endl;
    cetakGaris();

    for (const auto& b : inv) {
        cout << "| " << left  << setw(9)  << b.kodeBarang
             << " | " << setw(24) << b.namaBarang
             << " | " << right << setw(14) << formatRupiah(b.harga)
             << " | " << setw(7)  << b.stok
             << " |" << endl;
    }

    cetakGaris();
    cout << "  Total barang: " << inv.size() << " item\n";
}

void cariBarangTermahal(const vector<Barang>& inv) {
    system(CLEAR);
    cout << "      BARANG TERMAHAL        \n";

    if (inv.empty()) {
        cout << "  (Belum ada data barang.)\n";
        return;
    }

    auto it = max_element(inv.begin(), inv.end(),
        [](const Barang& a, const Barang& b) {
            return a.harga < b.harga;
        });

    cout << "  Kode Barang  : " << it->kodeBarang  << "\n";
    cout << "  Nama Barang  : " << it->namaBarang  << "\n";
    cout << "  Harga        : " << formatRupiah(it->harga) << "\n";
    cout << "  Stok         : " << it->stok         << " unit\n";
}

void hitungTotalNilai(const vector<Barang>& inv) {
    system(CLEAR);
    cout << "    TOTAL NILAI INVENTARIS    \n";

    if (inv.empty()) {
        cout << "  (Belum ada data barang.)\n";
        return;
    }

    double total = 0;
    cout << left  << setw(25) << "Nama Barang"
         << right << setw(8)  << "Stok"
         << setw(16) << "Harga Satuan"
         << setw(18) << "Subtotal\n";
    cout << string(67, '-') << "\n";

    for (const auto& b : inv) {
        double sub = b.harga * b.stok;
        total += sub;
        cout << left  << setw(25) << b.namaBarang
             << right << setw(8)  << b.stok
             << setw(16) << formatRupiah(b.harga)
             << setw(18) << formatRupiah(sub) << "\n";
    }

    cout << string(67, '=') << "\n";
    cout << right << setw(49) << "TOTAL NILAI INVENTARIS : "
         << setw(18) << formatRupiah(total) << "\n";
}

void cekRestock(const vector<Barang>& inv) {
    system(CLEAR);
    cout << "   BARANG KRITIS (STOK < 5)   \n";

    bool ada = false;
    cetakGaris();
    cout << "| " << left  << setw(9)  << "KODE"
         << " | " << setw(24) << "NAMA BARANG"
         << " | " << setw(14) << "HARGA"
         << " | " << setw(7)  << "STOK"
         << " |" << endl;
    cetakGaris();

    for (const auto& b : inv) {
        if (b.stok < 5) {
            ada = true;
            cout << "| " << left  << setw(9)  << b.kodeBarang
                 << " | " << setw(24) << b.namaBarang
                 << " | " << right << setw(14) << formatRupiah(b.harga)
                 << " | " << setw(7)  << b.stok
                 << " |" << endl;
        }
    }

    cetakGaris();
    if (!ada)
        cout << "  Semua barang memiliki stok yang cukup (5).\n";
    else
        cout << "  Segera lakukan pemesanan ulang untuk barang di atas!\n";
}

void updateStok(vector<Barang>& inv) {
    system(CLEAR);
    cout << "        UPDATE STOK          \n";
    if (inv.empty()) {
        cout << "  (Belum ada data barang.)\n";
        return;
    }

    string kode;
    cout << "Masukkan Kode Barang : ";
    getline(cin, kode);

    int* ptrStok = nullptr;
    string namaDitemukan;

    for (auto& b : inv) {
        if (b.kodeBarang == kode) {
            ptrStok       = &b.stok; 
            namaDitemukan = b.namaBarang;
            break;
        }
    }

    if (ptrStok == nullptr) {
        cout << "\n  [!] Barang dengan kode \"" << kode << "\" tidak ditemukan.\n";
        return;
    }

    cout << "\n  Barang ditemukan : " << namaDitemukan << "\n";
    cout << "  Stok saat ini   : " << *ptrStok << " unit\n\n";

    cout << "  [1] Tambah Stok  (Barang Masuk)\n";
    cout << "  [2] Kurangi Stok (Barang Keluar)\n";
    cout << "  [3] Set Stok Langsung\n";
    cout << "  Pilihan : ";

    int pilihan;
    if (!(cin >> pilihan) || pilihan < 1 || pilihan > 3) {
        cout << "  [!] Pilihan tidak valid.\n";
        bersihkanInput();
        return;
    }
    bersihkanInput();

    int jumlah;
    switch (pilihan) {
        case 1:
            while (true) {
                cout << "  Jumlah tambah : ";
                if (cin >> jumlah && jumlah >= 0) { bersihkanInput(); break; }
                cout << "  [!] Input tidak valid.\n"; bersihkanInput();
            }
            *ptrStok += jumlah;   
            cout << "\n  Stok berhasil ditambah. Stok baru: " << *ptrStok << " unit\n";
            break;

        case 2:
            while (true) {
                cout << "  Jumlah kurang : ";
                if (cin >> jumlah && jumlah >= 0) { bersihkanInput(); break; }
                cout << "  [!] Input tidak valid.\n"; bersihkanInput();
            }
            if (jumlah > *ptrStok) {
                cout << "  [!] Jumlah kurang melebihi stok yang ada (" << *ptrStok << ").\n";
            } else {
                *ptrStok -= jumlah;   
                cout << "\n   Stok berhasil dikurangi. Stok baru: " << *ptrStok << " unit\n";
            }
            break;

        case 3:
            while (true) {
                cout << "  Stok baru : ";
                if (cin >> jumlah && jumlah >= 0) { bersihkanInput(); break; }
                cout << "  [!] Stok tidak boleh negatif.\n"; bersihkanInput();
            }
            *ptrStok = jumlah;   
            cout << "\n  [âœ“] Stok berhasil diset ke " << *ptrStok << " unit\n";
            break;
    }
}

void tampilkanMenu() {
    cout << "  SISTEM MANAJEMEN INVENTARIS     \n";
    cout << "  [1] Tambah Barang               \n";
    cout << "  [2] Tampilkan Semua Barang      \n";
    cout << "  [3] Cari Barang Termahal        \n";
    cout << "  [4] Hitung Total Nilai          \n";
    cout << "  [5] Cek Restock (Stok < 5)      \n";
    cout << "  [6] Update Stok                 \n";
    cout << "  [7] Keluar                      \n";
    cout << "  Pilihan : ";
}

int main() {
    vector<Barang> inventaris;

    inventaris.push_back({"B001", "Laptop Asus VivoBook",  8500000, 12});
    inventaris.push_back({"B002", "Mouse Logitech M100",     85000,  3});
    inventaris.push_back({"B003", "Keyboard Mechanical",    450000,  7});
    inventaris.push_back({"B004", "Monitor 24 Inch",       2800000,  4});
    inventaris.push_back({"B005", "Flash Disk 64GB",         95000, 20});

    int pilihan;

    do {
        system(CLEAR);
        tampilkanMenu();

        if (!(cin >> pilihan)) {
            cout << "  [!] Masukkan angka 1-7.\n";
            bersihkanInput();
            continue;
        }
        bersihkanInput();

        switch (pilihan) {
            case 1: tambahBarang(inventaris);        break;
            case 2: tampilkanSemuaBarang(inventaris); break;
            case 3: cariBarangTermahal(inventaris);  break;
            case 4: hitungTotalNilai(inventaris);    break;
            case 5: cekRestock(inventaris);          break;
            case 6: updateStok(inventaris);          break;
            case 7:
                system(CLEAR);
                cout << "  Terima kasih telah menggunakan program ini. Sampai jumpa!\n\n";
                break;
            default:
                cout << "  [!] Pilihan tidak valid. Masukkan angka 1-7.\n";
        }

        if (pilihan != 7) {
            cout << "\n  Tekan Enter untuk kembali ke menu...";
            cin.get();
        }

    } while (pilihan != 7);

    return 0;
}