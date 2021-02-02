## Overview

ProcessingOfElectionResults is semester project for the school subject [Data Structures and Algorithms](https://vzdelavanie.uniza.sk/vzdelavanie/planinfo.php?kod=274661&lng=sk "Data Structures and Algorithms").
The aim of the work was to process a large amount of data, efficiently read, filter and sort.
The application uses only its own implemented data structures, sorting and filtering.
[Qt Framework](http://www.qt.io "Qt Framework") (v5.15) was used for better visualization and usability.
## User manual
	The main application window is the TableWidget.
	If we click on the table header, a dialog box for selecting filtering will appear.
	Double-click to sort the table according to the selected column.
	After pressing the SPACE key, the table is filtered according to the currently selected filter(s). If no filter is selected, the original unfiltered / unsorted table is displayed.
...obratzok...

#### Data reading
	Data are read from four files (uzemne_jednotky.csv, vysledky_hlasovania_okrsky.csv, politicke_subjekty.csv, hlas_pre_subjekty.csv).
	For this purpose, I generalized a class for retrieving data from the CSV format with different numbers of columns of different types using "variadic templates".
...dataloader...


* Loading data for territorial units: **O(n*log(n))** ... n (number of territorial units)
* Loading vote data for territorial units: **O(n*log(n))** ... n (number of territorial units)
* Loading of political entities: **O(n)**  ... n (number of political entities)
* Loading votes for political entities: **O(n*m)**  ... n (number of PS) ... m (number of UJ).
* Loading data for higher territorial units (District, Region, State): **O(n)**  ... n (number of lower territorial units).

#### Criterion:
* select the properties of individual objects.

#### Filter:
* cooperates with the criterion, takes over the set of elements, and uses the criterion to select those that suit it and returns them.

#### Sorting

For sorting, app uses the QuickSort algorithm (**O(n*log(n))** - **O (n^2)**).
Although the complexity of this algorithm can go as far as n^2, this behavior is very rare and in most cases very fast.
