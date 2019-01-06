#include "Blitzbot.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <fstream>

Blitzbot::Blitzbot() {
	return;
}

bool findCorner(std::string filename) {
	return true;
}

void Blitzbot::initialize(int argc, const char* argv[]) {	
	root = new Graphnode();
	boolBoard = (char*) malloc(20);
	memset(boolBoard, 1, 16); 

	buildTree(WORD_FILENAME);
	root->terminator = false;
	for (int i = 0; i < 26; i++) {
		root->letters[i]->terminator = false;
	}
	parseArgs(argc, argv);	

	//printBoard();

}

void Blitzbot::printBoard() {
	for (int y = 0; y < 4; y++) {
		fprintf(stderr, "%c %c %c %c\n\n", getChar(0, y), getChar(1, y), getChar(2, y), getChar(3, y)); 
	}
}

void Blitzbot::findWordsAt(int x, int y, Graphnode* node, char* foundWord, int idx) {
	if (getChar(x, y) == 's' || foundWord[0] == 's') {
//		fprintf(stderr, "checked letter at %c\n", getChar(x, y));
	}
	if (node == NULL) {
		return;
	}
	
	if (node->terminator) {
		foundWord[idx] = '\0';
		std::string convertedString = foundWord;
		if (hashmap.find(foundWord) == hashmap.end()) {
			printf("%s\n", foundWord);
			hashmap[foundWord] = 1;
		}
	}

	char c = getChar(x, y);
	setBool(x, y, 0);
	if ( c == '\0' ) {
		return;
	} else {
		foundWord[idx] = c;
	}
	findWordsAt(x + 1, y, node->letters[c - 'a'], foundWord, idx + 1);
	findWordsAt(x, y + 1, node->letters[c - 'a'], foundWord, idx + 1);
	findWordsAt(x - 1, y, node->letters[c - 'a'], foundWord, idx + 1);
	findWordsAt(x, y - 1, node->letters[c - 'a'], foundWord, idx + 1);

	findWordsAt(x + 1, y + 1, node->letters[c - 'a'], foundWord, idx + 1);
	findWordsAt(x - 1, y + 1, node->letters[c - 'a'], foundWord, idx + 1);
	findWordsAt(x + 1, y - 1, node->letters[c - 'a'], foundWord, idx + 1);
	findWordsAt(x - 1, y - 1, node->letters[c - 'a'], foundWord, idx + 1);
	setBool(x, y, 1);
}

void Blitzbot::findAllWords() {
	char* foundWord = (char*)malloc(20);
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; j++) {
			memset(foundWord, 0, 17);
			strcpy(boolBoard, gameBoard);
			findWordsAt(i, j, root, foundWord, 0);
		}
	}
	free(foundWord);
	
}


void Blitzbot::setChar(int x, int y, char c) {
	if (x < 0 || x > 3 || y < 0 || y > 3) {
		return;
	}
	gameBoard[x + 4*y] = c;
}

void Blitzbot::setBool(int x, int y, char c) {
	if (x < 0 || x > 3 || y < 0 || y > 3) {
		return;
	}
	boolBoard[x + 4*y] = c;
}

char Blitzbot::getChar(int x, int y) {
	if (x < 0 || x > 3 || y < 0 || y > 3) {
		return '\0';
	}
	if( boolBoard[x + 4*y] != 0) {
		return gameBoard[x + 4*y];
	} else {
	   return '\0';
	}	   
}

char Blitzbot::getBool(int x, int y) {
	if (x < 0 || x > 3 || y < 0 || y > 3) {
		return 0;
	}
	return boolBoard[x + 4+y];
}

void Blitzbot::parseArgs(int argc, const char* argv[]) {
	if (argc != 2) {
		perror("should've been 2 arguments\n");
		exit(1);
	}
	if (strlen(argv[1]) != 16) {
		perror("string length isn't correct!\n");
		exit(1);
	}

	gameBoard = strdup(argv[1]);
}

void Blitzbot::addWord(std::string word) {
	Graphnode *current = root;
	char c;
	for (size_t i = 0; i < word.length() - 1; i++) {
		c = word[i]; 
		if (c == '\0' || c == '\n' || c == ' ') {
			break;
		}
		if ((current->letters)[c - 'a'] == NULL) {
			Graphnode *newnode = new Graphnode();
			(current->letters)[c - 'a'] = newnode;
		}
		current = (current->letters)[c - 'a'];
	}
	current->terminator = true;
}


void Blitzbot::buildTree(std::string filename) {	
	std::ifstream wordfile;
	wordfile.open(WORD_FILENAME);
	
	std::string line;

	while (getline(wordfile, line) ) {
		if (line.length() > 17) {
			continue;
		}
		addWord(line);
	}

	wordfile.close();
}


void Blitzbot::run() {
	//Find words that have the pattern	
	findAllWords();
}
