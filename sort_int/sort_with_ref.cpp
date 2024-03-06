#define _CRT_SECURE_NO_WARNINGS

#include "sort_with_ref.h"
#include "compare_integers.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// versione 4  dell'esercizio, con struct e in c++, references e overloading

/*
in c++ l'overloading è ammesso
*/

// alias o riferimento
/*
nel mio main posso scrivere change_x(x) anziche change_x(&x)
molto utile perchè non mi devo ricordare ogni volta * e &
una reference è una variabile che contiene un indirizzo al valore di una variabile di tipo int
*/
void change_x(int& myvar) {
    myvar = 10;
}


struct vector {
    int* data_;
    size_t capacity_;
    size_t size_;

    //costruttore
    vector() {
        capacity_ = 10;
        size_ = 0;
        //il c++ è molto più rigoroso sui puntatori a void, serve un cast esplicito
        data_ = (int*)malloc(capacity_ * sizeof(int));
    }

    //deep copy constructor
    vector(const vector& other) {
        capacity_ = other.capacity_;
        size_ = other.size_;
        data_ = (int*)malloc(capacity_ * sizeof(int));
        for (size_t i = 0; i < size_; i++) {
            data_[i] = other.data_[i];
        }
    }

    //assignement operator 
    vector& operator=(const vector& rhs) {
        if (&rhs != this) {     //self assignement could be a problem
            free(data_);
            capacity_ = rhs.capacity_;
            size_ = rhs.size_;
            data_ = (int*)malloc(capacity_ * sizeof(int));
            for (size_t i = 0; i < size_; i++) {
                data_[i] = rhs.data_[i];
            }
        }
        return *this;
    }

    //distruttore
    ~vector() {
        free(data_);
    }
    //costruttore e distruttore non devono essere chiamati esplicitamente, avviene in automatico

    /*
    i metodi sono dentro alla struct, non c'è bisogno di specificare vector* this
    è sottointeso come primo parametro, se lo voglio const lo specifico fuori dalle parantesi
    */
    void push_back(int num) {
        // se necessito di spazio realloco memoria
        if (size_ == capacity_) {
            capacity_ *= 2;
            data_ = (int*)realloc(data_, capacity_ * sizeof(int));
        }
        //inserisco il dato
        data_[size_] = num;
        //incremento la dimensione
        size_++;
    }

    void sort() {
        qsort(data_, size_, sizeof(int), compare_integers);
    }

    /* overload di operator[]() e at(), in questo modo se chiamo la funzione su un const vector
        il risultato sarà modificabile, se invece la chiamo su un vector la funzione
        sarà modificabile    */
    const int& at(int i) const {
        assert(i >= 0 && i < size_);
        return data_[i];
    }
    int& at(int i) {
        assert(i >= 0 && i < size_);
        return data_[i];
    }
    const int& operator[](int i) const {
        assert(i >= 0 && i < size_);
        return data_[i];
    }
    int& operator[](int i) {
        assert(i >= 0 && i < size_);
        return data_[i];
    }

    //getter
    size_t size() const {
        return size_;
    }
};

//funzione di stampa
void print_vector(FILE* fout, const vector& v) {
    for (int i = 0; i < v.size(); i++) {
        printf("%d\n", v[i]);
        fprintf(fout, "%d\n", v[i]);
    }
}

vector read_vector(const char* filename)
{
    vector v;
    FILE* fin = fopen(filename, "r");
    if (fin != NULL) {
        int num;
        while (fscanf(fin, "%d", &num) == 1) {
            v.push_back(num);
        }
        fclose(fin);
    }
    else {
        printf("Error: Unable to open input file %s\n", filename);
    }
    return v;
}

//"main"
int sort_with_ref(char* filein, char* fileout) {

    // Read integers from the input file
    vector v = read_vector(filein);
    /* name return value optimization
    * in old school c++ (1998) non era consigliato ritornare oggetti in quanto sarebbe stato un spreco di risorse chiamando vari 
    * costruttori, oggi invece la funzione read_vector crea il vettore e lo ritorna immediatamente all'operatore =
    * in questo modo posso ritornare oggetti senza preoccuparmi dello spreco di risorse
    */

    FILE* fout = fopen(fileout, "w");
    if (fout == NULL) {
        fprintf(stderr, "Error: Unable to open output file %s\n", fileout);
        return 1;
    }

    // Sort the numbers
    v.sort();

    // Write sorted numbers to the output file
    print_vector(fout, v);
    fclose(fout);

    /*
    shallow copy, different synthax, same result
    il compilatore crea un costruttore che accetta lo stesso tipo di oggetto per farne una copia shallow
    in questo caso ho fatto overload del costruttore per fare una deep copy
    */
    vector x = v;       //deep
    vector y(v);        //deep
    //l'uguale di default fa una shallow copy
    vector z;
    z = v;              //shallow

    return 0;
}
