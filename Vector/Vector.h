#pragma once

#include "Structure.h"
#include "DSStructureTypes.h"
#include <stdexcept>

namespace Structures {

    class Vector : public Structure {
    public:
        Vector(size_t);
        Vector(const Vector &);
		Vector(Vector &&);
        ~Vector() override;

        Structure &operator=(const Structure &) override;
        Vector &operator=(const Vector &);
		Vector &operator=(Vector &&);

        Structure *clone() const override;
		size_t size() const override;

        bool operator==(const Vector &other) const;
        byte &operator[](const int index);
        byte operator[](const int index) const;

        byte &readBytes(const int index, const int count, byte &dest);
        byte *getBytePointer(const int index) const;

        static void copy(const Vector &src, const int srcStartIndex, Vector &dest, const int destStartIndex, const int length);

    private:
		void *memory;
		size_t size_;
    };

}
