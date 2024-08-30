#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
unsigned long long int User()  { return user_; }
    unsigned long long int Nice()  { return nice_; }
    unsigned long long int System()  { return system_; }
    unsigned long long int Idle()  { return idle_; }
    unsigned long long int IOwait()  { return iowait_; }
    unsigned long long int IRQ()  { return irq_; }
    unsigned long long int SoftIRQ()  { return softirq_; }
    unsigned long long int Steal()  { return steal_; }
    unsigned long long int TotalTime()  { return total_time_; }


    //setters
    void User(unsigned long long int value) { user_ = value; }
    void Nice(unsigned long long int value) { nice_ = value; }
    void System(unsigned long long int value) { system_ = value; }
    void Idle(unsigned long long int value) { idle_ = value; }
    void IOwait(unsigned long long int value) { iowait_ = value; }
    void IRQ(unsigned long long int value) { irq_ = value; }
    void SoftIRQ(unsigned long long int value) { softirq_ = value; }
    void Steal(unsigned long long int value) { steal_ = value; }
    void TotalTime(unsigned long long int value) { total_time_ = value; }
  // TODO: Declare any necessary private members
 private:
     unsigned long long int user_;
    unsigned long long int nice_;
    unsigned long long int system_;
    unsigned long long int idle_;
    unsigned long long int iowait_;
    unsigned long long int irq_;
    unsigned long long int softirq_;
    unsigned long long int steal_;
    unsigned long long int total_time_; 
};

#endif