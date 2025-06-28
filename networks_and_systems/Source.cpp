//
#include <iostream>
#include <bitset>
#include <fstream>
#include <vector>
#include <stack>
#include <cmath>

using namespace std;

struct polynom {
	int* pol;
	int len;
};

void printf_pol(int* pol, int len) {
	for (int i = 0; i < len; i++)
	{
		cout << "m[" << i << "]= " << pol[i] << " "; // На экран через пробелы выводятся все элементы массива
	}
	cout << "\n";;
}

void printf_pol1(int* pol, int len) {
	for (int i = len - 1; i >= 0; i--)
	{
		cout << pol[i]; // На экран через пробелы выводятся все элементы массива
	}
	cout << "\n";;
}

void printf_pol2(int* pol, int len) {
	for (int i = 0; i < len; i++)
	{
		cout << pol[i] << " "; // На экран через пробелы выводятся все элементы массива
	}
	cout << "\n";;
}

int field_galois(int num) {
	//int mod = abs(num) % 2;
	return abs(num) % 2;
}





polynom Div_Polynomials3(int* pol1, int* pol2, int size1, int size2)
//деление полинмов
{
	polynom pol;
	int* mod;
	int* quotient; // делимое
	int size3 = size1 - size2 + 1;
	int size4;
	quotient = new int[size3]; //length_k_mes=m-n+1
	size4 = size1;
	mod = new int[size1];
	int count = 0;
	for (int i = 0;i < size1;i++) {
		mod[i] = field_galois(pol1[i]);
	}
	int size_check_mod = 0;

	int temp_size4 = 0;
	for (int i = size1 - 1;i >= 0;i--) {
		if (mod[i] == 1) {
			temp_size4 = i + 1;
			break;
		}
	}

	if (temp_size4 < size2) { //size_check_mod == size1 - size2 + 2

		pol.len = size4;
		pol.pol = mod;

		return pol;

	}
	
	//cout << "здесь  " << endl;

	for (int i = 0; i < size3; i++)//o до к
	{
		double coeff = mod[size4 - i - 1] / pol2[size2 - 1];
		//quotient[size3 - i - 1] = coeff;
		quotient[size3 - i - 1] = field_galois(coeff);
		for (int j = 0; j < size2; j++)
		{
			mod[size4 - i - j - 1] = field_galois(mod[size4 - i - j - 1] - coeff * pol2[size2 - j - 1]);
		}

	}
	//cout << "Внутри деления";
	//printf_pol1(mod,size4);

	for (int i = size4 - 1;i >= 0;i--) {
		//std::cout << mod[i] << " ";

		if (mod[i] == 1 && i == size4 - 1) {

			break;
		}
		else {
			if (mod[i] == 1 && i != size4 - 1) {

				size4 = i + 1;

				break;
			}
		}
		if (mod[i] == 1) {
			count++;
		}

		if (count == 0 && i == 0) {

			size4 = 0;
		}
	}




	pol.pol = mod;
	pol.len = size4;
	return pol;
	//result_quotient = quotient;
	//result_mod = mod;
}




int fncSumm(unsigned int n)
{
	int summ = 0;
	for (int i = 0;i < sizeof(int) * 8;i++)
	{
		int k = (n >> i) & 0x01;
		summ += k;
	}
	return summ;
}

int C(int n, int k) //cочетание
{
	if (k == 0 || k == n)
		return 1;
	return C(n - 1, k - 1) * n / k;
}


double upper_estimate_decoding_error(double p, int n, int d) { //верхняя оценка ошибки декодирования
	double result = 0;
	for (int i = 0;i < d;i++) { //либо d-1;
		result = result + (double)C(n, i) * pow(p, i) * pow(1 - p, n - i);
	}
	return 1 - result;
}



double random(double min, double max)
{
	return (double)(rand()) / RAND_MAX * (max - min) + min;
}

unsigned int Random_vector(float p, int size) {
	//float q=1-p;
	unsigned int vector = 0;
	for (int i = 0;i < size;i++) {
		double  rand_num = random(0.0, 1.0);
		unsigned int bit = 1;
		if (rand_num >= 0 && rand_num <= p) {
			bit = bit << i;
			vector = vector | bit;
		}
	}

	return vector;
}





polynom Add_Polynomials(int* pol1, int* pol2, int size1, int size2)
//складывает полиномы
{
	int* pol3;
	int size3;
	//int size3;
	if (size1 >= size2) // Если первый полином самый длинный,то на его основе создаем конечный полином

	{
		pol3 = new int[size1];
		size3 = size1;
		for (int i = 0; i < size1; i++)
		{
			if (i < size2)
			{


				//pol3[i] = pol1[i] + pol2[i];
				pol3[i] = field_galois(pol1[i] + pol2[i]);
			}
			else
			{
				pol3[i] = field_galois(pol1[i]);
			}
		}
	}
	else // Если второй полином самый длинный,то на его основе создаем конечный полином
	{

		pol3 = new int[size2];
		size3 = size1;
		for (int i = 0; i < size2; i++)
		{
			if (i < size1)
			{
				pol3[i] = field_galois(pol1[i] + pol2[i]);
			}
			else
			{
				pol3[i] = field_galois(pol2[i]);

			}
		}
	}

	for (int i = size3 - 1;i > 0;i--) {
		if (pol3[i] == 1 && i == size3 - 1) {
			break;
		}
		else {
			if (pol3[i] == 1 && i != size3 - 1) {
			
				size3 = i + 1;
				break;
			}
		}
	}

	struct polynom pol;
	pol.pol = pol3;
	pol.len = size3;
	return pol;

}

polynom Mul_Polynomials(int* pol1, int* pol2, int size1, int size2)
//умножение полиномов
{

	int size3 = size1 + size2;
	int* pol3;
	pol3 = new int[size3];
	for (int i = 0;i < size3;i++) {
		pol3[i] = 0;
	}
	//перемножение множителей
	for (int i = 0; i < size1; i++)
	{ //первый многочлен
		for (int j = 0; j < size2; j++)
		{ //второй многчлен
			//pol3[i + j] = pol3[i + j] + pol1[i] * pol2[j];
			int temp1 = pol1[i] * pol2[j];
			int temp2 = pol3[i + j] + temp1;
			int temp3 = field_galois(temp2);

			pol3[i + j] = temp3;

		}
	}

	for (int i = size3 - 1;i > 0;i--) {
		if (pol3[i] == 1 && i == size3 - 1) {
			break;
		}
		else {
			if (pol3[i] == 1 && i != size3 - 1) {
			
				size3 = i + 1;
				break;
			}
		}
	}

	struct polynom pol;
	pol.pol = pol3;
	pol.len = size3;
	return pol;

}




void fill_polynom(int* pol, unsigned int vector, int lenght) {
	for (int i = 0;i < lenght;i++) {
		if ((vector & 1) == 1) {
			pol[i] = 1;
		}
		else {
			pol[i] = 0;
		}
		vector = vector >> 1;
	}
}

void fill_vector(int* pol, unsigned int& vector, int lenght) {
	vector = 0;
	unsigned int bit;
	for (int i = 0;i < lenght;i++) {
		bit = 1;
		bit = bit << i;
		if (pol[i] == 1) {
			vector = vector | bit;
		}
	}
}

void permutation3(int* pol_g, int pol_g_deg_r, int length_k_mes, int n, int d, int* pol_mes, std::vector<int>& number_code_words) //std::vector < std::vector <int> >& comb_s
{ //Размещения с повторением 2^n
	if (n < 0) {
		std::cout << "нельзя отрицательные\n";
		return;
	}
	if (n == 0)
	{

		//unsigned int mes_vector = Random_vector(p, length_k_mes);//вектор //без вероятности
		struct polynom pol;

		//int* pol_mes = new int[length_k_mes];

		//fill_polynom(pol_mes, mes_vector, length_k_mes);
		//std::cout << " аыфв " << mes_vector;
		//printf_pol(pol_mes, length_k_mes);
		// printf_pol1(pol_mes, length_k_mes);
		//printf_pol2(pol_mes, length_k_mes);

		int* pol_xr = new int[pol_g_deg_r];

		for (int i = 0;i < pol_g_deg_r - 1;i++) {
			pol_xr[i] = 0;
		}
		pol_xr[pol_g_deg_r - 1] = 1;


		pol = Mul_Polynomials(pol_mes, pol_xr, length_k_mes, pol_g_deg_r);

		int* temp_mes_mul_xr = pol.pol;
		int temp_mes_mul_xr_lenght = pol.len;
		for (int i = 0, j=0;i < length_k_mes;i++) {
			if (pol_mes[i]==0) {
				j++;
			}
			if (j == length_k_mes) {
				temp_mes_mul_xr_lenght = pol.len - 1;
			}
		}
		
		//printf_pol1(temp_mes_mul_xr, temp_mes_mul_xr_lenght);
		//printf_pol2(temp_mes_mul_xr, temp_mes_mul_xr_lenght);
		//printf_pol2(temp_mes_mul_xr, temp_mes_mul_xr_lenght);
		pol = Div_Polynomials3(temp_mes_mul_xr, pol_g, temp_mes_mul_xr_lenght, pol_g_deg_r);
		
		int* pol_c = pol.pol;
		int length_c = pol.len;
		//printf_pol1(pol_c, length_c);
		//cout << "temp_mes_mul_xr_lenght " << temp_mes_mul_xr_lenght;
		pol = Add_Polynomials(temp_mes_mul_xr, pol_c, temp_mes_mul_xr_lenght, length_c);

		int* pol_a = pol.pol;
		int length_a = pol.len;

		//printf_pol1(pol_a, length_a);
		int count = 0;
		for (int i = 0;i < pol.len;i++) {
			if (pol_a[i] == 1) {
				count++;
			}
		}


		//printf_pol1(pol_a, length_a);
		//printf_pol(pol_a, length_a);
		
		//cout << "  \n";


		if (count >= d) {
			number_code_words[count]++;
		}
		else {
			number_code_words[count] = 0;
		}


		return;
	}
	else {
		for (int i = 0;i <= 1;i++) {
			pol_mes[length_k_mes - n] = i;

			permutation3(pol_g, pol_g_deg_r, length_k_mes, n - 1, d, pol_mes, number_code_words);
		}
	}
}


double calculating_exact_value_decoding_error3(int* pol_g, int pol_g_deg_r, double p, int length_k_mes, int d) {
	double result = 0;
	//vector<int> arr_comb = vector<int>(n);
	vector<int> number_code_words = vector<int>(length_k_mes + pol_g_deg_r+1 ); //+1 или -1
	//cout << "length_k_mes + pol_g_deg_r - 1 " << length_k_mes + pol_g_deg_r - 1;
	int* pol_mes = new int[length_k_mes];

	permutation3(pol_g, pol_g_deg_r, length_k_mes, length_k_mes, d, pol_mes, number_code_words);
	/*
	for (int i = 0;i <= n;i++) { //либо d-1;
		cout<<i<<"=" << number_code_words[i] << " ";
	}
	*/
	for (int i = d;i < pol_g_deg_r + length_k_mes;i++) { //либо d-1;

		result = result + number_code_words[i] * pow(p, i) * pow(1 - p, pol_g_deg_r + length_k_mes - i-1);
	}

	return result;
}


int main()
{
	setlocale(LC_ALL, "Russian");
	srand(34);
	int pol_g_deg_r = 4;
	int* pol_g = new int[pol_g_deg_r];//задаем многочлен g(x)
	pol_g[0] = 1; //1011
	pol_g[1] = 0;  //1101
	pol_g[2] = 1;
	pol_g[3] = 1;



	//int r = pol_g_deg_r;
	int length_k_mes = 4; //длина кодируемой последотвальеность
	//вероятность ошибки 
	double epsilon = 0.005;//точность
	double N = 9.0 / (4.0 * epsilon * epsilon);
	int Ne = 0;
	int n = pol_g_deg_r + length_k_mes - 1;
	int d = 3;
	std::cout << N;


	ofstream fout1("Иммитационное моделирование.txt");

	std::cout << "\nPe=" << (double)Ne / N;
	
	for (double p = 0.1; p <= 1.0; p += 0.1) {
		cout << "p = " << p << endl;

		for (int i = 0;i < N;i++) {
			//1) генерируется случайное сообщение, затем к нему 
		//добавляется контрольная сумма по алгоритму, описанному в разделе 1.2.
			unsigned int mes_vector = Random_vector(p, length_k_mes);//вектор //без вероятности
			struct polynom pol;
			
			int* pol_mes = new int[length_k_mes];
			for (int i = 0;i < length_k_mes;i++) {
				
			}

			fill_polynom(pol_mes, mes_vector, length_k_mes);
			//std::cout << " аыфв " << mes_vector;
			int* pol_xr = new int[pol_g_deg_r];

			for (int i = 0;i < pol_g_deg_r - 1;i++) {
				pol_xr[i] = 0;
			}
			pol_xr[pol_g_deg_r - 1] = 1;


			pol = Mul_Polynomials(pol_mes, pol_xr, length_k_mes, pol_g_deg_r);

			int* temp_mes_mul_xr = pol.pol;
			int temp_mes_mul_xr_lenght = pol.len;

			pol = Div_Polynomials3(temp_mes_mul_xr, pol_g, temp_mes_mul_xr_lenght, pol_g_deg_r);
			int* pol_c = pol.pol;
			int length_c = pol.len;
			//cout << "temp_mes_mul_xr_lenght " << temp_mes_mul_xr_lenght;
			pol = Add_Polynomials(temp_mes_mul_xr, pol_c, temp_mes_mul_xr_lenght, length_c);
			int* pol_a = pol.pol;
			int length_a = pol.len;

			unsigned int vector_a;
			fill_vector(pol_a, vector_a, length_a);
			//std::cout <<"sda" << length_a;
			//2 генерируется случайный вектор ошибок,
		//	cout << "length_a " << length_a;
			unsigned int error_vector = Random_vector(p, n);
			//unsigned int error_vector = 29;
			unsigned int vector_b = vector_a ^ error_vector; //итоговый вектор
			//cout << " " << vector_b;

			//cкладываем
			//3


			int* pol_b = new int[n];
			int length_b = n;
			fill_polynom(pol_b, vector_b, length_b);


			pol = Div_Polynomials3(pol_b, pol_g, length_b, pol_g_deg_r);

			int* pol_syndrome = pol.pol;
			int length_syndrome = pol.len;

			int have_error = false;
			for (int i = 0;i < length_syndrome;i++) {
				if (pol_syndrome[i] == 1) {
					have_error = true;
					break;
				}
			}


			int error = 0;
			if (have_error) {
				error = 1;
			}
			if (error_vector != 0 && have_error == false) {
				Ne++;
			}


		}
		cout << "Ne=" << Ne << endl;
		cout << "Экспериментальное значение вероятности = " << (double)Ne / N <<
			endl;
		fout1 << p << " " << (double)Ne / N << std::endl;
		Ne = 0;


	}
	
	cout << " Вычисление точного значения ошибки декодирования" << endl;
	//cout << "Экспериментальное значение вероятности = " << calculating_exact_value_decoding_error2(pol_g, pol_g_deg_r, 0.1, n, d) <<
		//endl;
	//double p = 0.1;
		//cout << "Экспериментальное значение вероятности = " << calculating_exact_value_decoding_error3(pol_g, pol_g_deg_r, p, length_k_mes, d) <<
			//endl;
	ofstream fout2("точноr значениt ошибки декодирования.txt");
	
   
	for (double p = 0.1; p <= 1.0; p += 0.1) {
		cout << "p = " << p << endl;

		
		cout << "Экспериментальное значение вероятности = " << calculating_exact_value_decoding_error3(pol_g, pol_g_deg_r, p, length_k_mes, d) <<
			endl;
		fout2 << p << " " << calculating_exact_value_decoding_error3(pol_g, pol_g_deg_r, p, length_k_mes, d) << std::endl;
		Ne = 0;

	}
	
	cout << "Вычисление верхней оценки ошибки декодирования" << endl;
	ofstream fout3("верхняя оценка ошибки декодирования.txt");
	
	for (double p = 0.1; p <= 1.0; p += 0.1) {
		cout << "p = " << p << endl;


		cout << "Экспериментальное значение вероятности = " << upper_estimate_decoding_error(p, n, d) <<
			endl;
		fout3 << p << " " << upper_estimate_decoding_error(p, n, d) << std::endl;
		Ne = 0;


	}
	
	fout1.close();
	fout2.close();
	fout3.close();


	return 0;
}


