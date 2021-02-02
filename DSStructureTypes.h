#pragma once

namespace Structures {

    // Typy
	using byte = unsigned char;

    // ADT sktruktur
	enum StructureADT {
        adtVECTOR,
        adtARRAY,
		adtBITSET,
        adtLIST,
		adtMATRIX,
        adtQUEUE,
        adtSTACK,
        adtPRIORITY_QUEUE,
        adtTREE,
        adtGRAPH,
        adtTABLE,
        adtCount,
    };

    // ADS struktur
	enum StructureADS {
        adsVECTOR,
        adsARRAY,

		adsBITSET,
		adsBITSET_LARGE,
		adsBITSET_BST,
		adsBITSET_LARGE_BST,

        adsLIST_ARRAY,
		adsLIST_ARRAY_RAW,
        adsLIST_LINKED,
        adsLIST_DOUBLE_LINKED,
        adsLIST_CYCLICAL,

		adsMATRIX_STACK,
		adsMATRIX_HEAP,
		adsMATRIX_HEAP_CONTINUOUS,

        adsQUEUE_ARRAY,
        adsQUEUE_LIST,

        adsSTACK_ARRAY,
        adsSTACK_LIST,

        adsPRIORITY_QUEUE_ARRAY_LIST_UNSORTED,
        adsPRIORITY_QUEUE_ARRAY_LIST_SORTED,
        adsPRIORITY_QUEUE_LINKED_LIST,
        adsPRIORITY_QUEUE_TWO_LISTS,
		adsPRIORITY_QUEUE_TWO_LISTS_MEDIUM,
		adsPRIORITY_QUEUE_TWO_LISTS_LARGE,
        adsPRIORITY_QUEUE_DOUBLE_LAYER,
        adsPRIORITY_QUEUE_HEAP,

        adsTREE_MULTI_WAY,
        adsTREE_K_WAY,
        adsTREE_BINARY,

        adsGRAPH_MATRIX,
        adsGRAPH_FORWARD_STAR,
        adsGRAPH_BI_STAR,

        adsTABLE_SEQUENCE_SORTED,
        adsTABLE_SEQUENCE_UNSORTED,
        adsTABLE_LINKED,
        adsTABLE_DIAMOND,
        adsTABLE_HASH,
        adsTABLE_BST,
        adsTABLE_TREAP,

        adsCount
    };

	enum class ListOperationType {
		VLOZ_PRVY,
		VLOZ_POSLEDNY,
		VLOZ_NA_INDEX,
		ZRUS_PRVY,
		ZRUS_POSLEDNY,
		ZRUS_NA_INDEXE,
		SPRISTUPNI,
		NASTAV,
		INDEX_PRVKU
	};

	enum class PriorityQueueOperationType {
		VLOZ,
		VYBER,
		UKAZ
	};

	enum class MatrixOperationType {
		SPRISTUPNI,
		NASTAV,
		VYNASOB
	};

	enum class BitSetOperationType {
		VLOZ,
		VYBER,
		PATRI,
		JE_PODMNOZINOU,
		ZJEDNOTENIE,
		PRIENIK,
		ROZDIEL
	};

	enum class AllStructureOperationType {
		VLOZ_PRVY,
		VLOZ_POSLEDNY,
		VLOZ_NA_INDEX,
		ZRUS_PRVY,
		ZRUS_POSLEDNY,
		ZRUS_NA_INDEXE,
		SPRISTUPNI,
		NASTAV,
		INDEX_PRVKU,
		VLOZ,
		VYBER,
		UKAZ,
		PATRI,
		JE_PODMNOZINOU,
		ZJEDNOTENIE,
		PRIENIK,
		ROZDIEL,
		VYNASOB,
		UNDEFINED
	};
}
