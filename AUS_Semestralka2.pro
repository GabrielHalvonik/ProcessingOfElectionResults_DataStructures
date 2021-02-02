QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    App/DataLoader.cpp \
    App/PolitickySubjekt.cpp \
    App/UzemnaJednotka.cpp \
    App/Volic.cpp \
    App/DataLoading.cpp \
    App/Vseobecne.cpp \
    Data/DataAny.cpp \
    GUI/TableWidget.cpp \
    GUI/ToolBar.cpp \
    GUI/Ulohy/TabulkaUloh.cpp \
    GUI/Ulohy/TabulkaUlohDruha.cpp \
    GUI/Ulohy/TabulkaUlohPrva.cpp \
    RandomGenerator.cpp \
    UIRoutines.cpp \
    main.cpp \
    DSRoutines.cpp \
    DSStructureFactory.cpp \
    MemoryRoutines.cpp \
    Structure.cpp \
    Vector/Vector.cpp \
    Table/Sorting/Sort.cpp \
    GUI/MainWindow.cpp \

HEADERS += \
    App/Comparator.h \
    App/Kriterium.h \
    App/KriteriumFactory.h \
    App/PolitickySubjekt.h \
    App/TypUzemnejJednotky.h \
    App/UzemnaJednotka.h \
    App/Volic.h \
    App/DataLoader.h \
    App/DataLoading.h \
    App/Vseobecne.h \
    Data/DataAny.h \
    Data/Pair.h \
    GUI/Instances.h \
    GUI/TableWidget.h \
    GUI/ToolBar.h \
    GUI/Ulohy/TabulkaUloh.h \
    GUI/Ulohy/TabulkaUlohDruha.h \
    GUI/Ulohy/TabulkaUlohPrva.h \
    List/ArrayListRaw.h \
    List/DoublyCircularLinkedList.h \
    List/DoublyLinkedList.h \
    Array/Array.h \
    List/ArrayList.h \
    DSRoutines.h \
    DSStructureFactory.h \
    DSStructureTypes.h \
    HeapMonitor.h \
    Matrix/MatrixHeap.h \
    Matrix/MatrixHeapContinuous.h \
    Matrix/MatrixStack.h \
    MultiArray.h \
    PriorityQueue/PriorityQueueLimitedSortedArrayList.h \
    PriorityQueue/PriorityQueueTwoLists.h \
    Queue/ExplicitQueue.h \
    RandomGenerator.h \
    Set/BaseSet.h \
    Set/BaseSetBinarySearchTree.h \
    Set/BitSetBinarySearchTree.h \
    Stack/ExplicitStack.h \
    PriorityQueue/Heap.h \
    Queue/ImplicitQueue.h \
    Stack/ImplicitStack.h \
    List/LinkedList.h \
    List/List.h \
    MemoryRoutines.h \
    PriorityQueue/PriorityQueue.h \
    PriorityQueue/PriorityQueueLinkedList.h \
    PriorityQueue/PriorityQueueList.h \
    PriorityQueue/PriorityQueueSortedArrayList.h \
    PriorityQueue/PriorityQueueUnsortedArrayList.h \
    Queue/Queue.h \
    Stack/Stack.h \
    Structure.h \
    StructureIterator.h \
    UIRoutines.h \
    Vector/Vector.h \
    Matrix/Matrix.h \
    Set/BitSet.h \
    Data/DataTypes.h \
    Tree/Tree.h \
    Tree/MultiWayTree.h \
    Tree/KWayTree.h \
    Tree/BinaryTree.h \
    Table/BinarySearchTree.h \
    Table/HashTable.h \
    Table/LinkedTable.h \
    Table/SequenceTable.h \
    Table/Sorting/Shuffle.h \
    Table/Sorting/BubbleSort.h \
    Table/Sorting/HeapSort.h \
    Table/Sorting/InsertSort.h \
    Table/Sorting/MergeSort.h \
    Table/Sorting/QuickSort.h \
    Table/Sorting/RadixSort.h \
    Table/Sorting/SelectSort.h \
    Table/Sorting/ShellSort.h \
    Table/Sorting/Sort.h \
    Table/Table.h \
    Table/Treap.h \
    Table/SortedSequenceTable.h \
    Table/UnsortedSequenceTable.h \
    App/Filter.h \
    GUI/MainWindow.h \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += "/usr/local/include/vulkan"

RESOURCES +=
