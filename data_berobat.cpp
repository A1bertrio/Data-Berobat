#include "data_berobat.h"

void createListDokter(ListDokter &L) {
    L.first = nullptr;
    L.last = nullptr;
}

// createListPasien

adrDokter alokasiDokter(string nama, string spesialisasi) {
    adrDokter P = new elmDokter;
    P->info.nama_dokter = nama;
    P->info.spesialisasi = spesialisasi;
    P->info.jumlah_pasien = 0;
    P->next = nullptr;
    P->prev = nullptr;
    P->firstRelasi = nullptr; // inisialisasi head relasi
    return P;
}

// alokasiPasien

// a. Penambahan Dokter (Instert Last)
void insertLastDokter(ListDokter &L, adrDokter P) {
    if (L.first == nullptr) {
        L.first = P;
        L.last = P;
    } else {
        L.last->next = P;
        P->prev = L.last;
        L.last = P;
    }
}

// b. Penambahan Pasien (Insert First)

adrDokter findDokter(ListDokter L, string nama) {
    adrDokter P = L.first;
    while (P != nullptr) {
        if (P->info.nama_dokter == nama) {
            return P;
        }
        P = P->next;
    }
    return nullptr; // jika tidak ditemukan
}

// find pasien

// c. connect parent dengan child (dan sebaliknya)
void connect(ListDokter &LD, ListPasien &LP, string namaDokter, string namaPasien) {
    adrDokter D = findDokter(LD, namaDokter);
    adrPasien P = findPasien(LP, namaPasien);
    if (D == nullptr && P == nullptr) {
        cout << "Dokter atau Pasien tidak ditemukan\n";
        return;
    }
    // validasi jumlah dokter pada pasien maksimal 5
    if (P->info.jumlah_dokter > 5) {
        cout << "Pasien " << P->info.nama_pasien << " sudah memiliki 5 dokter (Max).\n";
        return;
    }
    // cek apakah relasi sudah ada
    adrRelasi cek = D->firstRelasi;
    while (cek != nullptr) {
        if (cek->child == P) {
            cout << "Relasi sudah ada sebelumnya.\n";
            return;
        }
        cek = cek->next;
    }
    // membuat relasi baru (insert first ke list relasi dokter)
    adrRelasi R = new elmRelasi;
    R->child = P;
    R->next = D->firstRelasi;
    D->firstRelasi = R;
    // update jumlah pasien pada dokter dan jumlah dokter pada pasien
    D->info.jumlah_pasien += 1;
    P->info.jumlah_dokter += 1;
    cout << "Berhasil menghubungkan Dr. " << D->info.nama_dokter << " dengan Pasien " << P->info.nama_pasien << ".\n";
}

// d. Menghapus data dokter tertentu beserta semua relasinya
void deleteDokter(ListDokter &L, string nama) {
    adrDokter D = findDokter(L, nama);
    if (D == nullptr) {
        cout << "Dokter tidak ditemukan.\n";
        return;
    }
    // menghapus semua relasi pada dokter tersebut dan update counter pasien
    adrRelasi R = D->firstRelasi;
    while (R != nullptr) {
        R->child->info.jumlah_dokter -= 1; // update jumlah dokter pada pasien
        adrRelasi temp = R;
        R = R->next;
        delete temp;
    }
    // menghapus node dokter dari list dokter
    if (D == L.first && D == L.last) {
        L.first = nullptr;
        L.last = nullptr;
    } else if (D == L.first) {
        L.first = D->next;
        L.first->prev = nullptr;
    } else if (D == L.last) {
        L.last = D->prev;
        L.last->next = nullptr;
    } else {
        D->prev->next = D->next;
        D->next->prev = D->prev;
    }
    delete D;
    cout << "Dokter " << nama << " beserta semua relasinya telah dihapus.\n";
}

// e. Menghapus data pasien tertentu beserta semua relasinya

// f. Menampilkan semua pasien beserta dokternya

// g. Menampilkan data pasien yang ditangani dokter tertentu

// h. Menampilkan data dokter yang menangani pasien tertentu
void showDokterByPasien (ListDokter LD, ListPasien LP, string namaPasien) {
    adrPasien P = findPasien(LP, namaPasien);
    if (P == nullptr) {
        cout << "Pasien tidak ditemukan.\n";
        return;
    }
    cout << "\nDokter yang menangani Pasien " << P->info.nama_pasien << ":\n";
    adrDokter D = LD.first;
    bool found = false;
    while (D != nullptr) {
        adrRelasi R = D->firstRelasi;
        while (R != nullptr) {
            if (R->child == P) {
                cout << "- Dr. " << D->info.nama_dokter << " (" << D->info.spesialisasi << ")\n";
                found = true;
            }
            R = R->next;
        }
        D = D->next;
    }
    if (!found) {
        cout << "Tidak ada dokter yang menangani pasien ini.\n";
    }
}

// i. Menampilkan data dokter yang tidak sibuk dan yang paling sibuk
void showDokterSibuk (ListDokter LD) {
    if (LD.first == nullptr) {
        cout << "Tidak ada data dokter.\n";
        return;
    }
    adrDokter D = LD.first;
    int maxPasien = -1;
    int minPasien = 9999; // asumsi tidak ada dokter dengan pasien sebanyak ini
    while (D != nullptr) {
        if (D->info.jumlah_pasien > maxPasien) {
            maxPasien = D->info.jumlah_pasien;
        }
        if (D->info.jumlah_pasien < minPasien) {
            minPasien = D->info.jumlah_pasien;
        }
        D = D->next;
    }
    cout << "\n=== KESIBUKAN DOKTER ===\n";
    cout << "Dokter Paling Sibuk (" << maxPasien << " pasien):\n";
    D = LD.first;
    while (D != nullptr) {
        if (D->info.jumlah_pasien == maxPasien) {
            cout << "- Dr. " << D->info.nama_dokter << " (" << D->info.spesialisasi << ")\n";
        }
        D = D->next;
    }
    cout << "\nDokter Paling Luang/Tidak Sibuk (" << minPasien << " pasien):\n";
    D = LD.first;
    while (D != nullptr) {
        if (D->info.jumlah_pasien == minPasien) {
            cout << "- Dr. " << D->info.nama_dokter << " (" << D->info.spesialisasi << ")\n";
        }
        D = D->next;
    }
}

// menampilkan dokter tanpa pasien
void showAllData (ListDokter LD) {
    cout << "\n=== DAFTAR DOKTER ===\n";
    adrDokter D = LD.first;
    while (D != nullptr) {
        cout << "\nDr. " << D->info.nama_dokter << " (" << D->info.spesialisasi << ")\n";
        cout << "Jumlah Pasien: " << D->info.jumlah_pasien << "\n";
        cout << "Daftar Pasien:\n";
        adrRelasi R = D->firstRelasi;
        if (R == nullptr) {
            cout << "- Tidak ada pasien.\n";
        } else {
            while (R != nullptr) {
                cout << "- " << R->child->info.nama_pasien << " (Umur: " << R->child->info.umur << ", Keluhan: " << R->child->info.keluhan << ")\n";
                R = R->next;
            }
        }
        D = D->next;
    }
}
