#include "data_berobat.h"

int main() {
    ListDokter LD;
    ListPasien LP;
    createListDokter(LD);
    createListPasien(LP);

    int pilihan, idP, umurP;
    string idD, namaD, spesialisD, namaP;

    do {
        cout << "\n==============================================" << endl;
        cout << "    APLIKASI MANAJEMEN RUMAH SAKIT (M-to-N)   " << endl;
        cout << "==============================================" << endl;
        cout << "1.  [a] Tambah Dokter" << endl;
        cout << "2.  [b] Tambah Pasien" << endl;
        cout << "3.  [c] Hubungkan Dokter & Pasien" << endl;
        cout << "4.  [d] Hapus Dokter (ID)" << endl;
        cout << "5.  [e] Hapus Pasien (ID)" << endl;
        cout << "6.  [f] Tampilkan Semua Pasien & Dokternya" << endl;
        cout << "7.  [g] Cari Pasien dari Dokter Tertentu" << endl;
        cout << "8.  [h] Cari Dokter dari Pasien Tertentu" << endl;
        cout << "9.  [i] Statistik Dokter (Sibuk/Luang)" << endl;
        cout << "10. Tampilkan List Dokter (Master)" << endl;
        cout << "0.  Keluar" << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch(pilihan) {
            case 1:
                cout << "Masukkan ID Dokter: "; cin >> idD;
                cout << "Nama Dokter: "; cin.ignore(); getline(cin, namaD);
                cout << "Spesialis: "; getline(cin, spesialisD);
                insertLastDokter(LD, alokasiDokter(namaD, spesialisD));
                break;
            case 2:
                cout << "Masukkan ID Pasien (Angka): "; cin >> idP;
                cout << "Nama Pasien: "; cin.ignore(); getline(cin, namaP);
                cout << "Umur: "; cin >> umurP;
                insertPasien(LP, alokasiPasien(namaP, idP, umurP));
                break;
            case 3:
                cout << "ID Dokter: "; cin >> idD;
                cout << "ID Pasien: "; cin >> idP;
                connect(LD, LP, idD, idP);
                break;
            case 4:
                cout << "ID Dokter yg dihapus: "; cin >> idD;
                deleteDokter(LD, idD);
                break;
            case 5:
                cout << "ID Pasien yg dihapus: "; cin >> idP;
                deletePasien(LP, LD, idP);
                break;
            case 6:
                showAllPasienWithDokter(LP, LD);
                break;
            case 7:
                cout << "ID Dokter: "; cin >> idD;
                showPasienByDokter(LD, idD);
                break;
            case 8:
                cout << "ID Pasien: "; cin >> idP;
                showDokterByPasien(LD, LP, idP);
                break;
            case 9:
                showDokterSibuk(LD);
                break;
            case 10:
                showAllDokter(LD);
                break;
        }
    } while (pilihan != 0);

    return 0;
}