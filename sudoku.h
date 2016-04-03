#include<iostream>
#include<cstdio>
#include<algorithm>
#include<ctime>
#include<cstdlib>
using namespace std;

class Sudoku
{
  public:
    Sudoku();
    Sudoku(const int init_map[]);
    void setMap(const int set_map[]);
    int getElement(int index);
    bool isCorrect();

    void giveQuestion();
    void readIn();
    void solve();
    void changeNum(int a, int b);
    void changeRow(int a, int b);
    void changeCol(int a, int b);
    void rotate(int n);
    void flip(int n);
    void transform();


    void print_out();
    void print_out_test();
    void change_function();
    void function_state();
    void change_single_row(int a, int b);
    void change_single_col(int a, int b);
    bool is_Valid();
    void transpose();
    static const int sudokuSize = 81;
    
  private:
    void sudokuSolve(int cur);
    bool checkUnity(int arr[]); //檢查1~9
    int map[sudokuSize];
    int solution_space[sudokuSize];
    int state;
    bool init;
    bool function;

};

Sudoku::Sudoku(const int init_map[])
{
  for(int i = 0; i < sudokuSize; i++)
    this->map[i] = init_map[i];
  this -> state = 0;
  this->function = false;
  this->init = true;
}

Sudoku::Sudoku()
{
  for(int i = 0; i < sudokuSize; i++)
    this->map[i] = 0;
  this->state = 0;
  this->function = false;
  this->init = true;
}


void Sudoku::setMap(const int set_map[])
{
  for(int i = 0; i < sudokuSize; i++)
    this->map[i] = set_map[i];
}

int Sudoku::getElement(int index)
{
  return this->map[index];

}


bool Sudoku::isCorrect()
{
    int *ptr = this->map;
    int temp[9];
    int temp_row[9], temp_col[9];
    int i, j, k, l, index;
    bool result = true;
   
 
    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            for(k = 0; k < 3; k++)
            {
                for(l = 0; l < 3; l++)
                {
                    temp[3*k + l] = this->map[3*3*3*i + 3*3*k + 3*j + l];
                }
            }
            sort(temp, temp+9);
            for(index = 0; index < 9; index++)
                if(temp[index] != index + 1)return false;
        }
    }
    
    for(i = 0; i < 9; i++)
    {
        for(j = 0; j < 9; j++)
        {
            temp_row[j] = ptr[9*i+j];
            temp_col[j] = ptr[9*j+i];
        }
        sort(temp_row, temp_row+9);
        sort(temp_col, temp_col+9);
        for(j = 0; j < 9; j++)
            if(temp_row[j] != j +1 || temp_col[j] != j+1)return false;
    }
    
    return true;
}


bool Sudoku::is_Valid()
{
    int *ptr = this->map;
    int temp[9];
    int count[10];
    int temp_row[9], temp_col[9];
    int i, j, k, l, index;
    bool result = true;
    

    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            for(k = 0; k < 3; k++)
            {
                for(l = 0; l < 3; l++)
                {
                    temp[3*k + l] = this->map[3*3*3*i + 3*3*k + 3*j + l];
                }
            }
            for(index = 0; index < 10; index++)count[index] = 0;
            for(index = 0; index < 9; index++)count[temp[index]]++;
            for(index = 1; index < 10; index++)if(count[index] > 1)return false;
        }
    }

    
    
    for(i = 0; i < 9; i++)
    {
        for(j = 0; j < 9; j++)
        {
            temp_row[j] = ptr[9*i+j];
            temp_col[j] = ptr[9*j+i];
        }
        for(index = 0; index < 10; index++)count[index] = 0;
        for(index = 0; index < 9; index++)count[temp_row[index]]++;
        for(index = 1; index < 10; index++)if(count[index] > 1)return false;

        for(index = 0; index < 10; index++)count[index] = 0;
        for(index = 0; index < 9; index++)count[temp_col[index]]++;
        for(index = 1; index < 10; index++)if(count[index] > 1)return false;

        /*
        sort(temp_row, temp_row+9);
        sort(temp_col, temp_col+9);
        for(j = 0; j < 9; j++)
            if(temp_row[j] != j +1 || temp_col[j] != j+1)return false;
       */
    }
    
    return true;
}





bool Sudoku::checkUnity(int arr[])
{
  int temp[9];
  for(int i = 0; i < 9; i++)
    temp[i] = arr[i];
  sort(temp, temp+9);
  
  for(int i = 0; i < 9; i++)
    if(temp[i] != i+1)return false;

  return true;
}



void Sudoku::sudokuSolve(int cur)
{
  if(cur == 81)
  {
    if(this->isCorrect())
    {
      if(!function)
      {
        for(int i = 0; i < 81; i++)
          this->solution_space[i] = this->map[i];
        this->state += 1;
      }
      else if(function)this->print_out();
    }
  }
  else if(this->map[cur])this->sudokuSolve(cur+1);
  else
  {
    bool usable[10];
    int pos[4];
    int cur_temp = cur;
    for(int i = 0; i < 10; i++)usable[i] = true;
    for(int i = 0; i < 4; i++)
    {
      pos[4-i-1] = cur_temp % 3;
      cur_temp /= 3;
    }


    int row_now = 3*pos[0] + pos[1];
    int col_now = 3*pos[2] + pos[3];
    
    for(int i = 0; i < 9; i++)
    {
      if(this->map[9*row_now + i])usable[this->map[9*row_now + i]] = false;
      if(this->map[9*i + col_now])usable[this->map[9*i + col_now]] = false;
    }

    for(int k = 0; k < 3; k++)
      for(int l = 0; l < 3; l++)
        if(this->map[3*3*3*pos[0] + 3*3*k + 3*pos[2] + l])
          usable[this->map[3*3*3*pos[0] + 3*3*k + 3*pos[2] + l]] = false;

    for(int i = 1; i < 10; i++)
    {
      if(usable[i])
      {
        this->map[cur] = i;
        usable[i] = false;
//        this->print_out(); 
        this->sudokuSolve(cur + 1);
        this->map[cur] = 0;
      }
      else continue;
    }

  }


}

void Sudoku::solve()
{
  if(this->is_Valid() == false)
  {
      printf("0\n");
      return;
  }
  this->sudokuSolve(0);
  if(function)
  {
    if(this->state == 0)printf("No sulution.\n");
    else if(this->state == 1)printf("There is 1 solution.\n");
    else printf("There are %d solutions.\n", this->state);
  }
  else if(!function)
  {
    if(this->state == 0)printf("0\n");
    else if(this -> state == 1)
    {
      printf("1\n");
      for(int i = 0; i < 9; i++)
      {
        for(int j = 0; j < 9; j++)
          printf("%d  ", solution_space[9*i + j]);
        printf("\n\n");
      }
    }
    else printf("2\n");
  }
}


void Sudoku::readIn()
{
  int temp[81];
  for(int i = 0; i < 81; i++)scanf("%d", &temp[i]);
  for(int i = 0; i < 81; i++){(this->map[i]) = temp[i];}
}

void Sudoku::print_out()
{
  for(int i = 0; i < 9; i++)
  {
    for(int j = 0; j < 9; j++)
      printf("%d  ", this->map[9*i + j]);
    printf("\n\n");
  }
  printf("\n");

}

void Sudoku::print_out_test()
{
  int i = 1; int j = 1;
//   for(int i = 0; i < 3; i++)
//    for(int j = 0; j < 3; j++)
      for(int k = 0; k < 3; k++)
        for(int l = 0; l < 3; l++)
          printf("%d", this->map[3*3*3*i + 3*3*k + 3*j + l]);
}

void Sudoku::change_function()
{
  this->function = !(this->function);
}

void Sudoku::function_state()
{
  if(this->function)printf("Enumeration mode:\n\n");
  else printf("Homework mode:\n\n");
}



void Sudoku::changeNum(int a, int b)
{
  if(a <=9 && a >=1 && b<=9 && b >= 1)
  {
    for(int i = 0; i < 81; i++)
    {
      if(this->map[i] == a)this->map[i] = b;
      else if(this->map[i] == b)this->map[i] = a;
    }
  }

}

void Sudoku::change_single_row(int a, int b)
{
  if(a >= 0 && a <9 && b >=0 && b <9)
  {
    int temp;
    for(int j = 0; j < 9; j++)
    {
      temp = this->map[9*a + j];
      this->map[9*a + j] = this->map[9*b+j];
      this->map[9*b+j] = temp;
    }
  }
}

void Sudoku::changeRow(int a, int b)
{
  if(a >= 0 && a <=2 && b >=0 && b <=2)
  {
    for(int i = 0; i < 3; i++)
      this->change_single_row(3*a+i, 3*b+i);
  }
}


void Sudoku::change_single_col(int a, int b)
{
  if(a >= 0 && a <9 && b >=0 && b < 9)
  {
    int temp;
    for(int i = 0; i < 9; i++)
    {
      temp = this->map[9*i + a];
      this->map[9*i+a] = this->map[9*i+b];
      this->map[9*i+b] = temp;
    }
  }
}

void Sudoku::changeCol(int a, int b)
{
  if(a >= 0 && a <= 2 && b >=0 && b <= 2)
  {
    for(int i = 0; i < 3; i++)
      this->change_single_col(3*a+i, 3*b+i);
  }
}

void Sudoku::flip(int n)
{
  int temp;
  if(n)
  {
    for(int i = 0; i < 9; i++)
    {
      for(int j = 0; j < 4; j++)
      {
        temp = this->map[9*i+j];
        this->map[9*i+j] = this->map[9*i + (9-j-1)];
        this->map[9*i + (9-j-1)] = temp;
      }
    }
  }
  else
  {
    for(int i = 0; i < 4; i++)
    {
      for(int j = 0; j < 9; j++)
      {
        temp = this->map[9*i+j];
        this->map[9*i+j] = this->map[9*(9-i-1) + j];
        this->map[9*(9-i-1)+j] = temp;
      }
    }
  }
}


void Sudoku::transpose()
{
  int temp;
  for(int i = 0; i < 9; i++)
  {
    for(int j = i; j < 9; j++)
    {
      temp = this->map[9*i+j];
      this->map[9*i+j] = this->map[9*j+i];
      this->map[9*j+i] = temp;
    }
  }
}

void Sudoku::rotate(int n)
{
  if(n % 4 == 0)return;
  else if(n % 4 == 1)
  {
    this->transpose();
    this->flip(1);
  }
  else {this->rotate(1);this->rotate((n%4)-1);}
}

void Sudoku::giveQuestion()
{
  int pre[9][9] = {{0, 0, 0, 0, 0, 0, 0, 0, 0}, {5, 0, 8, 0, 0, 0, 0, 0, 0},{0, 0, 0, 2, 0, 0, 0, 0, 1}, {0, 0, 0, 5, 0, 0, 0, 9, 0}, {0, 0, 0, 0, 0, 1, 0, 0, 6},{9, 0, 6, 0, 0, 0, 4, 0, 0},{0, 3, 1, 0, 0, 6, 0, 0, 7},{0, 0, 0, 7, 2, 0, 8, 0, 0},{0, 8, 2, 0, 9, 0, 0, 0, 3}};
  
  if(!(this->init))
  {
    int *ptr = &(pre[0][0]);
    for(int i = 0; i < 9; i++)
    {
      for(int j = 0; j < 9; j++)
        printf("%d　", ptr[9*i+j]);
      printf("\n\n");
    }
  }
  else
  {
    this->transform();
  }

}

void Sudoku::transform()
{
  this->transpose();
  srand(time(NULL));
  this->rotate(rand());
  this->print_out();
}
