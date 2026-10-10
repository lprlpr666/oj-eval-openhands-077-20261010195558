#pragma once

namespace sjtu {
class CrossArray {
private:
    int **data_; // pointers to each line array
    int *len_;   // length of each line
    int capacity_; // total allocated lines
    int count_; // number of inserted lines
public:
    explicit CrossArray(int lines) {
        capacity_ = lines;
        data_ = new int*[capacity_];
        len_ = new int[capacity_];
        for (int i = 0; i < capacity_; ++i) {
            data_[i] = nullptr;
            len_[i] = 0;
        }
        count_ = 0;
    }

    // copy constructor – deep copy
    CrossArray(const CrossArray &o) {
        capacity_ = o.capacity_;
        count_ = o.count_;
        data_ = new int*[capacity_];
        len_ = new int[capacity_];
        for (int i = 0; i < capacity_; ++i) {
            if (o.data_[i]) {
                len_[i] = o.len_[i];
                data_[i] = new int[len_[i]];
                for (int j = 0; j < len_[i]; ++j) {
                    data_[i][j] = o.data_[i][j];
                }
            } else {
                data_[i] = nullptr;
                len_[i] = 0;
            }
        }
    }

    // return reference to the larger CrossArray (by total element count)
    CrossArray & WhichGreater(CrossArray &o) {
        long long total_this = 0, total_o = 0;
        for (int i = 0; i < capacity_; ++i) {
            if (data_[i]) total_this += len_[i];
        }
        for (int i = 0; i < o.capacity_; ++i) {
            if (o.data_[i]) total_o += o.len_[i];
        }
        if (total_o > total_this) return o;
        return *this;
    }

    // true if both objects share the same underlying storage pointer
    bool IsSame(const CrossArray &o) {
        return data_ == o.data_;
    }

    // Insert a new array; index is count_ (0‑based). Return false if capacity exceeded.
    bool InsertArrays(const int *Input, int size) {
        if (count_ >= capacity_) return false;
        data_[count_] = new int[size];
        len_[count_] = size;
        for (int i = 0; i < size; ++i) data_[count_][i] = Input[i];
        ++count_;
        return true;
    }

    // Append to an existing line (Line is guaranteed to be valid and already inserted)
    void AppendArrays(const int *Input, int Line, int size) {
        int old_len = len_[Line];
        int new_len = old_len + size;
        int *new_arr = new int[new_len];
        for (int i = 0; i < old_len; ++i) new_arr[i] = data_[Line][i];
        for (int i = 0; i < size; ++i) new_arr[old_len + i] = Input[i];
        delete[] data_[Line];
        data_[Line] = new_arr;
        len_[Line] = new_len;
    }

    // Double the maximum number of lines, keeping existing data unchanged.
    void DoubleCrossLength() {
        int new_cap = capacity_ * 2;
        int **new_data = new int*[new_cap];
        int *new_len = new int[new_cap];
        for (int i = 0; i < capacity_; ++i) {
            new_data[i] = data_[i];
            new_len[i] = len_[i];
        }
        for (int i = capacity_; i < new_cap; ++i) {
            new_data[i] = nullptr;
            new_len[i] = 0;
        }
        delete[] data_;
        delete[] len_;
        data_ = new_data;
        len_ = new_len;
        capacity_ = new_cap;
    }

    // Return pointer to the beginning of line i (or nullptr).
    // Return pointer to the beginning of line i (or nullptr).
    const int * AtArray(int i) {
        return data_[i];
    }
    // Const overload for const objects
    const int * AtArray(int i) const {
        return data_[i];
    }

    // Return reference to element (i, j). Caller guarantees validity.
    int & At(int i, int j) {
        return data_[i][j];
    }

    ~CrossArray() {
        for (int i = 0; i < capacity_; ++i) {
            delete[] data_[i];
        }
        delete[] data_;
        delete[] len_;
    }
};
} // namespace sjtu
