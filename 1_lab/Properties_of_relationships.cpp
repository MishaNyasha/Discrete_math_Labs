#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void menu();
void request(string filename)
{
	int n = 0;
	bool arr[255][255];
	ifstream file(filename);
	if (!file)
	{
		cout << "\n# Error with file";

		cout << "\n\n-   -   -   -   -   -   -   -   -   -\n\n";

		menu();
		return;
	}
	string line;
	getline(file, line);
	for (int i = 0; i < line.length(); i++)
	{
		if (line[i] == '0' || line[i] == '1')
		{
			n++;
		}
	}
	cout << "# Matrix size - " << n << "x" << n << "\n\n";
	file.clear();
	file.seekg(0);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			file >> arr[i][j];
		}
	}
	file.close();

	cout << "# Matrix\n";
	for (int i = 0; i < n; i++)
	{
		cout << "\n    ";
		for (int j = 0; j < n; j++)
		{
			cout << arr[i][j] << " ";
		}
	}
	cout << endl;

	cout << "\n# Reflexivity          ";
	bool is_reflexive = true;
	for (int i = 0; i < n; i++)
	{
		if (arr[i][i] == 0)
		{
			is_reflexive = false;
			break;
		}
	}
	cout << (is_reflexive ? "[ + ]" : "[ - ]");

	cout << "\n# Anti_reflexivity     ";
	bool is_anti_reflexive = true;
	for (int i = 0; i < n; i++)
	{
		if (arr[i][i] == 1)
		{
			is_anti_reflexive = false;
			break;
		}
	}
	cout << (is_anti_reflexive ? "[ + ]" : "[ - ]");

	cout << "\n# Symmetry             ";
	bool is_symmetric = true;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (arr[i][j] != arr[j][i])
			{
				is_symmetric = false;
				break;
			}
		}
		if (!is_symmetric) break;
	}
	cout << (is_symmetric ? "[ + ]" : "[ - ]");

	cout << "\n# Asymmetry            ";
	bool is_asymmetric = true;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (arr[i][j] == arr[j][i] || arr[i][i] != 0)
			{
				is_asymmetric = false;
				break;
			}
		}
		if (!is_asymmetric) break;
	}
	cout << (is_asymmetric ? "[ + ]" : "[ - ]");

	cout << "\n# Anti_symmetry        ";
	bool is_anti_symmetric = true;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (arr[i][j] == arr[j][i] && arr[i][j] == 1)
			{
				is_anti_symmetric = false;
				break;
			}
		}
		if (!is_anti_symmetric) break;
	}
	cout << (is_anti_symmetric ? "[ + ]" : "[ - ]");

	cout << "\n# Transitivity         ";
	bool is_transitive = true;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (arr[i][j]) {
				for (int k = 0; k < n; k++)
				{
					if (arr[j][k] && !arr[i][k])
					{
						is_transitive = false;
						break;
					}
				}
				if (!is_transitive) break;
			}
		}
		if (!is_transitive) break;
	}
	cout << (is_transitive ? "[ + ]" : "[ - ]");

	cout << "\n# Connectedness        ";
	bool is_connected = true;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i != j and arr[i][j] != 1 and arr[j][i] != 1)
			{
				is_connected = false;
				break;
			}
		}
		if (!is_connected) break;
	}
	cout << (is_connected ? "[ + ]" : "[ - ]") << endl << endl;


	menu();
}
void menu()
{
	cout << "# Enter filename or exit :  ";
	string filename = "";
	cin >> filename;
	if (filename != "exit")
	{
		cout << "# filename - " << filename << endl;
		request(filename);
	}
}
int main()
{
	menu();
	return 0;
}