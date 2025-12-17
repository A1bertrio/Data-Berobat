#ifndef data_berobat_h
#define data_berobat_h

#include <iostream>
#include <string>
using namespace std;

// Data Pasien (Child)
struct Pasien {
    string nama_pasien;
    int umur;
    string keluhan;
    int jumlah_dokter; // maksimal 5 dokter
};

typedef struct elmPasien* adrPasien;

struct elmPasien {
    Pasien info;
    adrPasien next;
    adrPasien prev;
};

struct ListPasien {
    adrPasien first;
    adrPasien last;
};

// Manajemen Pasien
void createListPasien(ListPasien &L);
adrPasien alokasiPasien(string nama, int umur, string keluhan);
void insertLastPasien(ListPasien &L, adrPasien P);
void insertFirstPasien(ListPasien &L, adrPasien &P);
void deletePasien(ListPasien &L, string nama);
adrPasien findPasien(ListPasien L, string nama);
void showAllPasien(ListPasien L);


// Data Dokter (Parent)
struct Dokter {
    string nama_dokter;
    string spesialisasi;
    int jumlah_pasien;
};

typedef struct elmDokter* adrDokter;

struct elmDokter {
    Dokter info;
    adrDokter next;
    adrDokter prev;
    adrRelasi firstRelasi; 
};

struct ListDokter {
    adrDokter first;
    adrDokter last;
};

// Data Relasi
typedef struct elmRelasi *adrRelasi;
struct elmRelasi {
    adrRelasi next;
    adrRelasi child;
};

// Manajemen Dokter
void createListDokter(ListDokter &L);
adrDokter alokasiDokter(string nama, string spesialisasi);
void insertLastDokter(ListDokter &L, adrDokter P);
void insertFirstDokter(ListDokter &L, adrDokter &P);
void deleteDokter(ListDokter &L, string nama);
adrDokter findDokter(ListDokter L, string nama);
void showAllDokter(ListDokter L);

// Manajemen Pasien



// Manajemen Relasi
void connectPasienToDokter(ListDokter &LD, ListPasien &LP, string namaDokter, string namaPasien);
void showAllData (ListDokter LD);

//Mencari data child (pasien) pada parent tertentu

//Menghapus data child (pasien) pada parent tertentu

// Menghitung jumlah data child dari parent tertentu

#endif