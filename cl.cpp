#include <iostream>
#include <cmath>
#include <typeinfo>

template <typename T>
class MySet {
private:
    T *arr;
    int size;
    int N;


    /**
     * Returns index of array, in which desired element is located
    */
    int get_arr_index(int val) {
        return val / (8*sizeof(T));
    }

    /**
     * Gets number of bit in bit's field, in which desired element is located
    */
    int get_number_bit(int val) {
            return val % (8*sizeof(T));
    }

    /**
     * Set current bit by array index, bit number and value
    */
    void set_bit(int ind, int number, bool val) {
        arr[ind] = arr[ind] & (~(1 << number)); // all 1, 0 at number
                                                // now number is 0
        arr[ind] = arr[ind] | val << number; // now number is val
    }

    /**
     * Get current bit by array index, bit number
    */
    int get_bit(int ind, int number) {
        return (arr[ind] & 1 << number) >> number;
    }

    MySet _not() const {
        MySet<T> ret(N);
        for(int i = 0; i < size; i++)
            ret.edit_arr_elem(i, ~arr[i]);
        return ret;
    }


public:

    MySet() {
        this->size = 0;
        this->N = 0;
    }

    MySet(int N) {
        this->size = N / (sizeof(T) * 8) + 1;
        this->N = N;
        arr = new T[size];
    }

    MySet(const MySet& other) {
        if (typeid(T).name() != typeid(other.arr[0]).name()) {
            throw std::runtime_error("Used not correct type of set");
        }
        this->size = other.size;
        this->N = other.N;
        arr = new T[size];
        for(int i = 0; i < size; i++) {
            arr[i] = other.arr[i];
        }
    }

    /**
     * Inserts bit's field
    */
    void edit_arr_elem(int ind, T val) {
        if (ind >= size) {
            throw std::runtime_error("Index more than size of array");
        }
        arr[ind] = val;
    }

    MySet& operator= (const MySet& other) {
        if (typeid(T).name() != typeid(other.arr[0]).name()) {
            throw std::runtime_error("Used not correct type of set");
        }
        if (size > 0) {
            delete[] arr;
        }
        this->size = other.size;
        this->N = other.N;
        arr = new T[size];
        for(int i = 0; i < size; i++) {
            arr[i] = other.arr[i];
        }
        return *this;
    }

    ~MySet() {
        if (size > 0) {
            delete[] arr;
        }
    }

    bool find(int val) {
        if(val >= N) {
            throw std::runtime_error("Value is more than universe");
        }
        int ind = get_arr_index(val);
        int number = get_number_bit(val);
        return get_bit(ind, number);
    }

    void add(int val) {
        if(val >= N) {
            throw std::runtime_error("Value is more than universe");
        }
        int ind = get_arr_index(val);
        int number = get_number_bit(val);
        set_bit(ind, number, 1);
    }

    void remove(int val) {
        if(val >= N) {
            throw std::runtime_error("Value is more than universe");
        }
        int ind = get_arr_index(val);
        int number = get_number_bit(val);
        set_bit(ind, number, 0);
    }

    MySet union_with(const MySet &other) const {
        if (typeid(T).name() != typeid(other.arr[0]).name()) {
            throw std::runtime_error("Used not correct type of set");
        }
        int N = (N > other.N) ? N : other.N;
        int min_size = (size < other.size) ? size : other.size;
        int max_size = (size > other.size) ? size : other.size;
        MySet<T> ret(N);
        int i = 0;
        for(i = 0; i < min_size; i++) {
            ret.edit_arr_elem(i, arr[i] | other.arr[i]);
        }
        if (size > other.size) {
            for(; i < max_size; i++) {
                ret.edit_arr_elem(i, arr[i]);
            }
        } else {
            for(; i < max_size; i++) {
                ret.edit_arr_elem(i, other.arr[i]);
            }
        }
        return ret;
    } 

    MySet intersection_with(const MySet &other) const {
        if (typeid(T).name() != typeid(other.arr[0]).name()) {
            throw std::runtime_error("Used not correct type of set");
        }
        int N = (N > other.N) ? N : other.N;
        int min_size = (size < other.size) ? size : other.size;
        int max_size = (size > other.size) ? size : other.size;
        MySet<T> ret(N);
        int i = 0;
        for(i = 0; i < min_size; i++) {
            ret.edit_arr_elem(i, arr[i] & other.arr[i]);
        }
        if (size > other.size) {
            for(; i < max_size; i++) {
                ret.edit_arr_elem(i, arr[i]);
            }
        } else {
            for(; i < max_size; i++) {
                ret.edit_arr_elem(i, other.arr[i]);
            }
        }
        return ret;
    }

    friend MySet union_of(const MySet &a, const MySet &b) {
        return a.union_with(b);
    }

    friend MySet intersection_of(const MySet &a, const MySet &b) {
        return a.intersection_with(b);
    }

    friend MySet negative(const MySet &a) {
        return a._not();
    }

    MySet operator| (const MySet &other) {
        return union_of(*this, other);
    }

    MySet operator& (const MySet &other) {
        return intersection_of(*this, other);
    }

    MySet operator- () {
        return _not();
    }
};
