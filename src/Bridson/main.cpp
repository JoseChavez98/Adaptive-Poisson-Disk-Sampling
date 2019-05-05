#include <iostream>
#include <vector>
#define HEIGHT 45
#define WIDTH 45

extern int NUM_THREADS = 8;
extern int R = 1;

enum SampleStatus
{
  IDLE,
  ACTIVE,
  ACCEPTED,
  REJECTED
};

float generateRandomNumber(int, int);

#include "sample.h"

#define TRY_LIMITS 10000

void printGrid(std::pair<Sample, bool>, int);

int main()
{
  std::vector<Sample> active_list;

  float block_size = R / sqrt(2);
  int cols = WIDTH / block_size;
  int rows = HEIGHT / block_size;

  std::pair<Sample, bool> *grid;
  grid = new std::pair<Sample, bool>[cols * rows];

  for (int i = 0; i < cols * rows; i++)
  {
    grid[i].second = false;
  }

  Sample s1(0);
  std::pair<Sample, bool> SAMPLE;
  SAMPLE.first = s1;
  SAMPLE.second = true;

  int i = SAMPLE.first.getCoordinates().first / block_size;
  int j = SAMPLE.first.getCoordinates().second / block_size;
  grid[i + j * cols] = SAMPLE;
  active_list.push_back(SAMPLE.first);

  while (!active_list.empty())
  {
    bool found = false;
    int index = generateRandomNumber(0, active_list.size() - 1);
    Sample s2 = active_list[index];
    for (int loop = 0; loop < TRY_LIMITS; loop++)
    {
      int angle = generateRandomNumber(1, 360);
      int point_radius = generateRandomNumber(R, R * 2);
      float plusx = cos(angle) * point_radius;
      float plusy = sin(angle) * point_radius;

      Sample new_sample(s2.getCoordinates().first + plusx, s2.getCoordinates().second + plusy, IDLE);
      int col = new_sample.getCoordinates().first / block_size;
      int row = new_sample.getCoordinates().second / block_size;

      if (col > -1 && row > -1 && col < cols && row < rows && !grid[col + row * cols].second && new_sample.getCoordinates().first >= 0 && new_sample.getCoordinates().second >= 0)
      {
        bool switchs = true;
        for (int k = -1; k <= 1; k++)
        {
          for (int j = -1; j <= 1; j++)
          {
            if (grid[i + j * cols].second)
            {
              int position = (col + i) + (row + j) * cols;
              if (position >= 0 && position < cols * rows)
              {
                Sample neighbor = grid[position].first;
                float distance = new_sample.sampleDistance(neighbor);
                if (distance < R)
                {
                  switchs = false;
                  //break;
                }
              }
            }
          }
        }

        if (switchs)
        {
          found = true;
          std::pair<Sample, bool> new_pair;
          new_pair.first = new_sample;
          new_pair.second = true;
          grid[col + row * cols] = new_pair;
          active_list.push_back(new_sample);
        }
      }
    }
    if (!found)
    {
      active_list.erase(active_list.begin() + index);
    }
  }

  for (int i = 0; i < cols * rows; i++)
  {
    if (grid[i].second)
    {
      std::cout << grid[i].first.getCoordinates().first << " " << grid[i].first.getCoordinates().second << '\n';
    }
  }
  //printGrid(grid, cols * rows);

  return 0;
}

float generateRandomNumber(int range_init, int range_end)
{
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist6(range_init, range_end);
  return dist6(rng);
}

void printGrid(std::pair<Sample, bool> grid[], int space)
{
  for (int i = 0; i < space; i++)
  {
    if (grid[space].second)
    {
      std::cout << grid[space].first.getCoordinates().first << " " << grid[space].first.getCoordinates().second << '\n';
    }
  }
}
