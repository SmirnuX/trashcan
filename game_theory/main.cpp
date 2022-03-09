#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

/*================================================
	Game theory app
  Iterative method of solving antagonistic games.

  Format of command:
  .\gt <filename> [iteration count = 0] [first move = rand]

  Format of input file:
  <num of rows> <num of columns>
  <row 1>
  ....
  <row n>
================================================*/

int main(int argc, char* argv[])	//The only argument is file with matrix.
{
	if (argc < 2)
	{
		cout << "There are no arguments! Please provide path to file to read matrix from.\n";
		return EBADF;
	}
	cout << "\nOpening " << argv[1] << endl;
	uint it_count = 8;	//Number of iterations
	if (argc >= 3)
	{
		it_count = atoi(argv[2]);
		if (it_count <= 0)
		{
			cout << "Can't interpret second argument as a number. Make sure that second argument is non-zero positive number.\n";
			return EDOM;
		}
	}
	ifstream input(argv[1]);
	if (!input.good())
	{
		cout << "Error occured while trying to open file.\n";
		return EBADF;
	}
	uint rows, cols;
	input>>rows;
	input>>cols;
	if (rows<=0 || cols<=0)
	{
		cout << "Error occured while trying to get matrix dimensions.\n";
		return EBADF;
	}
	cout << "Matrix " << rows << "x" << cols << endl;
	uint first_move;	//First move of first player
	if (argc >= 4)
	{
		first_move = atoi(argv[3]) - 1;
		if (first_move < 0)
		{
			cout << "Can't interpret third argument as a number. Make sure that second argument is non-zero positive number.\n";
			return EDOM;
		}
	}
	else
	{
		srand(time(NULL));
		first_move = rand() % rows;	//Random first move
	}
	cout << "Player A move is " << first_move+1 << endl;
	double** matrix = new double*[rows];
	for (uint i = 0; i < rows; i++)
	{
		matrix[i] = new double[cols];
		for (uint j = 0; j < cols; j++)
		{			
			if (!input.good())
			{
				for (int k = 0; k <= i; k++)
					delete matrix[k];
				delete[] matrix;
				cout << "There is an error when parsing matrix file.\n";
				return EBADF;
			}
			input >> matrix[i][j];
		}
	}
	unique_ptr<double> A_accumulated(new double[cols]);
	unique_ptr<double> B_accumulated(new double[rows]);
	unique_ptr<uint> A_probabilities(new uint[cols]);
	unique_ptr<uint> B_probabilities(new uint[rows]);
	for (uint i = 0; i < cols; i++)
	{
		A_accumulated.get()[i] = 0;
		A_probabilities.get()[i] = 0;
	}
	for (uint i = 0; i < rows; i++)
	{
		B_accumulated.get()[i] = 0;	
		B_probabilities.get()[i] = 0;
	}
	uint next_A_move = first_move;
	uint next_B_move;
	double max_min_loss;
	double min_max_win;
	double delta;
	for (uint i = 0; i < it_count; i++)
	{
		uint curr_A_move = next_A_move;
		//Player A move
		double min_loss = 999999;
		A_probabilities.get()[next_A_move] ++;
		for (uint j = 0; j < cols; j++)
		{
			A_accumulated.get()[j] += matrix[next_A_move][j];
			if (A_accumulated.get()[j] < min_loss)
			{
				min_loss = A_accumulated.get()[j];
				next_B_move = j;
			}
		}	

		//Player B move
		B_probabilities.get()[next_B_move] ++;
		double max_win = 0;
		for (uint j = 0; j < rows; j++)
		{
			B_accumulated.get()[j] += matrix[j][next_B_move];
			if (B_accumulated.get()[j] > max_win)
			{
				max_win = B_accumulated.get()[j];
				next_A_move = j;
			}
		}
		//Counting max loss/win
		max_win /= (i+1);
		min_loss /= (i+1);
		if (i == 0)
		{
			max_min_loss = min_loss;
			min_max_win = max_win;
		}
		else
		{
			if (min_loss > max_min_loss)
				max_min_loss = min_loss;
			if (max_win < min_max_win)
				min_max_win = max_win;
		}
		//Counting delta
		delta = min_max_win - max_min_loss;
		//Output
		int col_size = 3;
		if (i == 0)	//Drawing head of table
		{
			cout <<setfill(' ') << "|" << setw(2) << "k" << setw(4) << "||" << setw(col_size+1) << "i" << setw(col_size+2) << "||";
			for (uint j = 0; j < cols; j++)
			{
				cout << setw(col_size+2) << "u" << j+1 << setw(col_size+1) << "|" ;
			}
			cout << setw(col_size+2) << "y2" << setw(col_size+1) << "|" << " max y2 ||" << setw(col_size+1) << "j" << setw(col_size+2) <<"||";
			for (uint j = 0; j < rows; j++)
			{
				cout << setw(col_size+2) << "v" << j+1 << setw(col_size+1) << "|" ;
			}
			cout << setw(col_size+2) << "y1" << setw(col_size+1) << "|" << " min y2 || delta ||" << endl;
		}
		//Drawing data
		cout << "|" << setw(4) << i+1 << "||" << setw(2*col_size) << curr_A_move+1 << " ||";
		for (uint j = 0; j < cols; j++)
		{
			cout << setw(2*col_size+2) << A_accumulated.get()[j] << " |" ;
		}
		cout << setw(2*col_size+2) << min_loss << "|" << setw(7) << max_min_loss <<" ||";

		cout << setw(2*col_size) << next_B_move+1 << " ||";
		for (uint j = 0; j < rows; j++)
		{
			cout << setw(2*col_size+2) << B_accumulated.get()[j] << " |" ;
		}
		cout << setw(2*col_size+2) << max_win << "|" << setw(7) << min_max_win <<" ||";
		cout << setw(7) << delta << "||" <<endl;
	}
	cout << setfill('=') <<setw(55)<<endl;
	cout << "Results: " << endl;
	cout << "\t Cost:\t" << (min_max_win + max_min_loss)/2 << endl;
	cout << "\t Strategy probabilities:       ";
	for (uint i = 0; i < rows; i++)
	{
		cout << setfill(' ') << "A" << i+1 << setw(8);
	}
	cout << endl << '\t' << setw(31) << " ";
	for (uint i = 0; i < rows; i++)
	{
		cout << (double)A_probabilities.get()[i] / it_count << setw(9);
	}
	cout << endl << '\t' << setw(23) << " ";

	for (uint i = 0; i < cols; i++)
	{
		cout << setfill(' ') << "B" << i+1 << setw(8);
	}
	cout << endl << '\t' << setw(31) << " ";
	for (uint i = 0; i < cols; i++)
	{
		cout << (double)B_probabilities.get()[i] / it_count << setw(9);
	}
	cout << endl;
	//Clearing memory
	for (uint i = 0; i < rows; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
	return 0;
}