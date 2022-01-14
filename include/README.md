# Arsitektur
Layer layer aplikasi terbagi dalam folder folder. 


## Entity
Digunakan untuk kumpulan domain model(struct) yang akan digunakan pada repository dan services.


## Repository
Digunakan untuk mengelola data dan terhubung ke database.


## Services
Digunakan untuk bisnis logic utama. Dimana semua alur dan tahapan berada pada folder ini.

## Infrastructure
Digunakan sebagai fondasi untuk menghubungkan atau membantu antar services.Contohnya menu handler