#include <iostream>
#include <fstream>
using namespace std;
int col, row;
int objectCol;
int area[45][20] = { 0 };//值=0 沒方格 值=1 有方格 值=2 有方格 且此方格會移動
string str;
int index;

bool Is_num_in_Array(int arr[], int num, int size) {//用來確認數字是否在陣列
	for (int i = 1; i <= size; i++)
		if (arr[i] == num)
			return true;
	return false;
}

void output_tetris() {//Debug用 將目前的情況output
	for (int i = row + 4; i >= 1; i--) {
		for (int j = 1; j <= col; j++) {
			cout << area[i][j]<<" ";
		}
		cout << endl;
	}
	cout << endl << endl;
}

void do_terminate_row() {//當方塊停止落下時，檢查是否有列可以消除方塊，並且消除列以及搬動方塊
	int row_have_been_changed[5] = { 0 };
	int pos = 0;
	int i, j;
	for (i = 0; i <= 3; i++) {
		for (j = 1; j <= col; j++)
			if (area[index + i][j] == 0)
				break;
		if (j > col) {
			row_have_been_changed[++pos] = index + i;
			for (int k = 1; k <= col; k++)
				area[index + i][k] = 0;
		}
	}
	int row_have_to_move = 1;
	if (pos > 0) {
		for (i = row_have_been_changed[1] + 1; i <= row + 4 - pos; i++) {
			for (j = 1; j <= col; j++) {
				if (Is_num_in_Array(row_have_been_changed, i, 4)) {
					row_have_to_move++;
					break;
				}
				area[i - row_have_to_move][j] = area[i][j];
				area[i][j] = 0;
			}
		}
		for (int i = row + 4 - pos; i <= row + 4; i++)
			area[i][j] = 0;
	}
	if (pos > 0)
		do_terminate_row();
}

bool If_End_Game() {//確認是否遊戲結束，如果方塊停止且進行do_terminate_row()之後，仍有方塊停在暫存區(遊戲視窗看不到的區域)，則停止遊戲
	for (int i = row + 1; i <= row + 4; i++) {
		for (int j = 1; j <= col; j++) {
			if (area[i][j] == 2 || area[i][j] == 1)
				return true;
		}
	}
	return false;
}

bool check_collision(int row) {//確認方塊落下時有沒有碰到其他方塊
	if (index == 1)
		return true;
	for (int j = index; j <= index + 3; j++) {
		for (int i = 1; i <= col; i++) {
			if (area[j][i] == 2 && area[j - 1][i] == 1)
				return true;
		}
	}
	return false;
}



void tetris() {//實作方塊落下的過程
	index = row + 1;
	if(str=="T1"|| str == "T3" || str == "L2" || str == "L4" || str == "J2" || str == "J4"|| str == "S1"|| str == "Z1"){
		if (objectCol + 2 > col)
			cout << "illegal input for objectCol" << endl;
	}

	else if (str == "T2" || str == "T4" || str == "L1" || str == "L3" || str == "J1" || str == "J3" || str == "S2" || str == "Z2" || str == "O") {
		if (objectCol + 1 > col)
			cout << "illegal input for objectCol" << endl;
	}
	else if (str == "I1") {
		if (objectCol > col)
			cout << "illegal input for objectCol" << endl;
	}
	else if (str == "I2") {
		if (objectCol + 3 > col)
			cout << "illegal input for objectCol" << endl;
	}
	if (str=="T1") {
		for (int i = 0; i < 3; i++)
			area[row + 2][objectCol + i] = 2;
		area[row + 1][objectCol + 1] = 2;
	}
	else if (str == "T2") {
 		for (int i = 1; i <= 3; i++)
			area[row + i][objectCol + 1] = 2;
		area[row + 2][objectCol] = 2;
	}
	else if (str == "T3") {
		for (int i = 0; i < 3; i++)
			area[row + 1][objectCol + i] = 2;
		area[row + 2][objectCol + 1] = 2;
	}
	else if (str == "T4") {
		for (int i = 1; i <= 3; i++)
			area[row + i][objectCol] = 2;
		area[row + 2][objectCol + 1] = 2;
	}
	else if (str == "I3") {
		for (int i = row + 1; i <= row + 4; i++)
			area[i][objectCol] = 2;
	}
	else if (str == "L1") {
		for (int i = 1; i <= 3; i++) {
			area[row + i][objectCol] = 2;
		}
		area[row + 1][objectCol + 1] = 2;
	}
	else if (str == "L2") {
		for (int i = 0; i <= 2; i++) {
			area[row + 2][objectCol + i] = 2;
		}
		area[row + 1][objectCol] = 2;
	}
	else if (str == "L3") {
		for (int i = row + 1; i <= row + 3; i++) {
			area[i][objectCol + 1] = 2;
		}
		area[row + 3][objectCol] = 2;
	}
	else if (str == "L4") {
		for (int i = 0; i <= 2; i++) {
			area[row + 1][objectCol + i] = 2;
		}
		area[row + 2][objectCol + 2] = 2;
	}
	else if (str == "J1") {
		for (int i = 1; i <= 3; i++) {
			area[row + i][objectCol + 1] = 2;
		}
		area[row + 1][objectCol] = 2;
	}
	else if (str == "J2") {
		for (int i = 0; i <= 2; i++) {
			area[row + 1][objectCol + i] = 2;
		}
		area[row + 2][objectCol] = 2;
	}
	else if (str == "J3") {
		for (int i = row + 1; i <= row + 3; i++) {
			area[i][objectCol] = 2;
		}
		area[row + 3][objectCol + 1] = 2;
	}
	else if (str == "J4") {
		for (int i = 0; i <= 2; i++) {
			area[row + 2][objectCol + i] = 2;
		}
		area[row + 1][objectCol + 2] = 2;
	}
	else if (str == "S1") {
		for (int i = 0; i <= 1; i++)
			area[row + 1][objectCol + i] = 2;
		for (int i = 1; i <= 2; i++)
			area[row + 2][objectCol + i] = 2;
	}
	else if (str == "S2") {
		for (int i = 2; i <= 3; i++)
			area[row + i][objectCol] = 2;
		for (int i = 1; i <= 2; i++)
			area[row + i][objectCol + 1] = 2;
	}
	else if (str == "Z1") {
		for (int i = 1; i <= 2; i++)
			area[row + 1][objectCol + i] = 2;
		for (int i = 0; i <= 1; i++)
			area[row + 2][objectCol + i] = 2;
	}
	else if (str == "Z2") {
		for (int i = 2; i <= 3; i++)
			area[row + i][objectCol + 1] = 2;
		for (int i = 1; i <= 2; i++)
			area[row + i][objectCol] = 2;
	}
	else if (str == "I1") {
		for (int i = 1; i <= 4; i++)
			area[row + i][objectCol] = 2;
	}
	else if (str == "I2") {
		for (int i = 0; i <= 3; i++)
			area[row + 1][objectCol + i] = 2;
	}
	else if (str == "O") {
		for (int i = 1; i <= 2; i++)
			for (int j = 0; j <= 1; j++)
				area[row + i][objectCol + j] = 2;
	}
	else {
		cout << str<<"方塊代碼錯誤" << endl;
		return;
	}
	if (objectCol == 5 && str == "I1")
		int a = 0;

	while (true) {
		//output_tetris();
		if (check_collision(index)) {
			break;
		}
		for (int i = index; i <= index + 3; i++) {
			for (int j = 1; j <= col; j++) {
				if (area[i][j] == 2) {
					area[i - 1][j] = 2;
					area[i][j] = 0;
				}
				else if (area[i][j] == 0 && area[i - 1][j] == 2)
					area[i - 1][j] = 0;
			}

		}
		for (int j = 1; j <= col; j++) {
			if (area[index + 3][j] == 2)
				area[index + 3][j] = 0;
		}
		index--;
	}
	for (int i = index; i <= index + 3; i++) {
		for (int j = 1; j <= col; j++) {
			if (area[i][j] == 2)
				area[i][j] = 1;
		}
	}
}

int main() {
	ifstream inputFile("Tetris.data");
	if (!inputFile)
		cout << "Fail to open 'Tetris.data'" << endl;

	fstream outputFile;
	outputFile.open("Tetris.output", ios::out);
	if (!outputFile)
		cout << "Fail to open 'Tetris.output'" << endl;


	inputFile >> row;
	inputFile >> col;

	while (1) {
		inputFile >> str;
		if (str == "End")
			break;
		inputFile >> objectCol;
		//cout << str << " " << objectCol << ":" << endl;//debug用
		tetris();
		do_terminate_row();
		//output_tetris();
		if (If_End_Game())
			break;
	}

	for (int i = row; i >= 1; i--) {
		for (int j = 1; j <= col; j++) {
			cout << area[i][j]<<" ";
		}
		cout <<endl;
	}

	for (int i = row; i >= 1; i--) {
		for (int j = 1; j <= col; j++) {
			outputFile << area[i][j];
		}
		outputFile << '\n';
	}

	inputFile.close();
	outputFile.close();
	return 0;
}
