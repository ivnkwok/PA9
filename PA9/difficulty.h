

class Difficulty {
public:
	int getSize();
	int getBoardSize();
	int getWindowSize();
	int setSize(int size);
	int setBoardSize(int size);
	int setWindowSize(int size);
protected:
	int size;
	int boardSize;
	int windowSize;
	void init();
};

class Easy : public Difficulty {
public:
	Easy();
};

class Medium : public Difficulty {
public:
	Medium();
};

class Hard : public Difficulty {
public:
	Hard();
};