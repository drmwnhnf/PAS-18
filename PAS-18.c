// Aplikasi Administrasi Servis Mobil
// Kelompok 18
// Nama: Darmawan Hanif, NPM: 2206829175
// Nama: Fabio Rabbani Prasetyo, NPM: 2206829490

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <omp.h>
#include <time.h>

// Struktur data untuk informasi pelanggan
struct Pelanggan {
    char nama[50];
    char namaKendaraan[50];
    char plat[50];
    char alamat[100];
    char service[100];
    float biaya;
    long long int tanggalDaftar;
    struct Pelanggan* next;
};

struct Cadangan {
	char nama[50];
    char namaKendaraan[50];
    char plat[50];
    char alamat[100];
    char service[100];
    long long int tanggalDaftar;
    float biaya;
};

// Deklarasi fungsi
void tambahPelanggan(struct Pelanggan** antrian);
void panggilPelanggan(struct Pelanggan** antrian);
void simpanDataPelanggan(struct Pelanggan* antrian, FILE* fileData);
void muatDataPelanggan(struct Pelanggan** antrian, FILE* fileData);
void sortingNama(struct Pelanggan** antrian);
void frekuensiPelanggan(struct Cadangan* cad, int n, int frek[]);
long long int tanggalSekarang();

int main() {
    system("title \'Aplikasi Administrasi Bengkel Mobil\'");
	system("color 03");
    int pilihan, pilihan1, i;
    char pass[10], uname[10], ch;
    char trueUname[] = "admin";
    char truePass[] = "kel18keren";
	int maxThread = omp_get_max_threads();
	omp_set_num_threads(maxThread);

    for(;;) {
        // Mengoutput tulisan untuk welcome dan login page
        system("cls");
        printf("Selamat Datang di Aplikasi Administrasi Bengkel!\n");
        printf("================== Login Page ==================\n");
        printf("Username: ");
        gets(uname);
        printf("Password: ");
        i = 0; 

        // Menginput membuat password tidak terlihat di terminal
        while((ch = getch()) != 13) {
            if(ch == '\b' && i != 0) {
                i--;
                pass[i] = '\0';
                printf("\b \b");
            }
            else if(ch != '\b' && i < 10) {
                pass[i] = ch;
                printf("*");
                i++;
            }
        }
        pass[i] = '\0';

        // Mengecek username dan password
        if(strcmp(uname, trueUname) == 0 && strcmp(pass, truePass) == 0) {
            printf("\nBerhasil masuk!\n");
            system("pause");
            break;
        }
        else {
            printf("\nUsername atau password salah!\n");
            system("pause");
        }
    }

    // Membuka file data pelanggan
    FILE* fileData = fopen("data_pelanggan.csv", "a+");
    if (fileData == NULL) {
        printf("Gagal membuka file data_pelanggan.csv.\n");
        return 1;
    }

    struct Pelanggan* antrian = NULL;

    do {
    	system("cls");
    	printf("===========================================\n");
    	printf("============= Selamat Datang ==============\n");
        printf("=== Aplikasi Administrasi Bengkel Mobil ===\n");
        printf("===========================================\n");      
        printf("1. Input Pelanggan\n");
        printf("2. Panggil Pelanggan\n");
        printf("3. Sorting Nama\n");
        printf("4. File Handling\n");
        printf("5. Panduan\n");
        printf("6. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);
        switch (pilihan) {
            case 1:
                tambahPelanggan(&antrian);
                break;
            case 2:
                panggilPelanggan(&antrian);
                break;
            case 3:
            	sortingNama(&antrian);
            	break;
            case 4:
            		system("cls");
            		printf("Pilih menu berikut :\n1. Muat Data\n2. Simpan Data\nPilihan Anda : ");
            		scanf("%d",&pilihan1);
            		if(pilihan1 == 1){
            			// Memuat data pelanggan dari file
    					muatDataPelanggan(&antrian, fileData);
    					printf("\nData pelanggan berhasil dimuat...");
    					printf("\n\nTekan apapun untuk kembali...");
					}
            		else if(pilihan1 == 2){
            			// Menyimpan data pelanggan
            			simpanDataPelanggan(antrian, fileData);
					}
					getch();
			case 5:
                printf("Petunjuk Penggunaan");
                printf ("\n");
                printf("Input\n");
                printf("1. User memasukan data-data yang perlu diisi\n");
                printf("2. Jika telah selesai menginput, ketik apapun untuk kembali ke menu\n");
                printf ("===============================================================================================\n");
                printf("Panggil Pelanggan\n");
                printf("1. Ketika user menginput 2 pada menu Panggil pelanggan\nmaka pelanggan akan dipanggil sesuai antrian\n");
                printf ("===============================================================================================\n");
                printf("Sorting Nama\n");
                printf("1. Terdapat 2 pilihan di dalam menu Sorting Nama\n");
                printf("2. User memasukan angka 1 jika ingin melihat secara ascending\n");
                printf("3. User memasukan angka 2 jika ingin melihat secara descending\n");
                printf ("===============================================================================================\n");
                printf("File Handling\n");
                printf("1. User memasukan angka 1 jika ingin memuat data\n");
                printf("2. USer memasukan angka 2 menyimpan data\n");
                printf("3. Jika user sudah menyimpan data kemudian keluar aplikasi\ndata yang sebelumnya bisa dimuat kembali dengan memasukan angka 1\n");
                printf ("===============================================================================================\n");
                system("pause");
				break;
            case 6:
                break;
            default:
                printf("Pilihan tidak valid.\n");
                break;
        }
    } while (pilihan != 6);

    // Menutup file data pelanggan
    fclose(fileData);

    return 0;
}

//Function untuk menghitung frekuensi pelanggan yang sudah pernah ke bengkel
void frekuensiPelanggan(struct Cadangan* cad, int n, int frek[]){
	int i = 0, j = 0, z = 0, gratis;
	for(i = 0; i < n; i++){
		if(strcmp(cad[i].nama, cad[i-1].nama) == 0){ //Melakukan pengecekan pada nama
			continue;
		}
		z++;
		for(j = 0; j < n; j++){
			if(strcmp(cad[i].nama, cad[j].nama) == 0){
				frek[z-1]++;
			}
		}
	}
	z = 0;
	printf("\n\nList Pasien Yang Sudah Pernah Kebengkel :");
	printf("\n(3 kali servis gratis 1 kali)");
	for(i = 0; i < n; i++){
		if(strcmp(cad[i].nama, cad[i-1].nama) == 0){
			continue;
		}
		z++;
		printf("\n%s : %d kali ", cad[i].nama, frek[z-1]);
		if(frek[z-1]/3 != 0){
			gratis = frek[z-1]/3;
			printf("(Gratis %d kali)", gratis);
		}
	}
}

//Function waktu real time
long long int tanggalSekarang() {
	time_t waktu = time(NULL); // Menginisialisasikan jumlah detik sesuai fungsi time (NULL)
	struct tm now = *localtime(&waktu); //Menginisialisasikan struct tm dengan nilai return dari fungsi localtime
	long long int tanggal = (now.tm_year + 1900)*10000 + (now.tm_mon + 1)*100 + now.tm_mday; // Mengassign tahun, bulan, hari (yyyymmdd)
	return tanggal;
}

// Function untuk sorting
void sortingNama(struct Pelanggan** antrian){
	system("cls");
	struct Pelanggan *temp, *temp1 = *antrian, *temp2 = *antrian;
	int i = 0, j = 0, n = 0, inp, frek[] = {0};
	struct Cadangan *cad, tmp;
	
	for(temp= *antrian; temp != NULL; temp = temp->next){
		n += 1;
	}
	cad = (struct Cadangan*)malloc(n * sizeof(struct Cadangan));
	while(temp1 != NULL){
		strcpy(cad[i].nama, temp1->nama);
		strcpy(cad[i].namaKendaraan, temp1->namaKendaraan);
		strcpy(cad[i].plat, temp1->plat);
		strcpy(cad[i].alamat, temp1->alamat);
		strcpy(cad[i].service, temp1->service);
		cad[i].tanggalDaftar = temp1->tanggalDaftar;
		cad[i].biaya = temp1->biaya;
		frek[i] = 0;
		i++;
		temp1 = temp1->next;
 	}
	printf("Sorting nama secara :\n1. Ascending (a-z)\n2. Descending (z-a)\nInput : ");
	scanf("%d", &inp);
	if(inp == 1){
		for(i = 0; i < n; i++){
			#pragma omp for
			for(j = 0; j < n; j++){
				#pragma omp task
				if(strcmpi(cad[i].nama, cad[j].nama) < 0){
					tmp = cad[i];
					cad[i] = cad[j];
					cad[j] = tmp;
				}
				#pragma omp taskwait
			}
			#pragma omp barrier
		}
	}
	else if(inp == 2){
		for(i = 0; i < n; i++){
			#pragma omp for
			for(j = 0; j < n; j++){
				#pragma omp task
				if(strcmpi(cad[i].nama, cad[j].nama) > 0){
					tmp = cad[i];
					cad[i] = cad[j];
					cad[j] = tmp;
				}
				#pragma omp taskwait
			}
			#pragma omp barrier
		}
	}
	#pragma omp for
	for(i = 0; i < n; i++){
		strcpy(temp2->nama, cad[i].nama);
		strcpy(temp2->namaKendaraan, cad[i].namaKendaraan);
		strcpy(temp2->plat, cad[i].plat);
		strcpy(temp2->alamat, cad[i].plat);
		strcpy(temp2->service, cad[i].service);
		temp2->tanggalDaftar = cad[i].tanggalDaftar;
		temp2->biaya = cad[i].biaya;
		printf("\nNama: %s\n", cad[i].nama);
    	printf("Nama Kendaraan: %s\n", cad[i].namaKendaraan);
    	printf("Nomor Plat : %s\n", cad[i].plat);
    	printf("Alamat: %s\n", cad[i].alamat);
    	printf("Jenis Service yang Dibutuhkan: %s\n", cad[i].service);
    	printf("Biaya: Rp%.2f\n", cad[i].biaya);
    	temp2 = temp2->next;
    	
	}
	#pragma omp barrier
	frekuensiPelanggan(cad, n, frek);
	printf("\n\nData pelanggan sudah terurut secara ");
	if(inp == 1){
		printf("Ascending");
	}
	else if(inp == 2){
		printf("Descending");
	}
	printf("\n\nTekan apapun untuk kembali...");
	getch();
}

// Fungsi untuk menambahkan pelanggan ke antrian
void tambahPelanggan(struct Pelanggan** antrian) {
	system("cls");
    struct Pelanggan* newPelanggan = (struct Pelanggan*)malloc(sizeof(struct Pelanggan));
    printf("Masukkan Nama: ");
    scanf(" %[^\n]", newPelanggan->nama);
    printf("Masukkan Nama Kendaraan: ");
    scanf(" %[^\n]", newPelanggan->namaKendaraan);
    printf("Masukan Plat : ");
    scanf(" %[^\n]", newPelanggan->plat);
    printf("Masukkan Alamat: ");
    scanf(" %[^\n]", newPelanggan->alamat);
    printf("Masukkan Jenis Service yang Dibutuhkan: ");
    scanf(" %[^\n]", newPelanggan->service);
    printf("Masukkan Biaya: ");
    scanf("%f", &(newPelanggan->biaya));
    newPelanggan->tanggalDaftar = tanggalSekarang();

    newPelanggan->next = NULL;

    if (*antrian == NULL) {
        // Antrian kosong
        *antrian = newPelanggan;
    } else {
        // Menambahkan pelanggan ke akhir antrian
        struct Pelanggan* temp = *antrian;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newPelanggan;
    }

    printf("Pelanggan telah ditambahkan ke antrian.");
    printf("\n\nTekan apapun untuk kembali...");
	getch();
}

// Fungsi untuk memanggil pelanggan dari antrian
void panggilPelanggan(struct Pelanggan** antrian) {
	system("cls");
    if (*antrian == NULL) {
        printf("Tidak ada pelanggan dalam antrian.\n");
        return;
    }

    struct Pelanggan* pelangganPanggilan = *antrian;
    *antrian = (*antrian)->next;

    printf("Pelanggan yang dipanggil:\n");
    printf("Nama: %s\n", pelangganPanggilan->nama);
    printf("Nama Kendaraan: %s\n", pelangganPanggilan->namaKendaraan);
    printf("Nomor Plat : %s\n", pelangganPanggilan->plat);
    printf("Alamat: %s\n", pelangganPanggilan->alamat);
    printf("Jenis Service yang Dibutuhkan: %s\n", pelangganPanggilan->service);
    printf("Biaya: Rp%.2f\n", pelangganPanggilan->biaya);
    printf("Tanggal Daftar : %lld\n", pelangganPanggilan->tanggalDaftar);

	printf("\n\nTekan apapun untuk kembali...");
    free(pelangganPanggilan);
	getch();
}

// Fungsi untuk menyimpan data pelanggan ke file
void simpanDataPelanggan(struct Pelanggan* antrian, FILE* fileData) {
    if (fileData == NULL) {
        printf("Gagal menyimpan data pelanggan.\n");
        return;
    }

    // Mengosongkan file sebelum menulis ulang
    fclose(fileData);
    fileData = fopen("data_pelanggan.csv", "w");
    if (fileData == NULL) {
        printf("Gagal menyimpan data pelanggan.\n");
        return;
    }

    fprintf(fileData, "Nama;Nama Kendaraan;Plat;Alamat;Jenis Servis;Biaya;Tanggal Daftar\n"); // Menulis header kolom

    struct Pelanggan* temp = antrian;
    while (temp != NULL) {
    	#pragma omp single
        fprintf(fileData, "%s;%s;%s;%s;%s;%.2f;%lld\n", temp->nama, temp->namaKendaraan, temp->plat, temp->alamat, temp->service, temp->biaya,temp->tanggalDaftar);
        temp = temp->next;
    }

    printf("Data pelanggan berhasil disimpan.");
    printf("\n\nTekan apapun untuk kembali...");
}

// Fungsi untuk memuat data pelanggan dari file
void muatDataPelanggan(struct Pelanggan** antrian, FILE* fileData) {
    if (fileData == NULL) {
        printf("Gagal memuat data pelanggan.\n");
        return;
    }

    char line[255];
    fgets(line, sizeof(line), fileData); // Membaca header kolom (baris pertama), dan mengabaikannya

    while (fgets(line, sizeof(line), fileData) != NULL) {
        struct Pelanggan* newPelanggan = (struct Pelanggan*)malloc(sizeof(struct Pelanggan));

        char* token = strtok(line, ";");
        strcpy(newPelanggan->nama, token);

        token = strtok(NULL, ";");
        strcpy(newPelanggan->namaKendaraan, token);

        token = strtok(NULL, ";");
        strcpy(newPelanggan->plat, token);

        token = strtok(NULL, ";");
        strcpy(newPelanggan->alamat, token);

        token = strtok(NULL, ";");
        strcpy(newPelanggan->service, token);

        token = strtok(NULL, ";");
        newPelanggan->biaya = atof(token);
        
        token = strtok(NULL, ";");
        newPelanggan->tanggalDaftar = atof(token);

        newPelanggan->next = NULL;

        if (*antrian == NULL) {
            // Antrian kosong
            *antrian = newPelanggan;
        } else {
            // Menambahkan pelanggan ke akhir antrian
            struct Pelanggan* temp = *antrian;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newPelanggan;
        }
    }
}
