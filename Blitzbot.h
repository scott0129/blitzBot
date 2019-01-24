#include <stdio.h>
#include <iostream>
#include <string>
#include <unordered_map>

static const std::string WORD_FILENAME = "words_alpha.txt";

class Blitzbot {
	
	struct Coordinate {
		Coordinate(int one, int two, char setChar) {
			first = one;
			second = two;
			character = setChar;
		};
		int first;
		int second;
		char character;
	};

	struct Graphnode {
		Graphnode() {
			terminator = false;
			for (int i = 0; i < 26; i++) {
				letters[i] = NULL;
			}
		}
		
		Graphnode* letters[26];
		bool terminator;
	};

	
	public:
		Blitzbot();
		void initialize(int argc, const char* argv[]);
		void parseArgs(int argc, const char* argv[]);

		void findWordsAt(int x, int y, Graphnode* node, Coordinate* solutionPath, int idx);
		void findAllWords();

		//gets char at location on the board, (0, 0) is top left
		char getChar(int x, int y);
		void setChar(int x, int y, char c);
		void run();
	private:
		std::pair<size_t, size_t> findCorner(std::string filename);
		char* readLetters(size_t x, size_t y);
		void buildTree(std::string filename);
		void addWord(std::string word);
		void printBoard();

		char getBool(int x, int y);
		void setBool(int x, int y, char c);
		void printPath(Coordinate* solutionPath, int pathLength);

		Graphnode* root;
		std::unordered_map<std::string, int> hashmap;
		char* gameBoard;
		char* boolBoard;
			
	
};

