#pragma once

#include "HeapMonitor.h"

namespace Structures {

    template <typename T>
    class DataItem {
    public:
        T& accessData();
    protected:
        DataItem(const T& data);
        DataItem(const DataItem<T>& other);
        virtual ~DataItem();
    private:
        T data_;
    };

    class Structure {
    public:
        virtual ~Structure();
        virtual Structure& operator=(const Structure& other) = 0;

        virtual Structure* clone() const = 0;
        virtual bool isEmpty() const;
		virtual size_t size() const = 0;
    protected:
        Structure();
    };

    template<typename T>
	inline T& DataItem<T>::accessData() {
        return data_;
    }

    template<typename T>
    inline DataItem<T>::DataItem(const T& data) :
        data_(data) {
    }

    template<typename T>
    inline DataItem<T>::DataItem(const DataItem<T>& other) :
        DataItem(other.data_) {
    }

    template<typename T>
    inline DataItem<T>::~DataItem() {
    }
}

