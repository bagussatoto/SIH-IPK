#include <fstream>
#include <algorithm>

namespace HitungIPKRepository
{
    const string SEPARATOR = "\t";
    string filename = "database/rekapipk.tsv";

    vector<HitungIPKEntity> Find()
    {
        vector<HitungIPKEntity> recordAll;
        fstream fin(filename, ios::in);
        string line;
        getline(fin, line); // skip firstline

        while (getline(fin, line))
        {
            HitungIPKEntity record;
            vector<string> items = split(line, SEPARATOR);
            record.npm = items.at(0);
            record.namaMahasiswa = items.at(1);
            record.kelas = items.at(2);
            record.nilai = stoi(items.at(3));
            record.totalSks = stof(items.at(4));
            record.ipk = stof(items.at(5));

            recordAll.push_back(record);
        }
        fin.close();
        return recordAll;
    }

    HitungIPKEntity FindOneByNpm(string npm)
    {
        HitungIPKEntity record;
        fstream fin(filename, ios::in);
        string line;
        while (getline(fin, line))
        {

            vector<string> items = split(line, SEPARATOR);

            if (items.at(0) == npm)
            {
                record.npm = items.at(0);
                record.namaMahasiswa = items.at(1);
                record.kelas = items.at(2);
                record.nilai = stoi(items.at(3));
                record.totalSks = stof(items.at(4));
                record.ipk = stof(items.at(5));
                fin.close();
            }
        }
        if (fin.is_open())
        {
            fin.close();
        }

        return record;
    }

    bool Create(HitungIPKEntity hitungipk)
    {
        fstream fin(filename, ios::in);
        string firstLine;
        getline(fin, firstLine);

        fstream fout(filename, ios::out | ios::app);
        if (firstLine == "")
        {
            fout << "NPM" << SEPARATOR << "Nama Mahasiswa" << SEPARATOR << "Kelas" << SEPARATOR << "Nilai" << SEPARATOR << "Total SKS" << SEPARATOR << "IPK"
                 << "\n";
        }
        if (FindOneByNpm(hitungipk.npm).npm != "")
        {
            return false;
        }
        fout << hitungipk.npm << SEPARATOR << hitungipk.namaMahasiswa << SEPARATOR << hitungipk.kelas << SEPARATOR << hitungipk.nilai << SEPARATOR << hitungipk.totalSks << SEPARATOR << hitungipk.ipk << "\n";
        fout.close();
        return true;
    }

    void CreateMany(vector<HitungIPKEntity> hitungipk)
    {
        for (auto record : hitungipk)
        {
            Create(record);
        }
    }
    void DeleteAll()
    {

        ofstream fout(filename, ofstream::out | ofstream::trunc);
        fout << "NPM" << SEPARATOR << "Nama Mahasiswa" << SEPARATOR << "Kelas" << SEPARATOR << "Nilai" << SEPARATOR << "Total SKS" << SEPARATOR << "IPK"
             << "\n";

        fout.close();
    }

    void Delete(string npm)
    {
        ifstream fin;
        std::string line;
        fin.open(filename);

        int i = 0;
        while (getline(fin, line))
        {
            ++i;
            if (i == 1)
                continue;

            if (line.find(npm + SEPARATOR) != string::npos)
            {
                delete_line(filename.c_str(), i);
            }
        }
        if (fin.is_open())
        {
            fin.close();
        }
    }
};
