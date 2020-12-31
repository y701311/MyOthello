#ifndef _OTHELLO_H_
#define _OTHELLO_H_

class othello {
public:

	void draw();
	void start();	
	void nomalSelect();
	int32 cornerSelect();
	int32 rondomSelect();
	int32 maxSelect();

	int32 turn;
	bool end;
	int32 color;

private:

	void const drawGridLines();
	void const drawCells();
	void makeButtons();
	void turnOver(int32 x, int32 y);
	int32 judge(int32 x, int32 y);
	int32 canPutColor(int32 x, int32 y);
	int32 count(int32 x, int32 y);
	int32 postProcess();
	void last();

	static constexpr int32 CellSize = 60;
	static constexpr int32 black = 1;
	static constexpr int32 white = -1;

	Grid<int32> board = Grid<int32>(10, 10, 0);
	Grid<int32> boardBefore = Grid<int32>(10, 10, 0);

};

#endif // !_OTHELLO_H_