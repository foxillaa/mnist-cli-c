#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "functions.h" // Swish funkcia a pomocne funkcie -- NEMENIT !!!
#include "data.h" // Makra, vahy a bias hodnoty -- NEMENIT !!!

void printWeight(int neuronIndex, int row, int column) {
	int index = neuronIndex * 784 + row * 28 + column;

	printf("%.2lf", weights[index]);
}

void weightLoss(double pixels[]) {
	double sum = 0;
	for(int neuron = 0; neuron < 10; neuron++) {
		for (int i = 0; i < 785; i++) {
			sum += weights[784*neuron + i]*pixels[i]; 
		}
		sum+=bias[neuron];
		printf("%8d %8.2lf",neuron, sum);
		if (neuron < 9) {
			printf("\n");
	}
		sum = 0;
	}
}

double softmax_sum(double max_value, double values[], int size) {
	double check_sum = 0.0;
	for (int i = 0; i < size; i++) {
			check_sum += exp(values[i] - max_value);
	}
	return check_sum;
}

double findMaxValue(double values[], int size) {
	double max_value = values[0];

	for (int i = 1; i < size; i++) {
			if (values[i] > max_value) {
					max_value = values[i];
			}
	}
	return max_value;
}

int findMaxIndex(double values[], int size) {
	int maxIndex = 0;

	for (int i = 1; i < size; i++) {
			if (values[i] > values[maxIndex]) {
					maxIndex = i;
			}
	}
	return maxIndex;
}

void mode4(double values[], int size) {
	double max_value = findMaxValue(values, size);

	double denominator = softmax_sum(max_value, values, size);

	for (int i = 0; i < size; i++) {
			values[i] = exp(values[i] - max_value) / denominator;
	}
	for (int i = 0; i < size; i++) {
		printf("%.2lf ", values[i]);
	}
}

void mode5(double values[], int size){
	int maxIndex = 0;
	double max_value = values[0];

	for (int i = 1; i < size; i++) {
			if (values[i] > max_value) {
					max_value = values[i];
					maxIndex = i;
			}
	}
	printf("%d", maxIndex);
	
}

int searchNeuronName(double pixels[]) {
	double sum = 0;
	int size = 10;
	double neurons[size];
	for(int neuron = 0; neuron < 10; neuron++) {
		for (int i = 0; i < 785; i++) {
			sum += weights[784*neuron + i]*pixels[i]; 
		}
		sum+=bias[neuron];
		neurons[neuron] = sum;
		sum = 0;
	}

	double max_value = findMaxValue(neurons, size);

	double denominator = softmax_sum(max_value, neurons, size);

	for (int i = 0; i < size; i++) {
			neurons[i] = exp(neurons[i] - max_value) / denominator;
	}
	int name = findMaxIndex(neurons, size);
	return name;
}

void mode6(double pixels[]){
	int name = searchNeuronName(pixels);
	printf("%d", name);
}

double mode7(double pixels[]) {
  int name = searchNeuronName(pixels);
	return name;
}

int main() {
	int mode = 0;
	scanf("%d", &mode);

	switch (mode) {
		case 1: {
			double pixels[785];
			int count = 0;
			while (count < 785 && scanf("%lf", &pixels[count]) == 1) { 
				count++;
			}
			print_image(pixels, 28, 28);
			break;
		}

		case 2: {
			double pixels[5];
			int count = 0;
			while (count < 5 && scanf("%lf", &pixels[count]) == 1) { 
				count++;
			}
			printWeight(pixels[0], pixels[1], pixels[2]);
			break;
		}
		case 3: {
			double pixels[785];
			int count = 0;
			while (count < 785 && scanf("%lf", &pixels[count]) == 1) {
				count++;
			}
			weightLoss(pixels);
			break;
		}
		case 4: {
			double values[10];
			int count = 0;
			while (count < 10 && scanf("%lf", &values[count]) == 1) { 
				count++;
			}
			mode4(values, count);
			break;
		}
		case 5: {
			double values[10];
			int count = 0;
			while (count < 10 && scanf("%lf", &values[count]) == 1) { 
				count++;
			}
			mode5(values, count);
			break;
		}
		case 6: {
			double pixels[785];
			int count = 0;
			while (count < 785 && scanf("%lf", &pixels[count]) == 1) { 
				count++;
			}
			mode6(pixels);
			break;
		}
		case 7: {
			int K ;
			scanf("%d", &K);
			int names[K];
			double pixels[784];
			int countPixel = 0;
			int k = 0;
			while (k < K && scanf("%d", &names[k]) == 1) { 
				k++;
			}
		int countedNeurons[K];
		int success = 0;
		for(int i = 0; i < K; i++) {
			while (countPixel < 785 && scanf("%lf", &pixels[countPixel]) == 1) { 
				countPixel++;
			}
      countedNeurons[i] = searchNeuronName(pixels);

      if(countedNeurons[i] == names[i]) success++;
			countPixel = 0;
			
		}

		double percent = (100.0*success)/K;
    printf("%.2lf", percent);
		// printf("\b");
		for(int i = 0; i < K; i++) {
			printf(" %d-%d-%d", i, names[i], countedNeurons[i]);
			// if(i==K) printf("\b");
		}
			break;
		}
		default:
			break;
	}

	return 0;
}
