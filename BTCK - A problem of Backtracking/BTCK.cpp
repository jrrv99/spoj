#include <iostream>

using namespace std;

int *ReadSequenceFromInput(int size)
{
  int *sequence = new int[size]; // dynamic array
  for (int j = 0; j < size; j++)
  {
    cin >> sequence[j]; // read the number
    cin.ignore(1);      // ignore the spaces
  }

  return sequence; // return the address
}

bool already_in(int arr[], int target, int limit)
{
  for (int i = 0; i < limit; i++) // Look only at positions already assigned
  {
    if (arr[i] == target)
      return true; // if found it
  }
  return false;
}

bool solve_permutation(int permutation[], int sequence[], int sum, int position, int K)
{
  if (sum >= K && position < 10) // if the sum is sum >= K before assigning all positions
    return false;

  if (position == 10) // base condition: when all positions have been assigned
    return sum == K;

  // position its the position in permutation, i its an ai
  for (int i = 0; i < 10; i++)
  {
    if (already_in(permutation, i, position))
      continue; // if repeated, ignore

    permutation[position] = i; // assign number in position
    if (solve_permutation(
            permutation,                                      // pass perm with updated value at position
            sequence,                                         // drop the sequence
            sum + permutation[position] * sequence[position], // update sum
            position + 1,                                     // increment position
            K))
      return true;

    permutation[position] = -1; // backtrack and discard path
  }

  return false;
}

void print_permutation(int sequence[])
{
  for (int i = 0; i < 10; i++)
  {
    cout << sequence[i] << " ";
  }
  cout << '\n';
}

void init_array(int arr[], int size, int value)
{
  for (int i = 0; i < size; i++)
  {
    arr[i] = value;
  }
}

int main()
{
  const int SEQUENCE_LENGTH = 10;
  int numTests, i; // number of test cases, K
  int permutation[SEQUENCE_LENGTH];

  cin >> numTests;                       // Read number of test cases
  int **sequences = new int *[numTests]; // dynamic array of arrays with pointers
  int *Ks = new int[numTests];           // dynamic array with pointer

  for (i = 0; i < numTests; i++)
  {
    sequences[i] = ReadSequenceFromInput(SEQUENCE_LENGTH); //  Read sequence and push to i-th position
    cin >> Ks[i];                                          // Read K and push to i-th position
  }

  // solution steps
  for (i = 0; i < numTests; i++)
  {
    init_array(permutation, SEQUENCE_LENGTH, -1);                  // init or reset permutation array to -1 in every position
    if (solve_permutation(permutation, sequences[i], 0, 0, Ks[i])) // do backtracking to find the solve and put it in permutation
    {
      print_permutation(permutation);
    }
    else
    {
      cout << -1 << '\n';
    }
    delete[] sequences[i]; // free memory space
  }

  delete[] sequences; // free memory space
  return EXIT_SUCCESS;
}
