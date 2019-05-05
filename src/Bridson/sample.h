//
// Created by jose on 01/05/19.
//

#ifndef ADAPTIVE_POISSON_DISK_SAMPLING_SAMPLE_H
#define ADAPTIVE_POISSON_DISK_SAMPLING_SAMPLE_H

#include <utility>
#include <random>
#include <limits>

class Sample
{

private:
  SampleStatus status;
  double priority;
  std::pair<float, float> coordinates;

public:
  Sample() = default;

  Sample(float x, float y, SampleStatus status)
  {
    coordinates.first = x;
    coordinates.second = y;
    this->status = status;
  }

  Sample(int id)
  {
    //generatePriority();
    coordinates.first = generateRandomNumber(0, WIDTH);
    coordinates.second = generateRandomNumber(0, HEIGHT);
    status = IDLE;
  }

  double generatePriority()
  {
    std::random_device rd;
    std::mt19937_64 eng(rd());

    std::uniform_int_distribution<unsigned long long int> distr;

    unsigned long long int rand = distr(eng);
    this->priority = ((rand * NUM_THREADS) + 1) /
                     (std::numeric_limits<unsigned long long int>::max() / NUM_THREADS);
  }

  SampleStatus getStatus() const
  {
    return status;
  }
  double getPriority() const
  {
    return priority;
  }
  std::pair<float, float> getCoordinates() const
  {
    return coordinates;
  }
  float sampleDistance(Sample a)
  {
    return sqrt(pow((a.getCoordinates().first - this->coordinates.first), 2) + pow((a.getCoordinates().second - this->coordinates.second), 2));
  }
  void print()
  {
    std::cout << "prio: " << priority << " "
              << "coordinates: " << coordinates.first << " " << coordinates.second << '\n';
  }
};

#endif //ADAPTIVE_POISSON_DISK_SAMPLING_SAMPLE_H
