//
// Created by DOC,JAOX,XROK on 01/05/19.
//

#ifndef ADAPTIVE_POISSON_DISK_SAMPLING_SAMPLE_H
#define ADAPTIVE_POISSON_DISK_SAMPLING_SAMPLE_H

#include <utility>
#include <random>
#include <limits>

enum SampleStatus{ IDLE, ACTIVE, ACCEPTED, REJECTED };



class Sample{

private:
    SampleStatus status;
    double priority;
    float pos[3];
    int face_id;

 public:
  Sample(){
    generate_priority();
  }

  double generate_priority(){
    std::random_device rd;
    std::mt19937_64 eng(rd());

    std::uniform_int_distribution<unsigned long long int> distr;

    unsigned long long int rand = distr(eng);
    this->priority= ((rand*NUM_THREADS) + 1)/
        (std::numeric_limits<unsigned long long int>::max()/NUM_THREADS );
  }

  double GetPriority() const {
    return priority;
  }

};

#endif //ADAPTIVE_POISSON_DISK_SAMPLING_SAMPLE_H
