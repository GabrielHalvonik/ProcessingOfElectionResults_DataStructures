#pragma once

#include "DSStructureTypes.h"
#include "Array/Array.h"

namespace Structures {

    class MemoryRoutines {
    public:
        const static byte MAX_BYTE = 255;

        static byte& byteSet(byte& B);
        static byte& byteReset(byte& B);
        static byte& byteXOR(byte& B);
        static byte& byteSHL(byte& B);
        static byte& byteSHR(byte& B);
        static bool byteNthBitGet(byte& B, int n);
        static byte& byteNthBitTo0(byte& B, int n);
        static byte& byteNthBitTo1(byte& B, int n);
        static byte& byteNthBitToggle(byte& B, int n);

//		template<typename R>
//		static int indexInArray(const Array<R>& array, const R& data) {
//			int result = 0;
//			for (int i = 0; i < array.size(); ++i) {
//				if (data == array[i]) {
//					return result;
//				} else {
//					++result;
//				}
//			}
//			return -1;
//		}
    private:
        MemoryRoutines();
    };
}

