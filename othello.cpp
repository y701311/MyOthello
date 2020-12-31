#include <Siv3D.hpp>
#include "othello.h"


void const othello::drawGridLines() {

	for (auto i : { 0, 1, 2, 3, 4, 5, 6, 7, 8 }) {
		Line(i * 60, 0, i * 60, 480).draw(2, ColorF(0.2));
		Line(0, i * 60, 480, i * 60).draw(2, ColorF(0.2));
	}

}

void const othello::drawCells() {

	for (int32 i = 1; i < 9; i++) {
		for (int32 j = 1; j < 9; j++) {

			const Rect cell((j - 1) * CellSize, (i - 1) * CellSize, CellSize, CellSize);

			if (board[i][j] == black) {
				Circle(cell.center(), CellSize * 0.4).draw(Palette::Black);
				continue;
			}
			else if (board[i][j] == white) {
				Circle(cell.center(), CellSize * 0.4).draw(Palette::White);
				continue;
			}

			if (cell.mouseOver()) {

				Cursor::RequestStyle(CursorStyle::Hand);
				cell.stretched(-2).draw(ColorF(1.0, 0.6));

			}

		}
	}

}

void othello::makeButtons() {

	if (SimpleGUI::ButtonAt(U"Pass", Vec2(580, 0))) {
		turn++;
	}

}

void othello::draw() {

	ClearPrint();

	if (!end) {
		if (turn % 2) {
			Print << U"黒のターンです。";
		}
		else {
			Print << U"白のターンです。";
		}
	}

	if (end) {
		last();
	}

	drawGridLines();
	drawCells();
	if (!end) {
		makeButtons();
	}

}

void othello::start() {

	turn = 1;
	end = false;

	for (int32 i = 0; i < 10; i++) {
		for (int32 j = 0; j < 10; j++) {
			board[i][j] = 0;
			boardBefore[i][j] = 0;
		}
	}

	board[4][4] = white;
	board[5][5] = white;
	board[4][5] = black;
	board[5][4] = black;

	boardBefore[4][4] = white;
	boardBefore[5][5] = white;
	boardBefore[4][5] = black;
	boardBefore[5][4] = black;

}

void othello::turnOver(int32 x, int32 y) {
	int32 i;

	for (i = x - 1; board[i][y] * -1 == board[x][y]; i--) {//	縦
		if (board[i - 1][y] == board[x][y]) {
			for (i = x - 1; board[i][y] * -1 == board[x][y]; i--) {
				board[i][y] *= -1;
			}
			break;
		}
	}
	for (i = x + 1; board[i][y] * -1 == board[x][y]; i++) {
		if (board[i + 1][y] == board[x][y]) {
			for (i = x + 1; board[i][y] * -1 == board[x][y]; i++) {
				board[i][y] *= -1;
			}
			break;
		}
	}
	for (i = y - 1; board[x][i] * -1 == board[x][y]; i--) {//	横
		if (board[x][i - 1] == board[x][y]) {
			for (i = y - 1; board[x][i] * -1 == board[x][y]; i--) {
				board[x][i] *= -1;
			}
			break;
		}
	}
	for (i = y + 1; board[x][i] * -1 == board[x][y]; i++) {
		if (board[x][i + 1] == board[x][y]) {
			for (i = y + 1; board[x][i] * -1 == board[x][y]; i++) {
				board[x][i] *= -1;
			}
			break;
		}
	}
	for (i = 1; board[x - i][y - i] * -1 == board[x][y]; i++) {//	左斜め
		if (board[x - i - 1][y - i - 1] == board[x][y]) {
			for (i = 1; board[x - i][y - i] * -1 == board[x][y]; i++) {
				board[x - i][y - i] *= -1;
			}
			break;
		}
	}
	for (i = 1; board[x + i][y + i] * -1 == board[x][y]; i++) {
		if (board[x + i + 1][y + i + 1] == board[x][y]) {
			for (i = 1; board[x + i][y + i] * -1 == board[x][y]; i++) {
				board[x + i][y + i] *= -1;
			}
			break;
		}
	}
	for (i = 1; board[x + i][y - i] * -1 == board[x][y]; i++) {//	右斜め
		if (board[x + i + 1][y - i - 1] == board[x][y]) {
			for (i = 1; board[x + i][y - i] * -1 == board[x][y]; i++) {
				board[x + i][y - i] *= -1;
			}
			break;
		}
	}
	for (i = 1; board[x - i][y + i] * -1 == board[x][y]; i++) {
		if (board[x - i - 1][y + i + 1] == board[x][y]) {
			for (i = 1; board[x - i][y + i] * -1 == board[x][y]; i++) {
				board[x - i][y + i] *= -1;
			}
			break;
		}
	}

}

int32 othello::judge(int32 x, int32 y) {
	int32 i, can = 0;

	for (i = x - 1; board[i][y] * -1 == board[x][y]; i--) {//	縦
		if (board[i - 1][y] == board[x][y]) {
			can = 1;
			break;
		}
	}
	for (i = x + 1; board[i][y] * -1 == board[x][y]; i++) {
		if (board[i + 1][y] == board[x][y]) {
			can = 1;
			break;
		}
	}
	for (i = y - 1; board[x][i] * -1 == board[x][y]; i--) {//	横
		if (board[x][i - 1] == board[x][y]) {
			can = 1;
			break;
		}
	}
	for (i = y + 1; board[x][i] * -1 == board[x][y]; i++) {
		if (board[x][i + 1] == board[x][y]) {
			can = 1;
			break;
		}
	}
	for (i = 1; board[x - i][y - i] * -1 == board[x][y]; i++) {//	左斜め
		if (board[x - i - 1][y - i - 1] == board[x][y]) {
			can = 1;
			break;
		}
	}
	for (i = 1; board[x + i][y + i] * -1 == board[x][y]; i++) {
		if (board[x + i + 1][y + i + 1] == board[x][y]) {
			can = 1;
			break;
		}
	}
	for (i = 1; board[x + i][y - i] * -1 == board[x][y]; i++) {//	右斜め
		if (board[x + i + 1][y - i - 1] == board[x][y]) {
			can = 1;
			break;
		}
	}
	for (i = 1; board[x - i][y + i] * -1 == board[x][y]; i++) {
		if (board[x - i - 1][y + i + 1] == board[x][y]) {
			can = 1;
			break;
		}
	}

	return can;
}

int32 othello::canPutColor(int32 x, int32 y) {

	if (board[x][y] == 0) {
		board[x][y] = color;
		if (judge(x, y)) {
			board[x][y] = 0;
			return 1;
		}
		board[x][y] = 0;
	}

	return 0;
}

void othello::nomalSelect() {

	for (int32 i = 1; i < 9; i++) {
		for (int32 j = 1; j < 9; j++) {

			const Rect cell((j - 1) * CellSize, (i - 1) * CellSize, CellSize, CellSize);

			if ((board[i][j] == 0) && cell.leftClicked()) {

				if (canPutColor(i, j)) {
					board[i][j] = color;
					turnOver(i, j);
					if (postProcess()) {
						end = true;
					}
				}

			}

		}
	}

}

int32 othello::cornerSelect() {
	bool corner = false;

	if (canPutColor(1, 1)) {
		board[1][1] = color;
		turnOver(1, 1);
		corner = true;
	}
	if (canPutColor(1, 8)) {
		board[1][8] = color;
		turnOver(1, 8);
		corner = true;

	}
	if (canPutColor(8, 1)) {
		board[8][1] = color;
		turnOver(8, 1);
		corner = true;
	}
	if (canPutColor(8, 8)) {
		board[8][8] = color;
		turnOver(8, 8);
		corner = true;
	}


	if (corner) {
		if (postProcess()) {
			end = true;
		}
		return 1;
	}

	return 0;
}

int32 othello::rondomSelect() {
	int32 i, j;
	int32 x, y;
	int32 can = 0;
	int32 cornerCancel = 0;

	for (i = 1; i < 9; i++) {
		for (j = 1; j < 9; j++) {

			if (canPutColor(i, j)) {
				can++;
			}

		}
	}
	if (can == 0) {
		turn++;
		return 0;
	}

	srand((unsigned)time(NULL));
	while (1) {
		x = rand() % 8 + 1;
		y = rand() % 8 + 1;

		if (canPutColor(x, y)) {

			board[x][y] = color;
			turnOver(x, y);

			if (cornerCancel > 15) {
				break;
			}
			color *= -1;
			if (canPutColor(1, 1) || canPutColor(8, 1) || canPutColor(1, 8) || canPutColor(8, 8)) {
				color *= -1;
				cornerCancel++;
				for (i = 1; i < 9; i++) {
					for (j = 1; j < 9; j++) {
						board[i][j] = boardBefore[i][j];
					}
				}
			}
			else {
				break;
			}

		}

	}

	if (postProcess()) {
		end = true;
	}

	return 0;
}

int32 othello::count(int32 x, int32 y) {
	int32 i, countKoma = 0;

	for (i = x - 1; board[i][y] * -1 == board[x][y]; i--) {//	縦
		if (board[i - 1][y] == board[x][y]) {
			for (i = x - 1; board[i][y] * -1 == board[x][y]; i--) {
				countKoma++;
			}
			break;
		}
	}
	for (i = x + 1; board[i][y] * -1 == board[x][y]; i++) {
		if (board[i + 1][y] == board[x][y]) {
			for (i = x + 1; board[i][y] * -1 == board[x][y]; i++) {
				countKoma++;
			}
			break;
		}
	}
	for (i = y - 1; board[x][i] * -1 == board[x][y]; i--) {//	横
		if (board[x][i - 1] == board[x][y]) {
			for (i = y - 1; board[x][i] * -1 == board[x][y]; i--) {
				countKoma++;
			}
			break;
		}
	}
	for (i = y + 1; board[x][i] * -1 == board[x][y]; i++) {
		if (board[x][i + 1] == board[x][y]) {
			for (i = y + 1; board[x][i] * -1 == board[x][y]; i++) {
				countKoma++;
			}
			break;
		}
	}
	for (i = 1; board[x - i][y - i] * -1 == board[x][y]; i++) {//	左斜め
		if (board[x - i - 1][y - i - 1] == board[x][y]) {
			for (i = 1; board[x - i][y - i] * -1 == board[x][y]; i++) {
				countKoma++;
			}
			break;
		}
	}
	for (i = 1; board[x + i][y + i] * -1 == board[x][y]; i++) {
		if (board[x + i + 1][y + i + 1] == board[x][y]) {
			for (i = 1; board[x + i][y + i] * -1 == board[x][y]; i++) {
				countKoma++;
			}
			break;
		}
	}
	for (i = 1; board[x + i][y - i] * -1 == board[x][y]; i++) {//	右斜め
		if (board[x + i + 1][y - i - 1] == board[x][y]) {
			for (i = 1; board[x + i][y - i] * -1 == board[x][y]; i++) {
				countKoma++;
			}
			break;
		}
	}
	for (i = 1; board[x - i][y + i] * -1 == board[x][y]; i++) {
		if (board[x - i - 1][y + i + 1] == board[x][y]) {
			for (i = 1; board[x - i][y + i] * -1 == board[x][y]; i++) {
				countKoma++;
			}
			break;
		}
	}

	return countKoma;
}

int32 othello::maxSelect() {
	int32 i, j;
	int32 x[60] = { 0 }, y[60] = { 0 };
	int32 can = 0;
	int32 countColor, max = 1, maxPlace = 0;
	int32 cornerCancel = 0;

	for (i = 1; i < 9; i++) {
		for (j = 1; j < 9; j++) {

			if (canPutColor(i, j)) {
				can++;
			}

		}
	}
	if (can == 0) {
		turn++;
		return 0;
	}

	for (i = 1; i < 9; i++) {
		for (j = 1; j < 9; j++) {

			if (board[i][j] == 0) {

				board[i][j] = color;
				countColor = count(i, j);
				board[i][j] = 0;

				if (max < countColor) {
					max = countColor;
					for (int32 c = 0; c <= maxPlace; c++) {
						x[c] = 0;
						y[c] = 0;
					}
					maxPlace = 0;
				}
				if (max == countColor) {
					x[maxPlace] = i;
					y[maxPlace] = j;
					maxPlace++;
				}

			}

		}
	}

	srand((unsigned)time(NULL));
	while (1) {
		int32 k = rand() % maxPlace;
		board[x[k]][y[k]] = color;
		turnOver(x[k], y[k]);

		if (cornerCancel > 15) {
			break;
		}
		color *= -1;
		if (canPutColor(1, 1) || canPutColor(8, 1) || canPutColor(1, 8) || canPutColor(8, 8)) {
			color *= -1;
			cornerCancel++;
			for (i = 1; i < 9; i++) {
				for (j = 1; j < 9; j++) {
					board[i][j] = boardBefore[i][j];
				}
			}
		}
		else {
			break;
		}
	}
	
	if (postProcess()) {
		end = true;
	}

	return 0;
}

int othello::postProcess() {
	int32 can_put = 0;

	for (int32 i = 1; i < 9; i++) {
		for (int32 j = 1; j < 9; j++) {
			boardBefore[i][j] = board[i][j];
		}
	}

	for (int32 i = 1; i < 9; i++) {
		for (int32 j = 1; j < 9; j++) {

				color = black;
				if (canPutColor(i, j)) {
					can_put++;
				}
				color = white;
				if (canPutColor(i, j)) {
					can_put++;
				}
				
		}
	}

	turn++;

	if (can_put > 0) {
		return 0;
	}
	else {
		return 1;
	}

}

void othello::last() {

	int32 black_count = 0, white_count = 0;
	for (int32 i = 1; i < 9; i++) {
		for (int32 j = 1; j < 9; j++) {
			if (board[i][j] == black) {
				black_count++;
			}
			if (board[i][j] == white) {
				white_count++;
			}
		}
	}

	if (black_count > white_count) {
		Print << U"黒の勝ち！";
	}
	else if (white_count > black_count) {
		Print << U"白の勝ち！";
	}
	else {
		Print << U"引き分け！";
	}
	Print << U"";
	Print << U"黒 … " << black_count << U"　" << U"白 … " << white_count;

}