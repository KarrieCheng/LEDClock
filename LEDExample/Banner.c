#include <stdio.h>
#include <stdlib.h>

int columns = 3;
int leds_per_column = 8;

//Number Segments
const int one_bar [8] =           {1,1,1,1,1,1,1,1};
const int one_blank [8] =         {0,0,0,0,0,0,0,0};
const int one_mid [8] =           {0,0,0,1,0,0,0,0};
const int one_top[8] =            {1,0,0,0,0,0,0,0};
const int two_top [8] =           {1,1,1,1,0,0,0,0};
//const int two_bottom [8] =        {0,0,0,0,1,1,1,1}; //Unused
const int two_exclam [8] =        {1,1,1,1,0,0,0,1};
const int two_inv_excl [8] =      {1,0,0,0,1,1,1,1};
const int two_spread [8] =        {1,0,0,0,0,0,0,1};
const int two_bot_spread [8] =    {0,0,0,0,1,0,0,1};
const int two_top_spread [8] =    {1,0,0,1,0,0,0,0};
const int three_spread [8] =      {1,0,0,1,0,0,0,1};
const int three_spread_inv [8] =  {1,0,0,0,1,0,0,1};

int main(){
	int column_counter = 0;
	int row_counter = 0;

	

	//int zero[3] =  {one_bar, two_spread, one_bar};
	int* zero = 	malloc(sizeof(int) * columns * leds_per_column);
	for (row_counter = 0; row_counter < leds_per_column; row_counter++){
		zero[row_counter + (0 * leds_per_column)] = one_bar[row_counter];
		zero[row_counter + (1 * leds_per_column)] = two_spread[row_counter];
		zero[row_counter + (2 * leds_per_column)] = one_bar[row_counter];
	}

	//int one [3] =   {one_blank, one_bar, one_blank};
	int* one = 		malloc(sizeof(int) * columns * leds_per_column);
	for (row_counter = 0; row_counter < leds_per_column; row_counter++){
		for (row_counter = 0; row_counter < leds_per_column; row_counter++){
			one[row_counter + (0 * leds_per_column)] = one_blank[row_counter];
			one[row_counter + (1 * leds_per_column)] = one_bar[row_counter];
			one[row_counter + (2 * leds_per_column)] = one_blank[row_counter];
		}
	}

	//int two [3] =   {two_inv_excl, three_spread_inv, two_exclam};
	int* two = 	malloc(sizeof(int) * columns * leds_per_column);
	for (row_counter = 0; row_counter < leds_per_column; row_counter++){
		for (row_counter = 0; row_counter < leds_per_column; row_counter++){
			two[row_counter + (0 * leds_per_column)] = two_inv_excl[row_counter];
			two[row_counter + (1 * leds_per_column)] = three_spread_inv[row_counter];
			two[row_counter + (2 * leds_per_column)] = two_exclam[row_counter];
		}
	}

	int* three = 	malloc(sizeof(int) * columns * leds_per_column);
	//int three [3] = {three_spread, three_spread, one_bar};
	for (row_counter = 0; row_counter < leds_per_column; row_counter++){
		for (row_counter = 0; row_counter < leds_per_column; row_counter++){
			three[row_counter + (0 * leds_per_column)] = three_spread[row_counter];
			three[row_counter + (1 * leds_per_column)] = three_spread[row_counter];
			three[row_counter + (2 * leds_per_column)] = one_bar[row_counter];
		}
	}

	//int four [3] =  {two_top, one_mid, one_bar};
	
	int* four = 	malloc(sizeof(int) * columns * leds_per_column);
	for (row_counter = 0; row_counter < leds_per_column; row_counter++){
		for (row_counter = 0; row_counter < leds_per_column; row_counter++){
			four[row_counter + (0 * leds_per_column)] = two_top[row_counter];
			four[row_counter + (1 * leds_per_column)] = one_mid[row_counter];
			four[row_counter + (2 * leds_per_column)] = one_bar[row_counter];
		}
	}

	//int five [3] =  {two_exclam, three_spread_inv, two_inv_excl};
	int* five = 	malloc(sizeof(int) * columns * leds_per_column);
	for (row_counter = 0; row_counter < leds_per_column; row_counter++){
		for (row_counter = 0; row_counter < leds_per_column; row_counter++){
			five[row_counter + (0 * leds_per_column)] = two_exclam[row_counter];
			five[row_counter + (1 * leds_per_column)] = three_spread_inv[row_counter];
			five[row_counter + (2 * leds_per_column)] = two_inv_excl[row_counter];
		}
	}

	//int six [3] =   {one_bar, three_spread_inv, two_inv_excl};
	int* six = 		malloc(sizeof(int) * columns * leds_per_column);
	for (row_counter = 0; row_counter < leds_per_column; row_counter++){
		for (row_counter = 0; row_counter < leds_per_column; row_counter++){
			six[row_counter + (0 * leds_per_column)] = one_bar[row_counter];
			six[row_counter + (1 * leds_per_column)] = three_spread_inv[row_counter];
			six[row_counter + (2 * leds_per_column)] = two_inv_excl[row_counter];
		}
	}

	//int seven [3] = {one_top, one_top, one_bar};
	int* seven = 	malloc(sizeof(int) * columns * leds_per_column);
	for (row_counter = 0; row_counter < leds_per_column; row_counter++){
		for (row_counter = 0; row_counter < leds_per_column; row_counter++){
			seven[row_counter + (0 * leds_per_column)] = one_top[row_counter];
			seven[row_counter + (1 * leds_per_column)] = one_top[row_counter];
			seven[row_counter + (2 * leds_per_column)] = one_bar[row_counter];
		}
	}

	//int eight [3] = {one_bar, three_spread, one_bar};
	int* eight = 	malloc(sizeof(int) * columns * leds_per_column);
	for (row_counter = 0; row_counter < leds_per_column; row_counter++){
		for (row_counter = 0; row_counter < leds_per_column; row_counter++){
			eight[row_counter + (0 * leds_per_column)] = one_bar[row_counter];
			eight[row_counter + (1 * leds_per_column)] = three_spread[row_counter];
			eight[row_counter + (2 * leds_per_column)] = one_bar[row_counter];
		}
	}

	//int nine [3] =  {two_top, two_top_spread, one_bar};
	int* nine = 	malloc(sizeof(int) * columns * leds_per_column);
	for (row_counter = 0; row_counter < leds_per_column; row_counter++){
		for (row_counter = 0; row_counter < leds_per_column; row_counter++){
			nine[row_counter + (0 * leds_per_column)] = two_top[row_counter];
			nine[row_counter + (1 * leds_per_column)] = two_top_spread[row_counter];
			nine[row_counter + (2 * leds_per_column)] = one_bar[row_counter];
		}
	}

	int* led_reps [10] = {zero, one, two, three, four, five, six, seven, eight, nine};

	int* digit;
	digit = zero;
	int j = 0;
	int k = 0;


	printf("\n\n\n%s \n", "LED rep");
	for (int i = 0; i < 10; ++i)
	{
		digit = led_reps[i];
		for (j = 0; j < 3; j++){
			for (k = 0; k < 8; k++){
					(digit[(j*leds_per_column) + k] == 1)? printf("X") : printf(" "); 
				}
				printf("\n");
		}
		printf("\n");
		printf("\n");
	}
	

	return 0;
}
