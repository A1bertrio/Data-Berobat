#include "data_berobat.h"

void createListDokter(ListDokter &L) {
    L.first = nullptr;
    L.last = nullptr;
}

// createListPasien
void createListPasien(ListPasien &L) {
    L.first = nullptr;
}

adrDokter alokasiDokter(string nama, string id, string spesialisasi) {
    adrDokter P = new elmDokter;
    P->info.nama_dokter = nama;
    P->info.id = id;
    P->info.spesialisasi = spesialisasi;
    P->info.jumlah_pasien = 0;
    P->next = nullptr;
    P->prev = nullptr;
    P->firstRelasi = nullptr; // inisialisasi head relasi
    return P;
}

// alokasiPasien
adrPasien alokasiPasien(string nama, int id, int umur, string keluhan) {
    adrPasien P = new elmPasien;
    P->info.nama_pasien = nama;
    P->info.id = id;
    P->info.umur = umur;
    P->info.jumlah_dokter = 0;
    P->info.keluhan = keluhan;
    P->next = nullptr;
    return P;
}

// a. Penambahan Dokter (Instert Last)
void insertLastDokter(ListDokter &L, adrDokter P) {
    if (L.first == nullptr) {
        L.first = P;
        L.last = P;
    } else {
        P->prev = L.last;
        L.last->next = P;
        L.last = P;
    }
}

// b. Penambahan Pasien (Insert First)
void insertPasien(ListPasien &L, adrPasien P) {
    if (L.first == nullptr) {
        L.first = P;
    } else {
        P->next = L.first;
        L.first = P;
    }
}

adrDokter findDokter(ListDokter L, string id) {
    adrDokter P = L.first;
    while (P != nullptr) {
        if (P->info.id == id) {
            return P;
        }
        P = P->next;
    }
    return nullptr; // jika tidak ditemukan
}

// find pasien
adrPasien findPasien(ListPasien L, int id) {
    adrPasien P = L.first;
    while (P != nullptr) {
        if (P->info.id == id) return P;
        P = P->next;
    }
    return nullptr;
}
// c. connect parent dengan child (dan sebaliknya)
void connect(ListDokter &LD, ListPasien &LP, string idDokter, int idPasien) {
    adrDokter D = findDokter(LD, idDokter);
    adrPasien P = findPasien(LP, idPasien);
    if (D == nullptr && P == nullptr) {
        cout << "Dokter atau Pasien tidak ditemukan\n";
        return;
    }
    // validasi jumlah dokter pada pasien maksimal 5
    if (P->info.jumlah_dokter >= 5) {
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
void deleteDokter(ListDokter &L, string id) {
    adrDokter D = findDokter(L, id);
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
    cout << "Dokter " << D->info.nama_dokter << " beserta semua relasinya telah dihapus.\n";
    delete D;
}

// e. Menghapus data pasien tertentu beserta semua relasinya
void deletePasien(ListPasien &LP, ListDokter &LD, int id) {
    adrPasien P = findPasien(LP, id);
    if (P == nullptr) {
        cout << "Pasien tidak ditemukan." << endl;
        return;
    }

    // hapus relasi pasien dari semua dokter
    adrDokter D = LD.first;
    while (D != nullptr) {
        adrRelasi R = D->firstRelasi;
        adrRelasi prevR = nullptr;
        bool deleted = false;
            
        while (R != nullptr) {
            if (R->child == P) {
                if (prevR == nullptr) {
                    D->firstRelasi = R->next;
                } else {
                    prevR->next = R->next;
                }
                adrRelasi temp = R;
                R = R->next;
                delete temp;
                deleted = true;
                break; // Satu dokter hanya punya 1 relasi ke pasien yg sama
            } else {
                prevR = R;
                R = R->next;
            }
        }
        if (deleted) D->info.jumlah_pasien--; // Update counter dokter
        D = D->next;
    }

    // hapus node pasien dari list pasien
    if (LP.first == P) {
        LP.first = P->next;
    } else {
        adrPasien prec = LP.first;
        while (prec->next != P) {
            prec = prec->next;
        }
        prec->next = P->next;
    }
    delete P;
    cout << "Data Pasien berhasil dihapus beserta seluruh relasinya." << endl;
}

// f. Menampilkan semua pasien beserta dokternya
void showAllPasienWithDokter(ListPasien LP, ListDokter LD) {
    cout << "\n=== DATA PASIEN & DOKTERNYA ===" << endl;
    if (LP.first == nullptr) { cout << "Data Pasien Kosong." << endl; return; }

    adrPasien P = LP.first;
    while (P != nullptr) {
        cout << "Pasien: " << P->info.nama_pasien << " (ID: " << P->info.id << ")" << endl;
        cout << "   Dokter yang menangani: ";
        
        bool ada = false;
        // Cari dokter yang punya relasi ke P
        adrDokter D = LD.first;
        while (D != nullptr) {
            adrRelasi R = D->firstRelasi;
            while(R != nullptr) {
                if (R->child == P) {
                    cout << D->info.nama_dokter << ", ";
                    ada = true;
                }
                R = R->next;
            }
            D = D->next;
        }
        if (!ada) cout << "- Tidak ada -";
        cout << endl;
        P = P->next;
    }
}

// g. Menampilkan data pasien yang ditangani dokter tertentu
void showPasienByDokter(ListDokter LD, string idDokter) {
    adrDokter D = findDokter(LD, idDokter);
    if (!D) {
        cout << "Dokter dengan id " << idDokter << " tidak ditemukan.\n";
        return;
    }

    cout << "\n=== Pasien yang ditangani Dr. " << D->info.nama_dokter << " ===\n";
    if (D->firstRelasi == nullptr) {
        cout << "- Belum ada pasien.\n";
        return;
    }

    // for loop pointer
    for (adrRelasi R = D->firstRelasi; R != nullptr; R = R->next) {
        adrPasien P = R->child;
        cout << "- " << P->info.nama_pasien
             << " | Umur: " << P->info.umur
             << " | Keluhan: " << P->info.keluhan << "\n";
    }
}

// h. Menampilkan data dokter yang menangani pasien tertentu
void showDokterByPasien (ListDokter LD, ListPasien LP, int idPasien) {
    adrPasien P = findPasien(LP, idPasien);
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
void showAllDokter (ListDokter L) {
    cout << "\n=== DAFTAR DOKTER ===\n";
    adrDokter D = L.first;
    while (D != nullptr) {
        cout << "Nama Dokter: " << D->info.nama_dokter << endl;
        cout << "ID: " << D->info.id << endl;
        cout << "Spesialisasi: " << D->info.spesialisasi << endl;
        cout << "Jumlah pasien: " << D->info.jumlah_pasien << endl;
        cout << "-----------------------------" << endl;
        D = D->next;
    }
}