#ifndef BOGGLECONSTANTS_H
#define BOGGLECONSTANTS_H

#include <QColor>

const int kBoggleCubeWidth=40;
const int kBoggleCubeHeight=40;
const int kWindowXMin = 240;
const int kWindowYMin = 300;
const int kTextEntryYMin = 20;
const QColor kDefaultSquareColor = QColor("burlywood");
const QColor kHighlightSquareColor = QColor("chocolate");

enum BoardSize { SMALL=4, LARGE=5 };
const BoardSize kDefaultBoardSize = SMALL;

const int kSmallNumCubes = 16;
const QString kStandardCubes[kSmallNumCubes] = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

const int kLargeNumCubes = 25;
const QString kBigBoggleCubes[kLargeNumCubes] = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

enum Player { NONE, HUMAN, COMPUTER };

#endif // BOGGLECONSTANTS_H
